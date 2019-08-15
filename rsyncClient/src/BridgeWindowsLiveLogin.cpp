#include "BridgeWindowsLiveLogin.h"
#include <Windows.h>
#include <comdef.h>
#include "WindowsLiveLogin.h"
#include <iostream>
#include <cassert>

using namespace Reach;

BridgeWindowsLiveLogin::BridgeWindowsLiveLogin()
{
	HRESULT	hr;
	hr = CoInitialize(0);
	assert(SUCCEEDED(hr));

	hr = CoCreateInstance(CLSID_IDBHOCtrl,
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_IIDBHOCtrl,
		(void**)&_bho);

	assert(SUCCEEDED(hr));
}

BridgeWindowsLiveLogin::~BridgeWindowsLiveLogin()
{
	HRESULT	hr;
	hr = _bho->Release();
	assert(SUCCEEDED(hr));

	::CoUninitialize();
}

void BridgeWindowsLiveLogin::GetAuthenticatedUserToken()
{
	HRESULT	hr;
	_bstr_t token;
	_bstr_t version;
	int val;

	hr = _bho->get_Version(version.GetAddress());
	assert(SUCCEEDED(hr));
	
	hr = _bho->get_ComputerSetting(&val);
	assert(SUCCEEDED(hr));
	hr = _bho->GetAuthenticatedUserToken(token.GetAddress());

	assert(SUCCEEDED(hr));
}