#include "stdafx.h"
#include "Utility.h"
#include "Poco/DateTimeFormatter.h"
#include "Poco/Net/HTTPRequest.h"
#include "Poco/Net/HTTPResponse.h"
#include "Poco/Debugger.h"
#include "Poco/String.h"
#include "Poco/StreamCopier.h"
#include "Poco/String.h"
#include "Poco/UnicodeConverter.h"
#include "Poco/RegularExpression.h"
#include "Poco/JSON/Parser.h"
#include "Poco/JSON/Object.h"
#include "Poco/DynamicStruct.h"
#include "Poco/Dynamic/Var.h"
#include "Poco/URI.h"
#include <cassert>
#include <sstream>

using Poco::Net::HTTPRequest;
using Poco::Net::HTTPResponse;
using Poco::Net::HTTPClientSession;
using Poco::UnicodeConverter;
using Poco::StreamCopier;
using Poco::Debugger;
using Poco::format;
using Poco::RegularExpression;
using Poco::JSON::Parser;
using Poco::JSON::Object;
using Poco::DynamicStruct;
using Poco::Dynamic::Var;

namespace Reach {
namespace ActiveX {


Poco::Net::HTTPClientSession Utility::_session("127.0.0.1", 9900);

Utility::Utility()
{
	_session.reset();
}

void Utility::get(const std::string& url)
{
	Debugger::message(format("request url [%s] body [%s]", url));
	HTTPRequest request(HTTPRequest::HTTP_GET, url);
	_session.sendRequest(request);

	HTTPResponse response;
	std::istream& receive = _session.receiveResponse(response);
	std::ostringstream ostr;
	StreamCopier::copyStream(receive, ostr);
	Debugger::message(format("response {%s}", ostr.str()));
}

void Utility::request(const std::string& url, const std::string& body)
{
	try
	{
		Debugger::message(format("request url [%s] body [%s]", url, body));
		HTTPRequest request(HTTPRequest::HTTP_POST, url);
		request.setContentLength((int)body.length());
		request.setContentType("application/json");
		_session.sendRequest(request) << (body);
	}
	catch (Poco::Exception& e)
	{
		Debugger::message(e.message());
	}
	
}

std::string Utility::response()
{
	std::ostringstream ostr;
	try 
	{
		HTTPResponse response;
		std::istream& receive = _session.receiveResponse(response);
		StreamCopier::copyStream(receive, ostr);
		Debugger::message(format("response {%s}", ostr.str()));
	}
	catch (Poco::Exception& e) 
	{
		Debugger::message(e.message());
	}
	return ostr.str();
}

std::string Utility::SuperRequest(const std::string& url, const std::string& body)
{
	HTTPResponse response;
	HTTPRequest request(HTTPRequest::HTTP_POST, url);
	request.setContentLength((int)body.length());

	HTTPClientSession session("127.0.0.1", 11200);
	session.sendRequest(request) << (body);

	std::istream& receive = session.receiveResponse(response);
	std::ostringstream ostr;
	StreamCopier::copyStream(receive, ostr);

	return ostr.str();
}

 std::wstring Utility::convert(const std::string& utf8)
{
	 std::wstring ucs;
	 UnicodeConverter::toUTF16(utf8, ucs);
	 return ucs;
}

std::string Utility::formatUid(const std::string& entries)
 {
	std::string uid;

	try
	{
		Parser ps;
		Var result = ps.parse(entries);
		assert(result.type() == typeid(Object::Ptr));
		DynamicStruct ds = *result.extract<Object::Ptr>();
		std::string userlist = ds["data"]["userlist"];

		std::string pattern("(\\S+)\\|\\|(\\S+)[&&&]*");
		int options = 0;

		RegularExpression re(pattern, options);
		RegularExpression::Match mtch;

		if (!re.match(userlist, mtch)) {
			throw Poco::LogicException();
		}

		std::vector<std::string> tags;
		re.split(userlist, tags, options);
		assert(tags.size() > 1);
		uid = tags[2];
	}
	catch (Poco::Exception& e)
	{
		Debugger::message(e.message());
	}
	
	return uid;
 }

}} //Reach::ActiveX