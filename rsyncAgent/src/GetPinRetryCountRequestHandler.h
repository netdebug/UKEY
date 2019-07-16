#pragma once

#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/HTTPServerRequest.h"

namespace Reach {

	using Poco::Net::HTTPRequestHandler;
	using Poco::Net::HTTPServerRequest;
	using Poco::Net::HTTPServerResponse;

	///RS_GetPinRetryCount
	class GetPinRetryCount
	{
	public:
		GetPinRetryCount(const std::string& uid)
			:_uid(uid)
		{}
		GetPinRetryCount& execute()
		{
			UDevice::default();

			_retryCount = SOF_GetPinRetryCount(_uid);

			return *this;
		}

		operator std::string()
		{
			JSONStringify data;
			data.addObject("retryCount", _retryCount);
			return data;
		}
	private:
		int _retryCount;
		std::string _uid;
	};
	class GetPinRetryCountRequestHandler : public HTTPRequestHandler
	{
	public:
		void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
		{
			Application& app = Application::instance();
			app.logger().information("GetPinRetryCountRequestHandler Request from " + request.clientAddress().toString());
			response.set("Access-Control-Allow-Origin", "*");
			response.set("Access-Control-Allow-Methods", "GET, POST, HEAD");

			std::string data;
			HTMLForm form(request, request.stream());
			if (!form.empty()) {
				std::string uid(form.get("containerId", ""));
				GetPinRetryCount command(uid);
				data += command.execute();
			}
			return response.sendBuffer(data.data(), data.length());
		}
	};
}