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

namespace Reach {

	using Poco::Net::HTTPRequestHandler;
	using Poco::Net::HTTPServerRequest;
	using Poco::Net::HTTPServerResponse;
	using Poco::Net::HTMLForm;
	using Poco::Net::NameValueCollection;
	using Poco::Util::Application;
	using Reach::UDevice;
	using Reach::JSONStringify;

	///RS_CertLogin
	class CertLogin
	{
	public:
		CertLogin(const std::string& uid, const std::string& password)
			:_uid(uid), _pwd(password)
		{}
		CertLogin& execute()
		{
			UDevice::default();

			if (_uid.empty() || _pwd.empty())
				throw Poco::InvalidArgumentException("Argument Invalid!", 0x34);

			int retryCount = SOF_GetPinRetryCount(_uid);
			if (retryCount <= 0)
				throw Poco::LogicException("UKEY have been locked! containerId is", _uid, 0x33);

			if (!SOF_Login(_uid, _pwd))
				throw Poco::LogicException("UKEY Login failed! containerId is", _uid, 0x35);

			return *this;
		}

		operator std::string()
		{
			JSONStringify data;
			data.addObject("containerId", _uid);
			return data;
		}
	private:
		std::string _uid, _pwd;
	};

	class CertLoginRequestHandler : public HTTPRequestHandler
	{
	public:
		void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
		{
			Application& app = Application::instance();
			app.logger().information("CertLoginRequestHandler Request from " + request.clientAddress().toString());

			std::string data;
			HTMLForm form(request, request.stream());
			if (!form.empty()) {
				std::string uid(form.get("containerId", ""));
				std::string pwd(form.get("password", ""));
				CertLogin command(uid, pwd);
				data += command.execute();
			}
			return response.sendBuffer(data.data(), data.length());
		}
	};
}