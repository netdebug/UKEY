//
// ActiveXTestSuite.h
//
// Definition of the ActiveXTestSuite class.
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef ActiveXTestSuite_INCLUDED
#define ActiveXTestSuite_INCLUDED


#include "CppUnit/TestSuite.h"


class ActiveXTestSuite
{
public:
	static CppUnit::Test* suite();
};


#endif // ActiveXTestSuite_INCLUDED
