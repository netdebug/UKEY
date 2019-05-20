//
// RSProviderTest.cpp
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#include "RSProviderTest.h"
#include "CppUnit/TestCaller.h"
#include "CppUnit/TestSuite.h"
#include "Poco/SharedLibrary.h"
#include "Poco/Exception.h"
#include <stdio.h>
#include <sstream>
#include "Poco/StreamCopier.h"

using Poco::SharedLibrary;
using Poco::NotFoundException;
using Poco::LibraryLoadException;
using Poco::LibraryAlreadyLoadedException;

RSProviderTest::RSProviderTest(const std::string& name): CppUnit::TestCase(name)
{
}


RSProviderTest::~RSProviderTest()
{
}

void RSProviderTest::testRSGetConfigParameters()
{
	//using FJCA Interface to implement workflow ( in the parenthese)
	{

	}
}

void RSProviderTest::testRSConfigParameters()
{
	//using FJCA Interface to implement workflow ( in the parenthese)
	{

	}
}

void RSProviderTest::testRSGetUserList()
{
	//using FJCA Interface to implement workflow ( in the parenthese)
	{

	}
}

void RSProviderTest::testRSGetCertBase64String()
{
	//using FJCA Interface to implement workflow ( in the parenthese)
	{

	}
}

void RSProviderTest::testRSGetCertInfo()
{
	//using FJCA Interface to implement workflow ( in the parenthese)
	{

	}
}

void RSProviderTest::testRSCertLogin()
{
	//using FJCA Interface to implement workflow ( in the parenthese)
	{

	}
}

void RSProviderTest::testRSGetPinRetryCount()
{
	//using FJCA Interface to implement workflow ( in the parenthese)
	{

	}
}

void RSProviderTest::testRSKeyGetKeySn()
{
	//using FJCA Interface to implement workflow ( in the parenthese)
	{

	}
}

void RSProviderTest::testRSKeySignByP1()
{
	//using FJCA Interface to implement workflow ( in the parenthese)
	{

	}
}

void RSProviderTest::testRSVerifySignByP1()
{
	//using FJCA Interface to implement workflow ( in the parenthese)
	{

	}
}

void RSProviderTest::testRSKeyEncryptData()
{
	//using FJCA Interface to implement workflow ( in the parenthese)
	{

	}
}

void RSProviderTest::testRSKeyDecryptData()
{
	//using FJCA Interface to implement workflow ( in the parenthese)
	{

	}
}

void RSProviderTest::testRSKeyEncryptByDigitalEnvelope()
{
	//using FJCA Interface to implement workflow ( in the parenthese)
	{

	}
}

void RSProviderTest::testRSKeyDecryptByDigitalEnvelope()
{
	//using FJCA Interface to implement workflow ( in the parenthese)
	{

	}
}

void RSProviderTest::setUp()
{
	std::string path = "XSSealProviderLib.dll";
	sl.load(path);
	assert(sl.isLoaded());
}


void RSProviderTest::tearDown()
{
	sl.unload();
	assert(!sl.isLoaded());
}


CppUnit::Test* RSProviderTest::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("RSProviderTest");

	CppUnit_addTest(pSuite, RSProviderTest, testRSGetConfigParameters);
	CppUnit_addTest(pSuite, RSProviderTest, testRSConfigParameters);
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
