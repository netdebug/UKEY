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
#include "Poco/Crypto/X509Certificate.h"
#include "Poco/UnicodeConverter.h"
#include "Poco/Base64Decoder.h"
#include <sstream>
#include <cassert>

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

std::string cat(const std::string& delim, std::size_t pos, const std::string& str)
{
	assert(pos < str.length());

	std::string result;

	for (int i = 0; i < str.length(); i++)
	{
		result.push_back(str[i]);
		if (i > 0 && i % pos == 0) result.append(delim);
	}
	result.append(delim);
	return result;
}

void TestUtil::testGetCertInfoByPocoCrypt()
{
	std::string PEM;
	std::string cer("MIIDjjCCAvegAwIBAgIQKhiG6D6xLFuyEQiu5iwiVjANBgkqhkiG9w0BAQUFADBJMQswCQYDVQQGEwJDTjEPMA0GA1UEChMGTk1HIENBMSkwJwYDVQQDEyBOTUcgQ2VydGlmaWNhdGUgQXV0aG9yaXR5IENlbnRlcjAeFw0xOTA3MDEwMjA5MThaFw0yNDA2MjkwMjA5MThaMGwxCzAJBgNVBAYTAkNOMQ4wDAYDVQQKDAVOTUdDQTESMBAGA1UECAwJ5YaF6JKZ5Y+kMRswGQYDVQQLDBLotaTls7DlhazlhbHotYTmupAxHDAaBgNVBAMME+aUv+W6nOmHh+i0rea1i+ivlTcwgZ8wDQYJKoZIhvcNAQEBBQADgY0AMIGJAoGBALiD56YjVb+k/DHAJkzVOrX9zM1pNzgeaCp5xQe/FUy0CsUwsG1nhnX8UwgoJc41uczlofrGZi0WTMdKtur5cFAQ/LrNh+l9ad05lU3VdHRtgiZw9vGH4MlnxjBw1c3fLeNjwxZ/07t0BYgRbNxtA44WH3IaSCMfSS5MdPrQXIkdAgMBAAGjggFSMIIBTjCB+wYDVR0fBIHzMIHwMDegNaAzpDEwLzELMAkGA1UEBhMCQ04xEDAOBgNVBAsMB0FERDZDUkwxDjAMBgNVBAMMBWNybDMzMDagNKAyhjBodHRwOi8vY29ubmVjdG9yLmFueGluY2EuY29tL25tZ3JzYWNybC9jcmwzMy5jcmwwfaB7oHmGd2xkYXA6Ly9zbTJsZGFwLmFueGluY2EuY29tOjM5MC9DTj1jcmwzMyxPVT1BREQ2Q1JMLEM9Q04/Y2VydGlmaWNhdGVSZXZvY2F0aW9uTGlzdD9iYXNlP29iamVjdGNsYXNzPWNSTERpc3RyaWJ1dGlvblBvaW50MA4GA1UdDwEB/wQEAwIGwDAfBgNVHSMEGDAWgBS9kmu6xE8kA4yfgq+5pH7Z6VRrhjAdBgNVHQ4EFgQUkwty/cpxr6M/y2rsga/NwCoW610wDQYJKoZIhvcNAQEFBQADgYEABx5LEjMBc8loa+0/WKlfstO7LzaN9UokQcKRgDNfY2r2iYxFFWviaJA5exgFrCm8UaI/4iUVmWw6PqLBbtg3GcCF5Rimv2xDdeXHFzGpFxymaRNnjncC8S2uoR6IbaZHQejCkjdJ+G1Tpz9AYpka4f6uMJGjB6jtoD0W/XgbSwE=");
	std::string cer1("MIICETCCAbWgAwIBAgIIfPRbHhGBlBUwDAYIKoEcz1UBg3UFADBGMQswCQYDVQQGEwJDTjEMMAoGA1UECgwDTU9GMSkwJwYDVQQDDCBDZXJ0aWZpY2F0ZSBBdXRob3JpdHkgT2YgTU9GIFNNMjAeFw0xOTA5MjgwNDE2MDNaFw0yMDA3MjQwNDE2MDNaMFUxCzAJBgNVBAYTAkNOMQwwCgYDVQQKDANNT0YxGzAZBgNVBAwMEjkxMzIxMzAyTUExWDlYQ0pYTDEbMBkGA1UEAwwS6YeR6LSi5rWL6K+VS0VZMDA4MFkwEwYHKoZIzj0CAQYIKoEcz1UBgi0DQgAEzntIOvUEhKWHtFiR9D5qiw6wAO+IJHyM+LRhT08yvXUyzvOdOG6XGBUMmVZUqpyH22ZQcNFkvXn93RkYJJdfZaN8MHowCwYDVR0PBAQDAgbAMCsGA1UdHwQkMCIwIKAeoByGGmh0dHA6Ly8xMjcuMC4wLjEvY3JsNDEuY3JsMB0GA1UdDgQWBBSdnGNijzaTkwY3tulwi7ApKckOGDAfBgNVHSMEGDAWgBQVwLk0ftx1G+i6jVUGr5DxWNQywzAMBggqgRzPVQGDdQUAA0gAMEUCIQDBhRSOL6I3G62+7HDmjHrgEf/0dgZqm7cpSFRjs1wYwwIgefbWu2OZCkkH1rJvm8zOQ03Ajof50rneH+yjjGi1QKE=");
	std::string NMGSM2("MIIDHDCCAsCgAwIBAgIQPjrQybnacjyXKDM2mzHf4TAMBggqgRzPVQGDdQUAMDMxCzAJBgNVBAYTAkNOMQ8wDQYDVQQKEwZOTUcgQ0ExEzARBgNVBAMTCk5NRyBTTTIgQ0EwHhcNMTkwNzAxMDIxNjM0WhcNMjQwNjI5MDIxNjM0WjBxMQswCQYDVQQGEwJDTjEPMA0GA1UECgwGTk1HIENBMRIwEAYDVQQIDAnlhoXokpnlj6QxHjAcBgNVBAsMFemYv+aLieWWhOWFrOWFsei1hOa6kDEdMBsGA1UEAwwU5pS/5bqc6YeH6LSt5rWL6K+VMTIwWTATBgcqhkjOPQIBBggqgRzPVQGCLQNCAAQap0YL85Fwjk6gJ64iikyYKlxJRPa9U843JJU7s/TWHPvrKaQk1/L0X7h/jE/zEIGnK1d14f67xVIwwVAg2hKAo4IBdDCCAXAwgfsGA1UdHwSB8zCB8DA3oDWgM6QxMC8xCzAJBgNVBAYTAkNOMRAwDgYDVQQLDAdBREQzQ1JMMQ4wDAYDVQQDDAVjcmwzNTA2oDSgMoYwaHR0cDovL2Nvbm5lY3Rvci5hbnhpbmNhLmNvbS9ubWdzbTJjcmwvY3JsMzUuY3JsMH2ge6B5hndsZGFwOi8vc20ybGRhcC5hbnhpbmNhLmNvbTozOTAvQ049Y3JsMzUsT1U9QUREM0NSTCxDPUNOP2NlcnRpZmljYXRlUmV2b2NhdGlvbkxpc3Q/YmFzZT9vYmplY3RjbGFzcz1jUkxEaXN0cmlidXRpb25Qb2ludDAgBgUqVgsHAwEB/wQUExIxMjM0NTY3ODkxMjM0NTY3ODkwDgYDVR0PAQH/BAQDAgbAMB0GA1UdDgQWBBTrJFft1Fc0tU52Sx5zI9PPQOXeIzAfBgNVHSMEGDAWgBTor//GXJmnUWN3Ws7uptt2PcvPEDAMBggqgRzPVQGDdQUAA0gAMEUCID886jjOo3PdBZXuZidT2asHlJCNPxeebcxByBzOMVVMAiEA2/XbJEzLmCKq6O9XCPAxTHJIandar4KcmG1UboNpoWo=+VS0VZMzAwWTATBgcqhkjOPQIBBggqgRzPVQGCLQNCAAT1KwymXS1BJHd7vXYWLGiLSU4C/EX6m/CV+Lpo+VOSwoX7jXjdUTYcZdajJ6EwWDr2nRfBhuq0yNkR20OUVEAZo3wwejALBgNVHQ8EBAMCBsAwKwYDVR0fBCQwIjAgoB6gHIYaaHR0cDovLzEyNy4wLjAuMS9jcmw0MS5jcmwwHQYDVR0OBBYEFLh1QQIcZs5YGMjtNVVrrLpWXXIxMB8GA1UdIwQYMBaAFBXAuTR+3HUb6LqNVQavkPFY1DLDMAwGCCqBHM9VAYN1BQADRwAwRAIgDDWqTCyIpLOq2rSKGBEKQemqU77iCiDdcSJXjEfffd4CID/mdQOZ40l6jBsZ5+RP4RJ3L7DVR2AEYOAgukdd+vmC");
	std::string personalQJ("MIICDzCCAbSgAwIBAgIIeNK39I6ujYQwDAYIKoEcz1UBg3UFADBGMQswCQYDVQQGEwJDTjEMMAoGA1UECgwDTU9GMSkwJwYDVQQDDCBDZXJ0aWZpY2F0ZSBBdXRob3JpdHkgT2YgTU9GIFNNMjAeFw0xOTA5MjkwMzM5MTRaFw0yMDA3MjUwMzM5MTRaMFQxCzAJBgNVBAYTAkNOMQwwCgYDVQQKDANNT0YxGzAZBgNVBAwMEjM1MDEwMjE5OTAwMzA3MzgzODEaMBgGA1UEAwwR6YeR6LSi5rWL6K+VS0VZMzIwWTATBgcqhkjOPQIBBggqgRzPVQGCLQNCAASWLae5ch8VzLEMz4CTDvyva0n3iRqUSFpW7PZK1uGQRhWeHa7wtCMWFefawIZCUf1/c2aCJAHgVUOUmB0Xiorco3wwejALBgNVHQ8EBAMCBsAwKwYDVR0fBCQwIjAgoB6gHIYaaHR0cDovLzEyNy4wLjAuMS9jcmw0MS5jcmwwHQYDVR0OBBYEFNv8WklKvZnxrd43dzA0+SOwFVlrMB8GA1UdIwQYMBaAFBXAuTR+3HUb6LqNVQavkPFY1DLDMAwGCCqBHM9VAYN1BQADRwAwRAIgG/+EjHJvrK/sf3ua9r1t3Ord2OAYC3Wtg+Lq6pHpk1ECIHAcGZCd1In4MbLK9XhCBamZUm7+iNLLr/dEBYWbMt2Q");

	PEM.append("-----BEGIN CERTIFICATE-----\n");
	PEM.append(cat("\n", 64, personalQJ));
	PEM.append("-----END CERTIFICATE-----\n");
	std::istringstream certStream(PEM);
	Poco::Crypto::X509Certificate x509(certStream);
	std::string text = x509.subjectName();
	std::ostringstream ostr;
	x509.print(ostr);
	std::string ST("\xE5\x86\x85\xE8\x92\x99\xE5\x8F\xA4");
	std::cout << ST << "subjectName :\n" << text << std::endl
		<< ostr.str() << std::endl;
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
	CppUnit_addTest(pSuite, TestUtil, testGetCertInfoByPocoCrypt);

	return pSuite;
}
