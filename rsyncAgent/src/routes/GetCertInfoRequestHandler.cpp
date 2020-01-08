#include "GetCertInfoRequestHandler.h"
#include "RequestHandleException.h"
#include "Reach/Data/Session.h"
#include "../Utility.h"
#include "Poco/Crypto/X509Certificate.h"
#include "Poco/String.h"
#include "Poco/DateTimeFormatter.h"
#include "Poco/Timezone.h"
#include "Poco/RegularExpression.h"

#include <cassert>
#include "Poco/HexBinaryDecoder.h"

using namespace Reach;
using Reach::Data::Session;
using Poco::Crypto::X509Certificate;
using Poco::format;
using Poco::DateTimeFormatter;
using Poco::Timezone;
using Poco::RegularExpression;
using Poco::LocalDateTime;
using Poco::DateTimeFormat;
using Poco::Debugger;
using Poco::NumberParser;
using Poco::DateTime;
using Poco::DateTimeParser;
using Poco::HexBinaryDecoder;

#define SGD_CERT_SUBJECT_CN 0x00000031
extern std::string SOF_GetCertInfoByOid(std::string Base64EncodeCert, std::string oid);
extern std::string SOF_GetCertInfo(std::string Base64EncodeCert, short Type);

GetCertInfo::GetCertInfo(const std::string& base64, int type)
	:_cer(base64), _type(type)
{
	
}

void GetCertInfo::load()
{
	try
	{
		std::string PEM;
		std::istringstream istr(_cer);
		PEM.append("-----BEGIN CERTIFICATE-----\n");
		PEM.append(cat("\n", 64, _cer));
		PEM.append("-----END CERTIFICATE-----\n");
		std::istringstream certStream(PEM);
		x509ptr = new X509Certificate(certStream);
	}
	catch (Poco::IOException& e)
	{
		throw RequestHandleException(e.message(), RAR_ERRORBASE64);
	}
}
/// GBK中文乱码

void GetCertInfo::parse()
{
	switch (_type) {
	case 1:
		_item = Poco::format("V%ld", x509ptr->version());
		break;
	case 2:
		_item = x509ptr->serialNumber();
		break;
	case 5:
	case 7:
	case 33:
	case 34:
	case 35:
	case 49:
	case 50:
	case 51:
	case 52:
		//extract(x509ptr->issuerName()); break;
		_item = SOF_GetCertInfo(_cer, _type); break;
	case 6:
		x509_validFrom_expiresOn(); break;
	/*case 7:
		extract(x509ptr->subjectName()); break;
	case 33:
		_item = x509ptr->issuerName(X509Certificate::NID_COMMON_NAME);
		break;
	case 34:
		_item = x509ptr->issuerName(X509Certificate::NID_ORGANIZATION_NAME);
		break;
	case 35:
		_item = x509ptr->issuerName(X509Certificate::NID_ORGANIZATION_UNIT_NAME);
		break;
	case 49:
		_item = x509ptr->subjectName(X509Certificate::NID_COMMON_NAME);
		break;
	case 50:
		_item = x509ptr->subjectName(X509Certificate::NID_ORGANIZATION_NAME);
		break;
	case 51:
		_item = x509ptr->subjectName(X509Certificate::NID_ORGANIZATION_UNIT_NAME);
		break;
	case 52:
		_item = x509ptr->subjectName(X509Certificate::NID_PKCS9_EMAIL_ADDRESS);
		break;
		*/
	case 53:
		personal(); break;
	case 54:
		enterprise(); break;
	case 300:
		/*调用福建ca keysn整串字符包含@*/
		keysn();
		break;
	default:
		throw RequestHandleException("InvalidArgumentException", RAR_ERRORCERTTYPE);
	}

}

void GetCertInfo::run()
{
	load();
	parse();

	add("info", _item);
}

#include "Reach/Data/FJCA/FJCA_FUN_GT_DLL.h"

void GetCertInfo::keysn()
{
	Application& app = Application::instance();

	char num[40] = { 0 };
	if (FJCA_GetCertOID(const_cast<char*>(_cer.c_str()), num, 40))
		_item = num;
	
	poco_information_f1(app.logger(), "%s", _item);
}

void GetCertInfo::personal()
{
	_item = GetCertOwnerID(_cer);
	if (_item.empty())extract(x509ptr->subjectName(), "title");
}

void GetCertInfo::enterprise()
{
	std::vector<std::string> eid;
	eid.push_back("1.2.156.10260.4.1.3");
	eid.push_back("1.2.156.10260.4.1.4");
	eid.push_back("1.2.86.11.7.3");
	eid.push_back("1.2.156.10260.4.1.1");

	for (int i = 0; i < eid.size(); ++i) {
		std::string str;
		str = SOF_GetCertInfoByOid(_cer, eid[i]);
		if (!str.empty())
		{
			if (eid[i] == "1.2.156.10260.4.1.1")
			{
				size_t pos = str.find_last_of("N");
				if (pos != std::string::npos)
					str = Poco::replace(str, "N", "");
				else
					break;
			}

			if (eid[i] == "1.2.86.11.7.3")
				str = Poco::replace(str, "\x13\x12", "");

			if (eid[i] == "1.2.156.10260.4.1.4") {
				str = Poco::replace(str, "\f\x12", "");
				str = Poco::replace(str, "\f\n", "");
			}

			_item = str; break;
		}
	}

	if (_item.empty())extract(x509ptr->subjectName(), "title");

}
void GetCertInfo::decode_utf8(const std::string& text)
{
	Application& app = Application::instance();

	std::string pattern("(\\\\x[0-F]{2})");

	std::string::size_type offset = 0;
	int options = 0;

	try
	{
		RegularExpression re(pattern, options);
		RegularExpression::Match mtch = { 0,0 };

		Poco::Buffer<char> T(64);
		while (re.match(text, offset, mtch) > 0)
		{
			std::string str;
			unsigned int value = 0;
			re.extract(text, mtch.offset, str);
			str = Poco::replace(str, "\\x", "");
			if (Poco::NumberParser::tryParseHex(str, value))
				T.append((char)value);

			offset += mtch.length;
		}

		std::string otc(T.begin(), T.size());

		Debugger::message(format("%s,", otc));
	}
	catch (Poco::RegularExpressionException& e)
	{
		poco_information_f1(app.logger(), "%s", e.message());
	}
}
/*
void GetCertInfo::extract(const std::string& text)
{
	std::string st = text;
	if (st.find("\\x") == std::string::npos)
	{
		_item = st;
		return;
	}
	;
	for (int idx = 0; idx < st.size();)
	{
		if (st[idx] == '\\' && st[idx + 1] == 'x')//占用4字节
		{
			idx += 4;
		}
		else {
			char v = st[idx];
			char c[3] = {};
			std::sprintf(c, "%02x", v);
			st.replace(idx, 1, c);
			idx +=2;
		}
	}
	st = Poco::replace(st, "\\x", "");
	std::istringstream istr(st);
	HexBinaryDecoder decoder(istr);
	std::string s;
	decoder >> s;
	_item += s;

	Debugger::message(format("%s", _item));
}
*/
void GetCertInfo::extract(const std::string& text, const std::string& tag)
{
	std::string pattern("/(\\w+)=(\\w+|.+)");
	int options = 0;
	std::string::size_type offset = 0;

	try
	{
		RegularExpression re(pattern, options);
		RegularExpression::Match mtch = { 0,0 };

		while (re.match(text, offset, mtch) > 0)
		{
			std::vector<std::string> strings;
			re.split(text, mtch.offset, strings);
			if (tag == strings[1]) {
				_item += strings[2]; break;
			}
			offset += mtch.length;
		}
	}
	catch (Poco::RegularExpressionException&)
	{
		_item.clear();
	}
}

void GetCertInfo::x509_validFrom_expiresOn()
{
	Poco::DateTime from = x509ptr->validFrom();
	Poco::DateTime expires = x509ptr->expiresOn();

	std::string timestamp = Poco::format("%s - %s",
		DateTimeFormatter::format(
			LocalDateTime(from),
			DateTimeFormat::SORTABLE_FORMAT),
		DateTimeFormatter::format(
			LocalDateTime(expires),
			DateTimeFormat::SORTABLE_FORMAT));

	_item = timestamp;
}

std::string GetCertInfo::cat(const std::string& delim, std::size_t pos, const std::string& str)
{
	assert(pos < str.length());

	std::string result;

	for (int i = 0; i < str.length(); i++)
	{
		result.push_back(str[i]);
		if (i > 0 && i % pos == 0) result.append(delim);
	}
	result.append(delim);
	return result;
}

std::string GetCertInfo::GetCertOwnerID(const std::string& base64)
{
	std::string item;
	std::string pattern("(\\d+[A-z]?)");
	std::vector<std::string> special_oid;
	special_oid.push_back("1.2.156.10260.4.1.1");
	special_oid.push_back("1.2.86.11.7.1");

	for (auto oid : special_oid) {
		item = SOF_GetCertInfoByOid(base64, oid);
		if (!item.empty()) {
			if (oid == "1.2.86.11.7.1")
				pattern = "\\x31[\\xA0\\x00-\\x20]+?(\\d+[A-z]?)";
			break;
		}
	}

	if (item.empty()) {
		item = SOF_GetCertInfo(base64, SGD_CERT_SUBJECT_CN);
		pattern = format("@%s@", pattern);
	}

	item = toLegelID(item, pattern);
	/// erase 0 if is id card
	if (!item.empty() && item.at(0) == '0')
		item = item.replace(0, 1, "");

	return item;
}


std::string GetCertInfo::toLegelID(const std::string& text, const std::string& pattern)
{

	/// SGD_CERT_SUBJECT_CN identify card (330602197108300018)
	/// CN = 041@0330602197108300018@测试个人一@00000001
	/// 十八位：^[1-9]\d{5}(18|19|([23]\d))\d{2}((0[1-9])|(10|11|12))(([0-2][1-9])|10|20|30|31)\d{3}[0-9Xx]$
	/// 十五位：^[1-9]\d{5}\d{2}((0[1-9])|(10|11|12))(([0-2][1-9])|10|20|30|31)\d{2}[0-9Xx]$
	///RegularExpression pattern("@(\\d+)@");
	int options = 0;

	std::string id;

	try {
		RegularExpression re(pattern, options);
		RegularExpression::Match mtch;

		if (!re.match(text, mtch))
			throw Poco::LogicException("RS_KeyDecryptData uid Exception!", 0x40);

		std::vector<std::string> tags;
		re.split(text, tags, options);
		id = tags[1];
	}
	catch (Poco::Exception&)
	{

	}

	return id;
}