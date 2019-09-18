#pragma once

#include "Command.h"
#include "RESTfulRequestHandler.h"
#include "Poco/Util/Application.h"
#include "VerifySignByP1ExtRequestHandler.h"

using Poco::Util::Application;

namespace Reach {
	///RS_VerifySignByP1
	class VerifySignByP1 : public Command
	{
	public:
		VerifySignByP1(const std::string& base64, const std::string& msg, const std::string& signature);
		virtual void run();

	private:
		bool _val;
		std::string _base64;
		std::string _msg;
		std::string _signature;
	};

	class VerifySignByP1RequestHandler : public RESTfulRequestHandler
	{
	public:
		void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
		{
			poco_information_f1(Application::instance().logger(), "Request from %s", request.clientAddress().toString());

			RESTfulRequestHandler::handleCORS(request, response);

			HTMLForm form(request, request.stream());
			std::string base64(form.get("certBase64", ""));
			std::string msg(form.get("msg", ""));
			std::string signature(form.get("signdMsg", ""));

			VerifySignByP1 command(base64, msg, signature);
			command.execute();

			return response.sendBuffer(command().data(), command().length());
		}
	};
}