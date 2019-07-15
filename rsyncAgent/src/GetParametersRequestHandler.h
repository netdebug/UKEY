#pragma once

#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTMLForm.h"
#include "Poco/Net/NameValueCollection.h"
#include "Poco/Util/Application.h"

namespace Reach {

	using Poco::Net::HTTPRequestHandler;
	using Poco::Net::HTTPServerRequest;
	using Poco::Net::HTTPServerResponse;
	using Poco::Net::HTMLForm;
	using Poco::Net::NameValueCollection;
	using Poco::Util::Application;

	///RS_GetParameters
	class GetParameters
	{
	public:
		GetParameters(const std::string& cmd){}
		GetParameters& execute()
		{
			return *this;
		}
		operator std::string()
		{
			return "GetParameters Not Implmented!";
		}
	};

	class GetParametersRequestHandler : public HTTPRequestHandler
	{
	public:
		void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
		{
			Application& app = Application::instance();
			app.logger().information("GetParameters Request from " + request.clientAddress().toString());

			std::string data;
			HTMLForm form(request, request.stream());
			if (!form.empty()) {
				std::string cmd = form.get("cmd", "");
				GetParameters command(cmd);
				data += command.execute();
				return response.sendBuffer(data.data(), data.length());
			}
			return response.sendBuffer(data.data(), data.length());
		}
	};
}