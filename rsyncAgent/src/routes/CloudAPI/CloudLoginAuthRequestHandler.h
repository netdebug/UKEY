#pragma once

#include "Poco/Util/Application.h"
#include "Poco/Net/HTTPClientSession.h"
#include "Poco/URI.h"
#include "Poco/JSON/Parser.h"
#include "Poco/DynamicStruct.h"
#include "Poco/FileStream.h"
#include "../Command.h"
#include "../RESTfulRequestHandler.h"


namespace Reach {

	using Poco::Util::Application;
	using Poco::Net::HTTPResponse;
	using Poco::Net::HTTPRequest;
	using Poco::Net::MediaType;
	using Poco::Net::HTTPClientSession;
	using Poco::URI;
	using Poco::JSON::Parser;
	using Poco::DynamicStruct;
	using Poco::FileInputStream;

	///RS_CloudLoginAuth
	class CloudLoginAuth : public Command
	{
	public:
		CloudLoginAuth(const std::string& transid)
			:_transid(transid), _action("1")
		{
		}

		void run()
		{
			Application& app = Application::instance();

			URI uri(app.config().getString("rsigncloudTest"));
			combineData();
		
			HTTPRequest request(HTTPRequest::HTTP_POST, uri.getPath());
			request.setContentLength((int)_sendBuffer.length());
			request.setContentType("application/json");
			HTTPClientSession session(uri.getHost(), uri.getPort());
			session.sendRequest(request) << _sendBuffer;
			poco_information_f3(app.logger(), "session : %s:[%u] {%s}", uri.getHost(), uri.getPort(), uri.getPath());

			HTTPResponse response;
			std::istream& out = session.receiveResponse(response);
			std::ostringstream ostr;
			StreamCopier::copyStream(out, ostr);

			poco_information_f1(app.logger(), "CloudLoginAuth receiveResponse:\n%s", ostr.str());

			Parser ps;
			Var result = ps.parse(ostr.str());
			assert(result.type() == typeid(Object::Ptr));
			DynamicStruct ds = *result.extract<Object::Ptr>();
			if (ds["head"]["code"] != "0000" || ds["body"].isEmpty())
				throw RequestHandleException(RAR_UNKNOWNERR);

			std::string authIdent = ds["body"];

			add("action", _action);
			add("authIdent", authIdent);
		}
	protected:
		void combineData()
		{
			Application& app = Application::instance();

			FileInputStream in("F:\\source\\RSTestRunner\\bin\\config\\CloudLoginAuth.json");
			Parser ps;
			Var result = ps.parse(in);
			assert(result.type() == typeid(Object::Ptr));
			DynamicStruct ds = *result.extract<Object::Ptr>();
			ds["bodyJson"]["action"] = _action;
			ds["bodyJson"]["transid"] = _transid;
			ds["body"] = ds["bodyJson"].toString();
			ds.erase("bodyJson");
			poco_information_f1(app.logger(), "CloudLoginAuth combineData:\n%s", ds.toString());
			_sendBuffer = ds.toString();
		}

	private:
		std::string _sendBuffer;
		std::string _transid;
		std::string _action;
		std::string _qrcode_data;
	};

	class CloudLoginAuthRequestHandler : public RESTfulRequestHandler
	{
	public:
		void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
		{
			poco_information_f1(Application::instance().logger(), "Request from %s", request.clientAddress().toString());
			RESTfulRequestHandler::handleCORS(request, response);

			HTMLForm form(request, request.stream());
			std::string transid = form.get("transid", "");
			CloudLoginAuth command(transid);
			command.execute();

			return response.sendBuffer(command().data(), command().length());
		}
	};
}