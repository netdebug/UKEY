#include "GetCertInfoRequestHandler.h"
#include "RequestHandleException.h"
#include "Reach/Data/Session.h"
#include "Utility.h"
#include "Poco/Crypto/X509Certificate.h"
#include "Poco/String.h"
#include "Poco/DateTimeFormatter.h"
#include "Poco/Timezone.h"
#include "Poco/RegularExpression.h"

using namespace Reach;
using Reach::Data::Session;
using Poco::Crypto::X509Certificate;
using Poco::format;
using Poco::DateTimeFormatter;
using Poco::Timezone;
using Poco::RegularExpression;
using Poco::LocalDateTime;
using Poco::DateTimeFormat;

GetCertInfo::GetCertInfo(const std::string& base64, int type)
	:_base64(base64), _type(type)
{
}

void GetCertInfo::run()
{
	/// FJCA SOF all use this
	//Session session("SOF", "REST");
	Session session(Utility::getSession());

	std::string info = session.getCertInfo(_base64, _type);

	add("info", info);
}


void parseFromX509(const std::string& cer)
{
	//1 RSA 2 SM2
	std::string PEM;
	PEM.append("-----BEGIN CERTIFICATE-----\n");
	PEM.append(Utility::cat("\n", 64, cer));
	PEM.append("-----END CERTIFICATE-----\n");
	std::istringstream certStream(PEM);
	X509Certificate x509(certStream);
	std::ostringstream ostr;
	x509.print(ostr);
	long version = x509.version();
	std::string SN = x509.serialNumber();
	std::string issuer = x509.issuerName();
	std::string owner = x509.subjectName();

	std::string validFrom = DateTimeFormatter::format(LocalDateTime(x509.validFrom()), DateTimeFormat::SORTABLE_FORMAT);
	std::string expiresOn = DateTimeFormatter::format(LocalDateTime(x509.expiresOn()), DateTimeFormat::SORTABLE_FORMAT);
	std::string validLife = format("From %s to %s", validFrom, expiresOn);

	std::string issuer_CN = x509.issuerName(X509Certificate::NID_COMMON_NAME);
	std::string issuer_O = x509.issuerName(X509Certificate::NID_ORGANIZATION_NAME);
	std::string issuer_OU = x509.issuerName(X509Certificate::NID_ORGANIZATION_UNIT_NAME);

	std::string owner_CN = x509.subjectName(X509Certificate::NID_COMMON_NAME);
	std::string owner_O = x509.subjectName(X509Certificate::NID_ORGANIZATION_NAME);
	std::string owner_OU = x509.subjectName(X509Certificate::NID_ORGANIZATION_UNIT_NAME);
	std::string owner_EMail = x509.subjectName(X509Certificate::NID_PKCS9_EMAIL_ADDRESS);
	//ostr_item = session.getCertInfo(_base64, _type);

	std::string person_id = Utility::GetCertInfoByOid(cer, "1.2.156.10260.4.1.1");
}
/*
统一组织机构代码：
SOF CFCA     1.2.156.10260.4.1.1，最后一位为N的表示组织机构代码 
SOF BJCA      1.2.156.10260.4.1.4
SOF NMCA	 1.2.86.11.7.3
FJCA      先1.2.156.10260.4.1.3，没有再1.2.156.10260.4.1.4
*/

std::string GetCertOwnerID(const std::string& base64)
{
	std::string item;
	/*std::string pattern("(\\d+[A-z]?)");
	std::string special_oid("1.2.156.10260.4.1.1");
	item = Utility::GetCertInfoByOid(base64, special_oid);
	if (item.empty()) {

		item = SOF_GetCertInfo(base64, SGD_CERT_SUBJECT_CN);
		pattern = format("@%s@", pattern);
	}

	item = toLegelID(item, pattern);
	/// erase 0 if is id card
	if (!item.empty() && item.at(0) == '0')
		item = item.replace(0, 1, "");*/

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