//
// SealProviderTest.cpp
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#include "SealProviderTest.h"
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

SealProviderTest::SealProviderTest(const std::string& name): CppUnit::TestCase(name)
{
}


SealProviderTest::~SealProviderTest()
{
}

void SealProviderTest::testIsUSBKeyExist()
{
	//接口说明：
	//原型：int IsUKIn()
	//描述：判断签章设备是否连接
	//返回值：0 签章设备存在 其他值签章设备不存在
	typedef int(*IsUKIn)();

	assert(sl.isLoaded());
	assert(sl.hasSymbol("IsUKIn"));
	IsUKIn fnTest = (IsUKIn)sl.getSymbol("IsUKIn");
	assertNotNullPtr(fnTest);
	int val = fnTest();
	std::ostringstream ostr;
	ostr << "The function actual result is :" << val << std::endl;
	ostr << "We will test Now!" << std::endl;
	std::cout << ostr.str() << std::endl;
	assertEqual(SealProviderTest::connected, fnTest());
}

void SealProviderTest::testGetSealCount()
{
	//描述：获取签章数目
	//返回值：签章数目
	typedef int(*GetSealCount)();

	assert(sl.isLoaded());
	assert(sl.hasSymbol("GetSealCount"));
	GetSealCount fnTest = (GetSealCount)sl.getSymbol("GetSealCount");
	assertNotNullPtr(fnTest);
	int val = fnTest();
	std::ostringstream ostr;
	ostr << "The function actual result is :" << val << std::endl;
	ostr << "We will test Now!" << std::endl;
	std::cout << ostr.str() << std::endl;
	assert(fnTest() > 0);
}

void SealProviderTest::testReadSealContent()
{
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

	assert(sl.isLoaded());
	assert(sl.hasSymbol("ReadSealData"));
	ReadSealData fnTest = (ReadSealData)sl.getSymbol("ReadSealData");
	assertNotNullPtr(fnTest);
	std::string content = fnTest(all_seal);
	assert(!content.empty());
	std::ostringstream ostr("We will test Now!");
	std::cout << ostr.str() << std::endl 
		<< content << std::endl;
}

void SealProviderTest::setUp()
{
	std::string path = "XSSealProviderLib.dll";
	sl.load(path);
	assert(sl.isLoaded());
}


void SealProviderTest::tearDown()
{
	sl.unload();
	assert(!sl.isLoaded());
}


CppUnit::Test* SealProviderTest::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("SealProviderTest");

	CppUnit_addTest(pSuite, SealProviderTest, testIsUSBKeyExist);
	CppUnit_addTest(pSuite, SealProviderTest, testGetSealCount);
	CppUnit_addTest(pSuite, SealProviderTest, testReadSealContent);

	return pSuite;
}
