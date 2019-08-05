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

	///RS_KeyDecryptByDigitalEnvelope
	class KeyDecryptByDigitalEnvelope : public Command
	{
	public:
		KeyDecryptByDigitalEnvelope(std::string& uid, std::string& EncryptFile, std::string& OutDir, std::string& cryptogrphic)
			:_uid(uid), _cryptogrphic(cryptogrphic), _encrypt(EncryptFile), _decrypt_directory(OutDir),
			_decrypted(false)
		{
			File fi(_encrypt);
			if (!fi.exists())
				throw Poco::FileNotFoundException(fi.path(), SAR_FAIL);
		}

		void run()
		{
			UDevice::default();

			std::string pattern("(\\S+)@@@(\\S+)");
			int options = 0;

			RegularExpression re(pattern, options);
			RegularExpression::Match mtch;

			if (!re.match(_cryptogrphic, mtch))
				throw Poco::LogicException("RS_KeyDecryptData enRsKey Exception!", SAR_FAIL);

			std::vector<std::string> tags;
			re.split(_cryptogrphic, tags, options);
			assert(tags.size() > 2);
			std::string& encrypt = tags[1];
			std::string& cert = tags[2];

			std::string content = SOF_ExportExChangeUserCert(_uid);

			if (content != cert)
				throw Poco::LogicException("certificate error", SAR_FAIL);

			///Asymmetric_key algorithm by private cert
			///_cryptogrphic = asymmetric_key_algorithm(_cert,_random_digital);
			_random_digital = SOF_AsDecrypt(_uid, encrypt);
			if (_random_digital.empty())
				throw RequestHandleException(SOF_GetLastError());

			///Symmetric-key algorithm by _random_digital
			///_encrypt_data = symmetric-key_algorithm(_random_digital,_source_data);
			_decrypted = SOF_DecryptFile(_random_digital, _encrypt, _decrypt_directory);
			if (!_decrypted)
				throw RequestHandleException(SOF_GetLastError());
		}
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