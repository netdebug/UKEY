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

	
	void testSOFGetVersion();
	void testSOFSetSignMethod();
	void testSOFSetEncryptMethod();

	//User Interaciton
	void testSOFGetUserList();
	void testSOFExportUserCert();
	void testSOFLogin();
	void testSOFGetPinRetryCount();
	void testSOFChangePassWd();
	void testSOFExportExChangeUserCert();

	void testSOFGetCertInfo();
	void testSOFSignData();
	void testSOFVerifySignedData();

	//Device Commuication
	void testOpenDevice();
	void testCloseDevice();
	void testSOFGetDeviceInfo();
	
	void testSOFGenRandom();

	void testSOFEncryptFile();
	void testSOFDecryptFile();

	void testSOFAsEncrypt();
	void testSOFAsDecrypt();

	void setUp();
	void tearDown();

	static CppUnit::Test* suite();

private:
	Poco::SharedLibrary sl;
};


#endif // SOFProviderTest_INCLUDED
