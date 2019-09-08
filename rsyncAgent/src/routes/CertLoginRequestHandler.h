#pragma once

#include "Command.h"
#include "RESTfulRequestHandler.h"
#include "Poco/Util/Application.h"


using Poco::Util::Application;

namespace Reach {

	///RS_CertLogin
	class CertLogin :public Command
	{
	public:
		CertLogin(const std::string& uid, const std::string& password);
		virtual void run();
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