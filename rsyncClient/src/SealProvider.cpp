#include "SealProvider.h"
#include "Poco/Exception.h"
#include "Utility.h"

using namespace Reach;
using namespace Reach::ActiveX;

SealProvider::SealProvider()
{
}


SealProvider::~SealProvider()
{

}

void SealProvider::setProperty(const std::string& name, const std::string& value)
{
	if (name == "Provider")
	{
		_Provider = value;
	}
	else if (name == "name")
	{
		_name = value;
	}
	else if (name == "seals")
	{
		_seals = value;
	}
	else
		throw Poco::PropertyNotSupportedException(name);
}

std::string SealProvider::getProperty(const std::string& name) const
{
	if (name == "Provider")
	{
		return _Provider;
	}
	else if (name == "name")
	{
		return _name;
	}
	else if (name == "seals")
	{
		return _seals;
	}
	else
		throw Poco::PropertyNotSupportedException(name);
}

void SealProvider::handleLastError(const std::string& result)
{
	JSON_PARSE(result);
	int code = ds["code"];
	switch (code) {
	case 9001:
		throw Poco::ProtocolException(ds.toString(), getProperty("Provider"), code);
	default:
		throw Poco::UnhandledException("UnhandledException", getProperty("Provider"), code);
	}
}