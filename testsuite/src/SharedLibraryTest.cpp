//
// SharedLibraryTest.cpp
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#include "SharedLibraryTest.h"
#include "CppUnit/TestCaller.h"
#include "CppUnit/TestSuite.h"
#include "Poco/SharedLibrary.h"
#include "Poco/Exception.h"


using Poco::SharedLibrary;
using Poco::NotFoundException;
using Poco::LibraryLoadException;
using Poco::LibraryAlreadyLoadedException;

#define CONNECT 0
#define ALL_SEAL -1
#define SEAL_BEGIN 0

#include <stdio.h>
#include <sstream>
#include "Poco/StreamCopier.h"

using namespace Poco;
//接口说明：
//原型：int IsUKIn()
//描述：判断签章设备是否连接
//返回值：0 签章设备存在 其他值签章设备不存在
typedef int (*IsUKIn)();

//描述：获取签章数目
//返回值：签章数目
typedef int (*GetSealCount)();

//描述：获取签章数据
//参数：nIndex 签章索引 0为第一个章，以此类推 - 1获取所有签章
//返回值：签章数据
typedef char* (*ReadSealData)(int nIndex);
//ReadSealData 返回值格式如下：
//<sealinfos>
//	<sealbaseinfo>
//		<username>用户名称</username>
//		<projectname>项目名称</projectname>
//	</sealbaseinfo>
//	<sealinfo>	//如果有多个签章，则会有多个此节点
//		<sealname>签章名称</sealname>
//		<sealtime>签章到期时间</sealtime>
//		<sealdata>签章印模base64数据</sealdata>
//	</sealinfo>
//</sealinfos>

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

SharedLibraryTest::SharedLibraryTest(const std::string& name): CppUnit::TestCase(name)
{
}


SharedLibraryTest::~SharedLibraryTest()
{
}

void SharedLibraryTest::testSKFInterface()
{
	/*std::string path = "SKFAPI20549.DLL";
	SharedLibrary sl;
	sl.load(path);
	assert(sl.isLoaded());

	SKF_EnumDev fn_SKF_EnumDev = (SKF_EnumDev)sl.getSymbol("SKF_EnumDev");

	ULONG pulSize;
	char szNameList[2048] = {0};
	assert(SAR_OK == fn_SKF_EnumDev(true, szNameList, &pulSize));

	SKF_ConnectDev fn_SKF_ConnectDev = (SKF_ConnectDev)sl.getSymbol("SKF_ConnectDev");

	DEVHANDLE hDev = NULL;
	assert(SAR_OK == fn_SKF_ConnectDev(szNameList, &hDev) && hDev);

	DEVINFO devInfo;
	SKF_GetDevInfo fn_SKF_GetDevInfo = (SKF_GetDevInfo)sl.getSymbol("SKF_GetDevInfo");
	assert(SAR_OK == fn_SKF_GetDevInfo(hDev, &devInfo));

	SKF_DisConnectDev fn_SKF_DisConnectDev = (SKF_DisConnectDev)sl.getSymbol("SKF_DisConnectDev");
	assert(SAR_OK == fn_SKF_DisConnectDev(hDev));

	sl.unload();
	assert(!sl.isLoaded());*/
}

void SharedLibraryTest::setUp()
{
}


void SharedLibraryTest::tearDown()
{
}


CppUnit::Test* SharedLibraryTest::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("SharedLibraryTest");

	CppUnit_addTest(pSuite, SharedLibraryTest, testSKFInterface);

	return pSuite;
}
