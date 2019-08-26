// RSyncControl.cpp: CRSyncControlApp 和 DLL 注册的实现。

#include "stdafx.h"
#include "RSyncControl.h"
#include "Cathelp.h"
#include "objsafe.h"
#include <cassert>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CRSyncControlApp theApp;

const GUID CDECL _tlid = { 0xa8de96ca,0x374b,0x497d,{0xaa,0x5f,0x3c,0x03,0x09,0xc8,0xa9,0xf0} };
const GUID CDECL _RSyncControlCtrl = { 0xa0b23721,0x9350,0x4b4d,{0xb5,0x81,0x65,0xad,0xd1,0xa7,0x7a,0x5e} };

const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;



// CRSyncControlApp::InitInstance - DLL 初始化

BOOL CRSyncControlApp::InitInstance()
{
	BOOL bInit = COleControlModule::InitInstance();

	if (bInit)
	{
		// TODO:  在此添加您自己的模块初始化代码。
		AfxEnableControlContainer();
	}

	return bInit;
}



// CRSyncControlApp::ExitInstance - DLL 终止

int CRSyncControlApp::ExitInstance()
{
	// TODO:  在此添加您自己的模块终止代码。

	return COleControlModule::ExitInstance();
}



// DllRegisterServer - 将项添加到系统注册表

STDAPI DllRegisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(TRUE))
		return ResultFromScode(SELFREG_E_CLASS);

	RegisterControlsSafely();
	
	return NOERROR;
}



// DllUnregisterServer - 将项从系统注册表中移除

STDAPI DllUnregisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	UnRegisterControlsSafely();

	if (!AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(FALSE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}


void RegisterControlsSafely()
{
	HRESULT hr;

	/// 将控件标记为可安全编写脚本

	hr = CreateComponentCategory(CATID_SafeForScripting,
		L"Controls safely  scriptable!");
	assert(SUCCEEDED(hr));

	hr = RegisterCLSIDInCategory(_RSyncControlCtrl,
		CATID_SafeForScripting);
	assert(SUCCEEDED(hr));

	/// 将控件标记为可安全编写脚本

	hr = CreateComponentCategory(CATID_SafeForScripting,
		L"Controls safely  scriptable!");
	assert(SUCCEEDED(hr));

	hr = RegisterCLSIDInCategory(_RSyncControlCtrl,
		CATID_SafeForScripting);
	assert(SUCCEEDED(hr));
}

void UnRegisterControlsSafely()
{
	HRESULT hr;
	
	/// 删除控件初始化安全入口

	hr = UnRegisterCLSIDInCategory(_RSyncControlCtrl, CATID_SafeForInitializing);
	assert(SUCCEEDED(hr));

	/// 删除控件脚本安全入口 

	hr = UnRegisterCLSIDInCategory(_RSyncControlCtrl, CATID_SafeForScripting);
	assert(SUCCEEDED(hr));
}