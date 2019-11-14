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
	//�ӿ�˵����
	//ԭ�ͣ�int IsUKIn()
	//�������ж�ǩ���豸�Ƿ�����
	//����ֵ��0 ǩ���豸���� ����ֵǩ���豸������
	typedef int(*IsUKIn)();

	//��������ȡǩ����Ŀ
	//����ֵ��ǩ����Ŀ
	typedef int(*GetSealCount)();

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

	void setupLogger();
private:
	static const int connected = 0;
	static const int all_seal = -1;
	static const int frist_seal_index = 0;
	static int count;

	Poco::SharedLibrary sl;
};


#endif // SealProviderTest_INCLUDED
