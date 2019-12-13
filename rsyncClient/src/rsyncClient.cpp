//
// rsyncClient.cpp
//
// This sample demonstrates the Application class.
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//
#include "Poco/Util/Application.h"
#include "Poco/Util/Option.h"
#include "Poco/Util/OptionSet.h"
#include "Poco/Util/HelpFormatter.h"
#include "Poco/TaskManager.h"
#include "rsyncClient.h"
//#include "SampleTask.h"
#include "QZSyncWorker.h"
#include <objbase.h>

using namespace Reach;

using Poco::Util::Application;
using Poco::Util::Option;
using Poco::Util::OptionSet;
using Poco::Util::OptionCallback;
using Poco::Util::HelpFormatter;
using Poco::TaskManager;

rsyncClient::rsyncClient() : _helpRequested(false)
{
}

rsyncClient::~rsyncClient()
{
}

void rsyncClient::initialize(Application& self)
{
	loadConfiguration(); // load default configuration files, if present
	ServerApplication::initialize(self);
	logger().information("starting up");
}

void rsyncClient::uninitialize()
{
	logger().information("shutting down");
	ServerApplication::uninitialize();
}

void rsyncClient::defineOptions(OptionSet& options)
{
	ServerApplication::defineOptions(options);

	options.addOption(
		Option("help", "h", "display help information on command line arguments")
		.required(false)
		.repeatable(false)
		.callback(OptionCallback<rsyncClient>(this, &rsyncClient::handleHelp)));
}

void rsyncClient::handleHelp(const std::string& name, const std::string& value)
{
	_helpRequested = true;
	displayHelp();
	stopOptionsProcessing();
}

void rsyncClient::displayHelp()
{
	HelpFormatter helpFormatter(options());
	helpFormatter.setCommand(commandName());
	helpFormatter.setUsage("OPTIONS");
	helpFormatter.setHeader("A sample application that demonstrates some of the features of the Util::Application class.");
	helpFormatter.format(std::cout);
}

int rsyncClient::main(const ArgVec& args)
{
	if (!_helpRequested)
	{
		CoInitialize(0);
		Application& app = Application::instance();
		TaskManager tm;
		//tm.start(new SampleTask(host, port));
		tm.start(new QZSyncWorker);
		waitForTerminationRequest();
		tm.cancelAll();
		tm.joinAll();
		::CoUninitialize();
	}
	return Application::EXIT_OK;
}

POCO_SERVER_MAIN(rsyncClient)
