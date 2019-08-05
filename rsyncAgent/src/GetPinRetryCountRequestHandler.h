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

	///RS_GetPinRetryCount
	class GetPinRetryCount : public Command
	{
	public:
		GetPinRetryCount(const std::string& uid)
			:_uid(uid)
		{}

		void run()
		{
			UDevice::default();
			_retryCount = SOF_GetPinRetryCount(_uid);

			add("retryCount", _retryCount);
		}

	private:
		int _retryCount;
		std::string _uid;
	};
	class GetPinRetryCountRequestHandler : public RESTfulRequestHandler
	{
	public:
		void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
		{
			poco_information_f1(Application::instance().logger(), "Request from %s", request.clientAddress().toString());

			RESTfulRequestHandler::handleCORS(request, response);

			HTMLForm form(request, request.stream());
			std::string uid(form.get("containerId", ""));

			GetPinRetryCount command(uid);
			command.execute();

			return response.sendBuffer(command().data(), command().length());
		}
	};
}