#pragma once

#include "Poco/Util/Application.h"
#include "Poco/Net/HTTPClientSession.h"
#include "Poco/URI.h"
#include "Poco/JSON/Parser.h"
#include "Poco/DynamicStruct.h"
#include "Poco/JSON/Object.h"
#include "Poco/FileStream.h"
#include "../Command.h"
#include "../RESTfulRequestHandler.h"
#include "CloudCommand.h"
#include "../../TokenManager.h"


namespace Reach {

	using Poco::Util::Application;
	using Poco::URI;
	using Poco::JSON::Parser;
	using Poco::JSON::Object;
	using Poco::DynamicStruct;
	using Poco::FileInputStream;

	///RS_CloudGetAuth
	class CloudGetAuth : public Command, public CloudCommand
	{
	public:
		CloudGetAuth(const std::string& transid, const std::string& url)
			:CloudCommand(url), _transid(transid), _authResult("0")
		{
		}

		void run()
		{
			mixValue();

			add("authResult", _authResult);
			add("token", _token);
			add("keySn", _keysn);
			add("mobile", _mobile);
			add("userName", _userName);
			add("userID", _userID);
		}
	protected:
		virtual void mixValue()
		{
			Application& app = Application::instance();

			std::string cache = TokenManager::default().get(_transid);
			if (!cache.empty()) 
			{
				poco_information(app.logger(), cache);
				JSON_PARSE(cache);

				_authResult = ds["authResult"].toString();
				_mobile = ds["mobile"].toString();
				_userName = ds["userName"].toString();
				_userID = ds["userId"].toString();

				size_t authType = app.config().getUInt("authType", 0);
				if (!authType)
					_token = ds["token"].toString();
				else
					_keysn = app.config().getString("keySn");
			}
		}

	private:
		std::string _transid;
		std::string _action;
		std::string _authResult;
		std::string _token;
		std::string _keysn;
		std::string _mobile;
		std::string _userName;
		std::string _userID;
	};

	class CloudGetAuthRequestHandler : public RESTfulRequestHandler
	{
	public:
		void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
		{
			Application& app = Application::instance();
			poco_information_f1(app.logger(), "Request from %s", request.clientAddress().toString());

			RESTfulRequestHandler::handleCORS(request, response);

			HTMLForm form(request, request.stream());
			std::string transid = form.get("transid", "");
			std::string url = app.config().getString("rsigncloud");
			CloudGetAuth command(transid, url);
			command.execute();

			return response.sendBuffer(command().data(), command().length());
		}
	};
}