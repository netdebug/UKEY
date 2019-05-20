//
// SOFProviderTest.cpp
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#include "SOFProviderTest.h"
#include "CppUnit/TestCaller.h"
#include "CppUnit/TestSuite.h"
#include "Poco/SharedLibrary.h"
#include "Poco/Exception.h"
#include <stdio.h>
#include <sstream>
#include "Poco/StreamCopier.h"
#include "SoFProvider.h"

using Poco::SharedLibrary;
using Poco::NotFoundException;
using Poco::LibraryLoadException;
using Poco::LibraryAlreadyLoadedException;

typedef long(*pfn_GetLastError)();

SOFProviderTest::SOFProviderTest(const std::string& name): CppUnit::TestCase(name)
{
}


SOFProviderTest::~SOFProviderTest()
{
}

//template <typename FuncType>
//FuncType* FunctionPtr(std::string func)
//{
//	assert(sl.isLoaded());
//	assert(sl.hasSymbol(func));
//	FuncType ptr = (FuncType)sl.getSymbol(func);
//	assertNotNullPtr(fnTest);
//	return ptr;
//}

void SOFProviderTest::testSOFGetVersion()
{

}

void SOFProviderTest::testSOFSetSignMethod()
{
	typedef long(*pfn_SetSignMethod)(long SignMethod);
}

void SOFProviderTest::testSOFSetEncryptMethod()
{
	typedef long(*pfn_SetEncryptMethod)(long EncryptMethod);
}

void SOFProviderTest::testSOFGetUserList()
{
	typedef BSTR(*pfn_GetUserList)();
}

void SOFProviderTest::testSOFExportUserCert()
{
	typedef BSTR(*pfn_ExportUserCert)(BSTR ContainerName);
}

void SOFProviderTest::testSOFLogin()
{
	typedef BOOL(*pfn_Login)(BSTR  ContainerName, BSTR  PassWd);
}

void SOFProviderTest::testSOFGetPinRetryCount()
{
	typedef long(*pfn_GetPinRetryCount)(BSTR AppName);
}

void SOFProviderTest::testSOFChangePassWd()
{

}

void SOFProviderTest::testSOFExportExChangeUserCert()
{
	typedef BSTR(*pfn_ExportExChangeUserCert)(BSTR ContainerName);
}

void SOFProviderTest::testSOFGetCertInfo()
{
	typedef BSTR(*pfn_GetCertInfo)(BSTR Base64EncodeCert, short Type);
}

void SOFProviderTest::testSOFSignData()
{
	typedef BSTR(*pfn_SignData)(BSTR ContainerName, BSTR InData);
}

void SOFProviderTest::testSOFVerifySignedData()
{
	typedef BOOL(*pfn_VerifySignedData)(BSTR Base64EncodeCert, BSTR InData, BSTR SignValue);
}

void SOFProviderTest::testOpenDevice()
{
	typedef int(*pfn_OpenDevice)(void);
}

void SOFProviderTest::testCloseDevice()
{
	typedef int(*pfn_CloseDevice)(void);
}

void SOFProviderTest::testSOFGetDeviceInfo()
{

}

void SOFProviderTest::testSOFGenRandom()
{
	typedef BSTR(*pfn_GenRandom)(short RandomLen);
}

void SOFProviderTest::testSOFEncryptFile()
{
	typedef BOOL(*pfn_EncryptFile)(BSTR Pwd, BSTR InFile, BSTR OutFile);
}

void SOFProviderTest::testSOFDecryptFile()
{
	typedef BOOL(*pfn_DecryptFile)(BSTR Pwd, BSTR InFile, BSTR OutFile);
}

void SOFProviderTest::testSOFAsEncrypt()
{
	typedef BSTR(*pfn_AsEncrypt)(BSTR ContainerName, BSTR InData);
}

void SOFProviderTest::testSOFAsDecrypt()
{
	typedef BSTR(*pfn_AsDecrypt)(BSTR ContainerName, BSTR Indata);
}

void SOFProviderTest::setUp()
{
	std::string path = "SoFProvider.dll";
	sl.load(path);
	assert(sl.isLoaded());
}


void SOFProviderTest::tearDown()
{
	sl.unload();
	assert(!sl.isLoaded());
}


CppUnit::Test* SOFProviderTest::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("SOFProviderTest");

	CppUnit_addTest(pSuite, SOFProviderTest, testSOFGetVersion);
	CppUnit_addTest(pSuite, SOFProviderTest, testSOFSetSignMethod);
	CppUnit_addTest(pSuite, SOFProviderTest, testSOFSetEncryptMethod);
	CppUnit_addTest(pSuite, SOFProviderTest, testSOFGetUserList);
	CppUnit_addTest(pSuite, SOFProviderTest, testSOFExportUserCert);
	CppUnit_addTest(pSuite, SOFProviderTest, testSOFLogin);
	CppUnit_addTest(pSuite, SOFProviderTest, testSOFGetPinRetryCount);
	CppUnit_addTest(pSuite, SOFProviderTest, testSOFChangePassWd);
	CppUnit_addTest(pSuite, SOFProviderTest, testSOFExportExChangeUserCert);
	CppUnit_addTest(pSuite, SOFProviderTest, testSOFGetCertInfo);
	CppUnit_addTest(pSuite, SOFProviderTest, testSOFSignData);
	CppUnit_addTest(pSuite, SOFProviderTest, testSOFVerifySignedData);
	CppUnit_addTest(pSuite, SOFProviderTest, testOpenDevice);
	CppUnit_addTest(pSuite, SOFProviderTest, testCloseDevice);
	CppUnit_addTest(pSuite, SOFProviderTest, testSOFGetDeviceInfo);
	CppUnit_addTest(pSuite, SOFProviderTest, testSOFGenRandom);
	CppUnit_addTest(pSuite, SOFProviderTest, testSOFEncryptFile);
	CppUnit_addTest(pSuite, SOFProviderTest, testSOFDecryptFile);
	CppUnit_addTest(pSuite, SOFProviderTest, testSOFAsEncrypt);
	CppUnit_addTest(pSuite, SOFProviderTest, testSOFAsDecrypt);

	return pSuite;
}
