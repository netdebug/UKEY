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
#include <sstream>

using Poco::Net::HTTPRequest;
using Poco::Net::HTTPResponse;
using Poco::Net::HTTPClientSession;
using Poco::UnicodeConverter;
using Poco::StreamCopier;
using Poco::Debugger;
using Poco::format;

namespace Reach {
namespace ActiveX {


Poco::Net::HTTPClientSession Utility::_session("127.0.0.1", 11200);

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
	Debugger::message(format("request url [%s] body [%s]", url, body));
	HTTPRequest request(HTTPRequest::HTTP_GET, url);
	request.setContentLength((int)body.length());
	_session.sendRequest(request) << body;
}

std::string Utility::response()
{
	HTTPResponse response;
	std::istream& receive = _session.receiveResponse(response);
	std::ostringstream ostr;
	StreamCopier::copyStream(receive, ostr);
	Debugger::message(format("response {%s}", ostr.str()));
	return ostr.str();
}

 std::wstring Utility::convert(const std::string& utf8)
{
	 std::wstring ucs;
	 UnicodeConverter::toUTF16(utf8, ucs);
	 return ucs;
}

}} //Reach::ActiveX