//
// SealProviderTest.h
//
// Definition of the SealProviderTest class.
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef SealProviderTest_INCLUDED
#define SealProviderTest_INCLUDED


#include "Poco/Foundation.h"
#include "Poco/SharedLibrary.h"
#include "CppUnit/TestCase.h"


class SealProviderTest: public CppUnit::TestCase
{
public:
	SealProviderTest(const std::string& name);
	~SealProviderTest();

	void testIsUSBKeyExist();
	void testGetSealCount();
	void testReadSealContent();

	void setUp();
	void tearDown();

	static CppUnit::Test* suite();

protected:
	//接口说明：
	//原型：int IsUKIn()
	//描述：判断签章设备是否连接
	//返回值：0 签章设备存在 其他值签章设备不存在
	typedef int(*IsUKIn)();

	//描述：获取签章数目
	//返回值：签章数目
	typedef int(*GetSealCount)();

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

	void setupLogger();
private:
	static const int connected = 0;
	static const int all_seal = -1;
	static const int frist_seal_index = 0;
	static int count;

	Poco::SharedLibrary sl;
};


#endif // SealProviderTest_INCLUDED
