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
	//�ӿ�˵����
	//ԭ�ͣ�int IsUKIn()
	//�������ж�ǩ���豸�Ƿ�����
	//����ֵ��0 ǩ���豸���� ����ֵǩ���豸������
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
	//��������ȡǩ����Ŀ
	//����ֵ��ǩ����Ŀ
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
	//��������ȡǩ������
	//������nIndex ǩ������ 0Ϊ��һ���£��Դ����� - 1��ȡ����ǩ��
	//����ֵ��ǩ������
	typedef char* (*ReadSealData)(int nIndex);
	//ReadSealData ����ֵ��ʽ���£�
	//<sealinfos>
	//	<sealbaseinfo>
	//		<username>�û�����</username>
	//		<projectname>��Ŀ����</projectname>
	//	</sealbaseinfo>
	//	<sealinfo>	//����ж��ǩ�£�����ж���˽ڵ�
	//		<sealname>ǩ������</sealname>
	//		<sealtime>ǩ�µ���ʱ��</sealtime>
	//		<sealdata>ǩ��ӡģbase64����</sealdata>
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
