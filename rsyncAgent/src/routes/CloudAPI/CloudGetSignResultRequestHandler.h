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
			_token(token), _transid(transid), _signResult("0")
		{
		}

		void run()
		{
			mixValue();

			add("signResult", _signResult);
			add("signdMsg", _signdMsg);
			add("certBase64", _certBase64);
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

				_signResult = ds["authResult"].toString();
				if (_signResult == "1") {
					_signdMsg = ds["signdMsg"].toString();
					_certBase64 = ds["certBase64"].toString();
				}
			}
		}

	private:
		std::string _action;
		std::string _token;
		std::string _transid;
		std::string _signResult;
		std::string _signdMsg;
		std::string _certBase64;
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
			std::string url = app.config().getString("rsigncloud");
			CloudGetSignResult command(transid, token, url);
			command.execute();

			return response.sendBuffer(command().data(), command().length());
		}
	};
}