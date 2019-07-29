#pragma once

#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTMLForm.h"
#include "Poco/Net/NameValueCollection.h"
#include "Poco/Util/Application.h"
#include "Poco/Base64Decoder.h"
#include "Poco/StreamCopier.h"
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
	using Reach::UDevice;
	using Poco::Base64Decoder;
	using Poco::StreamCopier;
	using Reach::JSONStringify;
	

	///RS_KeyDecryptData
	class KeyDecryptData
	{
	public:
		KeyDecryptData(const std::string& uid, const std::string& encryptBuffer)
			:_uid(uid),_encrypt_data(encryptBuffer)
		{}
		KeyDecryptData& execute()
		{
			UDevice::default();

			std::string pattern("(\\S+)@@@(\\S+)");
			int options = 0;

			RegularExpression re(pattern, options);
			RegularExpression::Match mtch;

			if (!re.match(_encrypt_data, mtch))
				throw Poco::LogicException("RS_KeyDecryptData enRsKey Exception!", 0x40);

			std::vector<std::string> tags;
			re.split(_encrypt_data, tags, options);
			std::string& encrypt = tags[1];
			std::string& cert = tags[2];

			assert(tags.size() > 2);
			std::string content = SOF_ExportExChangeUserCert(_uid);

			if (content != cert)
				throw Poco::LogicException("certificate error");

			_decrypt_data = SOF_AsDecrypt(_uid, encrypt);

			std::istringstream istr(_decrypt_data);
			Base64Decoder decoder(istr);
			StreamCopier::copyToString(decoder, _text);

			return *this;
		}

		operator std::string()
		{
			if (_text.empty())
			{
				int error = SOF_GetLastError();
				JSONStringify data("unsuccessful", error);
				data.addNullObject();
				return data;
			}

			JSONStringify data;
			data.addObject("rsKey", _text);
			return data;
		}
	private:
		std::string _uid;
		std::string _encrypt_data;
		std::string _decrypt_data;
		std::string _text;
	};

	class KeyDecryptDataRequestHandler : public HTTPRequestHandler
	{
	public:
		void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
		{
			Application& app = Application::instance();
			app.logger().information("KeyDecryptDataRequestHandler Request from " + request.clientAddress().toString());
			response.set("Access-Control-Allow-Origin", "*");
			response.set("Access-Control-Allow-Methods", "GET, POST, HEAD");

			std::string data;
			HTMLForm form(request, request.stream());
			if (!form.empty()) {
				std::string uid(form.get("containerId", ""));
				std::string encryptBuffer(form.get("encRsKey", ""));
				KeyDecryptData command(uid, encryptBuffer);
				data += command.execute();
			}
			return response.sendBuffer(data.data(), data.length());
		}
	};
}