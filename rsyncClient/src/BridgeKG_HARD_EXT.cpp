#include "BridgeKG_HARD_EXT.h"
#include <Windows.h>
#include <comdef.h>
#include "KG_HARD_EXT.h"
#include <iostream>
#include <cassert>
#include "Poco/Exception.h"

using namespace Reach;

BridgeKG_HARD_EXT::BridgeKG_HARD_EXT()
	:_ext(0)
{
	HRESULT	hr;
	hr = CoInitialize(0);
	assert(SUCCEEDED(hr));

	hr = CoCreateInstance(CLSID_KG_HARD_EXT,
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_IKG_HARD_EXT,
		(void**)&_ext);

	assert(SUCCEEDED(hr));
	if (!_ext) throw Poco::ApplicationException("BridgeKG_HARD_EXT", "CoCreateInstance Failed!");
}

void BridgeKG_HARD_EXT::WebConnectDev()
{
	HRESULT	hr;
	long ret;

	hr = _ext->WebConnectDev(0, &ret);
	assert(SUCCEEDED(hr));
	if (!ret) throw Poco::ApplicationException("BridgeKG_HARD_EXT", "WebConnectDev Failed!");
}

const std::string BridgeKG_HARD_EXT::WebGetSerial()
{
	HRESULT	hr;
	_bstr_t sn;

	hr = _ext->WebGetSerial(sn.GetAddress());
	assert(SUCCEEDED(hr));

	return std::string(sn,sn.length());
}

void BridgeKG_HARD_EXT::WebDisconnectDev()
{
	HRESULT	hr;
	long ret;

	hr = _ext->WebDisconnectDev(&ret);
	assert(SUCCEEDED(hr));
}

void BridgeKG_HARD_EXT::WebGetKeyDefineInfo()
{
	HRESULT	hr;
	_bstr_t szFileID;
	hr = _ext->WebGetKeyDefineInfo(0, szFileID.GetAddress());
	assert(SUCCEEDED(hr));
}

BridgeKG_HARD_EXT::~BridgeKG_HARD_EXT()
{
	release();
}

void BridgeKG_HARD_EXT::release()
{
	HRESULT	hr;
	hr = _ext->Release();
	assert(SUCCEEDED(hr));

	::CoUninitialize();
}
