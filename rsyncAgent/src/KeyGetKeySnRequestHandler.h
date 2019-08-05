#pragma once

#include "SoFProvider.h"
#include "SOFErrorCode.h"
#include "Command.h"
#include "RESTfulRequestHandler.h"
#include "RequestHandleException.h"
#include "Poco/Util/Application.h"

namespace Reach {

	using Poco::Util::Application;
	///RS_KeyGetKeySn
	class KeyGetKeySn : public Command
	{
	public:
		KeyGetKeySn(const std::string& uid)
			:_uid(uid)
		{}
		void run()
		{
			UDevice::default();

			_SNkey = SOF_GetDeviceInfo(_uid, SGD_DEVICE_SERIAL_NUMBER);

			if (_SNkey.empty()) {
				throw RequestHandleException("SOF_GetDeviceInfo failed!", SOF_GetLastError());
			}

			add("containerId", _uid);
			add("keySn", _SNkey);
		}

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