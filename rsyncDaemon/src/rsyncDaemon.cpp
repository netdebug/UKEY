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
#include "Poco/Util/ServerApplication.h"
#include "Poco/Util/Option.h"
#include "Poco/Util/OptionSet.h"
#include "Poco/Util/HelpFormatter.h"
#include "Poco/Task.h"
#include "Poco/TaskManager.h"
#include "Poco/DateTimeFormatter.h"
#include "Poco/LogStream.h"
#include "Poco/Process.h"
#include <iostream>


using namespace Reach;

using Poco::Util::Application;
using Poco::Util::ServerApplication;
using Poco::Util::Option;
using Poco::Util::OptionSet;
using Poco::Util::OptionCallback;
using Poco::Util::HelpFormatter;
using Poco::Task;
using Poco::TaskManager;
using Poco::DateTimeFormatter;
using Poco::LogStream;
using Poco::Process;
using Poco::ProcessHandle;


class SampleTask: public Task
{
public:
	SampleTask(): Task("SampleTask")
	{
	}

	void runTask()
	{
		Application& app = Application::instance();
		LogStream ls(app.logger());
		std::string name("updater");
		std::string cmd;
#if defined(_DEBUG) && (POCO_OS != POCO_OS_ANDROID)
		name += "d";
#endif
		std::vector<std::string> args;
		args.push_back("-checkforupdates");

		std::string initialDirectory = app.config().getString("application.dir");
		cmd.append(initialDirectory);
		cmd.append(name);

		while (!sleep(5000*12*30))
		{
			ls.information("busy doing nothing... " + DateTimeFormatter::format(app.uptime())) << std::endl
				<< ("application.dir = " + app.config().getString("application.dir")) << std::endl
				<< ("launch " + cmd) << std::endl;

			ProcessHandle ph = Process::launch(cmd, args, initialDirectory);

			ls.information("Process::PID ... : ") << ph.id() << "isRunning :" << Process::isRunning(ph) << std::endl;
		}
	}
};


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
		tm.start(new SampleTask);
		waitForTerminationRequest();
		tm.cancelAll();
		tm.joinAll();
	}
	return Application::EXIT_OK;
}


POCO_SERVER_MAIN(rsyncDaemon)
