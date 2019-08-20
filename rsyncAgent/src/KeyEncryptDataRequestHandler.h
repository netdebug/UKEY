#pragma once

#include "UDevice.h"
#include "SoFProvider.h"
#include "SOFErrorCode.h"
#include "Command.h"
#include "RESTfulRequestHandler.h"
#include "RequestHandleException.h"
#include "Poco/Util/Application.h"
#include "Poco/File.h"
#include <cassert>

namespace Reach {

	using Poco::Util::Application;
	using Poco::File;

	///RS_KeyEncryptData
	class KeyEncryptData : public Command
	{
	public:
		KeyEncryptData(const std::string& paintText, const std::string& base64)
			:_paintext(paintText), _base64(base64), _encrypt_data("")
		{}
		void run()
		{
			//UDevice::default();
			Reach::Data::Session session("SOF", "REST");

			if (_paintext.empty())
				throw RequestHandleException(RAR_ERRNODECRYPT);

			_encrypt_data = session.encryptData(_paintext, _base64);

			_encrypt_data.append("@@@");
			_encrypt_data.append(_base64);

			add("encRsKey", _encrypt_data);
		}

	private:
		std::string _base64;
		std::string _paintext;
		std::string _encrypt_data;
	};
	class KeyEncryptDataRequestHandler : public RESTfulRequestHandler
	{
	public:
		void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
		{
			poco_information_f1(Application::instance().logger(), "Request from %s", request.clientAddress().toString());

			RESTfulRequestHandler::handleCORS(request, response);

			HTMLForm form(request, request.stream());
			std::string text(form.get("rsKey", ""));
			std::string cert(form.get("certBase64", ""));

			KeyEncryptData command(text, cert);
			command.execute();

			return response.sendBuffer(command().data(), command().length());
		}
	};
}