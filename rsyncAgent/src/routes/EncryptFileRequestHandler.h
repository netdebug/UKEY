#pragma once

#include "Command.h"
#include "RESTfulRequestHandler.h"
#include "Poco/Util/Application.h"
#include "Poco/FileStream.h"
#include "Poco/Crypto/Cipher.h"
using Poco::Util::Application;

namespace Reach {
	///RS_EncryptFile
	class EncryptFile : public Command
	{
	public:
		EncryptFile(const std::string& SourceFile, const std::string& EncryptFile);
		virtual void run();
	protected:
		virtual void generateKey();
	private:
		bool _encrypted;
		Poco::FileInputStream _sink;
		Poco::FileOutputStream _sank;
		Poco::Crypto::Cipher* _pCipher;
		std::string _symKey;
	};

	class EncryptFileRequestHandler : public RESTfulRequestHandler
	{
	public:
		void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
		{
			poco_information_f1(Application::instance().logger(), "Request from %s", request.clientAddress().toString());

			RESTfulRequestHandler::handleCORS(request, response);

			HTMLForm form(request, request.stream());
			std::string SourceFilePath(form.get("souceFilePath", ""));
			std::string EncryptFilePath(form.get("encFilePath", ""));

			EncryptFile command(SourceFilePath, EncryptFilePath);
			command.execute();

			return response.sendBuffer(command().data(), command().length());
		}
	};
}