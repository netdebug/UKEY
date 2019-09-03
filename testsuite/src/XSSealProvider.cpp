#include "XSSealProvider.h"
#include "CppUnit/TestCaller.h"
#include "CppUnit/TestSuite.h"

XSSealProvider::XSSealProvider(const std::string & name)
	: CppUnit::TestCase(name)
	, logger(Poco::Logger::get("LoggerTest"))
{
}

XSSealProvider::~XSSealProvider()
{
}

void XSSealProvider::testGetSealCount()
{
	GetSealCount pfnGetSealCount = 0;
	int count = pfnGetSealCount();
	assert(count > 0);
	poco_information_f1(logger, "GetSealCount count : %d", count);
}

void XSSealProvider::testReadSealData()
{
	ReadSealData pfnReadSealData = 0;
	int all_seal = -1;
	std::string content = pfnReadSealData(all_seal);
	assert(!content.empty());
	if (!content.empty()) {
		poco_information_f2(logger, "ReadSealData content :%s count : %d", content, content.length());
	}
}

void XSSealProvider::setUp()
{
}

void XSSealProvider::tearDown()
{
}

CppUnit::Test * XSSealProvider::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("XSSealProvider");

	CppUnit_addTest(pSuite, XSSealProvider, testGetSealCount);
	CppUnit_addTest(pSuite, XSSealProvider, testReadSealData);
	return pSuite;
}