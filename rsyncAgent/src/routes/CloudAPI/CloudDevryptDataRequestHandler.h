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

	///RS_CloudDevryptData
	class CloudDevryptData : public Command, public CloudCommand
	{
	public:
		CloudDevryptData(const std::string& encSymKey, const std::string& callbackUrl, const std::string& transid, const std::string& token, 
			const std::string& url) :
			CloudCommand(url),
			_encSymKey(encSymKey),
			_callbackUrl(callbackUrl),
			_transid(transid),
			_token(token),
			_action("")
		{
		}

		void run()
		{
			mixValue();
			sendRequest();

			if (!success())
				throw CloudCommandException(extract("head", "message"),
					std::stoi(extract("head", "code"), 0, 16));

			add("symKey", extract("body"));
		}
	protected:
		virtual void mixValue()
		{
			Application& app = Application::instance();
			FileInputStream in(Utility::config("config\\CloudDevryptData.json"));
			DynamicStruct ds = *parse(in).extract<Object::Ptr>();
			ds["bodyJson"]["token"] = _token;
			ds["bodyJson"]["transid"] = _transid;
			ds["bodyJson"]["dealData"] = Poco::toUpper(_encSymKey);
			ds["bodyJson"]["bussUrl"] = _callbackUrl;

			ds["bodyJson"]["authCode"] = app.config().getString("authCode", "");
			ds["body"] = ds["bodyJson"].toString();
			ds.erase("bodyJson");

			prepare(ds.toString());
			poco_information_f1(app.logger(), "CloudDevryptData mixValue:\n%s", ds.toString());
		}

	private:
		std::string _transid;
		std::string _action;
		std::string _encSymKey;
		std::string _callbackUrl;
		std::string _token;
	};

	class CloudDevryptDataRequestHandler : public RESTfulRequestHandler
	{
	public:
		void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
		{
			Application& app = Application::instance();
			poco_information_f1(app.logger(), "Request from %s", request.clientAddress().toString());
			RESTfulRequestHandler::handleCORS(request, response);

			HTMLForm form(request, request.stream());
			std::string encSymKey = form.get("encSymKey", "");
			std::string callbackUrl = form.get("url", "");
			std::string transid = form.get("transid", "");
			std::string token = form.get("token", "");
			std::string url = app.config().getString("rsigncloud");
			CloudDevryptData command(encSymKey, callbackUrl, transid, token, url);
			command.execute();

			return response.sendBuffer(command().data(), command().length());
		}
	};
}