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
	using Poco::FileOutputStream;

	///RS_CloudDevryptFile
	class CloudDevryptFile : public Command, public CloudCommand
	{
	public:
		CloudDevryptFile(const std::string& encrypt, const std::string& decrypt, const std::string& callbackUrl, const std::string& transid, const std::string& token,
			const std::string& url) :
			CloudCommand(url),
			_encrypt(encrypt),
			_decrypt(decrypt),
			_callbackUrl(callbackUrl),
			_transid(transid),
			_token(token),
			_action("")
		{
			FileInputStream in(encrypt);
			assert(in.good());
			in >> _buffer_encrypt;
		}

		void run()
		{
			mixValue();
			sendRequest();

			if (!success())
				throw CloudCommandException(extract("head", "message"),
					std::stoi(extract("head", "code"), 0, 16));

			_buffer_decrypt = extract("body");

			FileOutputStream out(_decrypt);
			out << _buffer_decrypt;
			out.close();
		}
	protected:
		virtual void mixValue()
		{
			Application& app = Application::instance();
			FileInputStream in(Utility::config("config\\CloudDevryptFile.json"));
			DynamicStruct ds = *parse(in).extract<Object::Ptr>();
			ds["bodyJson"]["token"] = _token;
			ds["bodyJson"]["transid"] = _transid;
			ds["bodyJson"]["dealData"] = _buffer_encrypt;
			ds["bodyJson"]["bussUrl"] = _callbackUrl;

			ds["bodyJson"]["authCode"] = app.config().getString("authCode", "");
			ds["body"] = ds["bodyJson"].toString();
			ds.erase("bodyJson");

			prepare(ds.toString());
			poco_information_f1(app.logger(), "CloudDevryptFile mixValue:\n%s", ds.toString());
		}

	private:
		std::string _transid;
		std::string _action;
		std::string _encrypt;
		std::string _decrypt;
		std::string _callbackUrl;
		std::string _token;
		std::string _buffer_encrypt;
		std::string _buffer_decrypt;
	};

	class CloudDevryptFileRequestHandler : public RESTfulRequestHandler
	{
	public:
		void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
		{
			Application& app = Application::instance();
			poco_information_f1(app.logger(), "Request from %s", request.clientAddress().toString());
			RESTfulRequestHandler::handleCORS(request, response);

			HTMLForm form(request, request.stream());
			std::string encrypt = form.get("encFilePath", "");
			std::string decrypt = form.get("dncFilePath", "");
			std::string callbackUrl = form.get("url", "");
			std::string transid = form.get("transid", "");
			std::string token = form.get("token", "");
			std::string url = app.config().getString("rsigncloud");
			CloudDevryptFile command(encrypt, decrypt, callbackUrl, transid, token, url);
			command.execute();

			return response.sendBuffer(command().data(), command().length());
		}
	};
}