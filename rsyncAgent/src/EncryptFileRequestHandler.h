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

	///RS_EncryptFile
	class EncryptFile : public Command
	{
	public:
		EncryptFile(const std::string& SourceFile, const std::string& EncryptFile)
			:_source(SourceFile), _encrypt(EncryptFile), _encrypted(false)
		{
			File fi(_source);
			if (!fi.exists())
				throw Poco::FileExistsException("Source File Not Exists!", _source);
		}
		void run()
		{
			UDevice::default();

			_random_digital = SOF_GenRandom(UDevice::default().random());
			if (_random_digital.empty()) {
				throw RequestHandleException("SOF_GenRandom", SOF_GetLastError());
			}

			_encrypted = SOF_EncryptFile(_random_digital, _source, _encrypt);
			if (!_encrypted) {
				throw RequestHandleException("SOF_EncryptFile failed!", SOF_GetLastError());
			}

			add("symKey", _random_digital);
		}

	private:
		bool _encrypted;
		std::string _source;
		std::string _encrypt;
		std::string _random_digital;
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