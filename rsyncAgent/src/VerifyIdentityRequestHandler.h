#pragma once

#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTMLForm.h"
#include "Poco/Net/NameValueCollection.h"
#include "Poco/Util/Application.h"
#include "UDevice.h"
#include "JSONStringify.h"
#include "GMCrypto.h"
#include "SoFProvider.h"

namespace Reach {

	using Poco::Net::HTTPRequestHandler;
	using Poco::Net::HTTPServerRequest;
	using Poco::Net::HTTPServerResponse;
	using Poco::Net::HTMLForm;
	using Poco::Net::NameValueCollection;
	using Poco::Util::Application;
	using Reach::UDevice;
	using Reach::JSONStringify;

	///RS_VerifyIdentity
	class VerifyIdentity
	{
	public:
		VerifyIdentity()
		{}
		VerifyIdentity& execute()
		{
			return *this;
		}
	
		operator std::string()
		{
			return "";
		}
	};
	class VerifyIdentityRequestHandler : public HTTPRequestHandler
	{
	public:
		void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
		{
			Application& app = Application::instance();
			app.logger().information("VerifyIdentityRequestHandler Request from " + request.clientAddress().toString());
			response.set("Access-Control-Allow-Origin", "*");
			response.set("Access-Control-Allow-Methods", "GET, POST, HEAD");

			std::string data;
			HTMLForm form(request, request.stream());
			if (!form.empty()) {
				VerifyIdentity command;
				data += command.execute();
			}
			return response.sendBuffer(data.data(), data.length());
		}
	};
}