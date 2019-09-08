#pragma once

#include "Command.h"
#include "RESTfulRequestHandler.h"
#include "Poco/Util/Application.h"

using Poco::Util::Application;

namespace Reach {
	///RS_KeyDecryptByDigitalEnvelope
	class KeyDecryptByDigitalEnvelope : public Command
	{
	public:
		KeyDecryptByDigitalEnvelope(std::string& uid, std::string& EncryptFile, std::string& OutDir, std::string& cryptogrphic);
		virtual void run();
	private:
		std::string _uid;
		/// _cryptogrphic(对称密钥信息流)
		/// asymmetric_key_algorithm(_cert,_random_digital)@@@cert
		std::string _cryptogrphic;
		std::string _encrypt;
		std::string _decrypt_directory;
		std::string _random_digital;
		bool _decrypted;
	};

	class KeyDecryptByDigitalEnvelopeRequestHandler : public RESTfulRequestHandler
	{
	public:
		void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
		{
			poco_information_f1(Application::instance().logger(), "Request from %s", request.clientAddress().toString());

			RESTfulRequestHandler::handleCORS(request, response);

			HTMLForm form(request, request.stream());
			std::string uid(form.get("containerId", ""));
			std::string cryptogrphic(form.get("encRsKeyPath", ""));
			std::string EncryptFile(form.get("encFilePath", ""));
			std::string OutDir(form.get("dncDirectory", ""));

			KeyDecryptByDigitalEnvelope command(uid, EncryptFile, OutDir, cryptogrphic);
			command.execute();

			return response.sendBuffer(command().data(), command().length());
		}
	};
}