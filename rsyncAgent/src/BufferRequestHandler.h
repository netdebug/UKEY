#pragma once

#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Logger.h"
#include "Poco/Util/Application.h"
#include "routes/RESTfulRequestHandler.h"

namespace Reach {

	using Poco::Util::Application;

	class BufferRequestHandler : public RESTfulRequestHandler
	{
	public:
		void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
		{
			poco_information_f1(Application::instance().logger(), "Request from %s", request.clientAddress().toString());

			RESTfulRequestHandler::handleCORS(request, response);

			std::string data("buffer request is deprecate!");
			response.sendBuffer(data.data(), data.length());
		}
	};
}