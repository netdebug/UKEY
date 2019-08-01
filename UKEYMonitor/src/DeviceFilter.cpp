#include "DeviceFilter.h"
#include "Poco/Debugger.h"
#include "Poco/String.h"
#include "Poco/RegularExpression.h"
#include "Poco/File.h"
#include "Poco/FileStream.h"
#include "Poco/StreamCopier.h"
#include "Poco/JSON/Parser.h"
#include "Poco/Util/Application.h"
#include "Poco/Data/SessionFactory.h"
#include "Poco/Data/Session.h"
#include "Poco/Data/RecordSet.h"
#include "Poco/Data/Column.h"
#include "Poco/Data/SQLite/Connector.h"
#include "Poco/Util/WinService.h"
#include "Poco/Thread.h"
#include <sstream>
#include <cassert>


using namespace Reach;
using Poco::Debugger;
using Poco::format;
using Poco::isubstr;
using Poco::istring;
using Poco::replace;
using Poco::Path;
using Poco::File;
using Poco::FileInputStream;
using Poco::StreamCopier;
using Poco::JSON::Parser;
using Poco::RegularExpression;
using Poco::Util::Application;
using Poco::Data::Session;
using Poco::Data::Statement;
using Poco::Data::RecordSet;
using Poco::Util::WinService;
using Poco::Thread;
using namespace Poco::Data::Keywords;

DeviceFilter::DeviceFilter(const std::string& enumerate_id, bool presented)
	:_enumerate(enumerate_id), _presented(presented)
{
	try
	{
		loadConfigure();
		resetRESTfulService();
		enqueue();
	}
	catch (Poco::Exception& e)
	{
		dbgview(format("DeviceFilter Exception : %d - %s - %s - %s", e.code(), e.displayText(), std::string(e.what()), std::string(e.className())));
	}

}

DeviceFilter::~DeviceFilter()
{

}

std::string DeviceFilter::current()
{
	Application& app = Application::instance();
	Path appPath(app.commandPath());
	std::string fullname = appPath.getFileName();
	return Poco::replace(app.commandPath(), fullname, std::string(""));
}

void DeviceFilter::loadConfigure()
{
	Application& app = Application::instance();
	std::string configuration = app.config().getString("application.devices.configfile");

	Path filePath(current(), configuration);
	dbgview(format("presented :%b configuration filePath : %s", _presented, filePath.toString()));

	std::ostringstream ostr;
	if (filePath.isFile())
	{
		File inputFile(filePath);
		if (inputFile.exists())
		{
			FileInputStream fis(filePath.toString());
			StreamCopier::copyStream(fis, ostr);
		}
	}
	std::string jsonStr = ostr.str();
	Parser sparser;
	Var result = sparser.parse(jsonStr);
	Poco::JSON::Array::Ptr arr = result.extract<Poco::JSON::Array::Ptr>();
	_data = *arr;
}

void DeviceFilter::enqueue()
{
	std::string pattern("\\?\\\\(\\S+)#(\\S+)#(\\S+)#(\\S+)");
	int options = 0;
	try
	{
		RegularExpression re(pattern, options);
		RegularExpression::Match mtch;

		if (!re.match(_enumerate, mtch))
			return;

		std::vector<std::string> tags;
		re.split(_enumerate, tags, options);
		/// lpdbv->dbcc_name tags 0 : ?\USB#VID_1D99&PID_0001#5&38e97a59&0&10#{a5dcbf10-6530-11d2-901f-00c04fb951ed}
		/// lpdbv->dbcc_name tags 1 : USB					# enumerator
		///	lpdbv->dbcc_name tags 2 : VID_1D99&PID_0001   # hardware identification string
		///	lpdbv->dbcc_name tags 3 : 5&38e97a59&0&10	  # os-specific-instance
		///	lpdbv->dbcc_name tags 4 : {a5dcbf10-6530-11d2-901f-00c04fb951ed} # class guid
		/// Sqlite table : "CREATE TABLE DeviceSet (Description VARCHAR(30), ENUMERATOR VARCHAR(32), HardwareID VARCHAR(200), InstanceID VARCHAR(32), ClassGUID VARCHAR(39)), PRESENT BOOLEAN(1)"
		if (isLegelDevice(tags[2])) {

			Session session("SQLite", "DeQLite.db");
		
			std::vector<std::string> HardwareSet;
			session << "SELECT * FROM DeviceSet WHERE HardwareID = ? AND InstanceID = ?",
				use(tags[2]),use(tags[3]),into(HardwareSet),now;

			if (!HardwareSet.empty()) {
				session << "DELETE FROM DeviceSet WHERE HardwareID = ? AND InstanceID = ?",
					use(tags[2]), use(tags[3]), now;
			}

			session << "INSERT INTO DeviceSet VALUES(?, ?, ?, ?, ?, ?)", 
				use(_description),
				use(tags[1]),
				use(tags[2]),
				use(tags[3]),
				use(tags[4]),
				use(_presented),
				now;

				dbgview(format("Update SQLite ->\n Description : %s\n  enumerator : %s\n HardwareID : %s\n InstanceID : %s\n   ClassGUID : %s\n",
					_description, tags[1], tags[2], tags[3], tags[4]));
		}
	}
	catch (Poco::RegularExpressionException& e)
	{
		dbgview(format("lpdbv->dbcc_name tags %d : %s", e.code(), e.displayText()));
	}
}

void DeviceFilter::resetRESTfulService()
{
	std::vector<std::string> HardwareSet;

	Session session("SQLite", "DeQLite.db");
	session << "SELECT HardwareID FROM DeviceSet WHERE PRESENT = 1",
		into(HardwareSet), now;
	/// specific when swap multiple device by user ,ukey cannot not work.
	if (!_presented && HardwareSet.size() < 3) {
#ifdef _DEBUG
		WinService service("rsyncAgentd");
#else
		WinService service("rsyncAgent");
#endif // _DEBUG
		if (_presented && !service.isRunning())
			service.start();
		else if (!_presented) {
			service.stop();
			Thread::sleep(500);
			service.start();
		}
	}
}

bool DeviceFilter::isLegelDevice(const std::string& deivice_id)
{
	for (int i = 0; i < _data.size(); i++) {
		assert(_data[i].isStruct());
		std::string hardware = _data[i]["hardwareID"];
		if (isubstr(hardware, deivice_id) != istring::npos) {
			_description = _data[i]["description"].convert<std::string>();
			dbgview(format("description : %s", _description));
			return true;
		}
			
	}
	return false;
}

void DeviceFilter::dbgview(const std::string& message)
{
#ifndef _DEBUG
	::OutputDebugStringA(message.c_str());
#endif // !_NDEBUG
	Debugger::message(message);
}