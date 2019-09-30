#pragma once

#include "UDevice.h"
#include "SoFProvider.h"
#include "SOFErrorCode.h"
#include "Command.h"
#include "GMCrypto.h"
#include "RESTfulRequestHandler.h"
#include "RequestHandleException.h"
#include "Poco/Util/Application.h"
#include "Poco/RegularExpression.h"
#include "Poco/Timezone.h"
#include "Poco/Debugger.h"
#include "Poco/String.h"
#include "Poco/NumberParser.h"
#include "Poco/Crypto/X509Certificate.h"
#include "Poco/SharedPtr.h"
#include "Poco/String.h"
#include <cassert>

namespace Reach {

	using Poco::Util::Application;
	using Poco::RegularExpression;
	using Poco::Timezone;
	using Poco::DateTime;
	using Poco::DateTimeFormat;
	using Poco::DateTimeParser;
	using Poco::DateTimeFormatter;
	using Poco::LocalDateTime;
	using Poco::Debugger;
	using Poco::format;
	using Poco::Crypto::X509Certificate;
	using Poco::NumberParser;
	///RS_GetCertInfo
	class GetCertInfo : public Command
	{
	public:
		GetCertInfo(const std::string& base64, int type)
			:_cer(base64), _type(type)
		{
			std::string PEM;
			std::istringstream istr(_cer);
			PEM.append("-----BEGIN CERTIFICATE-----\n");
			PEM.append(cat("\n", 64, _cer));
			PEM.append("-----END CERTIFICATE-----\n");
			std::istringstream certStream(PEM);
			x509ptr = new X509Certificate(certStream);

			std::string text("/CN=\\xE9\\x87\\x91\\xE8\\xB4\\xA2\\xE6\\xB5\\x8B\\xE8\\xAF\\x95KEY32");
			std::string text1("/CN=\\xE9\\x87\\x91KEY32");
			decode_utf8(text);
		}

		void run()
		{
			switch (_type) {
			case 1:
				_item = Poco::format("V%ld", x509ptr->version());
				break;
			case 2:
				_item = x509ptr->serialNumber();
				break;
			case 5:
				extract(x509ptr->issuerName());break;
			case 6:
				x509_validFrom_expiresOn();break;
			case 7:
				extract(x509ptr->subjectName());break;		
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
			case 53:
				personal();break;
			case 54:
				enterprise();break;
			default:
				break;
			}

			add("info", _item);
		}
	protected:
		void personal()
		{
			_item = GetCertOwnerID(_cer);
			if(_item.empty())extract(x509ptr->subjectName(), "title");
		}
		void enterprise()
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
							str = Poco::replace(str, "N","");
						else
							break;
					}
					
					if (eid[i] == "1.2.86.11.7.3")
						str = Poco::replace(str,"\x13\x12", "");

					_item = str; break;
				}
			}

			if(_item.empty())extract(x509ptr->subjectName(), "title");
			
		}
		void decode_utf8(const std::string& text)
		{
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
					if (NumberParser::tryParseHex(str, value))
						T.append((char)value);
					
					offset += mtch.length;
				}

				std::string otc(T.begin(),T.size());

				Debugger::message(format("%s,", otc));
			}
			catch (Poco::RegularExpressionException& e)
			{

			}
		}
		void extract(const std::string& text)
		{
			std::string pattern("/(\\w+)=(\\w+|.+)");
			std::string::size_type offset = 0;
			int options = 0;

			try
			{		
				RegularExpression re(pattern, options);
				RegularExpression::Match mtch = { 0,0 };
				
				while (re.match(text, offset, mtch) > 0)
				{
					std::string str;
					re.extract(text, mtch.offset, str);
					_item += str;
					offset += mtch.length;
					_item += "\r\n";
				}
			}
			catch (Poco::RegularExpressionException& e)
			{
				_item.clear();
			}
			
			Debugger::message(format("%s", _item));
		}
		void extract(const std::string& text, const std::string& tag)
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
			catch (Poco::RegularExpressionException& e)
			{
				_item.clear();
			}
		}

		void x509_validFrom_expiresOn()
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

		std::string cat(const std::string& delim, std::size_t pos, const std::string& str)
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
		
		std::string toLocalTime(const std::string& time)
		{
			int options = 0;
			std::string pattern("^([0-9]\\d{1})([0-9]\\d{1})([0-9]\\d{1})([0-9]\\d{1})([0-9]\\d{1})([0-9]\\d{1})Z");
			RegularExpression re(pattern, options);
			RegularExpression::Match mtch;
			if (!re.match(time, mtch))
				throw Poco::RegularExpressionException(100);
			///
			/// Match 1:	210314155959	     0	    12
			/// Group 1:	2103	     0	     4
			/// Group 2:	14	     4	     2
			/// Group 3:	15	     6	     2
			/// Group 4:	59	     8	     2
			/// Group 5:	59	    10	     2
			///
			std::vector<std::string> tags;
			re.split(time, tags, options);

			std::string prefix;
			int oct = std::stod(tags[1]);
			oct > 49 ? prefix = "19" : prefix = "20";
			std::string fmt = format("%s%s-%s-%s %s:%s", prefix, tags[1], tags[2], tags[3], tags[4], tags[5], tags[6]);

			Debugger::message(format("Timezone utcOffset: %d, tzd:: % d, name : %s", Timezone::utcOffset(), Timezone::tzd(), Timezone::name()));
			Debugger::message(time);
			int tzd = Timezone::tzd();
			DateTime dt = DateTimeParser::parse(DateTimeFormat::SORTABLE_FORMAT, fmt, tzd);
			LocalDateTime lt(dt);
			std::string localtime = DateTimeFormatter::format(lt, DateTimeFormat::SORTABLE_FORMAT);
			Debugger::message(localtime);
			return localtime;
		}
		std::string GetCertOwnerID(const std::string& base64)
		{
			std::string item;
			std::string pattern("(\\d+[A-z]?)");
			std::string special_oid("1.2.156.10260.4.1.1");
			item = SOF_GetCertInfoByOid(base64, special_oid);
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

		std::string toLegelID(const std::string& text, const std::string& pattern)
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
		///base64 \/转义字符
	private:
		std::string _item;
		std::string _cer;
		int _type;
		Poco::SharedPtr<Poco::Crypto::X509Certificate> x509ptr;
	};

	class GetCertInfoRequestHandler : public RESTfulRequestHandler
	{
	public:
		void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
		{
			poco_information_f1(Application::instance().logger(), "Request from %s", request.clientAddress().toString());

			RESTfulRequestHandler::handleCORS(request, response);

			std::string base64, type;

			HTMLForm form(request, request.stream());
			if (request.getMethod() == "GET")
				form.read(request.getURI());

			base64 = form.get("certBase64", "");
			type = form.get("type", "");

			GetCertInfo command(base64, Var(type));
			command.execute();

			return response.sendBuffer(command().data(), command().length());
		}
	};
}