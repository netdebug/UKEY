//
// RSProviderTest.cpp
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#include "RSProviderTest.h"
#include "RSFoundation.h"
#include "CppUnit/TestCaller.h"
#include "CppUnit/TestSuite.h"
#include "Poco/SharedLibrary.h"
#include "Poco/Exception.h"
#include "Poco/StreamCopier.h"
#include "Poco/JSON/Parser.h"
#include "Poco/JSON/Array.h"
#include "Poco/Dynamic/Struct.h"
#include "Poco/Base64Encoder.h"
#include "Poco/Base64Decoder.h"
#include "Poco/Logger.h"
#include "Poco/LogStream.h"
#include "Poco/WindowsConsoleChannel.h"
#include "Poco/AutoPtr.h"

#include <stdio.h>
#include <sstream>
#include <iostream>

//#include "GMCrypto.h"
//#include "SOFProvider.h"

using Poco::SharedLibrary;
using Poco::NotFoundException;
using Poco::LibraryLoadException;
using Poco::LibraryAlreadyLoadedException;
using namespace Poco::JSON;
using namespace Poco::Dynamic;
using Poco::Base64Decoder;
using Poco::Base64Encoder;
using Poco::DynamicStruct;
using Poco::Logger;
using Poco::LogStream;
using Poco::Channel;
using Poco::WindowsColorConsoleChannel;
using Poco::Message;
using Poco::AutoPtr;

RSProviderTest::RSProviderTest(const std::string& name): CppUnit::TestCase(name)
{
}


RSProviderTest::~RSProviderTest()
{
}

void RSProviderTest::testRSGetUserList()
{
	Logger& root = Logger::get("LoggerTest");//Logger::root();
	LogStream ls(root);

	try
	{
		Reach::RSFoundation rsf;
		std::string json = rsf.RS_GetUserList();
		ls.trace() << json << std::endl;
		Parser parser;
		Var result = parser.parse(json);
		assert(result.type() == typeid(Object::Ptr));

		Object object = *result.extract<Object::Ptr>();
		DynamicStruct ds = object;

		assert(ds["code"] == 0);
	}
	catch (JSONException& jsone)
	{
		ls.error() << jsone.message() << std::endl;
	}
	catch (Poco::Exception& e)
	{
		ls.error() << e.message() << std::endl;
	}
}

void RSProviderTest::testRSGetCertBase64String()
{
	Logger& root = Logger::get("LoggerTest");//Logger::root();
	LogStream ls(root);

	Reach::RSFoundation rsf;
	std::string signd = rsf.RS_GetCertBase64String(sign, uid);
	ls.trace() << "signd" << signd << std::endl;
	std::string cypto = rsf.RS_GetCertBase64String(crypto, uid);
	ls.trace() << "cypto" << cypto << std::endl;
}

void RSProviderTest::testRSGetCertInfo()
{
	Logger& root = Logger::get("LoggerTest");//Logger::root();
	LogStream ls(root);

	#define SGD_CERT_VERSION 0x00000001
	#define SGD_CERT_SERIAL 0x00000002

	Reach::RSFoundation rsf;
	
	{
		std::string json = rsf.RS_GetCertBase64String(sign, uid);
		ls.trace() << json << std::endl;
		Parser parser;
		Var result = parser.parse(json);
		assert(result.type() == typeid(Object::Ptr));

		Object object = *result.extract<Object::Ptr>();
		Var test = object.get("data");
		Object subObject = *test.extract<Object::Ptr>();
		std::string cert = subObject.get("certBase64");

		ls.trace() << "SGD_CERT_VERSION" << rsf.RS_GetCertInfo(cert, SGD_CERT_VERSION) << std::endl;
		ls.trace() << "SGD_CERT_SERIAL" << rsf.RS_GetCertInfo(cert, SGD_CERT_SERIAL) << std::endl;
	}


	{
		std::string json = rsf.RS_GetCertBase64String(crypto, uid);
		ls.trace() << json << std::endl;
		Parser parser;
		Var result = parser.parse(json);
		assert(result.type() == typeid(Object::Ptr));

		Object object = *result.extract<Object::Ptr>();
		Var test = object.get("data");
		Object subObject = *test.extract<Object::Ptr>();
		std::string cert = subObject.get("certBase64");

		ls.trace() << "SGD_CERT_VERSION" << rsf.RS_GetCertInfo(cert, SGD_CERT_VERSION) << std::endl;
		ls.trace() << "SGD_CERT_SERIAL" << rsf.RS_GetCertInfo(cert, SGD_CERT_SERIAL) << std::endl;
	}
}

void RSProviderTest::testRSCertLogin()
{
	Logger& root = Logger::get("LoggerTest");//Logger::root();
	LogStream ls(root);

	Reach::RSFoundation rsf;
	std::string xia("00000000");
	std::string lg("1111111");

	try
	{
		ls.trace() << "RS_CertLogin except ok:" << rsf.RS_CertLogin(uid, xia) << std::endl;
		ls.trace() << "RS_CertLogin except failed:" << rsf.RS_CertLogin(uid, lg) << std::endl;
	}
	catch (Poco::LogicException& e)
	{
		ls.error() << "RS_CertLogin" << e.message() << std::endl;
	}
}

void RSProviderTest::testRSGetPinRetryCount()
{
	Logger& root = Logger::get("LoggerTest");//Logger::root();
	LogStream ls(root);

	Reach::RSFoundation rsf;
	ls.trace() << "Retry Count:" << rsf.RS_GetPinRetryCount(uid) << std::endl;
}

void RSProviderTest::testRSKeyGetKeySn()
{
	Logger& root = Logger::get("LoggerTest");//Logger::root();
	LogStream ls(root);

	Reach::RSFoundation rsf;
	ls.trace() << "UKey SN:" << rsf.RS_KeyGetKeySn(uid) << std::endl;
}

void RSProviderTest::testRSKeySignByP1()
{
	Logger& root = Logger::get("LoggerTest");//Logger::root();
	LogStream ls(root);

	Reach::RSFoundation rsf;

	std::string message("what is up? what the library!Signed the data!");
	std::string signedResult = rsf.RS_KeySignByP1(uid, message);
	ls.trace() << "signedResult:" << signedResult << std::endl;
	std::string value;
	{
		Parser parse;
		Var result = parse.parse(signedResult);
		assert(result.type() == typeid(Object::Ptr));

		Object object = *result.extract<Object::Ptr>();
		Var test = object.get("data");
		Object subObject = *test.extract<Object::Ptr>();
		value = subObject.get("signdMsg").toString();
	}
	
	std::string json = rsf.RS_GetCertBase64String(sign, uid);
	ls.trace() << json << std::endl;
	std::string cert;
	{
		Parser parser;
		Var result = parser.parse(json);
		assert(result.type() == typeid(Object::Ptr));

		Object object = *result.extract<Object::Ptr>();
		Var test = object.get("data");
		Object subObject = *test.extract<Object::Ptr>();
		cert = subObject.get("certBase64").toString();
	}

	{
		std::string t = rsf.RS_VerifySignByP1(cert, message, value);

		ls.trace() << t << std::endl;
		Parser parser;
		Var rt = parser.parse(t);
		assert(rt.type() == typeid(Object::Ptr));

		Object object = *rt.extract<Object::Ptr>();
		DynamicStruct ds = object;
		assert(ds["code"] == 0);
	}
}

void RSProviderTest::testRSVerifySignByP1()
{
}

void RSProviderTest::testRsaEncryptAndDecrypt()
{
	Logger& root = Logger::get("LoggerTest");//Logger::root();
	LogStream ls(root);

	Reach::RSFoundation rsf;
	std::string paintText("what is up? what library it is!");

	std::string json = rsf.RS_GetCertBase64String(crypto, uid);

	{
		Parser parser;
		Var result = parser.parse(json);
		assert(result.type() == typeid(Object::Ptr));

		Object object = *result.extract<Object::Ptr>();
		Var test = object.get("data");
		Object subObject = *test.extract<Object::Ptr>();
		std::string cert = subObject.get("certBase64");

		json = rsf.RS_KeyEncryptData(paintText, cert);

		ls.trace() << "paintText:" << paintText << std::endl
			<< "RS_GetCertBase64String certificate:" << cert << std::endl
			<< "RS_KeyEncryptData encrypt:" << json << std::endl;
	}

	{
		Parser parser;
		Var result = parser.parse(json);
		assert(result.type() == typeid(Object::Ptr));

		Object object = *result.extract<Object::Ptr>();
		Var test = object.get("data");
		Object subObject = *test.extract<Object::Ptr>();
		std::string encrypt = subObject.get("encRsKey");

		std::string xia("00000000");
		ls.trace() << "RS_CertLogin except ok:" << rsf.RS_CertLogin(uid, xia) << std::endl;

		std::string decrypt = rsf.RS_KeyDecryptData(uid, encrypt);

		Var result2 = parser.parse(decrypt);
		assert(result2.type() == typeid(Object::Ptr));
		Object object2 = *result2.extract<Object::Ptr>();
		Var test2 = object2.get("data");
		Object subObject2 = *test2.extract<Object::Ptr>();
		std::string base64 = subObject2.get("rsKey");
		std::istringstream istr(base64);
		Base64Decoder decoder(istr, Poco::BASE64_URL_ENCODING);
		std::string dt;
		int c = decoder.get();
		while (c != -1) { dt += char(c); c = decoder.get(); }
		assert(paintText == dt);
		ls.trace() << "decrypt text : " << dt << std::endl
			<< "uid:" << uid << std::endl
			<< "RS_KeyDecryptData decrypt:" << decrypt << std::endl;
	}
}

#include "Poco/File.h"
void RSProviderTest::testSymEncryptAndDecrypt()
{
	Logger& root = Logger::get("LoggerTest");//Logger::root();
	LogStream ls(root);

	Reach::RSFoundation rsf;
	std::string paintDir("F:/source/RSTestRunner/bin/paintText.txt");
	std::string encryptDir("F:/source/RSTestRunner/bin/encryptText.txt");
	std::string jsonkv = rsf.RS_EncryptFile(paintDir, encryptDir);

	ls.trace()
		<< paintDir << std::endl
		<< encryptDir << std::endl
		<< "RS_EncryptFile:jsonkv\n" << jsonkv << std::endl;

	Parser parser;
	Var result = parser.parse(jsonkv);
	Object object = *result.extract<Object::Ptr>();
	assert(result.type() == typeid(Object::Ptr));
	Var test = object.get("data");
	Object subObject = *test.extract<Object::Ptr>();
	std::string kv = subObject.get("symKey");

	std::string in("F:/source/RSTestRunner/bin/encryptText.txt");
	std::string out("F:/source/RSTestRunner/bin/DecryOut.txt");
	std::string decrypt = rsf.RS_DecryptFile(kv, in, out);

	ls.trace() 
		<< in << std::endl << out << std::endl << 
		"RS_DecryptFile:decrypt\n" << decrypt << std::endl;
}

void RSProviderTest::testRSKeyEncryptByDigitalEnvelope()
{
}

void RSProviderTest::testRSKeyDecryptByDigitalEnvelope()
{
}

void RSProviderTest::setUp()
{
	uid = "{1B57694E-911E-41D9-8123-971EDD71342C}";
	
	AutoPtr<Channel> pChannel = new WindowsColorConsoleChannel;
	pChannel->setProperty("traceColor", "lightGreen");
	Logger& root = Poco::Logger::get("LoggerTest");//Logger::root();
	root.setChannel(pChannel.get());
	root.setLevel(Message::PRIO_TRACE);
}


void RSProviderTest::tearDown()
{
	//sl.unload();
	//assert(!sl.isLoaded());
}


CppUnit::Test* RSProviderTest::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("RSProviderTest");

	/*CppUnit_addTest(pSuite, RSProviderTest, testRSGetConfigParameters);
	CppUnit_addTest(pSuite, RSProviderTest, testRSConfigParameters);*/
	CppUnit_addTest(pSuite, RSProviderTest, testRSGetUserList);
	CppUnit_addTest(pSuite, RSProviderTest, testRSGetCertBase64String);
	CppUnit_addTest(pSuite, RSProviderTest, testRSGetCertInfo);
	CppUnit_addTest(pSuite, RSProviderTest, testRSCertLogin);
	CppUnit_addTest(pSuite, RSProviderTest, testRSGetPinRetryCount);
	CppUnit_addTest(pSuite, RSProviderTest, testRSKeyGetKeySn);
	CppUnit_addTest(pSuite, RSProviderTest, testRSKeySignByP1);
	CppUnit_addTest(pSuite, RSProviderTest, testRSVerifySignByP1);
	CppUnit_addTest(pSuite, RSProviderTest, testRsaEncryptAndDecrypt);
	CppUnit_addTest(pSuite, RSProviderTest, testSymEncryptAndDecrypt);
	CppUnit_addTest(pSuite, RSProviderTest, testRSKeyEncryptByDigitalEnvelope);
	CppUnit_addTest(pSuite, RSProviderTest, testRSKeyDecryptByDigitalEnvelope);

	return pSuite;
}
