#pragma once

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
		GetParameters(const std::string& cmd)
			:_cmd(cmd), _defaultValue("")
		{}

		void run()
		{
			Application& app = Application::instance();
			std::string result = app.config().getString(_cmd, _defaultValue);

			add(_cmd, result);
		}
	private:
		std::string _cmd;
		std::string _defaultValue;
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