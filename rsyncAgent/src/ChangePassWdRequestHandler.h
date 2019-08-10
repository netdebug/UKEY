#pragma once

#include "UDevice.h"
#include "SoFProvider.h"
#include "ErrorCode.h"
#include "Command.h"
#include "RESTfulRequestHandler.h"
#include "RequestHandleException.h"
#include "Poco/Util/Application.h"

namespace Reach {

	using Reach::UDevice;
	using Reach::JSONStringify;
	using Poco::Util::Application;

	///RS_ChangePassWd
	class ChangePassWd :public Command
	{
	public:
		ChangePassWd(const std::string& uid, const std::string& oldCode, const std::string& newCode)
			:_uid(uid), _oldCode(oldCode), _newCode(newCode)
		{}
		void run()
		{
			UDevice::default();

			if (!SOF_ChangePassWd(_uid, _oldCode, _newCode))
			{
				throw RequestHandleException("SOF_ChangePassWd failed", RAR_UNKNOWNERR);
			}
		}

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