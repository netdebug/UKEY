//
// GmskfProviderTest.h
//
// Definition of the GmskfProviderTest class.
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef GmskfProviderTest_INCLUDED
#define GmskfProviderTest_INCLUDED


#include "Poco/Foundation.h"
#include "Poco/SharedLibrary.h"
#include "CppUnit/TestCase.h"


class GmskfProviderTest: public CppUnit::TestCase
{
public:
	GmskfProviderTest(const std::string& name);
	~GmskfProviderTest();

	void testEnumDev();
	void testGetDevInfo();

	void setUp();
	void tearDown();

	static CppUnit::Test* suite();

private:
	Poco::SharedLibrary sl;
};


#endif // GmskfProviderTest_INCLUDED
