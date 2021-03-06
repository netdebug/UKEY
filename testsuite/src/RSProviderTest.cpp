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
#include "GMCrypto.h"

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

RSProviderTest::RSProviderTest(const std::string& name) : CppUnit::TestCase(name)
{
}


RSProviderTest::~RSProviderTest()
{
}

#include "Poco/UnicodeConverter.h"
#include "Poco/JSON/Query.h"
#include <iomanip>

using Poco::UnicodeConverter;
using Poco::JSON::Query;

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

		Query query(result);
		Object::Ptr d = query.findObject("data");
		assert(!d.isNull());
		std::string list = d->getValue<std::string>("userlist");
		Poco::UTF16String out;
		UnicodeConverter::convert(list, out);
		std::wcout << std::setw(out.size()) << out << std::endl;
		assert(ds["code"] == "0000");
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
		ls.trace() << "RS_GetCertInfo:" << rsf.RS_GetCertInfo(cert, SGD_OID_IDENTIFY_NUMBER) << std::endl;
		ls.trace() << "RS_GetCertInfo:" << rsf.RS_GetCertInfo(cert, SGD_CERT_VALID_TIME) << std::endl;
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
		ls.trace() << "RS_GetCertInfo:" << rsf.RS_GetCertInfo(cert, SGD_OID_IDENTIFY_NUMBER) << std::endl;
		ls.trace() << "RS_GetCertInfo:" << rsf.RS_GetCertInfo(cert, SGD_CERT_VALID_TIME) << std::endl;
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
	waitforuser();

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

	//std::string xia("00000000");
	//std::string lg("1111111");
	rsf.RS_CertLogin(uid, pwd);

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

void RSProviderTest::testRSVerifySignByP7()
{
	Logger& root = Logger::get("LoggerTest");//Logger::root();
	LogStream ls(root);

	Reach::RSFoundation rsf;

	//std::string xia("00000000");
	//std::string lg("1111111");
	rsf.RS_CertLogin(uid, pwd);

	std::string message("what is up? what the library!Signed the data!");
	std::string signedResult = rsf.RS_KeySignByP7(message, "1", uid);
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
		std::string t = rsf.RS_VerifySignByP7(message, value, "1");

		ls.trace() << t << std::endl;
		Parser parser;
		Var rt = parser.parse(t);
		assert(rt.type() == typeid(Object::Ptr));

		Object object = *rt.extract<Object::Ptr>();
		DynamicStruct ds = object;
		assert(ds["code"] == 0);
	}
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

		
		ls.trace() << "RS_CertLogin except ok:" << rsf.RS_CertLogin(uid, pwd) << std::endl;

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

void RSProviderTest::testDesEncryptAndDecrypt()
{
	Logger& root = Logger::get("LoggerTest");//Logger::root();
	LogStream ls(root);

	std::string paintText("@This is a demo for test DesEncrypt And Decrypt,123@");
	std::string encryptText;

	Reach::RSFoundation rsf;

	{
		std::string json = rsf.RS_GetCertBase64String(crypto, uid);
		Parser parser;
		Var result = parser.parse(json);
		assert(result.type() == typeid(Object::Ptr));

		Object object = *result.extract<Object::Ptr>();
		Var test = object.get("data");
		Object subObject = *test.extract<Object::Ptr>();

		std::string cert = subObject.get("certBase64");

		{
			encryptText = rsf.DesEncrypt(paintText/*, cert*/);

			ls.trace() << "DesEncrypt paintText :" << paintText << std::endl
				<< "base64 certificate content :" << cert << std::endl
				<< "DesEncrypt encryptText json : " << encryptText << std::endl;

			Parser parser;
			Var result = parser.parse(encryptText);
			assert(result.type() == typeid(Object::Ptr));

			Object object = *result.extract<Object::Ptr>();
			Var test = object.get("data");
			Object subObject = *test.extract<Object::Ptr>();

			std::string encryptText = subObject.get("encrypt");
			std::string kv = subObject.get("symKey");

			{
				std::string resultJson = rsf.DesDecrypt(encryptText, kv);

				ls.trace() << "DesEncrypt paintText :" << paintText << std::endl
					<< "base64 certificate content :" << cert << std::endl
					<< "DesEncrypt encryptText json : " << resultJson << std::endl;

				Parser parser;
				Var result = parser.parse(resultJson);
				assert(result.type() == typeid(Object::Ptr));

				Object object = *result.extract<Object::Ptr>();
				Var test = object.get("data");
				Object subObject = *test.extract<Object::Ptr>();

				std::string encryptText = subObject.get("decrypt");

				assert(encryptText == paintText);
			}
		}
	}
}

void RSProviderTest::testMethodInfomation()
{
	Logger& root = Logger::get("LoggerTest");//Logger::root();
	LogStream ls(root);

	Reach::RSFoundation rsf;

	ls.trace() << "GetSignMethod Json\n" << rsf.GetSignMethod() << std::endl;
	ls.trace() << "GetEncryptMethod \n" << rsf.GetEncryptMethod() << std::endl;
}

void RSProviderTest::testSignVerifyByFile()
{
	Logger& root = Logger::get("LoggerTest");//Logger::root();
	LogStream ls(root);

	std::string toSign("F:/source/RSTestRunner/bin/encryptText.txt");
	std::string signature;
	Reach::RSFoundation rsf;

	signature = rsf.SignFile(uid, toSign);

	ls.trace() << "SignFile signature json: " << signature << std::endl;

	{
		Parser parser;
		Var result = parser.parse(signature);
		assert(result.type() == typeid(Object::Ptr));

		Object object = *result.extract<Object::Ptr>();
		Var test = object.get("data");
		Object subObject = *test.extract<Object::Ptr>();

		std::string value = subObject.get("signature");

		{
			std::string json = rsf.RS_GetCertBase64String(sign, uid);
			Parser parser;
			Var result = parser.parse(json);
			assert(result.type() == typeid(Object::Ptr));

			Object object = *result.extract<Object::Ptr>();
			Var test = object.get("data");
			Object subObject = *test.extract<Object::Ptr>();

			std::string cert = subObject.get("certBase64");

			ls.trace() << "VerifySignedFile result json : " << rsf.VerifySignedFile(cert, toSign, value) << std::endl;
		}
	}
}

void RSProviderTest::testRSKeyEncryptByDigitalEnvelope()
{
}

void RSProviderTest::testRSKeyDecryptByDigitalEnvelope()
{
}

void RSProviderTest::waitforuser()
{
	Logger& root = Logger::get("LoggerTest");//Logger::root();
	LogStream ls(root);

	std::string c;

	while (true) {
		std::cin >> c;
		ls.trace() << c << std::endl;
		if (c == "g")
			break;
	}


	ls.trace() << "go" << std::endl;
}

void RSProviderTest::setUp()
{
	uid = "{1B57694E-911E-41D9-8123-971EDD71342C}";
	pwd = "00000000";
	/*uid = "806000119631708";
	pwd = "111111";
	uid = "4334801F-55EA-4F16-982C-CFB2AB8B44F7";
	pwd = "111111";
	uid = "C64FB078-28B4-450D-8ACB-68AE249CBA8D";
	pwd = "111111";*/
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

	CppUnit_addTest(pSuite, RSProviderTest, testRSGetUserList);
	CppUnit_addTest(pSuite, RSProviderTest, testRSGetCertBase64String);
	CppUnit_addTest(pSuite, RSProviderTest, testRSGetCertInfo);
	CppUnit_addTest(pSuite, RSProviderTest, testRSCertLogin);
	CppUnit_addTest(pSuite, RSProviderTest, testRSGetPinRetryCount);
	CppUnit_addTest(pSuite, RSProviderTest, testRSKeyGetKeySn);
	CppUnit_addTest(pSuite, RSProviderTest, testRSKeySignByP1);
	CppUnit_addTest(pSuite, RSProviderTest, testRSVerifySignByP7);
	CppUnit_addTest(pSuite, RSProviderTest, testRsaEncryptAndDecrypt);
	CppUnit_addTest(pSuite, RSProviderTest, testSymEncryptAndDecrypt);
	CppUnit_addTest(pSuite, RSProviderTest, testRSKeyEncryptByDigitalEnvelope);
	CppUnit_addTest(pSuite, RSProviderTest, testRSKeyDecryptByDigitalEnvelope);
	CppUnit_addTest(pSuite, RSProviderTest, testDesEncryptAndDecrypt);
	CppUnit_addTest(pSuite, RSProviderTest, testMethodInfomation);
	CppUnit_addTest(pSuite, RSProviderTest, testSignVerifyByFile);

	return pSuite;
}
