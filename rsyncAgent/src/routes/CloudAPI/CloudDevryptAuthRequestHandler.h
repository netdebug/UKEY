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

	///RS_CloudDevryptAuth
	class CloudDevryptAuth : public Command, public CloudCommand
	{
	public:
		CloudDevryptAuth(const std::string& transid, const std::string& url) :
			CloudCommand(url),
			_transid(transid),
			_action("3")
		{
		}

		void run()
		{
			mixValue();
			sendRequest();

			if (!success())
				throw CloudCommandException(extract("head", "message"),
					std::stoi(extract("head", "code"), 0, 16));

			add("action", _action);
			add("authIdent", extract("body"));
		}
	protected:
		virtual void mixValue()
		{
			Application& app = Application::instance();
			FileInputStream in(Utility::config("config\\CloudDevryptAuth.json"));
			DynamicStruct ds = *parse(in).extract<Object::Ptr>();
			ds["bodyJson"]["action"] = _action;
			ds["bodyJson"]["transid"] = _transid;
			ds["bodyJson"]["authCode"] = app.config().getString("authCode", "");
			ds["bodyJson"]["clientId"] = app.config().getString("clientId", "456789");

			ds["body"] = ds["bodyJson"].toString();
			ds.erase("bodyJson");

			prepare(ds.toString());
			poco_information_f1(app.logger(), "CloudDevryptAuth mixValue:\n%s", ds.toString());
		}

	private:
		std::string _transid;
		std::string _action;
	};

	class CloudDevryptAuthRequestHandler : public RESTfulRequestHandler
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
			CloudDevryptAuth command(transid, url);
			command.execute();

			return response.sendBuffer(command().data(), command().length());
		}
	};
}