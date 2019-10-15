#include "Utility.h"
#include "Poco/Exception.h"
#include "Reach/Data/SessionHolder.h"
#include "Poco/SingletonHolder.h"
#include "Poco/Util/Application.h"
#include "Poco/Path.h"
#include "Poco/String.h"
#include "Poco/DateTimeFormatter.h"
#include "Poco/Random.h"
#include "Poco/JSON/Parser.h"
#include "Poco/JSON/Object.h"
#include "Poco/Dynamic/Struct.h"
#include "Poco/URI.h"
#include <cassert>

using namespace Reach;
using Poco::SingletonHolder;
using Reach::Data::SessionContainer;
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

extern std::string SOF_GetCertInfoByOid(std::string Base64EncodeCert, std::string oid);

Utility::~Utility()
{

}

std::string Utility::SOF_GenRandom(int size)
{
	throw Poco::NotImplementedException("SOF_GenRandom");
	return "";
}

bool Utility::SOF_EncryptFile(std::string&, std::string&, std::string&)
{
	throw Poco::NotImplementedException("SOF_EncryptFile");
	return false;
}

std::string Utility::SOF_ExportExChangeUserCert(const std::string&)
{
	throw Poco::NotImplementedException("SOF_ExportExChangeUserCert");
	return "";
}

std::string Utility::SOF_AsDecrypt(std::string&, std::string&)
{
	throw Poco::NotImplementedException("SOF_AsDecrypt");
	return "";
}

std::string Utility::SOF_AsEncrypt(std::string &, std::string &)
{
	throw Poco::NotImplementedException("SOF_AsEncrypt");
	return "";
}

bool Utility::SOF_DecryptFile(std::string&, std::string, std::string)
{
	throw Poco::NotImplementedException("SOF_DecryptFile");
	return false;
}

int Utility::random()
{
	throw Poco::NotImplementedException("random");
	return 16;
}

int Utility::SOF_GetPinRetryCount(const std::string&)
{
	throw Poco::NotImplementedException("SOF_GetPinRetryCount");
	return 0;
}

std::string Utility::SOF_SignMessage(short, std::string&, std::string&)
{
	throw Poco::NotImplementedException("SOF_SignMessage");
	return "";
}

bool Utility::SOF_VerifySignedMessage(const std::string&, const std::string&)
{
	throw Poco::NotImplementedException("SOF_VerifySignedMessage");
	return false;
}

int Utility::SOF_GetLastError()
{
	return 0xA000001;
}

std::string Utility::GetCertInfoByOid(const std::string& cer, const std::string& oid)
{
	throw Poco::NotImplementedException("GetCertInfoByOid");
	return "";
}

namespace
{
	static SingletonHolder<SessionContainer> sh;
}

SessionContainer& Utility::getSC()
{
	return *sh.get();
}

Session Utility::getSession()
{
	Application& app = Application::instance();
	std::string scheme = app.config().getString("engine.mode", "");
	std::string uri = Poco::format("%s:///REST",scheme);
	return Utility::getSC().get(uri);
}

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

	format(TRANSID, "%s%u", timestamp(), rnd.next());

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
		if (i > 0 && i % pos == 0) result.append(delim);
	}
	result.append(delim);
	return result;
}


