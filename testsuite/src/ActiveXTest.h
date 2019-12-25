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


class ActiveXTest: public CppUnit::TestCase
{
public:
	ActiveXTest(const std::string& name);
	~ActiveXTest();

	void test();

	void setUp();
	void tearDown();

	static CppUnit::Test* suite();

private:
};


#endif // ActiveXTest_INCLUDED
