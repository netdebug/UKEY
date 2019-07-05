#pragma once

#include "Poco/Net/HTTPMessage.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/StreamCopier.h"
#include <iostream>

namespace Reach {

	using Poco::StreamCopier;
	using Poco::Net::HTTPMessage;
	using Poco::Net::HTTPServerResponse;

	class EchoBodyRequestHandler : public HTTPRequestHandler
	{
	public:
		void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
		{
			if (request.getChunkedTransferEncoding())
				response.setChunkedTransferEncoding(true);
			else if (request.getContentLength() != HTTPMessage::UNKNOWN_CONTENT_LENGTH)
				response.setContentLength(request.getContentLength());

			response.setContentType(request.getContentType());

			std::istream& istr = request.stream();
			std::ostream& ostr = response.send();
			StreamCopier::copyStream(istr, ostr);
		}
	};
}