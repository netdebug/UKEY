#pragma once

#include "Command.h"
#include "RESTfulRequestHandler.h"
#include "Poco/Util/Application.h"

namespace Reach {

	using Poco::Util::Application;

	///RS_ConfigParameters
	class ConfigParameters : public Command
	{
	public:
		ConfigParameters(const std::string& cmd, const std::string& val)
			:_cmd(cmd), _val(val)
		{
		}

		void run()
		{
			Application& app = Application::instance();
			app.config().setString(_cmd, _val);
		}
	private:
		std::string _cmd;
		std::string _val;
	};

	class ConfigParametersRequestHandler : public RESTfulRequestHandler
	{
	public:
		void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
		{
			poco_information_f1(Application::instance().logger(), "Request from %s", request.clientAddress().toString());
			RESTfulRequestHandler::handleCORS(request, response);

			HTMLForm form(request, request.stream());
			std::string cmd = form.get("cmd", "");
			std::string value = form.get("val", "");
			ConfigParameters command(cmd, value);
			command.execute();

			return response.sendBuffer(command().data(), command().length());
		}
	};
}