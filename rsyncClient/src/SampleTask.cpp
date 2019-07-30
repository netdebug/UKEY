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

using Poco::Net::HTTPRequest;
using Poco::Net::HTTPResponse;
using Poco::Net::HTTPClientSession;
using Poco::StreamCopier;
using Poco::format;
using Poco::DateTimeFormatter;
using Poco::Util::Application;
using namespace Reach;


SampleTask::SampleTask(std::string& host, short port)
	: Task("SampleTask"), session(host, port)
{
}

void SampleTask::runTask()
{
	Application& app = Application::instance();

	while (!sleep(2000))
	{
		app.logger().trace("busy doing nothing... " + DateTimeFormatter::format(app.uptime()));

		HTTPRequest request(HTTPRequest::HTTP_GET, "/buffer");
		session.sendRequest(request);

		HTTPResponse response;
		std::istream& rs = session.receiveResponse(response);

		app.logger().trace(format("response contentType : %s ,length : %Ld", response.getContentType(), response.getContentLength()));
		std::ostringstream ostr;
		StreamCopier::copyStream(rs, ostr);

		app.logger().trace(format("response content : %s\n", ostr.str()));
	}
}
