#pragma once

#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTMLForm.h"
#include "Poco/Net/NameValueCollection.h"
#include "Poco/Util/Application.h"
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
	using Reach::JSONStringify;

	class OpenDevice
	{
	public:
		OpenDevice(){}
		OpenDevice& execute()
		{
			_status = SOF_OpenDevice();
			return *this;
		}
		operator std::string()
		{
			if (_status != 0 ) {
				int error = SOF_GetLastError();
				JSONStringify data("unsuccessful", error);
				data.addNullObject();
				return data;
			}

			JSONStringify data("successful", _status);
			data.addNullObject();
			return data;
		}
	private:
		std::string _line;
		int _status;
	};

	class extOpenDeviceRequestHandler : public HTTPRequestHandler
	{
	public:
		void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
		{
			Application& app = Application::instance();
			app.logger().information("extOpenDeviceRequestHandler Request from " + request.clientAddress().toString());
			response.set("Access-Control-Allow-Origin", "*");
			response.set("Access-Control-Allow-Methods", "GET, POST, HEAD");

			std::string data;
			OpenDevice command;
			data += command.execute();

			return response.sendBuffer(data.data(), data.length());
		}
	};
}