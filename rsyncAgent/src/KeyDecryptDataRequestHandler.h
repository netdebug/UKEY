#pragma once

#include "UDevice.h"
#include "SoFProvider.h"
#include "SOFErrorCode.h"
#include "Command.h"
#include "RESTfulRequestHandler.h"
#include "RequestHandleException.h"
#include "Poco/Util/Application.h"
#include "Poco/Base64Decoder.h"
#include "Poco/StreamCopier.h"

namespace Reach {

	using Poco::Util::Application;
	using Poco::Base64Decoder;
	using Poco::StreamCopier;


	///RS_KeyDecryptData
	class KeyDecryptData : public Command
	{
	public:
		KeyDecryptData(const std::string& uid, const std::string& encryptBuffer)
			:_uid(uid), _encrypt_data(encryptBuffer)
		{}
		void run()
		{
			UDevice::default();

			std::string pattern("(\\S+)@@@(\\S+)");
			int options = 0;

			RegularExpression re(pattern, options);
			RegularExpression::Match mtch;

			if (!re.match(_encrypt_data, mtch))
				throw RequestHandleException("KeyDecryptData enRsKey Exception!", RAR_ERRDECRYPTFILEFORMAT);

			std::vector<std::string> tags;
			re.split(_encrypt_data, tags, options);
			std::string& encrypt = tags[1];
			std::string& cert = tags[2];

			assert(tags.size() > 2);
			std::string content = SOF_ExportExChangeUserCert(_uid);

			if (content != cert)
				throw RequestHandleException("certificate error", RAR_ERRDECRYPTCERT);

			_decrypt_data = SOF_AsDecrypt(_uid, encrypt);
			if (_decrypt_data.empty())
				throw RequestHandleException(RAR_DECRYPTFAILED);

			std::istringstream istr(_decrypt_data);

			Base64Decoder decoder(istr);
			StreamCopier::copyToString(decoder, _text);

			add("rsKey", _text);
		}

	private:
		std::string _uid;
		std::string _encrypt_data;
		std::string _decrypt_data;
		std::string _text;
	};

	class KeyDecryptDataRequestHandler : public RESTfulRequestHandler
	{
	public:
		void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
		{
			poco_information_f1(Application::instance().logger(), "Request from %s", request.clientAddress().toString());

			RESTfulRequestHandler::handleCORS(request, response);

			HTMLForm form(request, request.stream());
			std::string uid(form.get("containerId", ""));
			std::string encryptBuffer(form.get("encRsKey", ""));

			KeyDecryptData command(uid, encryptBuffer);
			command.execute();

			return response.sendBuffer(command().data(), command().length());
		}
	};
}