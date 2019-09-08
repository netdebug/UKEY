#pragma once

#include "Command.h"
#include "RESTfulRequestHandler.h"
#include "Poco/Util/Application.h"

namespace Reach {

	using Poco::Util::Application;
	///RS_KeyGetKeySn
	class KeyGetKeySn : public Command
	{
	public:
		KeyGetKeySn(const std::string& uid);
		virtual void run();

	private:
		std::string _uid;
		std::string _SNkey;
	};

	class KeyGetKeySnRequestHandler : public RESTfulRequestHandler
	{
	public:
		void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
		{
			poco_information_f1(Application::instance().logger(), "Request from %s", request.clientAddress().toString());

			RESTfulRequestHandler::handleCORS(request, response);

			HTMLForm form(request, request.stream());
			std::string uid(form.get("containerId", ""));

			KeyGetKeySn command(uid);
			command.execute();

			return response.sendBuffer(command().data(), command().length());
		}
	};
}