#pragma once

#include "UDevice.h"
#include "SoFProvider.h"
#include "ErrorCode.h"
#include "Command.h"
#include "RESTfulRequestHandler.h"
#include "RequestHandleException.h"
#include "Poco/Util/Application.h"
#include "Reach/Data/Session.h"


namespace Reach {

	using Reach::UDevice;
	using Reach::JSONStringify;
	using Poco::Util::Application;
	///RS_CertLogin
	class CertLogin :public Command
	{
	public:
		CertLogin(const std::string& uid, const std::string& password)
			:_uid(uid), _pwd(password)
		{}
		void run()
		{	
			//Reach::Data::Session session("SOF", "REST");
			Reach::Data::Session session(getEngine(), "REST");

			if (_uid.empty() || _pwd.empty())
				throw RequestHandleException(RAR_UNKNOWNERR);

			if(_uid != session.contianer())
				throw RequestHandleException(RAR_UNIQUEIDUNCORRECT);

			int retryCount = session.getPinRetryCount();
			if (retryCount <= 0)
				throw RequestHandleException(_uid, RAR_UNKNOWNERR);

			if (!session.login(_pwd))
				throw RequestHandleException(_uid, RAR_UNKNOWNERR);

			add("containerId", _uid);
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

			std::string uid(form.get("containerId", ""));
			std::string pwd(form.get("password", ""));
			CertLogin command(uid, pwd);
			command.execute();

			return response.sendBuffer(command().data(), command().length());
		}
	};
}