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

using namespace Reach;

using Poco::Util::Application;
using Poco::Util::Option;
using Poco::Util::OptionSet;
using Poco::Util::OptionCallback;
using Poco::Util::HelpFormatter;
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
		logger().information("Command line:");
		std::ostringstream ostr;
		for (ArgVec::const_iterator it = argv().begin(); it != argv().end(); ++it)
		{
			ostr << *it << ' ';
		}
		logger().information(ostr.str());
		logger().information("Arguments to main():");
		for (ArgVec::const_iterator it = args.begin(); it != args.end(); ++it)
		{
			logger().information(*it);
		}
		logger().information("Application properties:");
		printProperties("");
		/*TaskManager tm;
		tm.start(new HTTPServer);
		waitForTerminationRequest();
		tm.cancelAll();
		tm.joinAll();*/
	}
	return Application::EXIT_OK;
}
#include "Poco/Util/AbstractConfiguration.h"
using Poco::Util::AbstractConfiguration;

void rsyncAgent::printProperties(const std::string& base)
{
	AbstractConfiguration::Keys keys;
	config().keys(base, keys);
	if (keys.empty())
	{
		if (config().hasProperty(base))
		{
			std::string msg;
			msg.append(base);
			msg.append(" = ");
			msg.append(config().getString(base));
			logger().information(msg);
		}
	}
	else
	{
		for (AbstractConfiguration::Keys::const_iterator it = keys.begin(); it != keys.end(); ++it)
		{
			std::string fullKey = base;
			if (!fullKey.empty()) fullKey += '.';
			fullKey.append(*it);
			printProperties(fullKey);
		}
	}
}

POCO_APP_MAIN(rsyncAgent)
