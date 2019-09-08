#pragma once

#include "Command.h"
#include "RESTfulRequestHandler.h"
#include "Poco/Util/Application.h"

using Poco::Util::Application;

namespace Reach {
	///RS_KeyEncryptByDigitalEnvelope
	class KeyEncryptByDigitalEnvelope : public Command
	{
	public:
		KeyEncryptByDigitalEnvelope(const std::string& SourceFile, const std::string& EncryptFile, std::string cert);
		virtual void run();

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