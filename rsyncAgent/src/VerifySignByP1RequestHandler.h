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
	///RS_VerifySignByP1
	class VerifySignByP1 : public Command
	{
	public:
		VerifySignByP1(const std::string& base64, const std::string& msg, const std::string& signature)
			:_base64(base64), _msg(msg), _signature(signature)
		{}

		void run()
		{
			Reach::Data::Session session("SOF", "REST");
			_val = session.verifySignByP1(_base64, _msg, _signature);
			
			if (!_val) {
				throw RequestHandleException("SOF_VerifySignedData failed!", RAR_UNKNOWNERR);
			}
		}

	private:
		bool _val;
		std::string _base64;
		std::string _msg;
		std::string _signature;
	};

	class VerifySignByP1RequestHandler : public RESTfulRequestHandler
	{
	public:
		void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
		{
			poco_information_f1(Application::instance().logger(), "Request from %s", request.clientAddress().toString());

			RESTfulRequestHandler::handleCORS(request, response);

			HTMLForm form(request, request.stream());
			std::string base64(form.get("certBase64", ""));
			std::string msg(form.get("msg", ""));
			std::string signature(form.get("signdMsg", ""));

			VerifySignByP1 command(base64, msg, signature);
			command.execute();

			return response.sendBuffer(command().data(), command().length());
		}
	};
}