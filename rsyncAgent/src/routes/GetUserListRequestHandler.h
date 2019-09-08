#pragma once

#include "Command.h"
#include "RESTfulRequestHandler.h"
#include "Poco/Util/Application.h"

using Poco::Util::Application;

namespace Reach {

	///RS_GetUserList
	///example
	///		{
	///			"code":"0000",
	///				"msg" : "Ö´ÐÐ³É¹¦",
	///				"data" : {
	///				"userlist":"BJCA-Application||806000119631708&&&BJCA-Application||806000119631714"
	///			}
	///		}


	class GetUserList : public Command
	{
	public:
		virtual void run();
	private:
		std::string _line;
	};

	class GetUserListRequestHandler : public RESTfulRequestHandler
	{
	public:
		void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
		{
			poco_information_f1(Application::instance().logger(), "Request from %s", request.clientAddress().toString());

			RESTfulRequestHandler::handleCORS(request, response);

			GetUserList command;
			command.execute();

			return response.sendBuffer(command().data(), command().length());
		}
	};
}