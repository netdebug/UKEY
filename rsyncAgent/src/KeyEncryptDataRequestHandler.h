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
#include <cassert>

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

	///RS_KeyEncryptData
	class KeyEncryptData
	{
	public:
		KeyEncryptData(const std::string& paintText, const std::string& base64)
			:_paintext(paintText),_base64(base64)
		{}
		KeyEncryptData& execute()
		{
			UDevice::default();

			assert(!_paintext.empty() && !_base64.empty());
			if (_paintext.empty()) return *this;
			if (_base64.empty())
				throw Poco::LogicException("RS_KeyEncryptData certificate must not be empty!", 0x45);

			std::string _encrypt_data = SOF_AsEncrypt(_base64, _paintext);
			if (_encrypt_data.empty())
			{
				int error = SOF_GetLastError();
				throw Poco::LogicException("RS_KeyEncryptData failed!", error);
			}

			_encrypt_data.append("@@@");
			_encrypt_data.append(_base64);

			return *this;
		}

		operator std::string()
		{
			JSONStringify data;
			data.addObject("encRsKey", _encrypt_data);
			return data;
		}
	private:
		std::string _base64;
		std::string _paintext;
		std::string _encrypt_data;
	};
	class KeyEncryptDataRequestHandler : public HTTPRequestHandler
	{
	public:
		void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
		{
			Application& app = Application::instance();
			app.logger().information("KeyEncryptDataRequestHandler Request from " + request.clientAddress().toString());

			std::string data;
			HTMLForm form(request, request.stream());
			if (!form.empty()) {
				std::string text(form.get("rsKey", ""));
				std::string cert(form.get("certBase64", ""));
				KeyEncryptData command(text, cert);
				data += command.execute();
			}
			return response.sendBuffer(data.data(), data.length());
		}
	};
}