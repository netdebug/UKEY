#include "SOFMedia.h"
#include "Utility.h"
#include "Poco/Net/HTMLForm.h"

using namespace Reach;
using namespace Reach::ActiveX;

using Poco::Net::HTMLForm;
using Poco::icompare;

SOFMedia::SOFMedia(const std::string& hid)
	:_hid(hid)
{
	
}

SOFMedia::~SOFMedia()
{
	close();
}

void SOFMedia::extract()
{
	if (_hid != "VID_5448&PID_0004")
		FetchKeySN();
	else
		KeySN();
	GetCertBase64String();
	CertValidity();
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

//#include <atlbase.h>
//#include <comdef.h>
#include <ObjBase.h>
#include <comutil.h>
#include "KG_HARD_EXT.h"
#include "KG_HARD_EXT_i.c"

void SOFMedia::KeySN()
{
	HRESULT	hr; long ret; _bstr_t sn;
	IKG_HARD_EXT* ikg = 0;

	CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);

	hr = CoCreateInstance(CLSID_KG_HARD_EXT,
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_IKG_HARD_EXT,
		(void**)&ikg);

	poco_assert(SUCCEEDED(hr) && ikg);

	hr = ikg->WebConnectDev(0, &ret);
	poco_assert(SUCCEEDED(hr));
	hr = ikg->WebGetSerial(sn.GetAddress());
	poco_assert(SUCCEEDED(hr));
	hr = ikg->WebDisconnectDev(&ret);
	poco_assert(SUCCEEDED(hr));

	setProperty("keysn", std::string(sn, sn.length()));

	CoUninitialize();
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
