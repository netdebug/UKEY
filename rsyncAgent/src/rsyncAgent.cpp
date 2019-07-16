//
// rsyncAgent.cpp
//
// This sample demonstrates the ServerApplication class.
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//

#include "rsyncAgent.h"
#include "Poco/Util/Application.h"
#include "Poco/Util/Option.h"
#include "Poco/Util/OptionSet.h"
#include "Poco/Util/HelpFormatter.h"
#include "Poco/TaskManager.h"
#include "Poco/Net/ServerSocket.h"
#include "Poco/Net/HTTPServer.h"
#include "Poco/Net/HTTPServerParams.h"
#include "RequestHandlerFactory.h"

using namespace Reach;

using Poco::Util::Application;
using Poco::Util::Option;
using Poco::Util::OptionSet;
using Poco::Util::OptionCallback;
using Poco::Util::HelpFormatter;
using Poco::Net::ServerSocket;
using Poco::Net::HTTPServer;
using Poco::Net::HTTPServerParams;
using Poco::TaskManager;

rsyncAgent::rsyncAgent() : _helpRequested(false)
{
}

rsyncAgent::~rsyncAgent()
{
}

void rsyncAgent::initialize(Application& self)
{
	loadConfiguration(); // load default configuration files, if present
	Application::initialize(self);
	logger().information("starting up");
}

void rsyncAgent::uninitialize()
{
	logger().information("shutting down");
	Application::uninitialize();
}

void rsyncAgent::defineOptions(OptionSet& options)
{
	Application::defineOptions(options);

	options.addOption(
		Option("help", "h", "display help information on command line arguments")
		.required(false)
		.repeatable(false)
		.callback(OptionCallback<rsyncAgent>(this, &rsyncAgent::handleHelp)));
}

void rsyncAgent::handleHelp(const std::string& name, const std::string& value)
{
	_helpRequested = true;
	displayHelp();
	stopOptionsProcessing();
}

void rsyncAgent::displayHelp()
{
	HelpFormatter helpFormatter(options());
	helpFormatter.setCommand(commandName());
	helpFormatter.setUsage("OPTIONS");
	helpFormatter.setHeader("A sample application that demonstrates some of the features of the Util::Application class.");
	helpFormatter.format(std::cout);
}

#include <sstream>
int rsyncAgent::main(const ArgVec& args)
{
	if (!_helpRequested)
	{
		unsigned short port = (unsigned short)config().getInt("HTTPFormServer.port", 9980);
		ServerSocket svs(port);
		HTTPServer srv(new RequestHandlerFactory, svs, new HTTPServerParams);
		srv.start();
		Application& app = Application::instance();
		app.logger().information("HTTPServer Listen from " + svs.address().toString());
		waitForTerminationRequest();
		srv.stop();

	}
	return Application::EXIT_OK;
}

POCO_SERVER_MAIN(rsyncAgent)
