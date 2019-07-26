#pragma once

#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/JSON/Object.h"
#include "Poco/JSON/Query.h"
#include "Poco/Dynamic/Var.h"
#include "Poco/NumberFormatter.h"
#include "Poco/DynamicStruct.h"

namespace Reach {

	using Poco::Net::HTTPRequestHandler;
	using Poco::Net::HTTPServerRequest;
	using Poco::Net::HTTPServerResponse;
	using Poco::JSONOptions;
	using Poco::JSON::Object;
	using Poco::JSON::Query;
	using Poco::JSON::Array;
	using Poco::Dynamic::Var;
	using Poco::NumberFormatter;
	using Poco::DynamicStruct;

	class BufferRequestHandler : public HTTPRequestHandler
	{
	public:
		void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
		{
			std::string data;
			std::ostringstream out;

			Array A(JSONOptions::JSON_PRESERVE_KEY_ORDER);
			A.add("USB\\VID_093A&PID_2510\\5&38e97a59&0&4");
			A.add("USB\\VID_6588&PID_1514\\5&38e97a59&0&10");
	
			A.stringify(out);
			data = out.str();
			response.sendBuffer(data.data(), data.length());
		}
	};
}