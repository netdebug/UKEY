//
// RSProviderTest.h
//
// Definition of the RSProviderTest class.
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef RSProviderTest_INCLUDED
#define RSProviderTest_INCLUDED


#include "Poco/Foundation.h"
#include "Poco/SharedLibrary.h"
#include "CppUnit/TestCase.h"


class RSProviderTest: public CppUnit::TestCase
{
	enum certType { sign = 1, crypto };
public:
	RSProviderTest(const std::string& name);
	~RSProviderTest();

	//14 RS Interfaces
/*	void testRSGetConfigParameters();
	void testRSConfigParameters()*/;
	void testRSGetUserList();
	void testRSGetCertBase64String();
	void testRSGetCertInfo();
	void testRSCertLogin();
	void testRSGetPinRetryCount();
	void testRSKeyGetKeySn();
	void testRSKeySignByP1();
	void testRSVerifySignByP7();
	void testRsaEncryptAndDecrypt();
	void testSymEncryptAndDecrypt();
	void testDesEncryptAndDecrypt();
	void testMethodInfomation();
	void testSignVerifyByFile();
	void testRSKeyEncryptByDigitalEnvelope();
	void testRSKeyDecryptByDigitalEnvelope();

	void waitforuser();

	void setUp();
	void tearDown();

	static CppUnit::Test* suite();

private:
	Poco::SharedLibrary sl;
	std::string uid;
	std::string selected;
	std::string pwd;
};


#endif // RSProviderTest_INCLUDED
