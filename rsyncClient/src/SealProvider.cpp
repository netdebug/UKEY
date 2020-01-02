#include "SealProvider.h"
#include "Poco/Exception.h"
#include "Poco/MD5Engine.h"
#include "Poco/DigestStream.h"
#include "Poco/DateTimeFormatter.h"
#include "Poco/UUID.h"
#include "Poco/UUIDGenerator.h"
#include "Poco/Crypto/X509Certificate.h"
#include "Utility.h"
#include "Poco/Net/HTMLForm.h"
#include <sstream>

using Poco::Net::HTMLForm;

using Poco::UUID;
using Poco::UUIDGenerator;
using Poco::MD5Engine;
using Poco::DigestEngine;
using Poco::DigestOutputStream;
using Poco::Crypto::X509Certificate;
using Poco::DateTimeFormatter;

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
	else if (name == "validStart")
	{
		_validStart = value;
	}
	else if (name == "validEnd")
	{
		_validEnd = value;
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
	else if (name == "validStart")
	{
		return _validStart;
	}
	else if (name == "validEnd")
	{
		return _validEnd;
	}
	else if (name == "seals")
	{
		return _seals;
	}
	else
		throw Poco::PropertyNotSupportedException(name);
}

void SealProvider::PeriodOfValidity()
{
	std::stringstream ss;
	ss << "-----BEGIN CERTIFICATE-----\n"
		<< _cert
		<< "\n-----END CERTIFICATE-----\n";

	X509Certificate cert(ss);
	std::string fmt("%Y-%m-%d");
	std::string validStart = DateTimeFormatter::format(cert.validFrom(), fmt);
	std::string validEnd = DateTimeFormatter::format(cert.expiresOn(), fmt);
	/// 证书有效期时间
	setProperty("validStart", validStart);
	setProperty("validEnd", validEnd);
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