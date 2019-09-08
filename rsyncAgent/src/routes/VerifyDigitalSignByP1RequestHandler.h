#pragma once

#include "Command.h"
#include "RESTfulRequestHandler.h"
#include "RequestHandleException.h"
#include "Poco/Util/Application.h"

namespace Reach {

	using Poco::Util::Application;

	///RS_VerifyDigitalSignByP1
	class VerifyDigitalSignByP1 : public Command
	{
	public:
		void run()
		{
			add("data", "RS_VerifyDigitalSignByP1 Not Implmented!");
		}
	};

	class VerifyDigitalSignByP1RequestHandler : public RESTfulRequestHandler
	{
	public:
		void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
		{
			poco_information_f1(Application::instance().logger(), "Request from %s", request.clientAddress().toString());

			RESTfulRequestHandler::handleCORS(request, response);

			VerifyDigitalSignByP1 command;
			command.execute();

			return response.sendBuffer(command().data(), command().length());
		}
	};
}