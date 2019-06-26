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

#include "UpdateTask.h"
#include "Poco/Util/ServerApplication.h"
#include "Poco/DateTimeFormatter.h"
#include "Poco/LogStream.h"
#include "Poco/Process.h"
#include "Poco/Debugger.h"
#include <iostream>


using namespace Reach;

using Poco::Util::Application;
using Poco::Task;
using Poco::DateTimeFormatter;
using Poco::LogStream;
using Poco::Process;
using Poco::ProcessHandle;
using Poco::Debugger;

UpdateTask::UpdateTask() 
	: Task("UpdateTask"), millisecond(5000 * 12)
{
}

UpdateTask::~UpdateTask()
{

}

void UpdateTask::runTask()
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
	int minute = app.config().getInt("updater.period.minute");
	int period = minute * millisecond;

	cmd.append(initialDirectory);
	cmd.append(name);

	while (!sleep(period))
	{
		ls.information("busy doing nothing... " + DateTimeFormatter::format(app.uptime())) << std::endl
			<< ("application.dir = " + app.config().getString("application.dir")) << std::endl
			<< ("launch " + cmd) << std::endl;

		ProcessHandle ph = Process::launch(cmd, args, initialDirectory);

		ls.information("Process::PID ... : ") << ph.id() << "isRunning :" << Process::isRunning(ph) << std::endl;
		std::printf("Process::PID ... : %d ,isRunning : %d", ph.id(), Process::isRunning(ph));
	}
}