//
// GmskfProviderTest.cpp
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#include "GmskfProviderTest.h"
#include "CppUnit/TestCaller.h"
#include "CppUnit/TestSuite.h"
#include "Poco/SharedLibrary.h"
#include "Poco/Exception.h"
#include <stdio.h>
#include <sstream>

using Poco::SharedLibrary;
using Poco::NotFoundException;
using Poco::LibraryLoadException;
using Poco::LibraryAlreadyLoadedException;

#define DEVAPI __stdcall
#define SAR_OK 0x00000000

typedef struct Struct_Version {
	BYTE	major;
	BYTE	minor;
}VERSION;

typedef struct Struct_DEVINFO {
	VERSION Version;
	CHAR	Manufacturer[64];
	CHAR	Issuer[32];
	CHAR	Label[32];
	CHAR	SerialNumber[32];
	VERSION HWVersion;
	VERSION FirmwareVersion;
	ULONG	AlgSymCap;
	ULONG	AlgAsymCap;
	ULONG	AlgHashCap;
	ULONG	DevAuthAlgId;
	ULONG	TotalSpace;
	ULONG	FreeSpace;
	ULONG	MaxECCBufferSize;
	ULONG	MaxBufferSize;
	BYTE	Reserved[64];
}DEVINFO,	*PDEVINFO;

typedef HANDLE DEVHANDLE;
typedef ULONG	(DEVAPI *SKF_EnumDev)(BOOL bPresent, LPCSTR szNameList, ULONG* pulSize);
typedef ULONG	(DEVAPI *SKF_ConnectDev)(LPCSTR szName, DEVHANDLE* phDev);
typedef ULONG	(DEVAPI *SKF_DisConnectDev)(DEVHANDLE phDev);
typedef ULONG	(DEVAPI *SKF_GetDevInfo)(DEVHANDLE hDev, DEVINFO* pDevInfo);

GmskfProviderTest::GmskfProviderTest(const std::string& name): CppUnit::TestCase(name)
{
}


GmskfProviderTest::~GmskfProviderTest()
{
}

void GmskfProviderTest::testEnumDev()
{
	std::string fnName("SKF_EnumDev");

	assert(sl.isLoaded());
	assert(sl.hasSymbol(fnName));
	SKF_EnumDev fnTest = (SKF_EnumDev)sl.getSymbol(fnName);
	assertNotNullPtr(fnTest);

	ULONG pulSize = 0;
	char szNameList[2048] = {0};
	assertEqual(SAR_OK, fnTest(true, szNameList, &pulSize));

	std::ostringstream ostr;
	ostr << "API:" << fnName << std::endl;
	ostr << "The function actual result is :" << std::string(szNameList, pulSize) << std::endl;
	ostr << "We will test Now!" << std::endl;
	std::cout << ostr.str() << std::endl;
}

void GmskfProviderTest::testGetDevInfo()
{
	ULONG pulSize = 0;
	char szNameList[2048] = { 0 };
	DEVHANDLE hDev = NULL;

	{
		std::string fnName("SKF_EnumDev");
		assert(sl.isLoaded());
		assert(sl.hasSymbol(fnName));
		SKF_EnumDev fnTest = (SKF_EnumDev)sl.getSymbol(fnName);
		assertNotNullPtr(fnTest);

		//ULONG pulSize = 0;
		//char szNameList[2048] = { 0 };
		assertEqual(SAR_OK, fnTest(true, szNameList, &pulSize));
	}
	
	{
		std::string fnName("SKF_ConnectDev");
		assert(sl.isLoaded());
		assert(sl.hasSymbol(fnName));
		SKF_ConnectDev fnTest = (SKF_ConnectDev)sl.getSymbol(fnName);
		assertNotNullPtr(fnTest);

		/*DEVHANDLE hDev = NULL;*/
		assertEqual(SAR_OK, fnTest(szNameList, &hDev));
		assertNotNullPtr(hDev);
	}

	{
		std::string fnName("SKF_GetDevInfo");
		assert(sl.isLoaded());
		assert(sl.hasSymbol(fnName));
		SKF_GetDevInfo fnTest = (SKF_GetDevInfo)sl.getSymbol(fnName);
		assertNotNullPtr(fnTest);

		DEVINFO devInfo = { 0 };
		assertEqual(SAR_OK, fnTest(hDev, &devInfo));

		std::ostringstream ostr;
		ostr << "devInfo.Version:" << devInfo.Version.major << "-" << devInfo.Version.minor << std::endl
			<< "devInfo.Manufacturer:" <<devInfo.Manufacturer << std::endl
			<< "devInfo.Issuer:" << devInfo.Issuer << std::endl 
			<< "devInfo.Label:" << devInfo.Label << std::endl
			<< "devInfo.SerialNumber" << devInfo.SerialNumber << std::endl 
			<< "devInfo.HWVersion:" << devInfo.HWVersion.major << "-" << devInfo.HWVersion.minor << std::endl
			<< "devInfo.FirmwareVersion:" << devInfo.FirmwareVersion.major << "-" << devInfo.FirmwareVersion.minor 
			<< std::endl;

		std::cout << ostr.str() << std::endl;
	}

	{
		std::string fnName("SKF_DisConnectDev");
		assert(sl.isLoaded());
		assert(sl.hasSymbol(fnName));
		SKF_DisConnectDev fnTest = (SKF_DisConnectDev)sl.getSymbol(fnName);
		assertNotNullPtr(fnTest);
		assertEqual(SAR_OK, fnTest(hDev));
	}
}

void GmskfProviderTest::setUp()
{
	//std::string path = "SKFAPI20549.dll";
	std::string path = "SKF_APP_XS.dll";
	sl.load(path);
	assert(sl.isLoaded());
}


void GmskfProviderTest::tearDown()
{
	sl.unload();
	assert(!sl.isLoaded());
}


CppUnit::Test* GmskfProviderTest::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("GmskfProviderTest");

	CppUnit_addTest(pSuite, GmskfProviderTest, testEnumDev);
	CppUnit_addTest(pSuite, GmskfProviderTest, testGetDevInfo);

	return pSuite;
}
