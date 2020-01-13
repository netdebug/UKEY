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
	else if (name == "imgArea")
	{
		_imgArea = value;
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
	else if (name == "imgArea")
	{
		return _imgArea;
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
	/// ֤����Ч��ʱ��
	setProperty("validStart", validStart);
	setProperty("validEnd", validEnd);
}

void MediaBase::GetImgAreaFromDN()
{
	std::stringstream ss;
	ss << "-----BEGIN CERTIFICATE-----\n"
		<< _cert
		<< "\n-----END CERTIFICATE-----\n";

	X509Certificate cert(ss);

	std::string issuer = cert.issuerName();

	//_imgArea ͨ����������ȡ�����ű��룬�����ṩ��
	setProperty("imgArea", "");
}