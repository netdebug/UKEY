#include "Utility.h"
#include "Poco/Util/Application.h"
#include "Poco/Path.h"
#include "Poco/String.h"
#include "Poco/DateTimeFormatter.h"
#include "Poco/Random.h"
#include "Poco/JSON/Parser.h"
#include "Poco/JSON/Object.h"
#include "Poco/Dynamic/Struct.h"
#include <cassert>

using Poco::format;
using Poco::replace;
using Poco::Path;
using Poco::Random;
using Poco::Timestamp;
using Poco::DateTimeFormatter;
using Poco::Util::Application;
using Poco::JSON::Parser;
using Poco::JSON::Object;
using Poco::DynamicStruct;
using namespace Poco::Dynamic;

using namespace Reach;

std::string Utility::config(const std::string& name)
{
	Application& app = Application::instance();

	std::string appName = Path(app.commandPath()).getFileName();
	std::string fullpath = replace(app.commandPath(), appName, std::string(""));

	Path filePath(fullpath, name);

	return filePath.toString();
}

std::string Utility::timestamp()
{
	Poco::Timestamp ts;
	ts.update();
	return DateTimeFormatter::format(ts, "%Y%m%d%H%M%S%i");
}

std::string Utility::UniqueTransOrder()
{
	std::string TRANSID;
	
	Random rnd(Random::RND_STATE_128);
	rnd.seed();
	
	format(TRANSID, "RS%s%u", timestamp(), rnd.next());

	return TRANSID;
}

bool Utility::resultFormLocal(const std::string& json)
{
	return result(json, "code");
}

bool Utility::resultFormNet(const std::string& json)
{
	return result(json, "RESULTCODE");
}

bool Utility::result(const std::string& json, const std::string& key)
{
	Parser C;
	Var v = C.parse(json);
	Object::Ptr object = v.extract<Object::Ptr>();
	DynamicStruct ds = *object;

	assert(ds.contains(key));
	return (ds[key] == "0000");
}

bool Utility::testJSON(const std::string& buffer)
{
	try
	{
		Parser C;
		Var result = C.parse(buffer);
		return true;
	}
	catch (Poco::JSON::JSONException& jsone)
	{
		std::cout << jsone.message() << std::endl;
	}
	return false;
}

std::string Utility::cat(const std::string& delim, std::size_t pos, const std::string& str)
{
	assert(pos < str.length());

	std::string result;
	
	for (int i = 0; i < str.length(); i++)
	{
		result.push_back(str[i]);
		if (i >0 && i % pos == 0) result.append(delim);
	}
	result.append(delim);
	return result;
}