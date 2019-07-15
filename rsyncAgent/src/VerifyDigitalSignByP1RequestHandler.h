#pragma once

#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/HTTPServerRequest.h"

namespace Reach {

	using Poco::Net::HTTPRequestHandler;
	using Poco::Net::HTTPServerRequest;
	using Poco::Net::HTTPServerResponse;

	class VerifyDigitalSignByP1RequestHandler : public HTTPRequestHandler
	{
	public:
		void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
		{
			std::string data("VerifyDigitalSignByP1RequestHandler");
			response.sendBuffer(data.data(), data.length());
		}
	};
}