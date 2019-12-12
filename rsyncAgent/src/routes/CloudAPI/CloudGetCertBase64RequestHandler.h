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

	///RS_CloudGetCertBase64
	class CloudGetCertBase64 : public Command, public CloudCommand
	{
	public:
		CloudGetCertBase64(const std::string& transid, const std::string& token,
			const std::string& url) :
			CloudCommand(url),
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

			add("certBase64", extract("body"));
		}
	protected:
		virtual void mixValue()
		{
			Application& app = Application::instance();
			FileInputStream in(Utility::config("config\\CloudGetCertBase64.json"));
			DynamicStruct ds = *parse(in).extract<Object::Ptr>();
			ds["bodyJson"]["token"] = _token;
			ds["bodyJson"]["transid"] = _transid;

			ds["bodyJson"]["authCode"] = app.config().getString("authCode", "");
			ds["body"] = ds["bodyJson"].toString();
			ds.erase("bodyJson");

			prepare(ds.toString());
			poco_information_f1(app.logger(), "CloudGetCertBase64 mixValue:\n%s", ds.toString());
		}

	private:
		std::string _action;
		std::string _transid;
		std::string _token;
	};

	class CloudGetCertBase64RequestHandler : public RESTfulRequestHandler
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
			std::string url = app.config().getString("rsigncloud");
			CloudGetCertBase64 command(transid, token, url);
			command.execute();

			return response.sendBuffer(command().data(), command().length());
		}
	};
}