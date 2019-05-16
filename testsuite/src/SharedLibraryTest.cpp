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

SharedLibraryTest::SharedLibraryTest(const std::string& name): CppUnit::TestCase(name)
{
}


SharedLibraryTest::~SharedLibraryTest()
{
}

void SharedLibraryTest::testXSSealProviderLib()
{
	std::string path = "XSSealProviderLib.dll";
	//XSSealProviderLibd.dll
	//path.append(SharedLibrary::suffix());
	SharedLibrary sl;
	sl.load(path);
	//assert(sl.getPath() == path);
	assert(sl.isLoaded());

	IsUKIn isUKIn = (IsUKIn)sl.getSymbol("IsUKIn");
	int ret = isUKIn();
	//assert(ret == 0);

	GetSealCount getSealCount = (GetSealCount)sl.getSymbol("GetSealCount");
	int count = getSealCount();
	//assert(getSealCount() > 0);

	ReadSealData readSealData = (ReadSealData)sl.getSymbol("ReadSealData");

	std::string data(readSealData(ALL_SEAL));
	std::istringstream istr(data);
	std::ostringstream ostr;
	std::streamsize n = StreamCopier::copyStreamUnbuffered(istr, ostr);

	sl.unload();
	assert(!sl.isLoaded());
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

	CppUnit_addTest(pSuite, SharedLibraryTest, testXSSealProviderLib);

	return pSuite;
}
