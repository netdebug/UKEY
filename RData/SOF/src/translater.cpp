#include "Reach/Data/SOF/translater.h"
#include "Poco/SingletonHolder.h"
#include "Poco/Util/Application.h"
#include "Poco/NumberFormatter.h"
#include "Reach/Data/SOF/Utility.h"
#include <cassert>

using Poco::SingletonHolder;
using Poco::NumberFormatter;
using Poco::Util::Application;
using Poco::Util::IniFileConfiguration;

namespace Reach {
namespace Data {
namespace SOF {


translater::translater()
{
	Application& app = Application::instance();
	std::string ini = app.config().getString("Language.IniFile", "Language.ini");

	_pConfig = new IniFileConfiguration(Utility::config(ini));
}

translater::~translater()
{

}

std::string translater::tr(int key)
{
	return tr(NumberFormatter::formatHex(key));
}

std::string translater::tr(const std::string& key)
{
	assert(_pConfig->has(key));
	return _pConfig->getString(key);
}

std::string translater::tr(const std::string& section, int key)
{
	return tr(section, NumberFormatter::formatHex(key));
}

std::string translater::tr(const std::string& section, const std::string& key)
{
	std::string v;
	v.append(section);
	v.append(".");
	v.append(key);

	assert(_pConfig->has(v));
	return _pConfig->getString(v);
}

namespace
{
	static SingletonHolder<translater> trans;
}

translater& translater::default()
{
	return *trans.get();
}

}}} //namespace