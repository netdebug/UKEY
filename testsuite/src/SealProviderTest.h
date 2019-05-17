//
// SealProviderTest.h
//
// Definition of the SealProviderTest class.
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef SealProviderTest_INCLUDED
#define SealProviderTest_INCLUDED


#include "Poco/Foundation.h"
#include "Poco/SharedLibrary.h"
#include "CppUnit/TestCase.h"


class SealProviderTest: public CppUnit::TestCase
{
public:
	SealProviderTest(const std::string& name);
	~SealProviderTest();

	void testIsUSBKeyExist();
	void testGetSealCount();
	void testReadSealContent();

	void setUp();
	void tearDown();

	static CppUnit::Test* suite();

private:
	static const int connected = 0;
	static const int all_seal = -1;
	static const int frist_seal_index = 0;

	Poco::SharedLibrary sl;
};


#endif // SealProviderTest_INCLUDED
