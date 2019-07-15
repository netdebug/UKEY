#pragma once

#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/HTTPServerRequest.h"

namespace Reach {

	using Poco::Net::HTTPRequestHandler;
	using Poco::Net::HTTPServerRequest;
	using Poco::Net::HTTPServerResponse;

	///RS_KeySignByP1
	class KeySignByP1
	{
	public:
		KeySignByP1(const std::string& uid, const std::string& msg)
			:_uid(uid),_msg(msg)
		{}
		KeySignByP1& execute()
		{
			UDevice::default();

			_signature = SOF_SignData(_uid, _msg);
			if (_signature.empty()) {
				int error = SOF_GetLastError();
				throw Poco::LogicException("SOF_SignData failed!", error);
			}

			return *this;
		}

		operator std::string()
		{
			JSONStringify data;
			data.addObject("signdMsg", _signature);
			return data;
		}
	private:
		std::string _signature;
		std::string _uid;
		std::string _msg;
	};
	class KeySignByP1RequestHandler : public HTTPRequestHandler
	{
	public:
		void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
		{
			Application& app = Application::instance();
			app.logger().information("KeySignByP1RequestHandler Request from " + request.clientAddress().toString());

			std::string data;
			HTMLForm form(request, request.stream());
			if (!form.empty()) {
				std::string uid(form.get("containerId", ""));
				std::string msg(form.get("asn1Msg", ""));
				KeySignByP1 command(uid,msg);
				data += command.execute();
			}
			return response.sendBuffer(data.data(), data.length());
		}
	};
}