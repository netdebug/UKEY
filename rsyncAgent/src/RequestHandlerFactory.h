#pragma once

#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPRequestHandlerFactory.h"

namespace Reach {

	using Poco::Net::HTTPServerRequest;
	using Poco::Net::HTTPRequestHandler;
	using Poco::Net::HTTPRequestHandlerFactory;

	class RequestHandlerFactory : public HTTPRequestHandlerFactory
	{
	public:
		HTTPRequestHandler* createRequestHandler(const HTTPServerRequest& request);
	};
}