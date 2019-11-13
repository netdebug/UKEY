//
// TestUtil.cpp
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#include "TestUtil.h"
#include "CppUnit/TestCaller.h"
#include "CppUnit/TestSuite.h"
#include "Poco/Exception.h"
#include "Poco/Logger.h"
#include "Poco/LogStream.h"
#include "Poco/WindowsConsoleChannel.h"
#include "Poco/TemporaryFile.h"
#include "Poco/FileStream.h"
#include "Poco/String.h"
#include "Poco/StreamCopier.h"
#include "Poco/Path.h"
#include "Poco/File.h"
#include <iostream>

using Poco::File;
using Poco::Path;
using Poco::replace;
using Poco::StreamCopier;

TestUtil::TestUtil(const std::string& name) : CppUnit::TestCase(name)
{
}


TestUtil::~TestUtil()
{
}

void TestUtil::testCreateCppHeaders()
{
	std::string templates("BufferRequestHandler.h");
	
	std::string buffer, classname, ext(".h");
	Poco::FileInputStream list(Path::current().append("class.list"));
	Poco::FileInputStream read(Path::current().append(templates));

#ifdef _DEBUG
	std::string debugDir = Path::current().append("class\\");
	File d(debugDir);
	d.createDirectory();
#endif // DEBUG

	while (!list.eof()) {
		list >> classname;
		StreamCopier::copyToString(read, buffer);
		std::string data = replace(buffer, "BufferRequestHandler", classname.c_str());
#ifdef _DEBUG
		Poco::FileStream write(debugDir + classname + ext);
#else
		Poco::FileStream write(Path::current().append(classname + ext));
#endif // _DEBUG
		write << data;
	}
	
}

int removeDuplicates(std::vector<int>& nums) {
	if (nums.empty()) return 0;
	int i = 0;
	for (int j = 1; j < nums.size(); j++) {
		if (nums[j] != nums[i]) {
			i++;
			nums[i] = nums[j];
		}
	}
	for (int j = 0; j < nums.size(); j++)
		std::cout << nums[j] << std::endl;
	return i + 1;
}

void TestUtil::removeDuplicates()
{
	std::vector<int> nums = { 1, 1, 2, 2, 3, 3 };
	::removeDuplicates(nums);
}




void TestUtil::setUp()
{
}


void TestUtil::tearDown()
{
}


CppUnit::Test* TestUtil::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("TestUtil");

	CppUnit_addTest(pSuite, TestUtil, testCreateCppHeaders);

	return pSuite;
}
