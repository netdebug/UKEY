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

	///RS_CloudGetSignResult
	class CloudGetSignResult : public Command, public CloudCommand
	{
	public:
		CloudGetSignResult(const std::string& transid, const std::string& token,
			const std::string& url) :
			CloudCommand(url),
			_token(token), _transid(transid),
			_action("")
		{
		}

		void run()
		{
			mixValue();
			sendRequest();

			if (!success())
				throw RequestHandleException(RAR_UNKNOWNERR);

			add("signResult", extract("signResult"));
			add("signdMsg", extract("signdMsg"));
			add("certBase64", extract("certBase64"));
		}
	protected:
		virtual void mixValue()
		{
			Application& app = Application::instance();
			FileInputStream in("F:\\source\\RSTestRunner\\bin\\config\\CloudGetSignResult.json");
			DynamicStruct ds = *parse(in).extract<Object::Ptr>();

			ds["bodyJson"]["token"] = _token;
			ds["bodyJson"]["transid"] = _transid;

			ds["bodyJson"]["authCode"] = app.config().getString("authCode", "");
			ds["body"] = ds["bodyJson"].toString();
			ds.erase("bodyJson");

			prepare(ds.toString());
			poco_information_f1(app.logger(), "CloudGetSignResult mixValue:\n%s", ds.toString());
		}

	private:
		std::string _action;
		std::string _token;
		std::string _transid;
	};

	class CloudGetSignResultRequestHandler : public RESTfulRequestHandler
	{
	public:
		void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
		{
			Application& app = Application::instance();
			poco_information_f1(app.logger(), "Request from %s", request.clientAddress().toString());
			RESTfulRequestHandler::handleCORS(request, response);

			HTMLForm form(request, request.stream());
			std::string transid = form.get("transid", "");
			std::string token = form.get("token", "");
			std::string url = app.config().getString("rsigncloudTest");
			CloudGetSignResult command(transid, token, url);
			command.execute();

			return response.sendBuffer(command().data(), command().length());
		}
	};
}