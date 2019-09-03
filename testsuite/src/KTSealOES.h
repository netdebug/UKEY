#pragma once
#include "CppUnit/TestCase.h"
#include "Poco/Logger.h"

class KTSealOES : public CppUnit::TestCase
{
public:
	KTSealOES(const std::string& name);
	~KTSealOES();

	void testGetSealCount();
	void testReadSealData();

	void setUp();
	void tearDown();

	static CppUnit::Test* suite();
private:
	void prepareCertification();
private:
	Poco::Logger& logger;
	typedef int (*OES_GetSealCount) (const char*signCert, const long DataLen, unsigned char*puchID, long*puchIDsLen);
	typedef int(*OES_ReadSealData) (const char*signCertB64Data, const long certDataLen, const char*sealID, unsigned char*puchSealJson, long * puchSealJsonLen);
};