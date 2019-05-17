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
#include <stdio.h>
#include <sstream>

using Poco::SharedLibrary;
using Poco::NotFoundException;
using Poco::LibraryLoadException;
using Poco::LibraryAlreadyLoadedException;

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
	std::string fnName("IsUKIn");

	assert(sl.isLoaded());
	assert(sl.hasSymbol(fnName));
	IsUKIn fnTest = (IsUKIn)sl.getSymbol(fnName);
	assertNotNullPtr(fnTest);
	int val = fnTest();
	std::ostringstream ostr;
	ostr << "API:"<< fnName << std::endl;
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
	std::string fnName("GetSealCount");

	assert(sl.isLoaded());
	assert(sl.hasSymbol(fnName));
	GetSealCount fnTest = (GetSealCount)sl.getSymbol(fnName);
	assertNotNullPtr(fnTest);
	int val = fnTest();
	std::ostringstream ostr;
	ostr << "API:" << fnName << std::endl;
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
	typedef char* (*ReadSealData)(int nIndex);
	std::string fnName("ReadSealData");


	assert(sl.isLoaded());
	assert(sl.hasSymbol(fnName));
	ReadSealData fnTest = (ReadSealData)sl.getSymbol(fnName);
	assertNotNullPtr(fnTest);
	std::string content = fnTest(SealProviderTest::all_seal);
	assert(!content.empty());
	std::cout << "API:"<< fnName << std::endl;
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
