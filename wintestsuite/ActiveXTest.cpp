//
// ActiveXTest.cpp
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#include "ActiveXTest.h"
#include "CppUnit/TestCaller.h"
#include "CppUnit/TestSuite.h"
#include "Poco/Exception.h"
//#include <atlbase.h>
//#include <atlcom.h>
//#include <Windows.h>

ActiveXTest::ActiveXTest(const std::string& name): CppUnit::TestCase(name)
{
}


ActiveXTest::~ActiveXTest()
{
}

void ActiveXTest::RS_KeyGetKeySn()
{
	assert(false);
}

void ActiveXTest::RS_KeyGetKeySnExt()
{

}

void ActiveXTest::RS_GetUserList()
{

}

void ActiveXTest::RS_GetCertBase64String()
{

}

void ActiveXTest::RS_CertLogin()
{

}

void ActiveXTest::RS_GetPinRetryCount()
{

}

void ActiveXTest::RS_ChangePassWd()
{

}

void ActiveXTest::RS_KeySignByP1()
{

}

void ActiveXTest::RS_VerifySignByP1()
{

}
void ActiveXTest::RS_KeyEncryptData()
{

}
void ActiveXTest::RS_KeyDecryptData()
{

}
void ActiveXTest::RS_GetCertInfo(){}
void ActiveXTest::RS_KeySignByP7(){}
void ActiveXTest::RS_VerifySignByP7(){}
void ActiveXTest::RS_CloudLoginAuth(){}
void ActiveXTest::RS_CloudSealAuth(){}
void ActiveXTest::RS_CloudGetAuth(){}
void ActiveXTest::RS_CloudGetSealList(){}
void ActiveXTest::RS_CloudSignByP7(){}
void ActiveXTest::RS_CloudGetSignResult(){}
void ActiveXTest::RS_CloudLogoutAuth(){}
void ActiveXTest::RS_CloudEncryptAuth(){}
void ActiveXTest::RS_CloudEncryptData(){}
void ActiveXTest::RS_CloudEncryptFile(){}
void ActiveXTest::RS_CloudDevryptAuth(){}
void ActiveXTest::RS_CloudDevryptData(){}
void ActiveXTest::RS_CloudDevryptFile(){}
void ActiveXTest::RS_CloudReceiveDevryptResult(){}
void ActiveXTest::RS_CloudGetCompanyCert(){}
void ActiveXTest::RS_CloudGetCertAuth(){}
void ActiveXTest::RS_CloudGetCertBase64(){}
void ActiveXTest::RS_CloudLogout(){}
void ActiveXTest::RS_KeyStatus(){}
void ActiveXTest::RS_ConfigParameters(){}
void ActiveXTest::RS_GetParameters(){}
void ActiveXTest::RS_GreateQRCode(){}
void ActiveXTest::RS_GetTransid(){}
void ActiveXTest::RS_EncryptFile(){}
void ActiveXTest::RS_DevryptFile(){}
void ActiveXTest::RS_VerifyIdentity(){}
void ActiveXTest::RS_KeyEncryptFile(){}
void ActiveXTest::RS_KeyDecryptFile(){}

void ActiveXTest::CodeSample()
{
	std::string code = "code";

	assert(!code.empty());
	assert(code == "sample");
	/*std::cout << "ActiveXTest test function" << std::endl;
	CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);

	CLSID clsid = { 0x0E0D0490,0x7085,0x4FA8,{0x86,0xA6,0x64,0x9F,0x0C,0xF1,0xDA,0x41} };
	HRESULT hr;

	CComPtr < IUnknown > spUnk;
	hr = ::CoCreateInstance(clsid, NULL, CLSCTX_ALL, IID_IUnknown, (LPVOID *)&spUnk);
	ATLASSERT(SUCCEEDED(hr));

	CComDispatchDriver spDisp(spUnk);
	CComVariant result, vOrg, vSig, vResult;

	spDisp.Invoke0(L"GetUserList", &result);
	BSTR ul = result.bstrVal;

	spDisp.Release(){}
	CoUninitialize(){}*/
}


void ActiveXTest::setUp()
{
}


void ActiveXTest::tearDown()
{
}


CppUnit::Test* ActiveXTest::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("ActiveXTest");

	CppUnit_addTest(pSuite, ActiveXTest, RS_KeyGetKeySn);
	CppUnit_addTest(pSuite, ActiveXTest, RS_KeyGetKeySnExt);
	CppUnit_addTest(pSuite, ActiveXTest, RS_GetUserList);
	CppUnit_addTest(pSuite, ActiveXTest, RS_GetCertBase64String);
	CppUnit_addTest(pSuite, ActiveXTest, RS_CertLogin);
	CppUnit_addTest(pSuite, ActiveXTest, RS_GetPinRetryCount);

	CppUnit_addTest(pSuite, ActiveXTest, CodeSample);

	return pSuite;
}
