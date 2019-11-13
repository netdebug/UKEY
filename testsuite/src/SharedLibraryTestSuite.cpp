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
#include "TestUtil.h"
#include <vector>
#include <iostream>

CppUnit::Test* SharedLibraryTestSuite::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("SharedLibraryTestSuite");

#if !defined(_WIN32) || defined(_DLL)
	pSuite->addTest(TestUtil::suite());
#endif
	return pSuite;
}
