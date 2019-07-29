#pragma once

#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTMLForm.h"
#include "Poco/Net/NameValueCollection.h"
#include "Poco/Util/Application.h"
#include "UDevice.h"
#include "JSONStringify.h"
#include "GMCrypto.h"
#include "SoFProvider.h"
#include "Poco/RegularExpression.h"
#include "Poco/Timezone.h"
#include "Poco/Debugger.h"
#include "Poco/String.h"

namespace Reach {

	using Poco::Net::HTTPRequestHandler;
	using Poco::Net::HTTPServerRequest;
	using Poco::Net::HTTPServerResponse;
	using Poco::RegularExpression;
	using Poco::Net::HTMLForm;
	using Poco::Net::NameValueCollection;
	using Poco::Util::Application;
	using Reach::UDevice;
	using Reach::JSONStringify;
	using Poco::Timezone;
	using Poco::DateTime;
	using Poco::DateTimeFormat;
	using Poco::DateTimeParser;
	using Poco::DateTimeFormatter;
	using Poco::Debugger;
	using Poco::format;
	///RS_GetCertInfo
	class GetCertInfo
	{
	public:
		GetCertInfo(const std::string& base64, int type)
			:_base64(base64), _type(type)
		{}
		GetCertInfo& execute()
		{
			if (SGD_CERT_VERSION == _type) {
				_item = GetCertVersion(_base64);
			}
			else if (SGD_CERT_VALID_TIME == _type) {
				_item = GetCertVaildTime(_base64);
			}
			else if (SGD_OID_IDENTIFY_NUMBER == _type) {
				/// only support user id card
				_item = GetCertOwnerID(_base64);
			}
			else
			{
				_item = SOF_GetCertInfo(_base64, _type);
			}
			return *this;
		}
		std::string GetCertVersion(const std::string& base64)
		{
			std::string item;
			item = SOF_GetCertInfo(base64, SGD_CERT_VERSION);

			///GB-T 20518-2006 信息安全技术 公钥基础设施 数字证书格式

			std::map<std::string, std::string> versions;
			versions["0"] = "V1";
			versions["1"] = "V2";
			versions["2"] = "V3";

			return versions[item];
		}
		std::string GetCertVaildTime(const std::string& base64)
		{
			std::string item;
			item = SOF_GetCertInfo(base64, SGD_CERT_VALID_TIME);
			return item;
			/// 190313160000Z - 210314155959Z
			/*
			int options = 0;
			std::string pattern("(\\S+)-(\\S+)");
			RegularExpression re(pattern, options);
			RegularExpression::Match mtch;
			if (!re.match(item, mtch))
				throw Poco::LogicException("GetCertVaildTime Exception!", 0x40);

			std::vector<std::string> tags;
			re.split(item, tags, options);

			std::string vaild_start = tags[1];
			std::string vaild_end = tags[2];

			Debugger::message(format("vaild_start : %s, vaild_start :%s", vaild_start, vaild_end));
			/// UTC to LocalTime +0800
			std::string vaildtime;
			vaildtime.append(toLocalTime(vaild_start));
			vaildtime.append("-");
			vaildtime.append(toLocalTime(vaild_end));

			Debugger::message(format("vaildtime : %s", vaildtime));
			return vaildtime;
			*/
		}

		std::string toLocalTime(const std::string& time)
		{
			int options = 0;
			std::string pattern("^([1-9]\\d{3})([1-9]\\d{1})([1-9]\\d{1})([1-9]\\d{1})([1-9]\\d{1})");
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
			std::string fmt = format("%s-%s-%s %s:%s:%s", tags[1], tags[2], tags[3], tags[4], tags[5]);

			Debugger::message(format("Timezone utcOffset: %d, tzd:: % d, name : %s", Timezone::utcOffset(), Timezone::tzd(), Timezone::name()));
			Debugger::message(time);
			int tzd = Timezone::tzd();
			DateTime dt = DateTimeParser::parse(DateTimeFormat::SORTABLE_FORMAT, fmt, tzd);
			std::string localtime = DateTimeFormatter::format(dt, DateTimeFormat::SORTABLE_FORMAT, Timezone::utcOffset());
			Debugger::message(localtime);
			return localtime;
		}
		std::string GetCertOwnerID(const std::string& base64)
		{
			std::string item;
			std::string pattern("(\\d+)");
			std::string special_oid("1.2.156.10260.4.1.1");
			item = SOF_GetCertInfoByOid(base64, special_oid);
			if (item.empty()) {

				item = SOF_GetCertInfo(base64, SGD_CERT_SUBJECT_CN);
				pattern = "@(\\d+)@";
			}

			item = toLegelID(item, pattern);
			/// erase 0 if is id card
			if (item.at(0) == '0')
				item = item.replace(0, 1, "");

			return item;
		}

		std::string toLegelID(const std::string& text, const std::string& pattern)
		{
			/// SGD_CERT_SUBJECT_CN identify card (330602197108300018)
			/// CN = 041@0330602197108300018@测试个人一@00000001
			/// 十八位：^[1-9]\d{5}(18|19|([23]\d))\d{2}((0[1-9])|(10|11|12))(([0-2][1-9])|10|20|30|31)\d{3}[0-9Xx]$
			/// 十五位：^[1-9]\d{5}\d{2}((0[1-9])|(10|11|12))(([0-2][1-9])|10|20|30|31)\d{2}[0-9Xx]$
			//std::string pattern("@(\\d+)@");
			int options = 0;

			RegularExpression re(pattern, options);
			RegularExpression::Match mtch;

			if (!re.match(text, mtch))
				throw Poco::LogicException("RS_KeyDecryptData uid Exception!", 0x40);

			std::vector<std::string> tags;
			re.split(text, tags, options);
			std::string id = tags[1];
			return id;
		}
		///base64 \/转义字符
		operator std::string()
		{
			JSONStringify data;
			data.addObject("info", _item);
			return data;
		}
	private:
		std::string _item;
		std::string _base64;
		int _type;
	};

	class GetCertInfoRequestHandler : public HTTPRequestHandler
	{
	public:
		void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
		{
			Application& app = Application::instance();
			app.logger().information("GetCertInfoRequestHandler Request from " + request.clientAddress().toString());
			response.set("Access-Control-Allow-Origin", "*");
			response.set("Access-Control-Allow-Methods", "GET, POST, HEAD");

			std::string data;
			HTMLForm form(request, request.stream());
			if (!form.empty()) {
				std::string base64(form.get("certBase64", ""));
				Var type(form.get("type", ""));
				GetCertInfo command(base64, type);
				data += command.execute();
			}
			return response.sendBuffer(data.data(), data.length());
		}
	};
}