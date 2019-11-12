#pragma once

#include "Poco/Util/Application.h"
#include "Poco/Net/HTTPClientSession.h"
#include "Poco/URI.h"
#include "Poco/JSON/Parser.h"
#include "Poco/DynamicStruct.h"
#include "Poco/JSON/Object.h"
#include "Poco/FileStream.h"
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

	///RS_CloudEncryptFile
	class CloudEncryptFile : public Command, public CloudCommand
	{
	public:
		CloudEncryptFile(const std::string& source, const std::string& encrypt, const std::string& transid, const std::string& token, const std::string& url) :
			CloudCommand(url),
			_source(source),
			_encrypt(encrypt),
			_transid(transid),
			_token(token),
			_action("")
		{
		}

		void run()
		{
			mixValue();
			sendRequest();

			if (!success())
				throw CloudCommandException(extract("head", "message"),
					std::stoi(extract("head", "code"), 0, 16));

			std::string pubkey = extract("body","pubkey");

			Poco::FileInputStream SI(_source);
			std::string data;
			Poco::StreamCopier::copyToString(SI, data);
			//external_encrypt(data, pubkey);
			Poco::FileOutputStream out(_encrypt);
			out.write(encyptdata.data(), encyptdata.size());
			out.close();

			add("signCertBase64", extract("signCertBase64"));
			add("encCertBase64", extract("encCertBase64"));
		}
	protected:
		/*void external_encrypt(std::string& source, const std::string& pubkey)
		{
			Application& app = Application::instance();

			std::istringstream iPub(pubkey);
			Poco::Crypto::ECKey ek(&iPub);
			size_t outlen = 512;
			Poco::Buffer<unsigned char> encrypt(outlen); encrypt.clear();

			if (!SM2_encrypt_with_recommended((unsigned char*)source.data(), source.size(), encrypt.begin(), &outlen,
				ek.impl()->getECKey())) {
				if (outlen > encrypt.capacity())
				{
					encrypt.resize(outlen, false);
					SM2_encrypt_with_recommended((unsigned char*)source.data(), source.size(), encrypt.begin(), &outlen,
						ek.impl()->getECKey());
				}
				else
					poco_information_f1(app.logger(), "%s", getOpenSSLError());
			}

			std::string enc((const char*)encrypt.begin(), encrypt.size());
			poco_information_f2(app.logger(), "encryptSM2,\n %s \n len:%u", enc, enc.length());

			encyptdata = enc;
		}*/
		virtual void mixValue()
		{
			Application& app = Application::instance();
			FileInputStream in(app.config().getString("cloudconfigdir","")+"CloudEncryptFile.json");
			DynamicStruct ds = *parse(in).extract<Object::Ptr>();
			ds["bodyJson"]["token"] = _token;
			ds["bodyJson"]["transid"] = _transid;

			ds["bodyJson"]["authCode"] = app.config().getString("authCode", "");
			ds["body"] = ds["bodyJson"].toString();
			ds.erase("bodyJson");

			prepare(ds.toString());
			poco_information_f1(app.logger(), "CloudEncryptFile mixValue:\n%s", ds.toString());
		}
		std::string getOpenSSLError()
		{
			BIO *bio = BIO_new(BIO_s_mem());
			ERR_print_errors(bio);
			char *buf;
			size_t len = BIO_get_mem_data(bio, &buf);
			std::string ret(buf, len);
			BIO_free(bio);
			return ret;
		}
	private:
		std::string _source;
		std::string _encrypt;
		std::string _transid;
		std::string _token;
		std::string _action;
		std::string _symKey;

		std::string encyptdata;
	};

	class CloudEncryptFileRequestHandler : public RESTfulRequestHandler
	{
	public:
		void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
		{
			Application& app = Application::instance();
			poco_information_f1(app.logger(), "Request from %s", request.clientAddress().toString());
			RESTfulRequestHandler::handleCORS(request, response);

			HTMLForm form(request, request.stream());
			std::string source = form.get("souceFilePath", "");
			std::string encrypt = form.get("encFilePath", "");
			std::string transid = form.get("transid", "");
			std::string token = form.get("token", "");
			std::string url = app.config().getString("rsigncloudTest");
			CloudEncryptFile command(source, encrypt, transid, token, url);
			command.execute();

			return response.sendBuffer(command().data(), command().length());
		}
	};
}