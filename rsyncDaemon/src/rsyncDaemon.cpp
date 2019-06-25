//
// rsyncDaemon.cpp
//
// This sample demonstrates the ServerApplication class.
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//

#include "rsyncDaemon.h"
#include "UpdateTask.h"
#include "Poco/Util/ServerApplication.h"
#include "Poco/Util/Option.h"
#include "Poco/Util/OptionSet.h"
#include "Poco/Util/HelpFormatter.h"
#include "Poco/TaskManager.h"

using namespace Reach;

using Poco::Util::Application;
using Poco::Util::ServerApplication;
using Poco::Util::Option;
using Poco::Util::OptionSet;
using Poco::Util::OptionCallback;
using Poco::Util::HelpFormatter;
using Poco::TaskManager;

rsyncDaemon::rsyncDaemon() : _helpRequested(false)
{
}

rsyncDaemon::~rsyncDaemon()
{
}

void rsyncDaemon::initialize(Application& self)
{
	loadConfiguration(); // load default configuration files, if present
	ServerApplication::initialize(self);
	logger().information("starting up");
}

void rsyncDaemon::uninitialize()
{
	logger().information("shutting down");
	ServerApplication::uninitialize();
}

void rsyncDaemon::defineOptions(OptionSet& options)
{
	ServerApplication::defineOptions(options);

	options.addOption(
		Option("help", "h", "display help information on command line arguments")
		.required(false)
		.repeatable(false)
		.callback(OptionCallback<rsyncDaemon>(this, &rsyncDaemon::handleHelp)));
}

void rsyncDaemon::handleHelp(const std::string& name, const std::string& value)
{
	_helpRequested = true;
	displayHelp();
	stopOptionsProcessing();
}

void rsyncDaemon::displayHelp()
{
	HelpFormatter helpFormatter(options());
	helpFormatter.setCommand(commandName());
	helpFormatter.setUsage("OPTIONS");
	helpFormatter.setHeader("A sample server application that demonstrates some of the features of the Util::ServerApplication class.");
	helpFormatter.format(std::cout);
}

int rsyncDaemon::main(const ArgVec& args)
{
	if (!_helpRequested)
	{
		TaskManager tm;
		tm.start(new UpdateTask);
		waitForTerminationRequest();
		tm.cancelAll();
		tm.joinAll();
	}
	return Application::EXIT_OK;
}


POCO_SERVER_MAIN(rsyncDaemon)
