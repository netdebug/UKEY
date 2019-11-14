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
#include "Poco/Logger.h"
#include "Poco/LogStream.h"
#include "Poco/WindowsConsoleChannel.h"
#include "Poco/AutoPtr.h"
#include <stdio.h>
#include <iostream>
#include <sstream>

using Poco::SharedLibrary;
using Poco::NotFoundException;
using Poco::LibraryLoadException;
using Poco::LibraryAlreadyLoadedException;
using Poco::Logger;
using Poco::LogStream;
using Poco::Channel;
using Poco::WindowsColorConsoleChannel;
using Poco::Message;
using Poco::AutoPtr;

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
}DEVINFO, *PDEVINFO;

typedef HANDLE DEVHANDLE;
typedef ULONG	(DEVAPI *SKF_WaitForDevEvent)(LPSTR szDevName, ULONG *pulDevNameLen, ULONG *pulEvent);
typedef ULONG	(DEVAPI *SKF_CancelWaitForDevEvent)();
typedef ULONG	(DEVAPI *SKF_EnumDev)(BOOL bPresent, LPCSTR szNameList, ULONG* pulSize);
typedef ULONG	(DEVAPI *SKF_ConnectDev)(LPCSTR szName, DEVHANDLE* phDev);
typedef ULONG	(DEVAPI *SKF_DisConnectDev)(DEVHANDLE phDev);
typedef ULONG	(DEVAPI *SKF_GetDevState)(LPCSTR szDevName, ULONG * pulDevState);
typedef ULONG	(DEVAPI *SKF_SetLabel)(DEVHANDLE hDev, LPSTR szLabel);
typedef ULONG	(DEVAPI *SKF_GetDevInfo)(DEVHANDLE hDev, DEVINFO* pDevInfo);
typedef ULONG	(DEVAPI *SKF_LockDev)(DEVHANDLE hDev, ULONG ulTimeOut);
typedef ULONG	(DEVAPI *SKF_UnlockDev)(DEVHANDLE hDev);
typedef ULONG	(DEVAPI *SKF_Transmit)(DEVHANDLE hDev, BYTE * pbCommand, ULONG ulCommandLen, BYTE * pbData, ULONG * pulDataLen);

typedef ULONG	(DEVAPI *SKF_GetLastError)();

GmskfProviderTest::GmskfProviderTest(const std::string& name)
	: CppUnit::TestCase(name)
{
	pChannel = new WindowsColorConsoleChannel;
	pChannel->setProperty("traceColor", "lightGreen");
	Logger& root = Poco::Logger::get("LoggerTest");//Logger::root();
	root.setChannel(pChannel.get());
	root.setLevel(Message::PRIO_TRACE);

	//std::string path = "SKF_Library\\001\\SKF_APP_XS.dll";
	//std::string path = "SKF_Library\\002\\SKFAPI20549.dll";
	std::string path = "SKF_Library\\003\\lgu3073_p1514_gm.dll";
	sl.load(path);
	assert(sl.isLoaded());
}


GmskfProviderTest::~GmskfProviderTest()
{
	sl.unload();
	assert(!sl.isLoaded());
}

void GmskfProviderTest::testEnumDev()
{
	ULONG pulSize = 512;
	std::string name(pulSize, 0);
	//std::vector<char> list(name.data(), name.data() + name.size() + 1u);
	auto p = name.data();
	assertEqual(SAR_OK, Symbol(SKF_EnumDev)(true, p, &pulSize));
	
	Poco::LogStream ls(Logger::get("LoggerTest"));
	ls.trace()
		<< "testEnumDev :" << name << std::endl;

	
}

void GmskfProviderTest::testGetDevInfo()
{
	ULONG pulSize = 2048;
	char szNameList[2048] = { 0 };
	DEVHANDLE hDev = NULL;

	{
		SKF_EnumDev fnTest = getSymbol<SKF_EnumDev>("SKF_EnumDev");
		assertEqual(SAR_OK, fnTest(true, szNameList, &pulSize));
	}

	{
		SKF_ConnectDev fnTest = getSymbol<SKF_ConnectDev>("SKF_ConnectDev");
		assertEqual(SAR_OK, fnTest(szNameList, &hDev));
		assertNotNullPtr(hDev);
	}

	{
		DEVINFO* devInfo = (DEVINFO*)malloc(sizeof(DEVINFO));
		memset(devInfo, 0, sizeof(devInfo));
		SKF_GetDevInfo fnTest = Symbol(SKF_GetDevInfo);
		assertEqual(SAR_OK, fnTest(hDev, devInfo));
		/*
		Poco::LogStream ls(Logger::get("LoggerTest"));

		ls.trace() << "devInfo->Version:" << std::to_string(devInfo->Version.major) << "." << std::to_string(devInfo->Version.minor) << std::endl
			<< "devInfo->Manufacturer:" << devInfo->Manufacturer << std::endl
			<< "devInfo->Issuer:" << devInfo->Issuer << std::endl
			<< "devInfo->Label:" << devInfo->Label << std::endl
			<< "devInfo->SerialNumber" << devInfo->SerialNumber << std::endl
			<< "devInfo->HWVersion:" << std::to_string(devInfo->HWVersion.major) << "." << std::to_string(devInfo->HWVersion.minor) << std::endl
			<< "devInfo->FirmwareVersion:" << std::to_string(devInfo->FirmwareVersion.major) << "." << std::to_string(devInfo->FirmwareVersion.minor)
			<< std::endl;
			*/
		free(devInfo);
	}

	{
		assertEqual(SAR_OK, Symbol(SKF_DisConnectDev)(hDev));
		//hDev = nullptr;
	}
}

#include <iostream>
#include <sstream>

void GmskfProviderTest::testHotSwap()
{
	/*ULONG ulEvent = 0;
	ULONG ulDevNameLen = 2048;*/
	//LPSTR szDevName = new CHAR[ulDevNameLen];
	//std::string name(ulDevNameLen, 'a');
	//std::vector<char> fcv(name.data(), name.data() + name.size() + 1u);
	//auto p = fcv.data();

	ULONG pulSize = 512;
	std::string name(pulSize, 0);
	auto v = name.data();
	assertEqual(SAR_OK, Symbol(SKF_EnumDev)(true, v, &pulSize));

	while (true) {

		/*ULONG Len = fcv.size();
		ULONG result = Symbol(SKF_WaitForDevEvent)(p, &Len, &ulEvent);
		if (SAR_OK != result) {
			ls.trace() << "error - " << std::hex << result << std::endl;
		}
		ls.trace() << "SKF_WaitForDevEvent : " << name << std::endl
			<< "DevNameLen" << Len << std::endl
			<< "Event :" << ulEvent << std::endl;
		assertEqual(SAR_OK, Symbol(SKF_CancelWaitForDevEvent)());*/
		
		testEnumDev();
		/*ULONG ulDevState = 0;
		assertEqual(SAR_OK, Symbol(SKF_GetDevState)(v, &ulDevState));

		ls.trace() << "SKF_GetDevState : " << std::endl
			<< v  << std::endl << "ulDevState : " << ulDevState << std::endl;*/
	}
}

void GmskfProviderTest::setUp()
{
}


void GmskfProviderTest::tearDown()
{
}


CppUnit::Test* GmskfProviderTest::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("GmskfProviderTest");

	CppUnit_addTest(pSuite, GmskfProviderTest, testEnumDev);
	CppUnit_addTest(pSuite, GmskfProviderTest, testGetDevInfo); 
	//CppUnit_addTest(pSuite, GmskfProviderTest, testHotSwap);

	return pSuite;
}
