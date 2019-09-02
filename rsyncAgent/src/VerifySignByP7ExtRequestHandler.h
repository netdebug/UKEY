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
			:_textual(textual), _signature(signature), _mode(mode), _verify(false)
		{
			generator();
		}

		void run()
		{
			poco_information(Application::instance().logger(), "VerifySignByP7Ext");
			
			HTTPResponse response;
			HTTPRequest request(HTTPRequest::HTTP_POST, "http://114.115.172.176:8080/Fjreach/Fjreach.json");
			request.setContentLength((int)_buffer.length());

			HTTPClientSession session;
			session.sendRequest(request) << (_buffer);

			std::istream& receive = session.receiveResponse(response);
			std::ostringstream ostr;
			StreamCopier::copyStream(receive, ostr);

			Parser C;
			Poco::Dynamic::Var v = C.parse(ostr.str());
			Object::Ptr object = v.extract<Object::Ptr>();
			Poco::DynamicStruct ds = *object;

			_verify = (ds["RESULTCODE"] == "0000");

			if (!_verify) {
				throw RequestHandleException("SOF_VerifySignedMessage failed!", RAR_UNKNOWNERR);
			}
		}
	protected:
		void generator()
		{
			std::string TRANSID;
			std::string fmt(
				"{\n"
				"	\"BIZCODE\" : \"BIZ.PK7VERIFY\",\n"
				"	\"DATA\" : {\n"
				"					\"msg\" : \"%s\",\n"
				"					\"signedMsg\" : \"%s\"\n"
				"			},\n"
				"	\"SYSID\" : \"b253fca87f6711e995aa005056a72395\",\n"
				"		\"TIMESTAMP\" : \"%s\",\n"
				"		\"TRANSID\" : \"%s\",\n"
				"		\"UNIT\" : \"RSYZ\"\n"
				"}");
			Poco::Timestamp ts;
			ts.update();
			std::string TIMESTAMP = DateTimeFormatter::format(ts, "%Y%m%d%H%M%S%i");
			Random rnd(Random::RND_STATE_128);
			rnd.seed();
			format(TRANSID, "RS%s%u", TIMESTAMP, rnd.next());
			format(_buffer, fmt, _textual, _signature, TIMESTAMP, TRANSID);

			assert(testJSON(_buffer));
			poco_information_f1(Application::instance().logger(), "VerifySignByP7Ext JSON: %s", _buffer);
		}
		bool testJSON(const std::string& buffer)
		{
			try
			{
				Parser C;
				Var result = C.parse(buffer);
				return true;
			}
			catch (Poco::JSON::JSONException& jsone)
			{
				std::cout << jsone.message() << std::endl;
			}
			return false;
		}
	private:
		int _mode;///Attached = 0, Detached = 1
		bool _verify;
		std::string _textual;
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