#pragma once

#include "UDevice.h"
#include "SoFProvider.h"
#include "SOFErrorCode.h"
#include "Command.h"
#include "RESTfulRequestHandler.h"
#include "RequestHandleException.h"
#include "Poco/Util/Application.h"

namespace Reach {

	using Poco::Util::Application;

	///RS_GetParameters
	class GetParameters : public Command
	{
	public:
		GetParameters(const std::string& cmd) {}

		void run()
		{
			add("data", "GetParameters Not Implmented!");
		}
	};

	class GetParametersRequestHandler : public RESTfulRequestHandler
	{
	public:
		void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
		{
			poco_information_f1(Application::instance().logger(), "Request from %s", request.clientAddress().toString());

			RESTfulRequestHandler::handleCORS(request, response);

			HTMLForm form(request, request.stream());
			std::string cmd = form.get("cmd", "");

			GetParameters command(cmd);
			command.execute();

			return response.sendBuffer(command().data(), command().length());
		}
	};
}