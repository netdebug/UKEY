#include "MediaBase.h"
#include "Utility.h"
#include "Poco/Net/HTMLForm.h"

using namespace Reach;
using namespace Reach::ActiveX;
using Poco::Net::HTMLForm;

MediaBase::MediaBase()
{
	GetContainerId();
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
	else
		throw Poco::PropertyNotSupportedException(name);
}

void MediaBase::GetCertBase64String()
{
	HTMLForm params;
	params.set("containerId", _uid);
	params.set("certType", _signType);

	std::ostringstream body;
	params.write(body);
	std::string result = Utility::SuperRequest("/RS_GetCertBase64String", body.str());
	assert(!result.empty());
	if (_uid.empty())
		throw Poco::IOException("IOException : RS_GetCertBase64String result is empty!", getProperty("Provider"));

	JSON_PARSE(result);

	if (ds["code"] != "0000")
		handleLastError(result);

	std::string cert = ds["data"]["certBase64"].toString();
	setProperty("cert", cert);
}

void MediaBase::FetchKeySN()
{
	assert(!_uid.empty());
	if (_uid.empty())
		throw Poco::IOException("IOException : _uid is empty!", getProperty("Provider"));

	HTMLForm params;
	params.set("containerId", _uid);

	std::ostringstream body;
	params.write(body);
	std::string result = Utility::SuperRequest("/RS_KeyGetKeySn", body.str());
	assert(!result.empty());

	JSON_PARSE(result);

	if (ds["code"] != "0000")
		handleLastError(result);

	setProperty("keysn", ds["data"]["keySn"].toString());
}

void MediaBase::GetContainerId()
{
	std::string result = Utility::SuperRequest("/RS_GetUserList", "");
	assert(!result.empty());
	if (result.empty())
		throw Poco::IOException("IOException : RS_GetUserList result is empty!", getProperty("Provider"));

	JSON_PARSE(result);

	if (ds["code"] != "0000")
		handleLastError(result);

	_uid = Utility::formatUid(result);
}

void MediaBase::handleLastError(const std::string& result)
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

