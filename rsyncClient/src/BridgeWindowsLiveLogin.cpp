#include "BridgeWindowsLiveLogin.h"
#include <Windows.h>
#include <comdef.h>
#include "WindowsLiveLogin.h"
#include <iostream>
#include <cassert>
#include "Poco/Bugcheck.h"

using namespace Reach;

BridgeWindowsLiveLogin::BridgeWindowsLiveLogin()
{
	HRESULT	hr;
	hr = CoInitialize(0);
	poco_assert(SUCCEEDED(hr));

	hr = CoCreateInstance(CLSID_IDBHOCtrl,
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_IIDBHOCtrl,
		(void**)&_bho);

	poco_assert(SUCCEEDED(hr));
}

BridgeWindowsLiveLogin::~BridgeWindowsLiveLogin()
{
	HRESULT	hr;
	hr = _bho->Release();
	poco_assert(SUCCEEDED(hr));

	::CoUninitialize();
}

void BridgeWindowsLiveLogin::GetAuthenticatedUserToken()
{
	HRESULT	hr;
	_bstr_t token;
	_bstr_t version;
	int val;

	hr = _bho->get_Version(version.GetAddress());
	poco_assert(SUCCEEDED(hr));
	
	hr = _bho->get_ComputerSetting(&val);
	poco_assert(SUCCEEDED(hr));
	hr = _bho->GetAuthenticatedUserToken(token.GetAddress());

	poco_assert(SUCCEEDED(hr));
}