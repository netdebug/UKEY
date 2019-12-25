//
// ActiveXTestSuite.cpp
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#include "ActiveXTestSuite.h"
#include "ActiveXTest.h"

CppUnit::Test* ActiveXTestSuite::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("ActiveXTestSuite");

#if !defined(_WIN32) || defined(_DLL)
	pSuite->addTest(ActiveXTest::suite());
#endif
	return pSuite;
}
