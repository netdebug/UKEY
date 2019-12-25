//
// ActiveXTest.cpp
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#include "ActiveXTest.h"
#include "CppUnit/TestCaller.h"
#include "CppUnit/TestSuite.h"
//#include "Poco/ActiveX.h"
#include "Poco/Exception.h"

//using Poco::ActiveX;
using Poco::NotFoundException;
using Poco::LibraryLoadException;
using Poco::LibraryAlreadyLoadedException;

ActiveXTest::ActiveXTest(const std::string& name): CppUnit::TestCase(name)
{
}


ActiveXTest::~ActiveXTest()
{
}

void ActiveXTest::test()
{
	std::cout << "ActiveXTest test function" << std::endl;
}

void ActiveXTest::setUp()
{
}


void ActiveXTest::tearDown()
{
}


CppUnit::Test* ActiveXTest::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("ActiveXTest");

	CppUnit_addTest(pSuite, ActiveXTest, test);

	return pSuite;
}
