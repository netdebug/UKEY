//
// FoundationTestSuite.cpp
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#include "FoundationTestSuite.h"
#include "SharedLibraryTestSuite.h"


CppUnit::Test* FoundationTestSuite::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("FoundationTestSuite");

	pSuite->addTest(SharedLibraryTestSuite::suite());

	return pSuite;
}
