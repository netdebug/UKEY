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
//�ӿ�˵����
//ԭ�ͣ�int IsUKIn()
//�������ж�ǩ���豸�Ƿ�����
//����ֵ��0 ǩ���豸���� ����ֵǩ���豸������
typedef int (*IsUKIn)();

//��������ȡǩ����Ŀ
//����ֵ��ǩ����Ŀ
typedef int (*GetSealCount)();

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
