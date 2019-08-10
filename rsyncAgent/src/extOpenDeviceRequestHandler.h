#pragma once

#include "RESTfulRequestHandler.h"
#include "RequestHandleException.h"
#include "Poco/Util/Application.h"
#include "SoFProvider.h"
#include "SOFErrorCode.h"
#include "ErrorCode.h"

namespace Reach {

	using Poco::Util::Application;
	using Reach::JSONStringify;

	class OpenDevice : public Command
	{
	public:
		void run()
		{
			_status = SOF_OpenDevice();
			if (_status != SAR_OK)
				throw RequestHandleException(RAR_OPENDEVICEFAILED);
		}

	private:
		std::string _line;
		int _status;
	};

	class extOpenDeviceRequestHandler : public RESTfulRequestHandler
	{
	public:
		void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
		{
			poco_information_f1(Application::instance().logger(), "Request from %s", request.clientAddress().toString());

			RESTfulRequestHandler::handleCORS(request, response);

			OpenDevice command;
			command.execute();

			return response.sendBuffer(command().data(), command().length());
		}
	};
}