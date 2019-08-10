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
	///RS_KeySignByP1
	class KeySignByP1 : public Command
	{
	public:
		KeySignByP1(const std::string& uid, const std::string& msg)
			:_uid(uid), _msg(msg)
		{}

		void run()
		{
			UDevice::default();

			_signature = SOF_SignData(_uid, _msg);
			if (_signature.empty()) {
				throw RequestHandleException("SOF_SignData failed!", RAR_UNKNOWNERR);
			}

			add("signdMsg", _signature);
		}

	private:
		std::string _signature;
		std::string _uid;
		std::string _msg;
	};
	class KeySignByP1RequestHandler : public RESTfulRequestHandler
	{
	public:
		void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
		{
			poco_information_f1(Application::instance().logger(), "Request from %s", request.clientAddress().toString());

			RESTfulRequestHandler::handleCORS(request, response);

			HTMLForm form(request, request.stream());
			std::string uid(form.get("containerId", ""));
			std::string msg(form.get("asn1Msg", ""));

			KeySignByP1 command(uid, msg);
			command.execute();

			return response.sendBuffer(command().data(), command().length());
		}
	};
}