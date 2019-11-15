#pragma once

#include "Command.h"
#include "RESTfulRequestHandler.h"
#include "Poco/Util/Application.h"

using Poco::Util::Application;

namespace Reach {
	class KeyStatus :
		public Command
	{
	public:
		KeyStatus(const std::string& uid);
		virtual void run();
	private:
		std::string _uid;
		bool _isLogined;
	};

	class KeyStatusRequestHandler : public RESTfulRequestHandler
	{
	public:
		void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
		{
			poco_information_f1(Application::instance().logger(), "Request from %s", request.clientAddress().toString());

			RESTfulRequestHandler::handleCORS(request, response);

			HTMLForm form(request, request.stream());
			std::string uid(form.get("containerId", ""));

			KeyStatus command(uid);
			command.execute();

			return response.sendBuffer(command().data(), command().length());
		}
	};
}