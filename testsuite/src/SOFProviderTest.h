//
// SOFProviderTest.h
//
// Definition of the SOFProviderTest class.
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef SOFProviderTest_INCLUDED
#define SOFProviderTest_INCLUDED


#include "Poco/Foundation.h"
#include "Poco/SharedLibrary.h"
#include "CppUnit/TestCase.h"


class SOFProviderTest: public CppUnit::TestCase
{
public:
	SOFProviderTest(const std::string& name);
	~SOFProviderTest();

	
	void testGetVersion();
	void testSetSignMethod();
	void testSetEncryptMethod();

	//User Interaciton
	void testGetUserList();
	void testExportUserCert();
	void testLogin();
	void testGetPinRetryCount();
	void testChangePassWd();
	void testExportExChangeUserCert();

	void testGetCertInfo();
	void testSignData();
	void testVerifySignedData();

	//Device Commuication
	void testOpenDevice();
	void testCloseDevice();
	void testGetDeviceInfo();
	
	void testGenRandom();

	void testEncryptFile();
	void testDecryptFile();

	void testAsEncrypt();
	void testAsDecrypt();

	void setUp();
	void tearDown();

	static CppUnit::Test* suite();

private:
	Poco::SharedLibrary sl;
};


#endif // SOFProviderTest_INCLUDED
