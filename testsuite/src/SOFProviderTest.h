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
#include "CppUnit/TestCase.h"


class SOFProviderTest: public CppUnit::TestCase
{
public:
	SOFProviderTest(const std::string& name);
	~SOFProviderTest();

	void testSKFInterface();

	void setUp();
	void tearDown();

	static CppUnit::Test* suite();

private:
};


#endif // SOFProviderTest_INCLUDED
