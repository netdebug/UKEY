#include "KTSealOES.h"
#include "CppUnit/TestCaller.h"
#include "CppUnit/TestSuite.h"

KTSealOES::KTSealOES(const std::string & name) 
	: CppUnit::TestCase(name)
	,logger(Poco::Logger::get("LoggerTest"))
{

}

KTSealOES::~KTSealOES()
{
}

void KTSealOES::testGetSealCount()
{
	long bufferLen = 0;
	std::string cert;
	/*第一次获得数据时间大小*/
	OES_GetSealCount pfnGetSealCount = 0;
	int count = pfnGetSealCount(cert.data(), cert.size(), 0, &bufferLen);
	assert(count > 0);
	poco_information_f1(logger, "OES_GetSealCount count : %d",count);
}

void KTSealOES::testReadSealData()
{
	OES_ReadSealData pfnOES_ReadSealData = 0;

	std::string cert;
	std::string all_seal = "-1";

	long contentSize = 0;
	pfnOES_ReadSealData(cert.data(), cert.size(), "", 0, &contentSize);

	if (contentSize > 0) {
		unsigned char* content = new unsigned char[contentSize];
		std::memset(content, 0, contentSize);
		pfnOES_ReadSealData(cert.data(), cert.size(), "", content, &contentSize);
		poco_information_f2(logger, "OES_ReadSealData content :%s count : %d", content, contentSize);
		delete [] content;
	}
}

void KTSealOES::prepareCertification()
{

}

void KTSealOES::setUp()
{
	prepareCertification();
}

void KTSealOES::tearDown()
{
}

CppUnit::Test * KTSealOES::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("KTSealOES");

	CppUnit_addTest(pSuite, KTSealOES, testGetSealCount);
	CppUnit_addTest(pSuite, KTSealOES, testReadSealData);
	return pSuite;
}
