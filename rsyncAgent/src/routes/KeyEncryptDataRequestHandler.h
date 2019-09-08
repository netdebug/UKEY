#pragma once

#include "Command.h"
#include "RESTfulRequestHandler.h"
#include "Poco/Util/Application.h"

using Poco::Util::Application;

namespace Reach {
	

	///RS_KeyEncryptData
	class KeyEncryptData : public Command
	{
	public:
		KeyEncryptData(const std::string& paintText, const std::string& base64);
		virtual void run();

	private:
		std::string _base64;
		std::string _paintext;
		std::string _encrypt_data;
	};
	class KeyEncryptDataRequestHandler : public RESTfulRequestHandler
	{
	public:
		void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
		{
			poco_information_f1(Application::instance().logger(), "Request from %s", request.clientAddress().toString());

			RESTfulRequestHandler::handleCORS(request, response);

			HTMLForm form(request, request.stream());
			std::string text(form.get("rsKey", ""));
			std::string cert(form.get("certBase64", ""));

			KeyEncryptData command(text, cert);
			command.execute();

			return response.sendBuffer(command().data(), command().length());
		}
	};
}