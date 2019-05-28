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
	Reach::RSFoundation rsf;
	//rsf.RS_GetCertBase64String()
}

void RSProviderTest::testRSGetCertInfo()
{

}

void RSProviderTest::testRSCertLogin()
{
}

void RSProviderTest::testRSGetPinRetryCount()
{
	
}

void RSProviderTest::testRSKeyGetKeySn()
{
}

void RSProviderTest::testRSKeySignByP1()
{
}

void RSProviderTest::testRSVerifySignByP1()
{
}

void RSProviderTest::testRSKeyEncryptData()
{
}

void RSProviderTest::testRSKeyDecryptData()
{
}

void RSProviderTest::testRSKeyEncryptByDigitalEnvelope()
{
}

void RSProviderTest::testRSKeyDecryptByDigitalEnvelope()
{
}

void RSProviderTest::setUp()
{
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
	CppUnit_addTest(pSuite, RSProviderTest, testRSKeyEncryptData);
	CppUnit_addTest(pSuite, RSProviderTest, testRSKeyDecryptData);
	CppUnit_addTest(pSuite, RSProviderTest, testRSKeyEncryptByDigitalEnvelope);
	CppUnit_addTest(pSuite, RSProviderTest, testRSKeyDecryptByDigitalEnvelope);

	return pSuite;
}
