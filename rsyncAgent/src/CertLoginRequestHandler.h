#pragma once

#include "UDevice.h"
#include "JSONStringify.h"
#include "GMCrypto.h"
#include "SoFProvider.h"
#include "SOFErrorCode.h"
#include "Command.h"
#include "RESTfulRequestHandler.h"
#include "RequestHandleException.h"

namespace Reach {

	using Reach::UDevice;
	using Reach::JSONStringify;

	///RS_CertLogin
	class CertLogin : public Command
	{
	public:
		CertLogin(const std::string& uid, const std::string& password)
			:_uid(uid), _pwd(password)
		{}
		void run()
		{
			UDevice::default();

			if (_uid.empty() || _pwd.empty())
				throw RequestHandleException("无效的参数", 0x0A000006);

			int retryCount = SOF_GetPinRetryCount(_uid);
			if (retryCount <= 0)
				throw RequestHandleException("PIN被锁死", _uid, 0x0A000025);

			if (!SOF_Login(_uid, _pwd))
				throw Poco::LogicException("用户没有登录", _uid, 0x0A00002D);
		}

	private:
		std::string _uid, _pwd;
	};

	class CertLoginRequestHandler : public RESTfulRequestHandler
	{
	public:
		void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
		{
			poco_information_f1(Application::instance().logger(), "Request from %s", request.clientAddress().toString());

			RESTfulRequestHandler::handleCORS(request, response);

			HTMLForm form(request, request.stream());
			if (!form.empty()) {
				std::string uid(form.get("containerId", ""));
				std::string pwd(form.get("password", ""));
				CertLogin command(uid, pwd);
				command.execute();

				return response.sendBuffer(command().data(), command().length());
			}

			return response.sendBuffer("", 0);
		}
	};
}