#pragma once

#include "Poco/Util/Application.h"
#include "Poco/Net/HTTPClientSession.h"
#include "Poco/URI.h"
#include "Poco/JSON/Parser.h"
#include "Poco/DynamicStruct.h"
#include "Poco/JSON/Object.h"
#include "Poco/FileStream.h"
#include "../src/Utility.h"
#include "../Command.h"
#include "../RESTfulRequestHandler.h"
#include "CloudCommand.h"

namespace Reach {

	using Poco::Util::Application;
	using Poco::URI;
	using Poco::JSON::Parser;
	using Poco::JSON::Object;
	using Poco::DynamicStruct;
	using Poco::FileInputStream;

	///RS_CloudEncryptData
	class CloudEncryptData : public Command, public CloudCommand
	{
	public:
		CloudEncryptData(const std::string& symKey, const std::string& transid, const std::string& token, const std::string& url) :
			CloudCommand(url),
			_symKey(symKey),
			_transid(transid),
			_token(token),
			_action("")
		{
			g_pubkey = ""
				"-----BEGIN PUBLIC KEY-----\r\n"
				"MFkwEwYHKoZIzj0CAQYIKoEcz1UBgi0DQgAEPCU4B2kPThX/gOk+dCAm6opsi5VZ\r\n"
				"UadwGvIWe10HWOm8pTZRpv+Akb6HhJpnyITTMvnFWQ36ebVSexU7KJSZtA==\r\n"
				"-----END PUBLIC KEY-----\r\n"
				"";

			g_prikey = ""
				"-----BEGIN EC PRIVATE KEY-----\r\n"
				"Proc-Type: 4,ENCRYPTED\r\n"
				"DEK-Info: SMS4-CBC,A9B7D7B184D261B5F157B7A5173C0498\r\n"
				"\r\n"
				"llSyh1hIYx2956hVEzZvYSbApSQXOHGl3KS/+vwq9WxDZi+eWgIMu5f9pXcKJLV2\r\n"
				"5tw1etHVhVsvVskZ1ZYJ5RjdjX9Kvqw7YAWSdWduB72lWSvW9PUgNhliTRoqbe44\r\n"
				"i0j5E1iJRaUd+c9eGE6l6kswOBTjI0bZ9FTMg6bqjZ8=\r\n"
				"-----END EC PRIVATE KEY-----\r\n"
				"";
			g_fjprikey = ""
				"ASN1 OID: sm2p256v1\r\n"
				"NIST CURVE: SM2\r\n"
				"-----BEGIN EC PARAMETERS-----\r\n"
				"BggqgRzPVQGCLQ==\r\n"
				"-----END EC PARAMETERS-----\r\n"
				"-----BEGIN EC PRIVATE KEY-----\r\n"
				"MHcCAQEEIK2E4tOTtBhl5e8aD08bJBIwpV5POeyBqgQSjo3bKFByoAoGCCqBHM9V\r\n"
				"AYItoUQDQgAE/816jFNfcn7lfLfUUkhp3PWu1R7BhGobujB+856XKVRVlBPrLU2L\r\n"
				"AlZBUs/HEGkAAGcE4j4yxnfrE6gKCYeJbQ==\r\n"
				"-----END EC PRIVATE KEY-----\r\n"
				"";
			privateKeyPassphrase = "Fjreach";
		}
		void run()
		{
#ifdef TEST
			std::string source(_symKey);
			v_encrypt_by_sm2(std::string("standard encryption"), "0420F19FF762F0CC0EE77243FF76E02657E6596A4F9CD74A671BA862A485441051ED415A59DA78D5D087AFCB2EF12DF99561FB658B11645D3F92C4CA638730BA05");
			add("encReachKey", ciphertext);
			add("signCertBase64", "signCertBase64");
			add("encCertBase64", "encCertBase64");
#else
			mixValue();
			sendRequest();

			if (!success())
				throw CloudCommandException(extract("head", "message"),
					std::stoi(extract("head", "code"), 0, 16));

			std::string source(_symKey);
			std::string pubkey(extract("body", "pubkey"));
			std::string ciphertext = Utility::v_encrypt_by_sm2(source, pubkey);

			add("encReachKey", ciphertext);
			add("signCertBase64", extract("body", "signCertBase64"));
			add("encCertBase64", extract("body", "encCertBase64"));
#endif // TEST	
		}
	protected:

		virtual void mixValue()
		{
			Application& app = Application::instance();
			FileInputStream in(Utility::config("config\\CloudEncryptData.json"));
			DynamicStruct ds = *parse(in).extract<Object::Ptr>();
			ds["bodyJson"]["token"] = _token;
			ds["bodyJson"]["transid"] = _transid;

			ds["bodyJson"]["authCode"] = app.config().getString("authCode", "");
			ds["body"] = ds["bodyJson"].toString();
			ds.erase("bodyJson");

			prepare(ds.toString());
			poco_information_f1(app.logger(), "CloudEncryptData mixValue:\n%s", ds.toString());
		}
		

	private:
		std::string _symKey;
		std::string _transid;
		std::string _token;
		std::string _action;
		std::string _msg;

		std::string g_pubkey;
		std::string g_prikey;
		std::string privateKeyPassphrase;
		std::string g_fjprikey;
	};

	class CloudEncryptDataRequestHandler : public RESTfulRequestHandler
	{
	public:
		void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
		{
			Application& app = Application::instance();
			poco_information_f1(app.logger(), "Request from %s", request.clientAddress().toString());
			RESTfulRequestHandler::handleCORS(request, response);

			HTMLForm form(request, request.stream());
			std::string symKey = form.get("symKey", "");
			std::string transid = form.get("transid", "");
			std::string token = form.get("token", "");
			std::string url = app.config().getString("rsigncloud");
			CloudEncryptData command(symKey, transid, token, url);
			command.execute();

			return response.sendBuffer(command().data(), command().length());
		}
	};
}