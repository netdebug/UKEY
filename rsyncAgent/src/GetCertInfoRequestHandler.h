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
	///RS_GetCertInfo
	class GetCertInfo
	{
	public:
		GetCertInfo(const std::string& base64, int type)
			:_base64(base64), _type(type)
		{}
		GetCertInfo& execute()
		{
			if (SGD_CERT_VERSION < _type < SGD_CERT_DER_EXTENSIONS ||
				SGD_CERT_ISSUER_CN < _type < SGD_CERT_SUBJECT_EMAIL)
			{
				_item = SOF_GetCertInfo(_base64, _type);
			}
			if (SGD_OID_IDENTIFY_NUMBER == _type) {
				std::string special_oid("1.2.156.10260.4.1.1");
				_item = SOF_GetCertInfoByOid(_base64, special_oid);
				if (_item.empty()) {
					/// SGD_CERT_SUBJECT_CN identify card (330602197108300018)
					/// CN = 041@0330602197108300018@测试个人一@00000001
					/// 十八位：^[1-9]\d{5}(18|19|([23]\d))\d{2}((0[1-9])|(10|11|12))(([0-2][1-9])|10|20|30|31)\d{3}[0-9Xx]$
					/// 十五位：^[1-9]\d{5}\d{2}((0[1-9])|(10|11|12))(([0-2][1-9])|10|20|30|31)\d{2}[0-9Xx]$
					std::string CN_ITEM = SOF_GetCertInfo(_base64, SGD_CERT_SUBJECT_CN);
					std::string pattern("@(\\d+)@");
					int options = 0;

					RegularExpression re(pattern, options);
					RegularExpression::Match mtch;

					if (!re.match(CN_ITEM, mtch))
						throw Poco::LogicException("RS_KeyDecryptData uid Exception!", 0x40);

					std::vector<std::string> tags;
					re.split(CN_ITEM, tags, options);
					std::string id = tags[1];
					/// erase 0 if is id card
					if (id.at(0) == '0')
						_item = id.replace(0, 1, "");
				}
			}
			return *this;
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