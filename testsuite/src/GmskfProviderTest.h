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
#include "Poco/Logger.h"
#include "Poco/LogStream.h"
#include "Poco/AutoPtr.h"
#include "Poco/Channel.h"


class GmskfProviderTest: public CppUnit::TestCase
{
public:
	GmskfProviderTest(const std::string& name);
	~GmskfProviderTest();

#define Symbol( n ) getSymbol<##n>(#n)

	template<typename T>
	T getSymbol(const std::string& name)
	{
		assert(sl.isLoaded());
		assert(sl.hasSymbol(name));
		T fn = (T)sl.getSymbol(name);
		assertNotNullPtr(fn);
		return fn;
	}

	void testEnumDev();
	void testGetDevInfo();
	void testHotSwap();

	void setUp();
	void tearDown();

	static CppUnit::Test* suite();

private:
	Poco::SharedLibrary sl;
	Poco::AutoPtr<Poco::Channel> pChannel;
};


#endif // GmskfProviderTest_INCLUDED
