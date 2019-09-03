#pragma once
#include "CppUnit/TestCase.h"
#include "Poco/Logger.h"

class KG_GetKeyInfo_FJRS : public CppUnit::TestCase
{
public:
	KG_GetKeyInfo_FJRS(const std::string& name);
	~KG_GetKeyInfo_FJRS();

	void testGetSealCount();
	void testReadSealData();

	void setUp();
	void tearDown();

	static CppUnit::Test* suite();

private:
	Poco::Logger& logger;
};