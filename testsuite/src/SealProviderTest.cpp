//
// SealProviderTest.cpp
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#include "SealProviderTest.h"
#include "CppUnit/TestCaller.h"
#include "CppUnit/TestSuite.h"
#include "Poco/SharedLibrary.h"
#include "Poco/Exception.h"
#include "Poco/Logger.h"
#include "Poco/AutoPtr.h"
#include "Poco/Channel.h"
#include "Poco/WindowsConsoleChannel.h"
#include <stdio.h>
#include <sstream>
#include <iostream>

using Poco::SharedLibrary;
using Poco::NotFoundException;
using Poco::LibraryLoadException;
using Poco::LibraryAlreadyLoadedException;
using Poco::AutoPtr;
using Poco::Channel;
using Poco::WindowsColorConsoleChannel;

int SealProviderTest::count = 0;

SealProviderTest::SealProviderTest(const std::string& name): CppUnit::TestCase(name)
{
}


SealProviderTest::~SealProviderTest()
{
	
}

void SealProviderTest::testIsUSBKeyExist()
{
	Poco::Logger& logger = Poco::Logger::get("LoggerTest");

	std::string fnName("IsUKIn");
	assert(sl.hasSymbol(fnName));

	IsUKIn fnTest = (IsUKIn)sl.getSymbol(fnName);
	assertNotNullPtr(fnTest);

	int val = fnTest();
	poco_information_f3(logger, "\n%s\n API: %s\n The function actual result is :%d", sl.getPath(), fnName, val);
	assertEqual(SealProviderTest::connected, fnTest());
}

void SealProviderTest::testGetSealCount()
{
	Poco::Logger& logger = Poco::Logger::get("LoggerTest");

	std::string fnName("GetSealCount");
	assert(sl.hasSymbol(fnName));
	GetSealCount fnTest = (GetSealCount)sl.getSymbol(fnName);
	assertNotNullPtr(fnTest);
	
	int val = fnTest();
	count = val;
	poco_information_f3(logger, "\n%s\n API: %s\n The function actual result is :%d", sl.getPath(), fnName, val);
	assert(fnTest() > 0);
}

void SealProviderTest::testReadSealContent()
{
	Poco::Logger& logger = Poco::Logger::get("LoggerTest");

	std::string fnName("ReadSealData");
	assert(sl.hasSymbol(fnName));
	ReadSealData fnTest = (ReadSealData)sl.getSymbol(fnName);
	assertNotNullPtr(fnTest);

	std::string content = fnTest(SealProviderTest::all_seal);
	poco_information_f3(logger, "\n%s\n API: %s\n The function actual result is :%s", sl.getPath(), fnName, content);
	assert(!content.empty());

	for (size_t i = 0; i < count; i++) {
		std::string text = fnTest(i);
		poco_information_f3(logger, "\n API: %s\n The index : %d actual result is :%s" ,fnName, i, text);
	}
}

void SealProviderTest::setUp()
{
	std::string path = "XSSealProviderLib.dll";
	sl.load(path);
	assert(sl.isLoaded());

	setupLogger();
}

void SealProviderTest::setupLogger()
{
	AutoPtr<Channel> pChannel = new WindowsColorConsoleChannel;
	pChannel->setProperty("informationColor", "brown");
	Poco::Logger::get("LoggerTest").setChannel(pChannel.get());
}

void SealProviderTest::tearDown()
{
	sl.unload();
	assert(!sl.isLoaded());
}


CppUnit::Test* SealProviderTest::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("SealProviderTest");

	CppUnit_addTest(pSuite, SealProviderTest, testIsUSBKeyExist);
	CppUnit_addTest(pSuite, SealProviderTest, testGetSealCount);
	CppUnit_addTest(pSuite, SealProviderTest, testReadSealContent);

	return pSuite;
}
