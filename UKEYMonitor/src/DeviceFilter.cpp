#include "DeviceFilter.h"
#include "Poco/Debugger.h"
#include "Poco/String.h"
#include "Poco/RegularExpression.h"
#include "Poco/File.h"
#include "Poco/FileStream.h"
#include "Poco/StreamCopier.h"
#include "Poco/JSON/Parser.h"
#include "Poco/Util/Application.h"
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


DeviceFilter::DeviceFilter(const std::string& enumerate_id, bool removed)
	:_enumerate(enumerate_id), _removed(removed)
{
	try
	{
		loadConfigure();
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

void DeviceFilter::loadConfigure()
{
	Application& app = Application::instance();
	std::string configuration = app.config().getString("application.devices.configfile");

	Path appPath(app.commandPath());
	std::string fullname = appPath.getFileName();
	std::string dir = Poco::replace(app.commandPath(), fullname, std::string(""));

	Path filePath(dir, configuration);
	dbgview(format("removed :%b configuration filePath : %s", _removed, filePath.toString()));

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

		if (isLegelDevice(tags[2])) {
			for (int i = 0; i < tags.size(); i++) {
				dbgview(format("lpdbv->dbcc_name tags %d : %s", i, tags[i]));
			}
		}
	}
	catch (Poco::RegularExpressionException& e)
	{
		dbgview(format("lpdbv->dbcc_name tags %d : %s", e.code(), e.displayText()));
	}
}
bool DeviceFilter::isLegelDevice(const std::string& deivice_id)
{
	for (int i = 0; i < _data.size(); i++) {
		assert(_data[i].isStruct());
		std::string hardware = _data[i]["hardwareID"];
		if (isubstr(hardware, deivice_id) != istring::npos) {
			std::string desc = _data[i]["description"];
			dbgview(format("description : %s", desc));
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