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
	//�ӿ�˵����
	//ԭ�ͣ�int IsUKIn()
	//�������ж�ǩ���豸�Ƿ�����
	//����ֵ��0 ǩ���豸���� ����ֵǩ���豸������
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
	//��������ȡǩ����Ŀ
	//����ֵ��ǩ����Ŀ
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
	//��������ȡǩ������
	//������nIndex ǩ������ 0Ϊ��һ���£��Դ����� - 1��ȡ����ǩ��
	//����ֵ��ǩ������
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
