#include "RequestHandlerFactory.h"
#include "EchoBodyRequestHandler.h"
#include "EchoHeaderRequestHandler.h"
#include "RedirectRequestHandler.h"
#include "AuthRequestHandler.h"
#include "BufferRequestHandler.h"
#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPServerRequest.h"


using namespace Reach;

using Poco::Net::HTTPRequestHandler;
using Poco::Net::HTTPServerRequest;

HTTPRequestHandler * Reach::RequestHandlerFactory::createRequestHandler(const HTTPServerRequest & request)
{

	if (request.getURI() == "/echoBody")
		return new EchoBodyRequestHandler;
	else if (request.getURI() == "/echoHeader")
		return new EchoHeaderRequestHandler;
	else if (request.getURI() == "/redirect")
		return new RedirectRequestHandler();
	else if (request.getURI() == "/auth")
		return new AuthRequestHandler();
	else if (request.getURI() == "/buffer")
		return new BufferRequestHandler();
	else
		return 0;
}
