#pragma once
#include "../Command.h"
#include "Poco/Logger.h"
#include "CloudCommand.h"
#include "../RESTfulRequestHandler.h"
#include "Poco/Util/Application.h"
#include "../src/Utility.h"
#include "Poco/Crypto/RSAKey.h"
#include <iosfwd>
#include "Poco/StringTokenizer.h"
#include "Poco/Base64Decoder.h"
#include "Poco/HexBinaryDecoder.h"
#include "Poco/Base64Encoder.h"
#include "Reach/Data/FJCA/FJCA_FUN_GT_DLL.h"
#include "Poco/HexBinaryEncoder.h"
#include "Poco/Crypto/EVPPKey.h"
#include "openssl/ossl_typ.h"
#include "Poco/Crypto/ECKey.h"


namespace Reach {
	using Poco::Util::Application;
	using Poco::Crypto::RSAKey;
	using Poco::StringTokenizer;
	using Poco::HexBinaryEncoder;
	using Poco::Base64Decoder;
	using Poco::Crypto::EVPPKey;
	using Poco::Crypto::ECKey;
	//RS_EncryptData
	class EncryptData : public Command
	{
	public:
		EncryptData(const std::string& symKey, std::string& certBase64)
			:_symkey(symKey),
			_certbase64(certBase64)
		{

		}
		~EncryptData() {

		}
		virtual void run()
		{
			std::string source(_symkey);
			std::string PEM;
			PEM.append("-----BEGIN CERTIFICATE-----\n");
			PEM.append(Utility::cat("\n", 64, _certbase64));
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
			std::string ciphertext;
			std::string upperstr = Poco::toUpper(str.str());
			ciphertext = Utility::v_encrypt_by_sm2(source, upperstr);

			add("encReachKey", ciphertext);
		}
		virtual void mixValue() {

		}
		
	protected:

	private:
		std::string _symkey;
		std::string _certbase64;
	};
	class EncryptDataBase64RequestHandler : public RESTfulRequestHandler
	{
	public:
		void handleRequest(HTTPServerRequest& request, HTTPServerResponse& respone) {

			Application& app = Application::instance();
			poco_information_f1(Application::instance().logger(), "Request from %s", request.clientAddress().toString());

			HTMLForm form(request, request.stream());
			std::string symKey(form.get("symKey", ""));
			std::string certBase64(form.get("certBase64", ""));

			EncryptData command(symKey, certBase64);
			command.execute();

			return respone.sendBuffer(command().data(), command().length());
		}
	};
}