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
			:CloudCommand(url), _transid(transid)
		{
		}

		void run()
		{
			mixValue();
			sendRequest();

			filter();
			
			add("authResult", _authResult);
			add("token", _token);
			add("keySn", _keysn);
		}
	protected:
		void filter()
		{
			Application& app = Application::instance();

			const std::string code = extract("head", "code");
			if (code == "0000")
				_authResult = "1";//授权成功
			else if (code == "0028")
				_authResult = "0";//未授权
			else
				_authResult = "4";//其他情况

			size_t authType = app.config().getUInt("authType", 0);
			if (!authType)
				_token = extract("body", "token");
			else
				_keysn = app.config().getString("keySn");
		}
		virtual void mixValue()
		{
			Application& app = Application::instance();
			FileInputStream in(Utility::config("config\\CloudGetAuth.json"));
			DynamicStruct ds = *parse(in).extract<Object::Ptr>();
			ds["bodyJson"]["action"] = _action;
			ds["bodyJson"]["transid"] = _transid;
			ds["bodyJson"]["authCode"] = app.config().getString("authCode", "");
			ds["body"] = ds["bodyJson"].toString();
			ds.erase("bodyJson");

			prepare(ds.toString());
			poco_information_f1(app.logger(), "CloudGetAuth mixValue:\n%s", ds.toString());
		}

	private:
		std::string _transid;
		std::string _action;
		std::string _authResult;
		std::string _token;
		std::string _keysn;
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