#pragma once

#include "Command.h"
#include "RESTfulRequestHandler.h"
#include "Poco/Util/Application.h"

using Poco::Util::Application;

namespace Reach {
	class KeyEncryptFile
		:public Command
	{
	public:
		KeyEncryptFile(const std::string& fpPlain, const std::string& fpCipher, const std::string& cert);
		virtual void run();

	private:
		std::string _fpPlain;
		std::string _fpCipher;
		std::string _cert;
	};

	class KeyEncryptFileRequestHandler : public RESTfulRequestHandler
	{
	public:
		void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
		{
			poco_information_f1(Application::instance().logger(), "Request from %s", request.clientAddress().toString());

			RESTfulRequestHandler::handleCORS(request, response);

			HTMLForm form(request, request.stream());
			std::string fpPlain(form.get("souceFilePath", ""));
			std::string fpCipher(form.get("encFilePath", ""));
			std::string cert(form.get("certBase64", ""));

			KeyEncryptFile command(fpPlain, fpCipher, cert);
			command.execute();

			return response.sendBuffer(command().data(), command().length());
		}
	};
}