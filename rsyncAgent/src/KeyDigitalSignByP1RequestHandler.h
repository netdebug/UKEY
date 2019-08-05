#pragma once

#include "UDevice.h"
#include "SoFProvider.h"
#include "SOFErrorCode.h"
#include "Command.h"
#include "RESTfulRequestHandler.h"
#include "RequestHandleException.h"
#include "Poco/Util/Application.h"

namespace Reach {

	using Poco::Util::Application;
	///RS_KeyDigitalSignByP1
	class KeyDigitalSignByP1: public Command
	{
	public:
		void run()
		{
			add("data", "RS_KeyDigitalSignByP1 Not Unsupported");
		}
	};

	class KeyDigitalSignByP1RequestHandler : public RESTfulRequestHandler
	{
	public:
		void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
		{
			poco_information_f1(Application::instance().logger(), "Request from %s", request.clientAddress().toString());

			RESTfulRequestHandler::handleCORS(request, response);

			KeyDigitalSignByP1 command;
			command.execute();
			
			return response.sendBuffer(command().data(), command().length());
		}
	};
}