#pragma once

#include "Command.h"
#include "RESTfulRequestHandler.h"
#include "Poco/Util/Application.h"
#include "Poco/Dynamic/Var.h"

using Poco::Util::Application;
using Poco::Dynamic::Var;

namespace Reach {

	///RS_KeySignByP7
	class KeySignByP7 : public Command
	{
	public:
		KeySignByP7(const std::string& textual, int mode, const std::string& uid);
		virtual void run();

	private:
		std::string _textual;
		short _mode;///Attached = 0, Detached =1
		std::string _uid;
		std::string _signature;
	};

	class KeySignByP7RequestHandler : public RESTfulRequestHandler
	{
	public:
		void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
		{
			poco_information_f1(Application::instance().logger(), "Request from %s", request.clientAddress().toString());

			RESTfulRequestHandler::handleCORS(request, response);

			HTMLForm form(request, request.stream());
			std::string textual(form.get("msg", ""));
			std::string uid(form.get("containerId", ""));
			Var mode(form.get("flag", ""));

			KeySignByP7 command(textual, mode, uid);
			command.execute();

			return response.sendBuffer(command().data(), command().length());
		}
	};
}