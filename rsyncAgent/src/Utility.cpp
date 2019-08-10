#include "Utility.h"
#include "Poco/Util/Application.h"
#include "Poco/Path.h"
#include "Poco/String.h"

using Poco::replace;
using Poco::Path;
using Poco::Util::Application;

using namespace Reach;

std::string Utility::config(const std::string& name)
{
	Application& app = Application::instance();

	std::string appName = Path(app.commandPath()).getFileName();
	std::string fullpath = replace(app.commandPath(), appName, std::string(""));

	Path filePath(fullpath, name);

	return filePath.toString();
}