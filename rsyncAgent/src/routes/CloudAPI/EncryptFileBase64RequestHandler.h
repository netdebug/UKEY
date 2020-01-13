#pragma once
#include "CloudCommand.h"
#include "../Command.h"
#include "../RESTfulRequestHandler.h"
#include "Poco/Util/Application.h"
#include "Poco/FileStream.h"
#include "Poco/StreamCopier.h"
#include "../src/Utility.h"
namespace Reach {
	using Poco::Util::Application;

	class EncryptFilebase64 : public Command
	{
	public:
		EncryptFilebase64(const std::string& source, const std::string& encrypt, const std::string& base64)
			:_base64(base64)
			,_source(source)
			,_encrypt(encrypt)
		{

		}
		void run() {
			// pubkey 改成从base64公钥中获取
			std::string pubkey = _base64;
			std::string PEM;
			PEM.append("-----BEGIN CERTIFICATE-----\n");
			PEM.append(Utility::cat("\n", 64, _base64));
			PEM.append("-----END CERTIFICATE-----\n");
			std::istringstream certStream(PEM);
			X509Certificate a(certStream);
			const X509* x509 = a.certificate();
			ASN1_BIT_STRING* pubkeyval;
			pubkeyval = X509_get0_pubkey_bitstr(x509);
			int nlen = pubkeyval->length;
			unsigned char* val = pubkeyval->data;

			std::stringstream str;
			HexBinaryEncoder encoder(str);
			encoder.write((const char*)val, nlen);
			encoder.close();
			std::string upperstr = Poco::toUpper(str.str());
			Poco::FileInputStream SI(_source);
			std::string data;
			Poco::StreamCopier::copyToString(SI, data);

			std::string ciphertext = Utility::v_encrypt_by_sm2(data, upperstr);
			Poco::FileOutputStream out(_encrypt);
			out.write(ciphertext.data(), ciphertext.size());
			out.close();

			//add("signCertBase64", extract("body", "signCertBase64"));
			//add("encCertBase64", extract("body", "encCertBase64"));
		}

	private:
		std::string _source;
		std::string _encrypt;
		std::string _base64;
	};
	class EncryptFileBase64RequestHandler : public RESTfulRequestHandler
	{
	public:
		void handleRequest(HTTPServerRequest& request, HTTPServerResponse& respone) {

			Application& app = Application::instance();
			poco_information_f1(app.logger(), "Request from %s", request.clientAddress().toString());
			RESTfulRequestHandler::handleCORS(request, respone);

			HTMLForm form(request, request.stream());
			std::string source = form.get("souceFilePath", "");
			std::string encrypt = form.get("encFilePath", "");
			std::string base64 = form.get("certBase64", "");
			EncryptFilebase64 command(source, encrypt, base64);
			command.execute();

			return respone.sendBuffer(command().data(), command().length());
		}

	};
}