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

	///RS_CloudLogout
	class CloudLogout : public Command, public CloudCommand
	{
	public:
		CloudLogout(const std::string& userId, const std::string& url) 
			:CloudCommand(url),
			_action(""),
			_userId(userId)
		{
		}

		void run()
		{
			mixValue();
			sendRequest();

			if (!success())
				throw CloudCommandException(extract("head", "message"),
					std::stoi(extract("head", "code"), 0, 16));
		}
	protected:
		virtual void mixValue()
		{
			Application& app = Application::instance();
			FileInputStream in(Utility::config("config\\CloudLogout.json"));
			DynamicStruct ds = *parse(in).extract<Object::Ptr>();

			ds["bodyJson"]["userId"] = _userId;

			ds["bodyJson"]["authCode"] = app.config().getString("authCode", "");
			ds["body"] = ds["bodyJson"].toString();
			ds.erase("bodyJson");

			prepare(ds.toString());
			poco_information_f1(app.logger(), "CloudLogout mixValue:\n%s", ds.toString());
		}

	private:
		std::string _action;
		std::string _userId;
	};

	class CloudLogoutRequestHandler : public RESTfulRequestHandler
	{
	public:
		void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
		{
			Application& app = Application::instance();
			poco_information_f1(app.logger(), "Request from %s", request.clientAddress().toString());
			RESTfulRequestHandler::handleCORS(request, response);

			HTMLForm form(request, request.stream());
			std::string userId = form.get("userId", "");
			std::string url = app.config().getString("rsigncloud");
			CloudLogout command(userId, url);
			command.execute();

			return response.sendBuffer(command().data(), command().length());
		}
	};
}