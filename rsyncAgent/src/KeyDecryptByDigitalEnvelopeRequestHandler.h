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

	///RS_KeyDecryptByDigitalEnvelope
	class KeyDecryptByDigitalEnvelope
	{
	public:
		KeyDecryptByDigitalEnvelope(std::string& uid, std::string& EncryptFile, std::string& OutDir, std::string& cryptogrphic)
			:_uid(uid),_cryptogrphic(cryptogrphic),_encrypt(EncryptFile), _decrypt_directory(OutDir)
		{
			File fi(_encrypt);
			if (!fi.exists())
				throw Poco::FileExistsException("Encrypt File was not existd!", 0x40);

		}
		KeyDecryptByDigitalEnvelope& execute()
		{
			UDevice::default();

			std::string pattern("(\\S+)@@@(\\S+)");
			int options = 0;

			RegularExpression re(pattern, options);
			RegularExpression::Match mtch;

			if (!re.match(_cryptogrphic, mtch))
				throw Poco::LogicException("RS_KeyDecryptData enRsKey Exception!", 0x40);

			std::vector<std::string> tags;
			re.split(_cryptogrphic, tags, options);
			std::string& encrypt = tags[1];
			std::string& cert = tags[2];

			assert(tags.size() > 2);
			std::string content = SOF_ExportExChangeUserCert(_uid);

			if (content != cert)
				throw Poco::LogicException("certificate error");

			///Asymmetric_key algorithm by private cert
			///_cryptogrphic = asymmetric_key_algorithm(_cert,_random_digital);
			std::string _random_digital = SOF_AsDecrypt(_uid, encrypt);
			assert(!_random_digital.empty());
			if (_random_digital.empty())
			{
				int error = SOF_GetLastError();
				throw Poco::LogicException("SOF_AsDecrypt decrypt Exception", error);
			}

			///Symmetric-key algorithm by _random_digital
			///_encrypt_data = symmetric-key_algorithm(_random_digital,_source_data);
			if (!SOF_DecryptFile(_random_digital, _encrypt, _decrypt_directory))
			{
				int error = SOF_GetLastError();
				throw Poco::LogicException("SOF_DecryptFile decrypt file failed!", error);
			}

			return *this;
		}

		operator std::string()
		{
			JSONStringify data;
			data.addNullObject();
			return data;
		}
	private:
		std::string _uid;
		/// _cryptogrphic(对称密钥信息流)
		/// asymmetric_key_algorithm(_cert,_random_digital)@@@cert
		std::string _cryptogrphic;
		std::string _encrypt;
		std::string _decrypt_directory;
		std::string _random_digital;
	};

	class KeyDecryptByDigitalEnvelopeRequestHandler : public HTTPRequestHandler
	{
	public:
		void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
		{
			Application& app = Application::instance();
			app.logger().information("VerifyIdentityRequestHandler Request from " + request.clientAddress().toString());

			std::string data;
			HTMLForm form(request, request.stream());
			if (!form.empty()) {
				std::string uid(form.get("containerId", ""));
				std::string cryptogrphic(form.get("encRsKeyPath", ""));
				std::string EncryptFile(form.get("encFilePath", ""));
				std::string OutDir(form.get("dncDirectory", ""));
				KeyDecryptByDigitalEnvelope command(uid, EncryptFile, OutDir, cryptogrphic);
				data += command.execute();
			}
			return response.sendBuffer(data.data(), data.length());
		}
	};
}