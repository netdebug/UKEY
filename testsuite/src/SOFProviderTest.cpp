//
// SOFProviderTest.cpp
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#include "SOFProviderTest.h"
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

SOFProviderTest::SOFProviderTest(const std::string& name): CppUnit::TestCase(name)
{
}


SOFProviderTest::~SOFProviderTest()
{
}

void SOFProviderTest::testSKFInterface()
{

}

void SOFProviderTest::setUp()
{
}


void SOFProviderTest::tearDown()
{
}


CppUnit::Test* SOFProviderTest::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("SOFProviderTest");

	CppUnit_addTest(pSuite, SOFProviderTest, testSKFInterface);

	return pSuite;
}
