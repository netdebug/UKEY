//
// DataTest.cpp
//
// Copyright (c) 2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#include "DataTest.h"
#include "CppUnit/TestCaller.h"
#include "CppUnit/TestSuite.h"
#include "Reach/Data/Session.h"
#include "Reach/Data/SessionFactory.h"
#include "Reach/Data/DataException.h"
#include "Connector.h"
#include "Poco/BinaryReader.h"
#include "Poco/BinaryWriter.h"
#include "Poco/DateTime.h"
#include "Poco/Types.h"
#include "Poco/Dynamic/Var.h"
#include "Poco/Exception.h"
#include <cstring>
#include <sstream>
#include <iomanip>
#include <set>


using Poco::BinaryReader;
using Poco::BinaryWriter;
using Poco::UInt32;
using Poco::Int64;
using Poco::UInt64;
using Poco::DateTime;
using Poco::Dynamic::Var;
using Poco::InvalidAccessException;
using Poco::IllegalStateException;
using Poco::RangeException;
using Poco::NotFoundException;
using Poco::InvalidArgumentException;
using Poco::NotImplementedException;
using Reach::Data::Session;
using Reach::Data::SessionFactory;
using Reach::Data::NotSupportedException;
using Reach::Data::NotConnectedException;


DataTest::DataTest(const std::string& name): CppUnit::TestCase(name)
{
	Reach::Data::Test::Connector::addToFactory();
}


DataTest::~DataTest()
{
	Reach::Data::Test::Connector::removeFromFactory();
}


void DataTest::testSession()
{
	Session sess(SessionFactory::instance().create("test", "cs"));
	assert ("test" == sess.impl()->connectorName());
	assert (sess.connector() == sess.impl()->connectorName());
	assert ("cs" == sess.impl()->connectionString());
	assert ("test:///cs" == sess.uri());

	assert (sess.getLoginTimeout() == Session::LOGIN_TIMEOUT_DEFAULT);
	sess.setLoginTimeout(123);
	assert (sess.getLoginTimeout() == 123);

	Session sess2(SessionFactory::instance().create("TeSt:///Cs"));
	assert ("test" == sess2.impl()->connectorName());
	assert ("Cs" == sess2.impl()->connectionString());
	assert ("test:///Cs" == sess2.uri());

	sess.close();
	assert (!sess.getFeature("connected"));
	assert (!sess.isConnected());

	sess.open();
	assert (sess.getFeature("connected"));
	assert (sess.isConnected());

	sess.reconnect();
	assert (sess.getFeature("connected"));
	assert (sess.isConnected());
}


void DataTest::testStatementFormatting()
{
	Session sess(SessionFactory::instance().create("test", "cs"));
}


void DataTest::testFeatures()
{
	Session sess(SessionFactory::instance().create("test", "cs"));
	
	sess.setFeature("f1", true);
	assert (sess.getFeature("f1"));
	assert (sess.getFeature("f2"));
	
	try
	{
		sess.setFeature("f2", false);
	}
	catch (NotImplementedException&)
	{
	}
	
	sess.setFeature("f3", false);
	assert (!sess.getFeature("f2"));
	
	try
	{
		sess.setFeature("f3", true);
	}
	catch (NotImplementedException&)
	{
	}
	
	try
	{
		sess.setFeature("f4", false);
	}
	catch (NotSupportedException&)
	{
	}
}


void DataTest::testProperties()
{
	Session sess(SessionFactory::instance().create("test", "cs"));
		
	sess.setProperty("p1", 1);
	Poco::Any v1 = sess.getProperty("p1");
	assert (Poco::AnyCast<int>(v1) == 1);
	Poco::Any v2 = sess.getProperty("p2");
	assert (Poco::AnyCast<int>(v2) == 1);
	
	try
	{
		sess.setProperty("p2", 2);
	}
	catch (NotImplementedException&)
	{
	}
	
	sess.setProperty("p3", 2);
	v1 = sess.getProperty("p2");
	assert (Poco::AnyCast<int>(v1) == 2);
	
	try
	{
		sess.setProperty("p3", 3);
	}
	catch (NotImplementedException&)
	{
	}
	
	try
	{
		sess.setProperty("p4", 4);
	}
	catch (NotSupportedException&)
	{
	}
}


void DataTest::setUp()
{
}


void DataTest::tearDown()
{
}


CppUnit::Test* DataTest::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("DataTest");

	CppUnit_addTest(pSuite, DataTest, testSession);
	CppUnit_addTest(pSuite, DataTest, testStatementFormatting);
	CppUnit_addTest(pSuite, DataTest, testFeatures);
	CppUnit_addTest(pSuite, DataTest, testProperties);

	return pSuite;
}
