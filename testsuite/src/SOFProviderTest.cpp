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
#include "GMCrypto.h"

using Poco::SharedLibrary;
using Poco::NotFoundException;
using Poco::LibraryLoadException;
using Poco::LibraryAlreadyLoadedException;

typedef long (*pfn_GetLastError)();

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

void SOFProviderTest::testGetVersion()
{

}

void SOFProviderTest::testSetSignMethod()
{
	typedef long (*pfn_SetSignMethod)(long SignMethod);

	std::string func("SOF_SetSignMethod");
	assert(sl.isLoaded());
	assert(sl.hasSymbol(func));
	pfn_SetSignMethod ptr = (pfn_SetSignMethod)sl.getSymbol(func);
	assertNotNullPtr(ptr);
}

void SOFProviderTest::testSetEncryptMethod()
{
	typedef long (*pfn_SetEncryptMethod)(long EncryptMethod);

	std::string func("SOF_SetEncryptMethod");
	assert(sl.isLoaded());
	assert(sl.hasSymbol(func));
	pfn_SetEncryptMethod ptr = (pfn_SetEncryptMethod)sl.getSymbol(func);
	assertNotNullPtr(ptr);
}

void SOFProviderTest::testGetUserList()
{
	typedef BSTR (*pfn_GetUserList)();

	std::string func("SOF_GetUserList");
	assert(sl.isLoaded());
	assert(sl.hasSymbol(func));
	pfn_GetUserList ptr = (pfn_GetUserList)sl.getSymbol(func);
	assertNotNullPtr(ptr);
}

void SOFProviderTest::testExportUserCert()
{
	typedef BSTR(*pfn_ExportUserCert)(BSTR ContainerName);

	std::string func("SOF_ExportUserCert");
	assert(sl.isLoaded());
	assert(sl.hasSymbol(func));
	pfn_ExportUserCert ptr = (pfn_ExportUserCert)sl.getSymbol(func);
	assertNotNullPtr(ptr);
}

void SOFProviderTest::testLogin()
{
	typedef BOOL (*pfn_Login)(BSTR  ContainerName, BSTR  PassWd);

	std::string func("SOF_Login");
	assert(sl.isLoaded());
	assert(sl.hasSymbol(func));
	pfn_Login ptr = (pfn_Login)sl.getSymbol(func);
	assertNotNullPtr(ptr);
}

void SOFProviderTest::testGetPinRetryCount()
{
	typedef long (*pfn_GetPinRetryCount)(BSTR AppName);

	std::string func("SOF_GetPinRetryCount");
	assert(sl.isLoaded());
	assert(sl.hasSymbol(func));
	pfn_GetPinRetryCount ptr = (pfn_GetPinRetryCount)sl.getSymbol(func);
	assertNotNullPtr(ptr);
}

void SOFProviderTest::testChangePassWd()
{
	/*
	std::string func("SOF_ChangePassWd");
	assert(sl.isLoaded());
	assert(sl.hasSymbol(func));
	ptr = ()sl.getSymbol(func);
	assertNotNullPtr(ptr);
	*/
}

void SOFProviderTest::testExportExChangeUserCert()
{
	typedef BSTR (*pfn_ExportExChangeUserCert)(BSTR ContainerName);

	std::string func("SOF_ExportExChangeUserCert");
	assert(sl.isLoaded());
	assert(sl.hasSymbol(func));
	pfn_ExportExChangeUserCert ptr = (pfn_ExportExChangeUserCert)sl.getSymbol(func);
	assertNotNullPtr(ptr);
}

void SOFProviderTest::testGetCertInfo()
{
	typedef BSTR (*pfn_GetCertInfo)(BSTR Base64EncodeCert, short Type);

	std::string func("SOF_GetCertInfo");
	assert(sl.isLoaded());
	assert(sl.hasSymbol(func));
	pfn_GetCertInfo ptr = (pfn_GetCertInfo)sl.getSymbol(func);
	assertNotNullPtr(ptr);
}

void SOFProviderTest::testSignData()
{
	typedef BSTR (*pfn_SignData)(BSTR ContainerName, BSTR InData);

	std::string func("SOF_SignData");
	assert(sl.isLoaded());
	assert(sl.hasSymbol(func));
	pfn_SignData ptr = (pfn_SignData)sl.getSymbol(func);
	assertNotNullPtr(ptr);
}

void SOFProviderTest::testVerifySignedData()
{
	typedef BOOL (*pfn_VerifySignedData)(BSTR Base64EncodeCert, BSTR InData, BSTR SignValue);

	std::string func("SOF_VerifySignedData");
	assert(sl.isLoaded());
	assert(sl.hasSymbol(func));
	pfn_VerifySignedData ptr = (pfn_VerifySignedData)sl.getSymbol(func);
	assertNotNullPtr(ptr);
}

void SOFProviderTest::testOpenDevice()
{
	typedef int (*pfn_OpenDevice)(void);

	std::string func("SOF_OpenDevice");
	assert(sl.isLoaded());
	assert(sl.hasSymbol(func));
	pfn_OpenDevice ptr = (pfn_OpenDevice)sl.getSymbol(func);
	assertNotNullPtr(ptr);
	int val = ptr();
	assertEqual(0, val);
	std::cout << val << std::endl;
}

void SOFProviderTest::testCloseDevice()
{
	typedef int (*pfn_CloseDevice)(void);

	std::string func("SOF_CloseDevice");
	assert(sl.isLoaded());
	assert(sl.hasSymbol(func));
	pfn_CloseDevice ptr = (pfn_CloseDevice)sl.getSymbol(func);
	assertNotNullPtr(ptr);
	int val = ptr();
	assertEqual(0, val);
	std::cout << val << std::endl;
}

void SOFProviderTest::testGetDeviceInfo()
{
	/*
	std::string func("SOF_GetDeviceInfo");
	assert(sl.isLoaded());
	assert(sl.hasSymbol(func));
	ptr = ()sl.getSymbol(func);
	assertNotNullPtr(ptr);
	*/
}

void SOFProviderTest::testGenRandom()
{
	typedef BSTR (*pfn_GenRandom)(short RandomLen);

	std::string func("SOF_GenRandom");
	assert(sl.isLoaded());
	assert(sl.hasSymbol(func));
	pfn_GenRandom ptr = (pfn_GenRandom)sl.getSymbol(func);
	assertNotNullPtr(ptr);

	BSTR ran = ptr(35);

	std::cout << "true random:" << ran << std::endl;
}

void SOFProviderTest::testEncryptFile()
{
	typedef BOOL (*pfn_EncryptFile)(BSTR Pwd, BSTR InFile, BSTR OutFile);

	std::string func("SOF_EncryptFile");
	assert(sl.isLoaded());
	assert(sl.hasSymbol(func));
	pfn_EncryptFile ptr = (pfn_EncryptFile)sl.getSymbol(func);
	assertNotNullPtr(ptr);
}

void SOFProviderTest::testDecryptFile()
{
	typedef BOOL (*pfn_DecryptFile)(BSTR Pwd, BSTR InFile, BSTR OutFile);

	std::string func("SOF_DecryptFile");
	assert(sl.isLoaded());
	assert(sl.hasSymbol(func));
	pfn_DecryptFile ptr = (pfn_DecryptFile)sl.getSymbol(func);
	assertNotNullPtr(ptr);
}

void SOFProviderTest::testAsEncrypt()
{
	typedef BSTR (*pfn_AsEncrypt)(BSTR ContainerName, BSTR InData);

	std::string func("SOF_AsEncrypt");
	assert(sl.isLoaded());
	assert(sl.hasSymbol(func));
	pfn_AsEncrypt ptr = (pfn_AsEncrypt)sl.getSymbol(func);
	assertNotNullPtr(ptr);
}

void SOFProviderTest::testAsDecrypt()
{
	typedef BSTR (*pfn_AsDecrypt)(BSTR ContainerName, BSTR Indata);

	std::string func("SOF_AsDecrypt");
	assert(sl.isLoaded());
	assert(sl.hasSymbol(func));
	pfn_AsDecrypt ptr = (pfn_AsDecrypt)sl.getSymbol(func);
	assertNotNullPtr(ptr);
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

	/*CppUnit_addTest(pSuite, SOFProviderTest, testGetVersion);
	CppUnit_addTest(pSuite, SOFProviderTest, testSetSignMethod);
	CppUnit_addTest(pSuite, SOFProviderTest, testSetEncryptMethod);
	CppUnit_addTest(pSuite, SOFProviderTest, testGetUserList);
	CppUnit_addTest(pSuite, SOFProviderTest, testExportUserCert);
	CppUnit_addTest(pSuite, SOFProviderTest, testLogin);
	CppUnit_addTest(pSuite, SOFProviderTest, testGetPinRetryCount);
	CppUnit_addTest(pSuite, SOFProviderTest, testChangePassWd);
	CppUnit_addTest(pSuite, SOFProviderTest, testExportExChangeUserCert);
	CppUnit_addTest(pSuite, SOFProviderTest, testGetCertInfo);
	CppUnit_addTest(pSuite, SOFProviderTest, testSignData);
	CppUnit_addTest(pSuite, SOFProviderTest, testVerifySignedData);*/
	CppUnit_addTest(pSuite, SOFProviderTest, testOpenDevice);
	CppUnit_addTest(pSuite, SOFProviderTest, testCloseDevice);
	/*CppUnit_addTest(pSuite, SOFProviderTest, testGetDeviceInfo);
	CppUnit_addTest(pSuite, SOFProviderTest, testGenRandom);
	CppUnit_addTest(pSuite, SOFProviderTest, testEncryptFile);
	CppUnit_addTest(pSuite, SOFProviderTest, testDecryptFile);
	CppUnit_addTest(pSuite, SOFProviderTest, testAsEncrypt);
	CppUnit_addTest(pSuite, SOFProviderTest, testAsDecrypt);*/

	return pSuite;
}
