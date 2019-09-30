#pragma once

#include "Command.h"
#include "RESTfulRequestHandler.h"
#include "Poco/Util/Application.h"

namespace Reach {
	using Poco::Util::Application;
	class ReadSealData : public Command
	{
	public:
		ReadSealData(const std::string& uid);
		virtual void run();
	private:
		std::string _uid;
		std::string _;
	};

	class ReadSealDataRequestHandler : public RESTfulRequestHandler
	{
	public:
		void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
		{
			poco_information_f1(Application::instance().logger(), "Request from %s", request.clientAddress().toString());

			RESTfulRequestHandler::handleCORS(request, response);

			HTMLForm form(request, request.stream());
			std::string uid(form.get("containerId", ""));

			ReadSealData command(uid);
			command.execute();

			return response.sendBuffer(command().data(), command().length());
		}
	};
}