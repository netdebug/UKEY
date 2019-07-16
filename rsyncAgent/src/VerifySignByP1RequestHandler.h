#pragma once

#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/HTTPServerRequest.h"

namespace Reach {

	using Poco::Net::HTTPRequestHandler;
	using Poco::Net::HTTPServerRequest;
	using Poco::Net::HTTPServerResponse;

	///RS_VerifySignByP1
	class VerifySignByP1
	{
	public:
		VerifySignByP1(const std::string& base64, const std::string& msg, const std::string& signature)
			:_base64(base64),_msg(msg),_signature(signature)
		{}
		VerifySignByP1& execute()
		{
			_val = SOF_VerifySignedData(_base64, _msg, _signature);
			return *this;
		}

		operator std::string()
		{
			if (!_val) {
				JSONStringify data("unsuccessful", 3325);
				data.addNullObject();
				return data;
			}

			JSONStringify data;
			data.addNullObject();
			return data;
		}
	private:
		bool _val;
		std::string _base64;
		std::string _msg;
		std::string _signature;
	};
	class VerifySignByP1RequestHandler : public HTTPRequestHandler
	{
	public:
		void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
		{
			Application& app = Application::instance();
			app.logger().information("VerifySignByP1RequestHandler Request from " + request.clientAddress().toString());
			response.set("Access-Control-Allow-Origin", "*");
			response.set("Access-Control-Allow-Methods", "GET, POST, HEAD");

			std::string data;
			HTMLForm form(request, request.stream());
			if (!form.empty()) {
				std::string base64(form.get("certBase64", ""));
				std::string msg(form.get("msg", ""));
				std::string signature(form.get("signdMsg", ""));
				VerifySignByP1 command(base64,msg, signature);
				data += command.execute();
			}
			return response.sendBuffer(data.data(), data.length());
		}
	};
}