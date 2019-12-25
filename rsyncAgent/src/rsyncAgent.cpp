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
#include "AdaptiveRecevier.h"
#include "mqtt/CloudEventRecevier.h"
#include "Poco/Util/Application.h"
#include "Poco/Util/Option.h"
#include "Poco/Util/OptionSet.h"
#include "Poco/Util/HelpFormatter.h"
#include "Poco/TaskManager.h"
#include "Poco/Net/ServerSocket.h"
#include "Poco/Net/HTTPServer.h"
#include "Poco/Net/HTTPServerParams.h"
#include "RequestHandlerFactory.h"
#include <sstream>

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
	ServerApplication::initialize(self);
	logger().information("starting up");
}

void rsyncAgent::uninitialize()
{
	logger().information("shutting down");
	ServerApplication::uninitialize();
}

void rsyncAgent::defineOptions(OptionSet& options)
{
	ServerApplication::defineOptions(options);

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

int rsyncAgent::main(const ArgVec& args)
{
	if (!_helpRequested)
	{
		TaskManager tm;
		tm.start(new CloudEventRecevier);
		tm.start(new AdaptiveRecevier);
		unsigned short port = (unsigned short)config().getInt("HTTPFormServer.port", 9980);
		ServerSocket svs(port);
		HTTPServer srv(new RequestHandlerFactory, svs, new HTTPServerParams);
		srv.start();
		poco_information_f1(Application::instance().logger(), "HTTPServer Listen from %s", svs.address().toString());
		waitForTerminationRequest();
		srv.stop();
		tm.cancelAll();
		tm.joinAll();
	}
	return Application::EXIT_OK;
}

POCO_SERVER_MAIN(rsyncAgent)
