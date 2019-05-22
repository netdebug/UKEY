//
// SharedLibraryTestSuite.cpp
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#include "SharedLibraryTestSuite.h"
#include "SharedLibraryTest.h"
#include "SealProviderTest.h"
#include "GmskfProviderTest.h"
#include "RSProviderTest.h"
#include "SOFProviderTest.h"


CppUnit::Test* SharedLibraryTestSuite::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("SharedLibraryTestSuite");

#if !defined(_WIN32) || defined(_DLL)
	pSuite->addTest(SharedLibraryTest::suite());
	pSuite->addTest(SealProviderTest::suite());
	pSuite->addTest(GmskfProviderTest::suite());
	pSuite->addTest(RSProviderTest::suite());
	pSuite->addTest(SOFProviderTest::suite());
#endif

	return pSuite;
}
