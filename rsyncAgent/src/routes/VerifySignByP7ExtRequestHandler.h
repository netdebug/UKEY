#pragma once

#include "Command.h"
#include "RESTfulRequestHandler.h"
#include "RequestHandleException.h"
#include "Poco/Util/Application.h"
#include "Poco/Dynamic/Var.h"
#include "Poco/Dynamic/Struct.h"
#include "Poco/Net/HTTPClientSession.h"
#include "Poco/StreamCopier.h" 
#include "Poco/JSON/Parser.h"
#include "Poco/String.h"
#include "Poco/Timestamp.h"
#include "Poco/Random.h"
#include "Poco/DateTimeFormatter.h"
#include "../Utility.h"
#include <cassert>

namespace Reach {

	using Poco::Dynamic::Var;
	using Poco::Util::Application;
	using Poco::Net::HTTPResponse;
	using Poco::Net::HTTPRequest;
	using Poco::Net::HTTPClientSession;
	using Poco::StreamCopier;
	using Poco::JSON::Parser;
	using Poco::JSON::Object;
	using Poco::format;
	using Poco::Random;
	using Poco::DateTimeFormatter;
	///RS_VerifySignByP7Ext
	class VerifySignByP7Ext : public Command
	{
	public:
		VerifySignByP7Ext(const std::string& textual, const std::string& signature, int mode)
			:_msg(textual), _signature(signature), _mode(mode), _verify(false)
		{
			generator();
		}

		void run()
		{
			poco_information(Application::instance().logger(), "VerifySignByP7Ext");
			
			HTTPResponse response;
			HTTPRequest request(HTTPRequest::HTTP_POST, "/Fjreach/Fjreach.json");
			request.setContentLength((int)_buffer.length());

			HTTPClientSession session("114.115.172.176", 8080);
			session.sendRequest(request) << (_buffer);

			std::istream& receive = session.receiveResponse(response);
			std::ostringstream ostr;
			StreamCopier::copyStream(receive, ostr);

			_verify = Utility::resultFormNet(ostr.str());

			if (!_verify) {
				throw RequestHandleException("VerifySignByP7Ext failed!", RAR_UNKNOWNERR);
			}
		}
	protected:
		void generator()
		{
			/// Note: TIMESTAMP is NOT Equual to TRANSID's
			/// BIZ.PK7VERIFY   1
			/// BIZ.PK7ATTVERIFY   0
			std::string fmt(
				"{\n"
				"	\"BIZCODE\" : \"%s\",\n"
				"	\"DATA\" : {\n"
				"					\"msg\" : \"%s\",\n"
				"					\"signedMsg\" : \"%s\"\n"
				"			},\n"
				"	\"SYSID\" : \"b253fca87f6711e995aa005056a72395\",\n"
				"		\"TIMESTAMP\" : \"%s\",\n"
				"		\"TRANSID\" : \"%s\",\n"
				"		\"UNIT\" : \"RSYZ\"\n"
				"}");

			std::string bizCode;
			_mode ? (bizCode = "BIZ.PK7VERIFY") : (bizCode = "BIZ.PK7ATTVERIFY");
			format(_buffer, fmt, bizCode,_msg, _signature, Utility::timestamp(), Utility::UniqueTransOrder());

			assert(Utility::testJSON(_buffer));
			poco_information_f1(Application::instance().logger(), "VerifySignByP7Ext JSON: %s", _buffer);
		}

	private:
		int _mode;///Attached = 0, Detached = 1
		bool _verify;
		std::string _msg;
		std::string _signature;
		std::string _buffer;
	};

	class VerifySignByP7ExtRequestHandler : public RESTfulRequestHandler
	{
	public:
		void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
		{
			poco_information_f1(Application::instance().logger(), "Request from %s", request.clientAddress().toString());

			RESTfulRequestHandler::handleCORS(request, response);

			HTMLForm form(request, request.stream());
			std::string textual(form.get("msg", ""));
			std::string signature(form.get("signdMsg", ""));
			Var mode(form.get("flag", ""));

			VerifySignByP7Ext command(textual, signature, mode);
			command.execute();

			return response.sendBuffer(command().data(), command().length());
		}
	};
}