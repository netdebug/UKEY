#pragma once

#include "Poco/Net/HTTPRequest.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include <sstream>

namespace Reach {

	using Poco::Net::HTTPRequest;
	using Poco::Net::HTTPServerRequest;
	using Poco::Net::HTTPServerResponse;

	class EchoHeaderRequestHandler : public HTTPRequestHandler
	{
	public:
		void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
		{
			std::ostringstream osstr;
			request.write(osstr);
			int n = (int)osstr.str().length();
			response.setContentLength(n);
			std::ostream& ostr = response.send();
			if (request.getMethod() != HTTPRequest::HTTP_HEAD)
				request.write(ostr);
		}
	};
}