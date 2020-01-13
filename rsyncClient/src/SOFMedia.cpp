#include "SOFMedia.h"
#include "Utility.h"
#include "Poco/Net/HTMLForm.h"

using namespace Reach;
using namespace Reach::ActiveX;

using Poco::Net::HTMLForm;

SOFMedia::SOFMedia()
{
	
}

SOFMedia::~SOFMedia()
{
	close();
}

void SOFMedia::extract()
{
	FetchKeySN();
	GetCertBase64String();
	CertValidity();
	GetImgAreaFromDN();
}

void SOFMedia::open()
{
	GetContainerId();
}

void SOFMedia::close()
{

}

void SOFMedia::GetCertBase64String()
{
	HTMLForm params;
	params.set("containerId", _uid);
	params.set("certType", _signType);

	std::ostringstream body;
	params.write(body);
	std::string result = Utility::SuperRequest("/RS_GetCertBase64String", body.str());
	poco_assert(!result.empty());
	if (_uid.empty())
		throw Poco::IOException("IOException : RS_GetCertBase64String result is empty!", getProperty("Provider"));

	JSON_PARSE(result);

	if (ds["code"] != "0000")
		handleLastError(result);

	std::string cert = ds["data"]["certBase64"].toString();
	setProperty("cert", cert);
}

void SOFMedia::FetchKeySN()
{
	poco_assert(!_uid.empty());
	if (_uid.empty())
		throw Poco::IOException("IOException : _uid is empty!", getProperty("Provider"));

	HTMLForm params;
	params.set("containerId", _uid);

	std::ostringstream body;
	params.write(body);
	std::string result = Utility::SuperRequest("/RS_KeyGetKeySn", body.str());
	poco_assert(!result.empty());

	JSON_PARSE(result);

	if (ds["code"] != "0000")
		handleLastError(result);

	setProperty("keysn", ds["data"]["keySn"].toString());
}

void SOFMedia::GetContainerId()
{
	std::string result = Utility::SuperRequest("/RS_GetUserList", "");
	poco_assert(!result.empty());
	if (result.empty())
		throw Poco::IOException("IOException : RS_GetUserList result is empty!", getProperty("Provider"));

	JSON_PARSE(result);

	if (ds["code"] != "0000")
		handleLastError(result);

	_uid = Utility::formatUid(result);
}

void SOFMedia::handleLastError(const std::string& result)
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
