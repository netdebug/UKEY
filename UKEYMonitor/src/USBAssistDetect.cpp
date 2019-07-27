#include "USBAssistDetect.h"
#include "DeviceEventFilter.h"
#include "Poco/Util/Option.h"
#include "Poco/Util/OptionSet.h"
#include "Poco/Util/OptionException.h"
#include "Poco/FileStream.h"
#include "Poco/Exception.h"
#include "Poco/Process.h"
#include "Poco/NamedEvent.h"
#include "Poco/NumberFormatter.h"
#include "Poco/Logger.h"
#include "Poco/String.h"
#include "Poco/Util/WinService.h"
#include "Poco/Util/WinRegistryKey.h"
#include "Poco/UnicodeConverter.h"

using namespace Reach;
using Poco::Util::WinService;
using Poco::Util::WinRegistryKey;
using Poco::Util::Option;
using Poco::Util::OptionSet;
using Poco::Util::OptionCallback;
using Poco::Exception;
using Poco::SystemException;
using Poco::InvalidArgumentException;

Poco::NamedEvent      USBAssistDetect::_terminate(Poco::ProcessImpl::terminationEventName(Poco::Process::id()));
Poco::Event           USBAssistDetect::_terminated;
SERVICE_STATUS        USBAssistDetect::_serviceStatus;
SERVICE_STATUS_HANDLE USBAssistDetect::_serviceStatusHandle = 0;

USBAssistDetect::USBAssistDetect()
{
	_action = SRV_RUN;
	std::memset(&_serviceStatus, 0, sizeof(_serviceStatus));
}

USBAssistDetect::~USBAssistDetect()
{
}

bool USBAssistDetect::isInteractive() const
{
	bool runsInBackground = config().getBool("application.runAsDaemon", false) || config().getBool("application.runAsService", false);
	return !runsInBackground;
}

int USBAssistDetect::run(int argc, char ** argv)
{
	if (!hasConsole() && isService())
	{
		return 0;
	}
	else
	{
		int rc = EXIT_OK;
		try
		{
			init(argc, argv);
			switch (_action)
			{
			case SRV_REGISTER:
				registerService();
				rc = EXIT_OK;
				break;
			case SRV_UNREGISTER:
				unregisterService();
				rc = EXIT_OK;
				break;
			default:
				rc = run();
			}
		}
		catch (Exception& exc)
		{
			logger().log(exc);
			rc = EXIT_SOFTWARE;
		}
		return rc;
	}
}

int USBAssistDetect::run(const std::vector<std::string>& args)
{
	if (!hasConsole() && isService())
	{
		return 0;
	}
	else
	{
		int rc = EXIT_OK;
		try
		{
			init(args);
			switch (_action)
			{
			case SRV_REGISTER:
				registerService();
				rc = EXIT_OK;
				break;
			case SRV_UNREGISTER:
				unregisterService();
				rc = EXIT_OK;
				break;
			default:
				rc = run();
			}
		}
		catch (Exception& exc)
		{
			logger().log(exc);
			rc = EXIT_SOFTWARE;
		}
		return rc;
	}
}

#if defined(POCO_WIN32_UTF8) && !defined(POCO_NO_WSTRING)
int USBAssistDetect::run(int argc, wchar_t** argv)
{
	if (!hasConsole() && isService())
	{
		return 0;
	}
	else
	{
		int rc = EXIT_OK;
		try
		{
			init(argc, argv);
			switch (_action)
			{
			case SRV_REGISTER:
				registerService();
				rc = EXIT_OK;
				break;
			case SRV_UNREGISTER:
				unregisterService();
				rc = EXIT_OK;
				break;
			default:
				rc = run();
			}
		}
		catch (Exception& exc)
		{
			logger().log(exc);
			rc = EXIT_SOFTWARE;
		}
		return rc;
	}
}
#endif

void USBAssistDetect::terminate()
{
	_terminate.set();
}

int USBAssistDetect::run()
{
	return Application::run();
}

void USBAssistDetect::waitForTerminationRequest()
{
	SetConsoleCtrlHandler(ConsoleCtrlHandler, TRUE);
	_terminate.wait();
	_terminated.set();
}

void USBAssistDetect::defineOptions(OptionSet& options)
{
	Application::defineOptions(options);

	options.addOption(
		Option("registerService", "", "Register the application as a service.")
		.required(false)
		.repeatable(false)
		.callback(OptionCallback<USBAssistDetect>(this, &USBAssistDetect::handleRegisterService)));

	options.addOption(
		Option("unregisterService", "", "Unregister the application as a service.")
		.required(false)
		.repeatable(false)
		.callback(OptionCallback<USBAssistDetect>(this, &USBAssistDetect::handleUnregisterService)));

	options.addOption(
		Option("displayName", "", "Specify a display name for the service (only with /registerService).")
		.required(false)
		.repeatable(false)
		.argument("name")
		.callback(OptionCallback<USBAssistDetect>(this, &USBAssistDetect::handleDisplayName)));

	options.addOption(
		Option("description", "", "Specify a description for the service (only with /registerService).")
		.required(false)
		.repeatable(false)
		.argument("text")
		.callback(OptionCallback<USBAssistDetect>(this, &USBAssistDetect::handleDescription)));

	options.addOption(
		Option("startup", "", "Specify the startup mode for the service (only with /registerService).")
		.required(false)
		.repeatable(false)
		.argument("automatic|manual")
		.callback(OptionCallback<USBAssistDetect>(this, &USBAssistDetect::handleStartup)));
}

BOOL USBAssistDetect::ConsoleCtrlHandler(DWORD ctrlType)
{
	switch (ctrlType)
	{
	case CTRL_C_EVENT:
	case CTRL_CLOSE_EVENT:
	case CTRL_BREAK_EVENT:
		terminate();
		return _terminated.tryWait(10000) ? TRUE : FALSE;
	default:
		return FALSE;
	}
}

DWORD USBAssistDetect::ServiceControlHandler(DWORD control, DWORD eventType, LPVOID eventData, LPVOID context)
{
	switch (control)
	{
	case SERVICE_CONTROL_STOP:
	case SERVICE_CONTROL_SHUTDOWN:
		terminate();
		_serviceStatus.dwCurrentState = SERVICE_STOP_PENDING;
		DeviceEventFilter::default().unregisterNotification();
		break;
	case SERVICE_CONTROL_INTERROGATE:
		break;
	case SERVICE_CONTROL_DEVICEEVENT:
		DeviceEventFilter::default().emit(eventType, eventData);
		break;
	}
	SetServiceStatus(_serviceStatusHandle, &_serviceStatus);

	return NO_ERROR;
}

void USBAssistDetect::ServiceMain(DWORD argc, LPWSTR * argv)
{
	USBAssistDetect& app = static_cast<USBAssistDetect&>(Application::instance());

	app.config().setBool("application.runAsService", true);

	_serviceStatusHandle = RegisterServiceCtrlHandlerExW(L"", ServiceControlHandler, 0);

	if (!_serviceStatusHandle)
		throw SystemException("cannot register service control handler");

	DeviceEventFilter::default().registerNotification(_serviceStatusHandle);

	_serviceStatus.dwServiceType = SERVICE_WIN32;
	_serviceStatus.dwCurrentState = SERVICE_START_PENDING;
	_serviceStatus.dwControlsAccepted = SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_SHUTDOWN;
	_serviceStatus.dwWin32ExitCode = 0;
	_serviceStatus.dwServiceSpecificExitCode = 0;
	_serviceStatus.dwCheckPoint = 0;
	_serviceStatus.dwWaitHint = 0;
	SetServiceStatus(_serviceStatusHandle, &_serviceStatus);

	try
	{
		std::vector<std::string> args;
		for (DWORD i = 0; i < argc; ++i)
		{
			std::string arg;
			Poco::UnicodeConverter::toUTF8(argv[i], arg);
			args.push_back(arg);
		}
		app.init(args);

		_serviceStatus.dwCurrentState = SERVICE_RUNNING;
		SetServiceStatus(_serviceStatusHandle, &_serviceStatus);
		int rc = app.run();
		_serviceStatus.dwWin32ExitCode = rc ? ERROR_SERVICE_SPECIFIC_ERROR : 0;
		_serviceStatus.dwServiceSpecificExitCode = rc;
	}
	catch (Exception& exc)
	{
		app.logger().log(exc);
		_serviceStatus.dwWin32ExitCode = ERROR_SERVICE_SPECIFIC_ERROR;
		_serviceStatus.dwServiceSpecificExitCode = EXIT_CONFIG;
	}
	catch (...)
	{
		app.logger().error("fatal error - aborting");
		_serviceStatus.dwWin32ExitCode = ERROR_SERVICE_SPECIFIC_ERROR;
		_serviceStatus.dwServiceSpecificExitCode = EXIT_SOFTWARE;
	}
	_serviceStatus.dwCurrentState = SERVICE_STOPPED;
	SetServiceStatus(_serviceStatusHandle, &_serviceStatus);
}

bool USBAssistDetect::hasConsole()
{
#ifdef _DEBUG
	return false;
#else
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	return hStdOut != INVALID_HANDLE_VALUE && hStdOut != NULL;
#endif // _DEBUG
}

bool USBAssistDetect::isService()
{
	SERVICE_TABLE_ENTRYW svcDispatchTable[2];
	svcDispatchTable[0].lpServiceName = L"";
	svcDispatchTable[0].lpServiceProc = ServiceMain;
	svcDispatchTable[1].lpServiceName = NULL;
	svcDispatchTable[1].lpServiceProc = NULL;
	return StartServiceCtrlDispatcherW(svcDispatchTable) != 0;
}

void USBAssistDetect::registerService()
{
	std::string name = config().getString("application.baseName");
	std::string path = config().getString("application.path");

	WinService service(name);
	if (_displayName.empty())
		service.registerService(path);
	else
		service.registerService(path, _displayName);
	if (_startup == "auto")
		service.setStartup(WinService::SVC_AUTO_START);
	else if (_startup == "manual")
		service.setStartup(WinService::SVC_MANUAL_START);
	if (!_description.empty())
		service.setDescription(_description);
	logger().information("The application has been successfully registered as a service.");
}

void USBAssistDetect::unregisterService()
{
	std::string name = config().getString("application.baseName");

	WinService service(name);
	service.unregisterService();
	logger().information("The service has been successfully unregistered.");
}

void USBAssistDetect::handleRegisterService(const std::string& name, const std::string& value)
{
	_action = SRV_REGISTER;
}

void USBAssistDetect::handleUnregisterService(const std::string& name, const std::string& value)
{
	_action = SRV_UNREGISTER;
}

void USBAssistDetect::handleDisplayName(const std::string& name, const std::string& value)
{
	_displayName = value;
}

void USBAssistDetect::handleDescription(const std::string& name, const std::string& value)
{
	_description = value;
}

void USBAssistDetect::handleStartup(const std::string& name, const std::string& value)
{
	if (Poco::icompare(value, 4, std::string("auto")) == 0)
		_startup = "auto";
	else if (Poco::icompare(value, std::string("manual")) == 0)
		_startup = "manual";
	else
		throw InvalidArgumentException("argument to startup option must be 'auto[matic]' or 'manual'");
}