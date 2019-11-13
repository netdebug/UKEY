#pragma once

#include "Command.h"
#include "RESTfulRequestHandler.h"
#include "Poco/Util/Application.h"

using Poco::Util::Application;

namespace Reach {
	class KeyDecryptFile
		: public Command
	{
	public:
		KeyDecryptFile(const std::string& fpPlain, const std::string& fpCipher, const std::string& uid);
		virtual void run();

	private:
		std::string _fpPlain;
		std::string _fpCipher;
		std::string _uid;
	};
	class KeyDecryptFileRequestHandler : public RESTfulRequestHandler
	{
	public:
		void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
		{
			poco_information_f1(Application::instance().logger(), "Request from %s", request.clientAddress().toString());

			RESTfulRequestHandler::handleCORS(request, response);

			HTMLForm form(request, request.stream());
			std::string fpCipher(form.get("encFilePath", ""));
			std::string fpPlain(form.get("dncFilePath", ""));
			std::string uid(form.get("containerId", ""));

			KeyDecryptFile command(fpPlain, fpCipher, uid);
			command.execute();

			return response.sendBuffer(command().data(), command().length());
		}
	};
}