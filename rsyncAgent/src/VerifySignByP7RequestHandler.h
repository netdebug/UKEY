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
	///RS_VerifySignByP7
	class VerifySignByP7 : public Command
	{
	public:
		VerifySignByP7(const std::string& textual, const std::string& signature, int mode)
			:_textual(textual), _signature(signature), _mode(mode), _verify(false)
		{}

		void run()
		{
			UDevice::default();
			/////1 = Attached mode ,textual must be cleared!
			if (!_mode)
				_textual.clear();

			_verify = SOF_VerifySignedMessage(_signature, _textual);
			if (!_verify) {
				throw RequestHandleException("SOF_VerifySignedMessage failed!", RAR_UNKNOWNERR);
			}
		}

	private:
		int _mode;///Attached = 0, Detached = 1
		bool _verify;
		std::string _textual;
		std::string _signature;
	};

	class VerifySignByP7RequestHandler : public RESTfulRequestHandler
	{
	public:
		void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
		{
			poco_information_f1(Application::instance().logger(), "Request from %s", request.clientAddress().toString());

			RESTfulRequestHandler::handleCORS(request, response);

			HTMLForm form(request, request.stream());
			std::string textual(form.get("msg", ""));
			std::string signature(form.get("signdMsg", ""));
			Var mode(form.get("flag", ""));

			VerifySignByP7 command(textual, signature, mode);
			command.execute();

			return response.sendBuffer(command().data(), command().length());
		}
	};
}