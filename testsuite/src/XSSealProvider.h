#pragma once
#include "CppUnit/TestCase.h"
#include "Poco/Logger.h"

class XSSealProvider : public CppUnit::TestCase
{
public:
	XSSealProvider(const std::string& name);
	~XSSealProvider();

	void testGetSealCount();
	void testReadSealData();

	void setUp();
	void tearDown();

	static CppUnit::Test* suite();

private:
	Poco::Logger& logger;

	typedef int (*GetSealCount)();
	typedef char* (*ReadSealData)(int nIndex);
};