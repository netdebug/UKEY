#pragma once
#include "Command.h"
#include "RESTfulRequestHandler.h"
#include "Poco/Util/Application.h"

using Poco::Util::Application;

namespace Reach {
	///RS_DecryptFile
	class DecryptFile : public Command
	{
	public:
		DecryptFile(std::string& SymKey, std::string& EncryptFile, std::string& OutDir);
		virtual void run();
	private:
		bool _decrypted;
		std::string _kv;
		std::string _encrypt;
		std::string _decrypt;
	};

	class DecryptFileRequestHandler : public RESTfulRequestHandler
	{
	public:
		void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
		{
			poco_information_f1(Application::instance().logger(), "Request from %s", request.clientAddress().toString());

			RESTfulRequestHandler::handleCORS(request, response);

			HTMLForm form(request, request.stream());
			std::string SymKey(form.get("symKey", ""));
			std::string EncryptFile(form.get("encFilePath", ""));
			std::string OutDir(form.get("dncDirectoryPath", ""));

			DecryptFile command(SymKey, EncryptFile, OutDir);
			command.execute();

			return response.sendBuffer(command().data(), command().length());
		}
	};
}