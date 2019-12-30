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
#include "Poco/ASCIIEncoding.h"
#include "Poco/StreamConverter.h"
#include "WindowsGBKEncoding.h"
#include "Poco/TextConverter.h"
#include "Poco/Util/Application.h"

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
using Poco::OutputStreamConverter;
using Poco::UTF8Encoding;
using Poco::WindowsGBKEncoding;
using Poco::Util::Application;
using Poco::Path;
using Poco::replace;

using namespace Reach::ActiveX;


Poco::Net::HTTPClientSession Utility::_session("127.0.0.1", 9900);

Utility::Utility()
{
	_session.reset();
}

void Utility::get(const std::string& url)
{
	try
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
	catch (Poco::Exception& e)
	{
		Debugger::message(e.message());
	}
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
	std::ostringstream ostr;
	try
	{
		HTTPResponse response;
		HTTPRequest request(HTTPRequest::HTTP_POST, url);
		request.setContentLength((int)body.length());

		HTTPClientSession session("127.0.0.1", 11200);
		session.sendRequest(request) << (body);

		std::istream& receive = session.receiveResponse(response);
		
		StreamCopier::copyStream(receive, ostr);
	}
	catch (Poco::Exception& e)
	{
		Debugger::message(e.message());
	}
	return ostr.str();
}

std::wstring Utility::convert(const std::string& utf8)
{
	std::wstring ucs;
	UnicodeConverter::toUTF16(utf8, ucs);
	return ucs;
}

std::string Utility::config(const std::string& name)
{
	Application& app = Application::instance();

	std::string appName = Path(app.commandPath()).getFileName();
	std::string fullpath = replace(app.commandPath(), appName, std::string(""));

	Path filePath(fullpath, name);

	return filePath.toString();
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
		if (ds["code"] != "0000")
			throw Poco::Exception("formatUid error", ds.toString());

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

std::string Utility::GBKtoUTF8(const std::string& text)
{
	UTF8Encoding utf8Encoding;
	WindowsGBKEncoding gbkEncoding;
#ifndef TEST
	std::ostringstream ostr;
	OutputStreamConverter converter(ostr, gbkEncoding, utf8Encoding);
	converter << text;
	return ostr.str();
#else
	std::string convertext;
	Poco::TextConverter tc(gbkEncoding, utf8Encoding);
	tc.convert(text, convertext);
	poco_information_f1(app.logger(), "%s", convertext);
	return convertext;
#endif // TEST
}