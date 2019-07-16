#pragma once

#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/HTTPServerRequest.h"

namespace Reach {

	using Poco::Net::HTTPRequestHandler;
	using Poco::Net::HTTPServerRequest;
	using Poco::Net::HTTPServerResponse;

	///RS_KeySignByP7
	class KeySignByP7
	{
	public:
		KeySignByP7(const std::string& textual, int mode, const std::string& uid)
			:_textual(textual), _mode(mode),_uid(uid)
		{}
		KeySignByP7& execute()
		{
			UDevice::default();

			_signature = SOF_SignMessage(_mode, _uid, _textual);
			return *this;
		}

		operator std::string()
		{
			if (_signature.empty())
			{
				JSONStringify data("unsuccessful", 3325);
				data.addNullObject();
				return data;
			}

			JSONStringify data;
			data.addObject("signdMsg", _signature);
			return data;
		}
	private:
		std::string _textual;
		short _mode;///Attached = 0, Detached =1
		std::string _uid;
		std::string _signature;
	};

	class KeySignByP7RequestHandler : public HTTPRequestHandler
	{
	public:
		void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
		{
			Application& app = Application::instance();
			app.logger().information("KeySignByP7RequestHandler Request from " + request.clientAddress().toString());
			response.set("Access-Control-Allow-Origin", "*");
			response.set("Access-Control-Allow-Methods", "GET, POST, HEAD");

			std::string data;
			HTMLForm form(request, request.stream());
			if (!form.empty()) {
				std::string textual(form.get("msg", ""));
				std::string uid(form.get("containerId", ""));
				Var mode(form.get("flag", ""));
				KeySignByP7 command(textual,mode,uid);
				data += command.execute();
			}
			return response.sendBuffer(data.data(), data.length());
		}
	};
}