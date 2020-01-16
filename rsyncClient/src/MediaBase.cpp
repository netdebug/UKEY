#include "MediaBase.h"
#include "Utility.h"
#include "Poco/DateTimeFormatter.h"
#include "Poco/Crypto/X509Certificate.h"

using namespace Reach;
using namespace Reach::ActiveX;

using Poco::DateTimeFormatter;
using Poco::Crypto::X509Certificate;

MediaBase::MediaBase()
{
}

MediaBase::~MediaBase()
{

}

void MediaBase::setProperty(const std::string& name, const std::string& value)
{
	if (name == "Provider")
	{
		_Provider = value;
	}
	else if (name == "cert")
	{
		_cert = value;
	}
	else if (name == "keysn")
	{
		_keysn = value;
	}
	else if (name == "validStart")
	{
		_validStart = value;
	}
	else if (name == "validEnd")
	{
		_validEnd = value;
	}
	else
		throw Poco::PropertyNotSupportedException(name);
}

std::string MediaBase::getProperty(const std::string& name) const
{
	if (name == "Provider")
	{
		return _Provider;
	}
	else if (name == "keysn")
	{
		return _keysn;
	}
	else if (name == "cert")
	{
		return _cert;
	}
	else if (name == "validStart")
	{
		return _validStart;
	}
	else if (name == "validEnd")
	{
		return _validEnd;
	}
	else
		throw Poco::PropertyNotSupportedException(name);
}

void MediaBase::CertValidity()
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