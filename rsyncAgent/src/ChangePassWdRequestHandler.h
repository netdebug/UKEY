#pragma once

#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/HTTPServerRequest.h"

namespace Reach {

	using Poco::Net::HTTPRequestHandler;
	using Poco::Net::HTTPServerRequest;
	using Poco::Net::HTTPServerResponse;

	///RS_ChangePassWd
	class ChangePassWd
	{
	public:
		ChangePassWd(const std::string& uid, const std::string& oldCode, const std::string& newCode)
			:_uid(uid),_oldCode(oldCode),_newCode(newCode)
		{}
		ChangePassWd& execute()
		{
			UDevice::default();

			if (!SOF_ChangePassWd(_uid, _oldCode, _newCode))
			{
				int error = SOF_GetLastError();
				throw Poco::LogicException("SOF_ChangePassWd failed", error);
			}

			return *this;
		}

		operator std::string()
		{
			JSONStringify data;
			return data;
		}
	private:
		std::string _uid;
		std::string _oldCode;
		std::string _newCode;
	};

	class ChangePassWdRequestHandler : public HTTPRequestHandler
	{
	public:
		void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
		{
			Application& app = Application::instance();
			app.logger().information("ChangePassWdRequestHandler Request from " + request.clientAddress().toString());

			response.set("Access-Control-Allow-Origin", "*");
			response.set("Access-Control-Allow-Methods", "GET, POST, HEAD");

			std::string data;
			HTMLForm form(request, request.stream());
			if (!form.empty()) {
				std::string uid(form.get("containerId", ""));
				std::string oldCode(form.get("oldCode", ""));
				std::string newCode(form.get("newCode", ""));
				ChangePassWd command(uid, oldCode, newCode);
				data += command.execute();
			}

			return response.sendBuffer(data.data(), data.length());
		}
	};
}