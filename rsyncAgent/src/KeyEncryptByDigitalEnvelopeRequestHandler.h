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

	///RS_KeyEncryptByDigitalEnvelope
	class KeyEncryptByDigitalEnvelope
	{
	public:
		KeyEncryptByDigitalEnvelope(const std::string& SourceFile, const std::string& EncryptFile, std::string cert)
			:_source(SourceFile),_encrypt(EncryptFile),_cert(cert), 
			_encrypted(false), _random_digital(""), _cryptogrphic("")
		{
			assert(!_encrypt.empty());

			assert(!_cert.empty());
			if (_cert.empty())
				throw Poco::LogicException("RS_KeyEncryptData certificate must not be empty!", 0x45);

			assert(!_source.empty());
			
			File fi(_source);
			if (!fi.exists())
				throw Poco::FileExistsException("Source File Not Exists!", 0x40);
			
		}
		KeyEncryptByDigitalEnvelope& execute()
		{
			UDevice::default();

			///Symmetric-key algorithm by _random_digital
			///_encrypt_data = symmetric-key_algorithm(_random_digital,_source_data);
			_random_digital = SOF_GenRandom(UDevice::default().random());
			_encrypted = SOF_EncryptFile(_random_digital, _source, _encrypt);
			if(!_encrypted)
			{
				int error = SOF_GetLastError();
				throw Poco::LogicException("SOF_EncryptFile encrypt file failed!", error);
			}

			///Asymmetric_key algorithm by public cert
			///_cryptogrphic = asymmetric_key_algorithm(_cert,_random_digital);
			_cryptogrphic = SOF_AsEncrypt(_cert, _random_digital);
			if (_cryptogrphic.empty())
			{
				int error = SOF_GetLastError();
				throw Poco::LogicException("RS_KeyEncryptData failed!", error);
			}

			_cryptogrphic.append("@@@");
			_cryptogrphic.append(_cert);

			return *this;
		}

		operator std::string()
		{
			JSONStringify data;
			data.addObject("rsKey", _cryptogrphic);
			return data;
		}
	private:
		bool _encrypted;
		std::string _cert;
		std::string _source;
		std::string _encrypt;
		std::string _random_digital;
		/// _cryptogrphic(对称密钥信息流) 
		/// asymmetric_key_algorithm(_cert,_random_digital)@@@cert
		std::string _cryptogrphic;
	};

	class KeyEncryptByDigitalEnvelopeRequestHandler : public HTTPRequestHandler
	{
	public:
		void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
		{
			Application& app = Application::instance();
			app.logger().information("KeyEncryptByDigitalEnvelopeRequestHandler Request from " + request.clientAddress().toString());

			std::string data;
			HTMLForm form(request, request.stream());
			if (!form.empty()) {
				std::string SourceFile(form.get("souceFilePath", ""));
				std::string EncryptFile(form.get("encFilePath", ""));
				std::string cert(form.get("certBase64", ""));
				KeyEncryptByDigitalEnvelope command(SourceFile, EncryptFile, cert);
				data += command.execute();
			}
			return response.sendBuffer(data.data(), data.length());
		}
	};
}