#pragma once

#include "UDevice.h"
#include "SoFProvider.h"
#include "SOFErrorCode.h"
#include "Command.h"
#include "RESTfulRequestHandler.h"
#include "RequestHandleException.h"
#include "Poco/Util/Application.h"
#include "Poco/File.h"

namespace Reach {

	using Poco::Util::Application;
	using Poco::File;

	///RS_KeyEncryptByDigitalEnvelope
	class KeyEncryptByDigitalEnvelope : public Command
	{
	public:
		KeyEncryptByDigitalEnvelope(const std::string& SourceFile, const std::string& EncryptFile, std::string cert)
			:_source(SourceFile), _encrypt(EncryptFile), _cert(cert),
			_encrypted(false), _random_digital(""), _cryptogrphic("")
		{
			if (_cert.empty())
				throw RequestHandleException(_cert, RAR_ERRENCRYPTBASE64CERT);

			File fi(_source);
			if (!fi.exists())
				throw RequestHandleException(fi.path(), RAR_ERRNOENCRYPT);

		}

		void run()
		{
			UDevice::default();

			///Symmetric-key algorithm by _random_digital
			///_encrypt_data = symmetric-key_algorithm(_random_digital,_source_data);
			_random_digital = SOF_GenRandom(UDevice::default().random());
			_encrypted = SOF_EncryptFile(_random_digital, _source, _encrypt);
			if (!_encrypted)
				throw Poco::LogicException("SOF_EncryptFile failed!", SOF_GetLastError());

			///Asymmetric_key algorithm by public cert
			///_cryptogrphic = asymmetric_key_algorithm(_cert,_random_digital);
			_cryptogrphic = SOF_AsEncrypt(_cert, _random_digital);
			if (_cryptogrphic.empty()) {
				throw RequestHandleException("SOF_AsEncrypt failed!", RAR_ENCYPTFAILED);
			}

			_cryptogrphic.append("@@@");
			_cryptogrphic.append(_cert);

			add("rsKey", _cryptogrphic);
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

	class KeyEncryptByDigitalEnvelopeRequestHandler : public RESTfulRequestHandler
	{
	public:
		void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
		{
			poco_information_f1(Application::instance().logger(), "Request from %s", request.clientAddress().toString());

			RESTfulRequestHandler::handleCORS(request, response);

			HTMLForm form(request, request.stream());
			std::string SourceFile(form.get("souceFilePath", ""));
			std::string EncryptFile(form.get("encFilePath", ""));
			std::string cert(form.get("certBase64", ""));

			KeyEncryptByDigitalEnvelope command(SourceFile, EncryptFile, cert);
			command.execute();

			return response.sendBuffer(command().data(), command().length());
		}
	};
}