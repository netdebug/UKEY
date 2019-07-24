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

SERVICE_STATUS        UKEYMonitor::_serviceStatus;
SERVICE_STATUS_HANDLE UKEYMonitor::_serviceStatusHandle = 0;
HDEVNOTIFY UKEYMonitor::_notify = 0;

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
			//std::string service_name = app.name();

		}
	}
};

UKEYMonitor::UKEYMonitor() : _helpRequested(false)
{
	std::memset(&_serviceStatus, 0, sizeof(_serviceStatus));
}

UKEYMonitor::~UKEYMonitor()
{
}

void UKEYMonitor::initialize(Application& self)
{
	loadConfiguration(); // load default configuration files, if present
	ServerApplication::initialize(self);
	logger().information("starting up");
}

void UKEYMonitor::uninitialize()
{
	logger().information("shutting down");
	ServerApplication::uninitialize();
}

void UKEYMonitor::defineOptions(OptionSet& options)
{
	ServerApplication::defineOptions(options);

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


//DEFINE_GUID(GUID_CLASS_USB, 0x25dbce51, 0x6c8f, 0x4a72, \
//	0x8a, 0x6d, 0xb5, 0x4c, 0x2b, 0x4f, 0xc8, 0x35);

GUID WceusbshGUID = { 0x25dbce51, 0x6c8f, 0x4a72,
					  0x8a,0x6d,0xb5,0x4c,0x2b,0x4f,0xc8,0x35 };

#include <Dbt.h>
#include <WinIoCtl.h>

void UKEYMonitor::deviceEventNotify(DWORD eventType, LPVOID eventData)
{
	switch (eventType)
	{
		case DBT_DEVICEARRIVAL:
		{
			Application& app = Application::instance();
			app.logger().information("DBT_DEVICEARRIVAL... " + DateTimeFormatter::format(app.uptime()));

			break;
		}
		case DBT_DEVICEREMOVECOMPLETE:
		{
			Application& app = Application::instance();
			app.logger().information("DBT_DEVICEREMOVECOMPLETE... " + DateTimeFormatter::format(app.uptime()));
			break;
		}
	}
}

void UKEYMonitor::ServiceControlHandler(DWORD control, DWORD eventType, LPVOID eventData, LPVOID context)
{
	switch (control)
	{
	case SERVICE_CONTROL_STOP:
	case SERVICE_CONTROL_SHUTDOWN:
		UnregisterDeviceNotification(_notify);
		terminate();
		_serviceStatus.dwCurrentState = SERVICE_STOP_PENDING;
		break;
	case SERVICE_CONTROL_INTERROGATE:
		break;
	case SERVICE_CONTROL_DEVICEEVENT:
		deviceEventNotify(eventType, eventData);
		break;
	}
	SetServiceStatus(_serviceStatusHandle, &_serviceStatus);
}

void UKEYMonitor::RegisterUKEYNotification()
{
	_serviceStatusHandle = RegisterServiceCtrlHandlerEx("", (LPHANDLER_FUNCTION_EX)ServiceControlHandler, 0);
	if (!_serviceStatusHandle)
		throw SystemException("cannot register service control handler");

	DEV_BROADCAST_DEVICEINTERFACE NotificationFilter;

	ZeroMemory(&NotificationFilter, sizeof(NotificationFilter));
	NotificationFilter.dbcc_size =
		sizeof(DEV_BROADCAST_DEVICEINTERFACE);
	NotificationFilter.dbcc_devicetype = DBT_DEVTYP_DEVICEINTERFACE;
	memcpy(&(NotificationFilter.dbcc_classguid),
		&(WceusbshGUID),
		sizeof(struct _GUID));
	_notify = RegisterDeviceNotification(_serviceStatusHandle,
		&NotificationFilter,
		DEVICE_NOTIFY_SERVICE_HANDLE | DEVICE_NOTIFY_ALL_INTERFACE_CLASSES);
}

#include <sstream>
int UKEYMonitor::main(const ArgVec& args)
{
	if (!_helpRequested)
	{
		TaskManager tm;
		tm.start(new SampleTask);
		//RegisterUKEYNotification();
		waitForTerminationRequest();
		tm.cancelAll();
		tm.joinAll();
	}
	return Application::EXIT_OK;
}

//POCO_SERVER_MAIN(UKEYMonitor)
