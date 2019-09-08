#pragma once
#pragma once
#include "Command.h"
#include "RESTfulRequestHandler.h"
#include "Poco/Util/Application.h"
#include "Poco/Dynamic/Var.h"

using Poco::Util::Application;
using Poco::Dynamic::Var;

namespace Reach {
	///RS_VerifySignByP7
	class VerifySignByP7 : public Command
	{
	public:
		VerifySignByP7(const std::string& textual, const std::string& signature, int mode);
		virtual void run();

	private:
		int _mode;///Attached = 0, Detached = 1
		bool _verify;
		std::string _textual;
		std::string _signature;
	};

	class VerifySignByP7RequestHandler : public RESTfulRequestHandler
	{
	public:
		void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
		{
			poco_information_f1(Application::instance().logger(), "Request from %s", request.clientAddress().toString());

			RESTfulRequestHandler::handleCORS(request, response);

			HTMLForm form(request, request.stream());
			std::string textual(form.get("msg", ""));
			std::string signature(form.get("signdMsg", ""));
			Var mode(form.get("flag", ""));

			VerifySignByP7 command(textual, signature, mode);
			command.execute();

			return response.sendBuffer(command().data(), command().length());
		}
	};
}