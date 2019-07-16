#pragma once

#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/HTTPServerRequest.h"

namespace Reach {

	using Poco::Net::HTTPRequestHandler;
	using Poco::Net::HTTPServerRequest;
	using Poco::Net::HTTPServerResponse;

	///RS_KeyDigitalSignByP1

	class KeyDigitalSignByP1RequestHandler : public HTTPRequestHandler
	{
	public:
		void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
		{
			Application& app = Application::instance();
			app.logger().information("KeyDigitalSignByP1RequestHandler Request from " + request.clientAddress().toString());
			response.set("Access-Control-Allow-Origin", "*");
			response.set("Access-Control-Allow-Methods", "GET, POST, HEAD");

			std::string data("RS_KeyDigitalSignByP1 Not Unsupported");
			response.sendBuffer(data.data(), data.length());
		}
	};
}