#pragma once

#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/HTTPServerRequest.h"

namespace Reach {

	using Poco::Net::HTTPRequestHandler;
	using Poco::Net::HTTPServerRequest;
	using Poco::Net::HTTPServerResponse;

	///RS_KeyGetKeySn
	class KeyGetKeySn
	{
	public:
		KeyGetKeySn(const std::string& uid)
			:_uid(uid)
		{}
		KeyGetKeySn& execute()
		{
			UDevice::default();

			_SNkey = SOF_GetDeviceInfo(_uid, SGD_DEVICE_SERIAL_NUMBER);

			if (_SNkey.empty())
			{
				int error = SOF_GetLastError();
				throw Poco::LogicException("SOF_GetDeviceInfo Not Get UKEY SN", error);
			}

			return *this;
		}

		operator std::string()
		{
			JSONStringify data;
			data.addObject("containerId", _uid);
			data.addObject("keySn", _SNkey);
			return data;
		}
	private:
		std::string _uid;
		std::string _SNkey;
	};

	class KeyGetKeySnRequestHandler : public HTTPRequestHandler
	{
	public:
		void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
		{
			Application& app = Application::instance();
			app.logger().information("KeyGetKeySnRequestHandler Request from " + request.clientAddress().toString());
			response.set("Access-Control-Allow-Origin", "*");
			response.set("Access-Control-Allow-Methods", "GET, POST, HEAD");

			std::string data;
			HTMLForm form(request, request.stream());
			if (!form.empty()) {
				std::string uid(form.get("containerId", ""));
				KeyGetKeySn command(uid);
				data += command.execute();
			}
			return response.sendBuffer(data.data(), data.length());
		}
	};
}