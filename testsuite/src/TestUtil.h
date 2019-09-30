//
// TestUtil.h
//
// Definition of the TestUtil class.
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef TestUtil_INCLUDED
#define TestUtil_INCLUDED


#include "Poco/Foundation.h"
#include "CppUnit/TestCase.h"


class TestUtil: public CppUnit::TestCase
{
public:
	TestUtil(const std::string& name);
	~TestUtil();

	void testCreateCppHeaders();
	void testGetCertInfoByPocoCrypt();

	void setUp();
	void tearDown();

	static CppUnit::Test* suite();

};


#endif // TestUtil_INCLUDED
