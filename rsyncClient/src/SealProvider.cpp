#include "SealProvider.h"
#include "Poco/Exception.h"
#include "Poco/MD5Engine.h"
#include "Poco/DigestStream.h"
#include "Poco/DateTimeFormatter.h"
#include "Poco/UUID.h"
#include "Poco/UUIDGenerator.h"
#include "Poco/Crypto/X509Certificate.h"
#include <sstream>

using Poco::UUID;
using Poco::UUIDGenerator;
using Poco::MD5Engine;
using Poco::DigestEngine;
using Poco::DigestOutputStream;
using Poco::Crypto::X509Certificate;
using Poco::DateTimeFormatter;

using namespace Reach;

SealProvider::SealProvider()
{

}


SealProvider::~SealProvider()
{

}

void SealProvider::setProperty(const std::string& name, const std::string& value)
{
	if (name == "name")
	{
		_name = value;
	}
	else if (name == "code")
	{
		_code = value;
	}
	else if (name == "validStart")
	{
		_validStart = value;
	}
	else if (name == "validEnd")
	{
		_validEnd = value;
	}
	else if (name == "keysn")
	{
		_keysn = value;
	}
	else if (name == "seals")
	{
		_seals = value;
	}
	else if (name == "dataMD5")
	{
		_md5 = value;
	}
	else if (name == "cert")
	{
		_cert = value;
	}
	else
		throw Poco::PropertyNotSupportedException(name);
}

std::string SealProvider::getProperty(const std::string& name) const
{
	if (name == "name")
	{
		return _name;
	}
	else if (name == "code")
	{
		return _code;
	}
	else if (name == "validStart")
	{
		return _validStart;
	}
	else if (name == "validEnd")
	{
		return _validEnd;
	}
	else if (name == "keysn")
	{
		return _keysn;
	}
	else if (name == "seals")
	{
		return _seals;
	}
	else if (name == "dataMD5")
	{
		return _md5;
	}
	else if (name == "cert")
	{
		return _cert;
	}
	else
		throw Poco::PropertyNotSupportedException(name);
}

void SealProvider::GeneratedMD5()
{
	MD5Engine md5;
	DigestOutputStream ds(md5);
	ds << _keysn
		<< "&&"
		<< _md5;
	ds.close();

	std::string digest = DigestEngine::digestToHex(md5.digest());
	setProperty("dataMD5", digest);
}

void SealProvider::GeneratedCode()
{
	UUIDGenerator& gen = UUIDGenerator::defaultGenerator();
	UUID uuid = gen.createFromName(UUID::uri(), _keysn);
	setProperty("code", uuid.toString());
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
