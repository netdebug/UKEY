#pragma once

#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTMLForm.h"
#include "Poco/Net/NameValueCollection.h"
#include "Poco/Util/Application.h"
#include "Poco/File.h"
#include "UDevice.h"
#include "JSONStringify.h"
#include "GMCrypto.h"
#include "SoFProvider.h"
#include <cassert>

namespace Reach {

	using Poco::Net::HTTPRequestHandler;
	using Poco::Net::HTTPServerRequest;
	using Poco::Net::HTTPServerResponse;
	using Poco::Net::HTMLForm;
	using Poco::Net::NameValueCollection;
	using Poco::Util::Application;
	using Poco::File;
	using Reach::UDevice;
	using Reach::JSONStringify;

	///RS_EncryptFile
	class EncryptFile
	{
	public:
		EncryptFile(const std::string& SourceFile, const std::string& EncryptFile)
			:_source(SourceFile),_encrypt(EncryptFile), _encrypted(false)
		{
			assert(!_source.empty());
			assert(!_encrypt.empty());
			File fi(_source);
			if (!fi.exists())
				throw Poco::FileExistsException("Source File Not Exists!", _source);
		}
		EncryptFile& execute()
		{
			UDevice::default();

			_random_digital = SOF_GenRandom(UDevice::default().random());
			_encrypted = SOF_EncryptFile(_random_digital, _source, _encrypt);

			return *this;
		}

		operator std::string()
		{
			if (!_encrypted)
			{
				int error = SOF_GetLastError();
				JSONStringify data("unsuccessful", error);
				data.addNullObject();
				return data;
			}

			JSONStringify data;
			data.addObject("symKey", _random_digital);
			return data;
		}
	private:
		bool _encrypted;
		std::string _source;
		std::string _encrypt;
		std::string _random_digital;
	};

	class EncryptFileRequestHandler : public HTTPRequestHandler
	{
	public:
		void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
		{
			Application& app = Application::instance();
			app.logger().information("EncryptFileRequestHandler Request from " + request.clientAddress().toString());
			response.set("Access-Control-Allow-Origin", "*");
			response.set("Access-Control-Allow-Methods", "GET, POST, HEAD");

			std::string data;
			HTMLForm form(request, request.stream());
			if (!form.empty()) {
				std::string SourceFilePath(form.get("souceFilePath", ""));
				std::string EncryptFilePath(form.get("encFilePath", ""));
				EncryptFile command(SourceFilePath, EncryptFilePath);
				data += command.execute();
			}
			return response.sendBuffer(data.data(), data.length());
		}
	};
}