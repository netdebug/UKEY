//
// DataTest.h
//
// Definition of the DataTest class.
//
// Copyright (c) 2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef DataTest_INCLUDED
#define DataTest_INCLUDED


#include "Reach/Data/Data.h"
#include "Poco/BinaryReader.h"
#include "Poco/BinaryWriter.h"
#include "CppUnit/TestCase.h"


class DataTest: public CppUnit::TestCase
{
public:
	DataTest(const std::string& name);
	~DataTest();

	void testSession();
	void testStatementFormatting();
	void testFeatures();
	void testProperties();
	
	void setUp();
	void tearDown();

	static CppUnit::Test* suite();
};


#endif // DataTest_INCLUDED
