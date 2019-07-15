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

	///RS_GetUserList
	///example
	///		{
	///			"code":"0000",
	///				"msg" : "Ö´ÐÐ³É¹¦",
	///				"data" : {
	///				"userlist":"BJCA-Application||806000119631708&&&BJCA-Application||806000119631714"
	///			}
	///		}

	class GetUserList
	{
	public:
		GetUserList(){}
		GetUserList& execute()
		{
			UDevice::default();
			_line = SOF_GetUserList();
			return *this;
		}
		operator std::string()
		{
			JSONStringify data;
			data.addObject("userlist", _line);
			return data;
		}
	private:
		std::string _line;
	};

	class GetUserListRequestHandler : public HTTPRequestHandler
	{
	public:
		void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
		{
			Application& app = Application::instance();
			app.logger().information("GetUserListRequestHandler Request from " + request.clientAddress().toString());

			std::string data;
			GetUserList command;
			data += command.execute();
			return response.sendBuffer(data.data(), data.length());
		}
	};
}