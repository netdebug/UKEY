#pragma once

#include "UDevice.h"
#include "SoFProvider.h"
#include "SOFErrorCode.h"
#include "Command.h"
#include "RESTfulRequestHandler.h"
#include "RequestHandleException.h"
#include "Poco/Util/Application.h"
#include <cassert>

namespace Reach {

	using Poco::Util::Application;

	///RS_DecryptFile
	class DecryptFile : public Command
	{
	public:
		DecryptFile(std::string& SymKey, std::string& EncryptFile, std::string& OutDir)
			:_kv(SymKey), _encrypt(EncryptFile), _decrypt_directory(OutDir)
		{
			assert(!_decrypt_directory.empty());
			if (_encrypt.empty())
				throw RequestHandleException(SAR_FILEERR);
		}
		void run()
		{
			UDevice::default();
			_decrypted = SOF_DecryptFile(_kv, _encrypt, _decrypt_directory);
			if (!_decrypted)
				throw RequestHandleException(SAR_UNKNOWNERR);
		}

	private:
		bool _decrypted;
		std::string _kv;
		std::string _encrypt;
		std::string _decrypt_directory;
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