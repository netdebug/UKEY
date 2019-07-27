//
// UKEYMonitor.cpp
//
// This sample demonstrates the ServerApplication class.
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//

#include "UKEYMonitor.h"
#include "Poco/Util/Application.h"
#include "Poco/Util/Option.h"
#include "Poco/Util/OptionSet.h"
#include "Poco/Util/HelpFormatter.h"
#include "Poco/TaskManager.h"
#include "Poco/Task.h"
#include "Poco/DateTimeFormatter.h"
#include "Poco/Exception.h"

using namespace Reach;

using Poco::Util::Application;
using Poco::Util::Option;
using Poco::Util::OptionSet;
using Poco::Util::OptionCallback;
using Poco::Util::HelpFormatter;
using Poco::TaskManager;
using Poco::Task;
using Poco::DateTimeFormatter;
using Poco::SystemException;

class SampleTask : public Task
{
public:
	SampleTask() : Task("SampleTask")
	{
	}

	void runTask()
	{
		Application& app = Application::instance();
		while (!sleep(5000))
		{
			Application& app = Application::instance();
			app.logger().information("busy doing nothing... " + DateTimeFormatter::format(app.uptime()));
		}
	}
};

UKEYMonitor::UKEYMonitor() : _helpRequested(false)
{
}

UKEYMonitor::~UKEYMonitor()
{
}

void UKEYMonitor::initialize(Application& self)
{
	loadConfiguration(); // load default configuration files, if present
	USBAssistDetect::initialize(self);
	logger().information("starting up");
}

void UKEYMonitor::uninitialize()
{
	logger().information("shutting down");
	USBAssistDetect::uninitialize();
}

void UKEYMonitor::defineOptions(OptionSet& options)
{
	USBAssistDetect::defineOptions(options);

	options.addOption(
		Option("help", "h", "display help information on command line arguments")
		.required(false)
		.repeatable(false)
		.callback(OptionCallback<UKEYMonitor>(this, &UKEYMonitor::handleHelp)));
}

void UKEYMonitor::handleHelp(const std::string& name, const std::string& value)
{
	_helpRequested = true;
	displayHelp();
	stopOptionsProcessing();
}

void UKEYMonitor::displayHelp()
{
	HelpFormatter helpFormatter(options());
	helpFormatter.setCommand(commandName());
	helpFormatter.setUsage("OPTIONS");
	helpFormatter.setHeader("A sample application that demonstrates some of the features of the Util::Application class.");
	helpFormatter.format(std::cout);
}

int UKEYMonitor::main(const ArgVec& args)
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

MAIN(UKEYMonitor)
