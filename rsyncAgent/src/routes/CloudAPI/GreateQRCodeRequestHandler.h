#pragma once

#include "Poco/Util/Application.h"
#include "../Command.h"
#include "../RESTfulRequestHandler.h"
#include "qrencode.h"

namespace Reach {

	using Poco::Util::Application;

	///RS_GreateQRCode
	class GreateQRCode : public Command
	{
	public:
		GreateQRCode(const std::string& qrcode, const std::string& path)
			:_qrcode(qrcode), _path(path)
		{
		}

		void run()
		{
			throw Poco::NotImplementedException();
		}
	private:
		std::string _qrcode;
		std::string _path;
	};

	class GreateQRCodeRequestHandler : public RESTfulRequestHandler
	{
	public:
		void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
		{
			poco_information_f1(Application::instance().logger(), "Request from %s", request.clientAddress().toString());
			RESTfulRequestHandler::handleCORS(request, response);

			HTMLForm form(request, request.stream());
			std::string qrcode = form.get("qrcode", "");
			std::string path = form.get("path", "");
			GreateQRCode command(qrcode, path);
			command.execute();

			return response.sendBuffer(command().data(), command().length());
		}
	};
}