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

using namespace std;
int removeDuplicates(vector<int>& nums) {
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

CppUnit::Test* SharedLibraryTestSuite::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("SharedLibraryTestSuite");

#if !defined(_WIN32) || defined(_DLL)
	pSuite->addTest(SharedLibraryTest::suite());
	pSuite->addTest(SealProviderTest::suite());
	pSuite->addTest(GmskfProviderTest::suite());
	pSuite->addTest(RSProviderTest::suite());
	pSuite->addTest(TestUtil::suite());
	//pSuite->addTest(SOFProviderTest::suite());
#endif
	std::vector<int> nums = { 1, 1, 2, 2, 3, 3 };
	removeDuplicates(nums);
	return pSuite;
}
