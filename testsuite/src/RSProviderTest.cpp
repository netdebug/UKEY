//
// RSProviderTest.cpp
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#include "RSProviderTest.h"
#include "RSFoundation.h"
#include "CppUnit/TestCaller.h"
#include "CppUnit/TestSuite.h"
#include "Poco/SharedLibrary.h"
#include "Poco/Exception.h"
#include "Poco/StreamCopier.h"
#include "Poco/JSON/Parser.h"
#include "Poco/JSON/Array.h"
#include "Poco/Dynamic/Struct.h"
#include <stdio.h>
#include <sstream>
#include <iostream>

//#include "GMCrypto.h"
//#include "SOFProvider.h"

using Poco::SharedLibrary;
using Poco::NotFoundException;
using Poco::LibraryLoadException;
using Poco::LibraryAlreadyLoadedException;
using namespace Poco::JSON;
using namespace Poco::Dynamic;
using Poco::DynamicStruct;

RSProviderTest::RSProviderTest(const std::string& name): CppUnit::TestCase(name)
{
}


RSProviderTest::~RSProviderTest()
{
}

void RSProviderTest::testRSGetUserList()
{
	try
	{
		Reach::RSFoundation rsf;
		std::string json = rsf.RS_GetUserList();
		std::cout << json << std::endl;
		Parser parser;
		Var result = parser.parse(json);
		Object object = *result.extract<Object::Ptr>();
		assert(result.type() == typeid(Object::Ptr));

		DynamicStruct ds = object;
		assert(ds["code"] == "0000");
	}
	catch (JSONException& jsone)
	{
		std::cout << jsone.message() << std::endl;
	}
	catch (Poco::Exception& e)
	{
		std::cout << e.message() << std::endl;
	}
}

void RSProviderTest::testRSGetCertBase64String()
{
	enum certType { sign = 0, crypto };
	Reach::RSFoundation rsf;
	std::string signd = rsf.RS_GetCertBase64String(sign, uid);
	std::cout << "signd" << signd << std::endl;
	std::string cypto = rsf.RS_GetCertBase64String(crypto, uid);
	std::cout << "cypto" << cypto << std::endl;
}

void RSProviderTest::testRSGetCertInfo()
{
	#define SGD_CERT_VERSION 0x00000001
	#define SGD_CERT_SERIAL 0x00000002

	Reach::RSFoundation rsf;
	enum certType { sign = 0, crypto };
	
	{
		std::string cert = rsf.RS_GetCertBase64String(sign, uid);
		std::cout << "SGD_CERT_SERIAL" << rsf.RS_GetCertInfo(cert, SGD_CERT_VERSION) << std::endl;
		std::cout << "SGD_CERT_SERIAL" << rsf.RS_GetCertInfo(cert, SGD_CERT_SERIAL) << std::endl;
	}


	{
		std::string cert = rsf.RS_GetCertBase64String(crypto, uid);
		std::cout << "SGD_CERT_SERIAL" << rsf.RS_GetCertInfo(cert, SGD_CERT_VERSION) << std::endl;
		std::cout << "SGD_CERT_SERIAL" << rsf.RS_GetCertInfo(cert, SGD_CERT_SERIAL) << std::endl;
	}
}

void RSProviderTest::testRSCertLogin()
{
	Reach::RSFoundation rsf;
	std::string xia('0', 8);
	std::string lg('1', 6);
	std::cout << "RS_CertLogin except ok:" << rsf.RS_CertLogin(uid, xia) << std::endl;
	std::cout << "RS_CertLogin except failed:" << rsf.RS_CertLogin(uid, lg) << std::endl;
}

void RSProviderTest::testRSGetPinRetryCount()
{
	Reach::RSFoundation rsf;
	std::cout << "Retry Count:" << rsf.RS_GetPinRetryCount(uid) << std::endl;
}

void RSProviderTest::testRSKeyGetKeySn()
{
	Reach::RSFoundation rsf;
	rsf.RS_KeyGetKeySn(uid);
}

void RSProviderTest::testRSKeySignByP1()
{
}

void RSProviderTest::testRSVerifySignByP1()
{
}

void RSProviderTest::testRsaEncryptAndDecrypt()
{
	Reach::RSFoundation rsf;
	std::string paintText("what is up? what the fucking library!");
	enum certType { sign = 0, crypto };
	std::string cert = rsf.RS_GetCertBase64String(crypto, uid);
	std::string encrypt = rsf.RS_KeyEncryptData(paintText, cert);
	
	std::cout << "" << paintText << std::endl;

	std::string decrypt = rsf.RS_KeyDecryptData(uid, encrypt);

	assert(paintText == decrypt);
}

#include "Poco/File.h"
void RSProviderTest::testSymEncryptAndDecrypt()
{
	Reach::RSFoundation rsf;
	std::string paintDir("F:/source/RSTestRunner/bin/paintText.txt");
	std::string encryptDir("F:/source/RSTestRunner/bin/encryptText.txt");
	std::string jsonkv = rsf.RS_EncryptFile(paintDir, encryptDir);

	std::cout
		<< paintDir << std::endl
		<< encryptDir << std::endl
		<< "RS_EncryptFile:jsonkv\n" << jsonkv << std::endl;

	Parser parser;
	Var result = parser.parse(jsonkv);
	Object object = *result.extract<Object::Ptr>();
	assert(result.type() == typeid(Object::Ptr));

	DynamicStruct ds = object;
	std::string kv = ds["synKey"];

	std::string in("F:/source/RSTestRunner/bin/encryptText.txt");
	std::string out("F:/source/RSTestRunner/bin/DecryOut.txt");
	std::string decrypt = rsf.RS_DecryptFile(kv, in, out);

	std::cout 
		<< in << std::endl << out << std::endl << 
		"RS_DecryptFile:decrypt\n" << decrypt << std::endl;
}

void RSProviderTest::testRSKeyEncryptByDigitalEnvelope()
{
}

void RSProviderTest::testRSKeyDecryptByDigitalEnvelope()
{
}

void RSProviderTest::setUp()
{
	uid = "{1B57694E-911E-41D9-8123-971EDD71342C}";
	//std::string path = "RSProvider.dll";
	//sl.load(path);
	//assert(sl.isLoaded());
}


void RSProviderTest::tearDown()
{
	//sl.unload();
	//assert(!sl.isLoaded());
}


CppUnit::Test* RSProviderTest::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("RSProviderTest");

	/*CppUnit_addTest(pSuite, RSProviderTest, testRSGetConfigParameters);
	CppUnit_addTest(pSuite, RSProviderTest, testRSConfigParameters);*/
	CppUnit_addTest(pSuite, RSProviderTest, testRSGetUserList);
	CppUnit_addTest(pSuite, RSProviderTest, testRSGetCertBase64String);
	CppUnit_addTest(pSuite, RSProviderTest, testRSGetCertInfo);
	CppUnit_addTest(pSuite, RSProviderTest, testRSCertLogin);
	CppUnit_addTest(pSuite, RSProviderTest, testRSGetPinRetryCount);
	CppUnit_addTest(pSuite, RSProviderTest, testRSKeyGetKeySn);
	CppUnit_addTest(pSuite, RSProviderTest, testRSKeySignByP1);
	CppUnit_addTest(pSuite, RSProviderTest, testRSVerifySignByP1);
	CppUnit_addTest(pSuite, RSProviderTest, testRsaEncryptAndDecrypt);
	CppUnit_addTest(pSuite, RSProviderTest, testSymEncryptAndDecrypt);
	CppUnit_addTest(pSuite, RSProviderTest, testRSKeyEncryptByDigitalEnvelope);
	CppUnit_addTest(pSuite, RSProviderTest, testRSKeyDecryptByDigitalEnvelope);

	return pSuite;
}
