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
#include "Poco/Dynamic/Var.h"

namespace Reach {

	using Poco::Net::HTTPRequestHandler;
	using Poco::Net::HTTPServerRequest;
	using Poco::Net::HTTPServerResponse;
	using Poco::Net::HTMLForm;
	using Poco::Net::NameValueCollection;
	using Poco::Util::Application;
	using Poco::Dynamic::Var;
	using Reach::UDevice;
	using Reach::JSONStringify;

	///RS_GetCertBase64String
	class GetCertBase64String
	{
	public:
		GetCertBase64String(short ctype, const std::string& uid) 
			:_type(ctype),_uid(uid)
		{}
		GetCertBase64String& execute()
		{
			UDevice::default();

			enum certType { sign = 1, crypto };

			if (certType::sign == _type) {
				_content = SOF_ExportUserCert(_uid);
			}
			else if (certType::crypto == _type) {
				_content = SOF_ExportExChangeUserCert(_uid);
			}

			return *this;
		}
		operator std::string()
		{
			JSONStringify data;
			data.addObject("certBase64", _content);
			return data;
		}
	private:
		std::string _content;
		short _type;
		std::string _uid;
	};


	class GetCertBase64StringRequestHandler : public HTTPRequestHandler
	{
	public:
		void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
		{
			Application& app = Application::instance();
			app.logger().information("GetCertBase64StringRequestHandler Request from " + request.clientAddress().toString());
			response.set("Access-Control-Allow-Origin", "*");
			response.set("Access-Control-Allow-Methods", "GET, POST, HEAD");

			std::string data;
			HTMLForm form(request, request.stream());
			if (!form.empty()) {
				Var type(form.get("certType", ""));
				std::string uid(form.get("containerId", ""));
				GetCertBase64String command(type, uid);
				data += command.execute();
			}
			return response.sendBuffer(data.data(), data.length());
		}
	};
}