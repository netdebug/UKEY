//
// ActiveXTest.h
//
// Definition of the ActiveXTest class.
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef ActiveXTest_INCLUDED
#define ActiveXTest_INCLUDED


#include "Poco/Foundation.h"
#include "CppUnit/TestCase.h"
#include <wtypes.h>


class ActiveXTest: public CppUnit::TestCase
{
public:
	ActiveXTest(const std::string& name);
	~ActiveXTest();

	void RS_KeyGetKeySn();
	void RS_KeyGetKeySnExt();
	void RS_GetUserList();
	void RS_GetCertBase64String();
	void RS_CertLogin();
	void RS_GetPinRetryCount();
	void RS_ChangePassWd();
	void RS_KeySignByP1();
	void RS_VerifySignByP1();
	void RS_KeyEncryptData();
	void RS_KeyDecryptData();
	void RS_GetCertInfo();
	void RS_KeySignByP7();
	void RS_VerifySignByP7();
	void RS_CloudLoginAuth();
	void RS_CloudSealAuth();
	void RS_CloudGetAuth();
	void RS_CloudGetSealList();
	void RS_CloudSignByP7();
	void RS_CloudGetSignResult();
	void RS_CloudLogoutAuth();
	void RS_CloudEncryptAuth();
	void RS_CloudEncryptData();
	void RS_CloudEncryptFile();
	void RS_CloudDevryptAuth();
	void RS_CloudDevryptData();
	void RS_CloudDevryptFile();
	void RS_CloudReceiveDevryptResult();
	void RS_CloudGetCompanyCert();
	void RS_CloudGetCertAuth();
	void RS_CloudGetCertBase64();
	void RS_CloudLogout();
	void RS_KeyStatus();
	void RS_ConfigParameters();
	void RS_GetParameters();
	void RS_GreateQRCode();
	void RS_GetTransid();
	void RS_EncryptFile();
	void RS_DevryptFile();
	void RS_VerifyIdentity();
	void RS_KeyEncryptFile();
	void RS_KeyDecryptFile();

	void CodeSample();

	void setUp();
	void tearDown();

	std::string parseCode(BSTR str);
	std::string parseData(BSTR str);
	std::string parseCertBase64(BSTR str, std::string name);
	std::string GBKEncodingUTF8(const std::string& instring);
	std::string UTF8EncodingGBK(const std::string& instring);
	static CppUnit::Test* suite();

private:
};


#endif // ActiveXTest_INCLUDED
