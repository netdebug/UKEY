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
#include "routes/Utility.h"

using namespace Reach;
using Poco::FastMutex;
using Poco::format;
using Poco::Debugger;
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
	CheckDeviceDBEnv();

	while (!sleep(500))	{
		dbgview("AdaptiveRecevier running!");

		_event.wait();

		if (isCancelled()) break;

		dbgview("UKEYMonitor.DeviceChangedEvent raise!");
		CheckDeviceDBEnv();
	}

	dbgview("AdaptiveRecevier stop!");
}

void AdaptiveRecevier::CheckDeviceDBEnv()
{
	try
	{
		Application& app = Application::instance();
#ifdef _DEBUG
		Poco::Data::Session session("SQLite", "C:\\Windows\\SysWOW64\\DeQLite.db");
#else
		Poco::Data::Session session("SQLite", "DeQLite.db");
#endif // _DEBUG

		DeviceInfoSet devices;
		session << "SELECT ENGINE, HardwareID, InstanceID FROM DeviceSet WHERE PRESENT = 1", into(devices), now;

		std::string data;
		for (Iter it = devices.begin(); it != devices.end(); it++) {
			dbgview(format("DeviceSet tags %s:%s&&%s\n", it->get<0>(), it->get<1>(), it->get<2>()));
		}

		if (devices.empty())
		{
			FastMutex::ScopedLock lock(_mutex);

			Utility::getSC().shutdown();
			Utility::getSC().clear();
		}

		if (devices.size() == 1) {
			FastMutex::ScopedLock lock(_mutex);

			std::string engine = devices[0].get<0>();
			app.config().setString("engine.mode", engine);

			dbgview(Poco::format("%s:///%s", engine, std::string("REST")));
			Utility::getSC().add(engine, "REST");
		}
	}
	catch (Poco::Exception& e)
	{
		dbgview(format("CheckDeviceDBEnv Exception:%s", e.message()));
	}

}

void AdaptiveRecevier::cancel()
{
	Utility::getSC().shutdown();
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