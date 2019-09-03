#include "KG_GetKeyInfo_FJRS.h"
#include "CppUnit/TestCaller.h"
#include "CppUnit/TestSuite.h"

KG_GetKeyInfo_FJRS::KG_GetKeyInfo_FJRS(const std::string & name)
	: CppUnit::TestCase(name)
	, logger(Poco::Logger::get("LoggerTest"))
{
}

KG_GetKeyInfo_FJRS::~KG_GetKeyInfo_FJRS()
{
}

void KG_GetKeyInfo_FJRS::testGetSealCount()
{
}

void KG_GetKeyInfo_FJRS::testReadSealData()
{
	typedef char* (*KGGetKeyInfo)();
	KGGetKeyInfo pfnKGGetKeyInfo;
	std::string content = pfnKGGetKeyInfo();

	assert(!content.empty());
	if (!content.empty()) {
		poco_information_f2(logger, "KGGetKeyInfo content :%s count : %d", content, content.length());
	}
}

void KG_GetKeyInfo_FJRS::setUp()
{
}

void KG_GetKeyInfo_FJRS::tearDown()
{
}

CppUnit::Test * KG_GetKeyInfo_FJRS::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("KG_GetKeyInfo_FJRS");

	CppUnit_addTest(pSuite, KG_GetKeyInfo_FJRS, testGetSealCount);
	CppUnit_addTest(pSuite, KG_GetKeyInfo_FJRS, testReadSealData);
	return pSuite;
}
