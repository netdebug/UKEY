#pragma once

#include "Command.h"
#include "RESTfulRequestHandler.h"
#include "Poco/Util/Application.h"

using Poco::Util::Application;

namespace Reach {
	///RS_KeyDecryptData
	class KeyDecryptData : public Command
	{
	public:
		KeyDecryptData(const std::string& uid, const std::string& encryptBuffer);
		virtual void run();

	private:
		std::string _uid;
		std::string _encrypt_data;
		std::string _decrypt_data;
		std::string _text;
	};

	class KeyDecryptDataRequestHandler : public RESTfulRequestHandler
	{
	public:
		void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
		{
			poco_information_f1(Application::instance().logger(), "Request from %s", request.clientAddress().toString());

			RESTfulRequestHandler::handleCORS(request, response);

			HTMLForm form(request, request.stream());
			std::string uid(form.get("containerId", ""));
			std::string encryptBuffer(form.get("encRsKey", ""));

			KeyDecryptData command(uid, encryptBuffer);
			command.execute();

			return response.sendBuffer(command().data(), command().length());
		}
	};
}