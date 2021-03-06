#include "SampleTask.h"
#include "Poco/Util/Application.h"
#include "Poco/DateTimeFormatter.h"
#include "Poco/Net/HTTPRequest.h"
#include "Poco/Net/HTTPResponse.h"
#include "Poco/Net/HTTPClientSession.h"
#include "Poco/StreamCopier.h"
#include "Poco/String.h"
#include <cassert>
#include <sstream>
#include "UKeyDevice.h"

#include "BridgePDFReader.h"
#include "BridgeKG_HARD_EXT.h"
#include "BridgeWindowsLiveLogin.h"

using Poco::Net::HTTPRequest;
using Poco::Net::HTTPResponse;
using Poco::Net::HTTPClientSession;
using Poco::StreamCopier;
using Poco::format;
using Poco::DateTimeFormatter;
using Poco::Util::Application;
using namespace Reach;


SampleTask::SampleTask(std::string& host, short port)
	: Task("SampleTask"), session(host, port), _serialNumber(""), _fjca(false)
{
	session.reset();
}

void SampleTask::runTask()
{
	Application& app = Application::instance();

	

	while (!sleep(2000))
	{
		Poco::Logger& l = app.logger();
		l.trace("busy doing nothing... " + DateTimeFormatter::format(app.uptime()));
		int a = 1;
		try
		{
			if (IsUSBKeyPresent()) {

				sendKeySNByActiveX();
			}

		}
		catch (Poco::Exception& e)
		{
			app.logger().trace("%s : %s code=%d", std::string(e.className()), e.message(), e.code());
		}

	}
}

#include "Poco/JSON/Parser.h"
#include "Poco/JSON/Object.h"
#include "Poco/JSON/Array.h"
#include "Poco/Dynamic/Var.h"
#include "Poco/DynamicStruct.h"
#include "Poco/Logger.h"

using Poco::JSON::Parser;
using Poco::JSON::Object;
using Poco::JSON::Array;
using Poco::DynamicStruct;
using Poco::Dynamic::Var;

void SampleTask::getUserList()
{
	Application& app = Application::instance();

	HTTPResponse response;
	HTTPRequest request(HTTPRequest::HTTP_GET, "/RS_GetUserList");

	session.sendRequest(request);
	std::istream& receive = session.receiveResponse(response);

	Parser json;
	Var result = json.parse(receive);
	DynamicStruct ds = *result.extract<Object::Ptr>();

	std::string _userlist = ds["data"]["userlist"].toString();
	_ukey = new UKeyDevice(_userlist);

	poco_trace_f2(app.logger(), "getUserList < %s : %s >\n", _ukey->containerName(), _ukey->certificateName());
}

void SampleTask::getKeySN()
{
	Application& app = Application::instance();

	HTTPResponse response;
	HTTPRequest request(HTTPRequest::HTTP_GET, "/RS_KeyGetKeySn");
	std::string body(format("containerId=%s", _ukey->containerName()));
	request.setContentLength((int)body.length());
	session.sendRequest(request) << body;

	std::istream& receive = session.receiveResponse(response);
	std::ostringstream ostr;
	StreamCopier::copyStream(receive, ostr);

	Parser json;
	Var result = json.parse(ostr.str());
	DynamicStruct ds = *result.extract<Object::Ptr>();

	_serialNumber = ds["data"]["keySn"].toString();
	poco_trace_f1(app.logger(), "getKeySN : %s\n", ds["data"]["keySn"].toString());
}

void SampleTask::sendKeySNByActiveX()
{
	Application& app = Application::instance();

	if (IsFJCA())
	{
		BridgeKG_HARD_EXT ext;
		ext.WebConnectDev();
		_serialNumber = ext.WebGetSerial();
		ext.WebDisconnectDev();
	}
	else
	{
		getUserList();
		getKeySN();
	}


	BridgePDFReader reader;
	reader.set("VirtualKeyNumber", _serialNumber);

	poco_trace_f1(app.logger(), "sendKeySNByActiveX VirtualKeyNumber content : %s\n", _serialNumber);
}

bool SampleTask::IsUSBKeyPresent()
{
	Application& app = Application::instance();

	HTTPResponse response;
	HTTPRequest request(HTTPRequest::HTTP_GET, "/buffer");
	session.sendRequest(request);

	std::istream& receive = session.receiveResponse(response);
	std::ostringstream ostr;
	StreamCopier::copyStream(receive, ostr);

	QueryUSBKeyType(ostr.str());

	Parser json;
	Var result = json.parse(ostr.str());
	Array da = *result.extract<Array::Ptr>();

	poco_trace_f1(app.logger(), "IsUSBKeyPresent response content : %s\n", result.toString());

	return da.size() > 0;
}

void SampleTask::QueryUSBKeyType(const std::string& data)
{
	Application& app = Application::instance();

	Parser json;
	Var result = json.parse(data);
	Array da = *result.extract<Array::Ptr>();

	for (int i = 0; i < da.size(); i++) {
		assert(da.isObject(i));
		DynamicStruct ds = *da.getObject(i);
		assert(ds.contains("Description"));
		if (ds["Description"] == "FJCA") {
			_fjca = true; break;
		}
	}

	poco_trace_f1(app.logger(), "QueryUSBKeyType FJCA : %b", _fjca);
}
bool SampleTask::IsFJCA()
{
	return _fjca;
}