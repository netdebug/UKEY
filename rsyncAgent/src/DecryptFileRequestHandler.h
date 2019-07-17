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

	///RS_DecryptFile
	class DecryptFile
	{
	public:
		DecryptFile(std::string& SymKey, std::string& EncryptFile, std::string& OutDir)
			:_kv(SymKey),_encrypt(EncryptFile),_decrypt_directory(OutDir)
		{
			assert(!_decrypt_directory.empty());
			if (_encrypt.empty())
				throw Poco::FileNotFoundException("Encrypt File Not Exists!", _encrypt);
		}
		DecryptFile& execute()
		{
			UDevice::default();

			_decrypted = SOF_DecryptFile(_kv, _encrypt, _decrypt_directory);
			return *this;
		}

		operator std::string()
		{
			if (!_decrypted)
			{
				int error = SOF_GetLastError();
				JSONStringify data("unsuccessful", error);
				data.addNullObject();
				return data;
			}

			JSONStringify data;
			data.addNullObject();
			return data;
		}
	private:
		bool _decrypted;
		std::string _kv;
		std::string _encrypt;
		std::string _decrypt_directory;
	};

	class DecryptFileRequestHandler : public HTTPRequestHandler
	{
	public:
		void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
		{
			Application& app = Application::instance();
			app.logger().information("DecryptFileRequestHandler Request from " + request.clientAddress().toString());
			response.set("Access-Control-Allow-Origin", "*");
			response.set("Access-Control-Allow-Methods", "GET, POST, HEAD");

			std::string data;
			HTMLForm form(request, request.stream());
			if (!form.empty()) {
				std::string SymKey(form.get("symKey", ""));
				std::string EncryptFile(form.get("encFilePath", ""));
				std::string OutDir(form.get("dncDirectoryPath", ""));
				DecryptFile command(SymKey, EncryptFile, OutDir);
				data += command.execute();
			}
			return response.sendBuffer(data.data(), data.length());
		}
	};
}