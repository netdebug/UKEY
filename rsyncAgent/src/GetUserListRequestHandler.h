#pragma once

#include "UDevice.h"
#include "SoFProvider.h"
#include "SOFErrorCode.h"
#include "Command.h"
#include "RESTfulRequestHandler.h"
#include "RequestHandleException.h"
#include "Poco/Util/Application.h"

namespace Reach {

	using Reach::UDevice;
	using Reach::JSONStringify;
	using Poco::Util::Application;

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
		void run()
		{
			UDevice::default();
			_line = SOF_GetUserList();
			if (_line.empty())
				throw RequestHandleException(SOF_GetLastError());

			add("userlist" ,_line);
		}
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