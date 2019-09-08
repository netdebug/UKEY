#include "AdaptiveRecevier.h"
#include "Poco/Data/Session.h"
#include "Poco/Data/SQLite/Connector.h"
#include "Poco/String.h"
#include "Poco/Debugger.h"
#include "Poco/JSON/Array.h"
#include "Poco/JSON/Object.h"
#include "Poco/JSON/Stringifier.h"
#include "Poco/Util/Application.h"
#include "Poco/Tuple.h"
#include <string>
#include <vector>
#include "Reach/Data/SOF/Connector.h"
#include "Reach/Data/FJCA/Connector.h"

using namespace Reach;
using Poco::format;
using Poco::Debugger;
using Poco::Data::Session;
using Poco::Data::SQLite::Connector;
using Poco::Util::Application;
using namespace Poco::Data::Keywords;

typedef Poco::Tuple <std::string, std::string, std::string> DeviceInfo;
typedef std::vector<DeviceInfo> DeviceInfoSet;
typedef DeviceInfoSet::const_iterator Iter;

AdaptiveRecevier::AdaptiveRecevier()
	:Task("AdaptiveRecevier")
	,_event("DeviceChangedEvent")
{
	Poco::Data::SQLite::Connector::registerConnector();
	Reach::Data::SOF::Connector::registerConnector();
	Reach::Data::FJCA::Connector::registerConnector();
}

void AdaptiveRecevier::runTask()
{
	Application& app = Application::instance();

	while (!sleep(500))	{
		dbgview("AdaptiveRecevier running!");

		_event.wait();

		if (isCancelled()) return;

		dbgview("UKEYMonitor.DeviceChangedEvent raise!");
#ifdef _DEBUG
		Session session("SQLite", "C:\\Windows\\SysWOW64\\DeQLite.db");
#else
		Session session("SQLite", "DeQLite.db");
#endif // _DEBUG

		DeviceInfoSet devices;
		session << "SELECT ENGINE, HardwareID, InstanceID FROM DeviceSet WHERE PRESENT = 1", into(devices), now;

		std::string data;
		for (Iter it = devices.begin(); it != devices.end(); it++) {
			dbgview(format("DeviceSet tags %s:%s&&%s\n", it->get<0>(), it->get<1>(), it->get<2>()));
		}

		if (devices.size() == 1) {
			app.config().setString("engine.mode", devices[0].get<0>());
			dbgview(format("engine mode :%s",app.config().getString("engine.mode")));
		}
	}

	dbgview("AdaptiveRecevier stop!");
}

void AdaptiveRecevier::cancel()
{
	dbgview("AdaptiveRecevier::cancel()");
	Task::cancel();
	_event.set();
}

void AdaptiveRecevier::dbgview(const std::string& message)
{
#ifndef _DEBUG
	::OutputDebugStringA(message.c_str());
#endif // !_NDEBUG
	Debugger::message(message);
}