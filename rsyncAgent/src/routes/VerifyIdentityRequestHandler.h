#pragma once

#include "Command.h"
#include "RESTfulRequestHandler.h"
#include "RequestHandleException.h"
#include "Poco/Util/Application.h"

namespace Reach {

	using Poco::Util::Application;

	///RS_VerifyIdentity
	class VerifyIdentity : public Command
	{
	public:
		void run()
		{
			add("data", "RS_VerifyIdentity Not Implmented!");
		}
	};
	class VerifyIdentityRequestHandler : public RESTfulRequestHandler
	{
	public:
		void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
		{
			poco_information_f1(Application::instance().logger(), "Request from %s", request.clientAddress().toString());

			RESTfulRequestHandler::handleCORS(request, response);

			HTMLForm form(request, request.stream());

			VerifyIdentity command;
			command.execute();

			return response.sendBuffer(command().data(), command().length());
		}
	};
}