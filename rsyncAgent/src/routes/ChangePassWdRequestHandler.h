#pragma once
#include "Command.h"
#include "RESTfulRequestHandler.h"
#include "Poco/Util/Application.h"

using Poco::Util::Application;

namespace Reach {
	///RS_ChangePassWd
	class ChangePassWd :public Command
	{
	public:
		ChangePassWd(const std::string& uid, const std::string& oldCode, const std::string& newCode);
		virtual void run();

	private:
		std::string _uid;
		std::string _oldCode;
		std::string _newCode;
	};

	class ChangePassWdRequestHandler : public RESTfulRequestHandler
	{
	public:
		void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
		{
			poco_information_f1(Application::instance().logger(), "Request from %s", request.clientAddress().toString());

			RESTfulRequestHandler::handleCORS(request, response);

			HTMLForm form(request, request.stream());
			std::string uid(form.get("containerId", ""));
			std::string oldCode(form.get("oldCode", ""));
			std::string newCode(form.get("newCode", ""));

			ChangePassWd command(uid, oldCode, newCode);
			command.execute();

			return response.sendBuffer(command().data(), command().length());
		}
	};
}