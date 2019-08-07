//
// Connector.cpp
//
// Copyright (c) 2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#include "Connector.h"
#include "SessionImpl.h"
#include "Reach/Data/SessionFactory.h"


namespace Reach {
namespace Data {
namespace Test {


const std::string Connector::KEY("test");


Connector::Connector()
{
}


Connector::~Connector()
{
}


Poco::AutoPtr<Reach::Data::SessionImpl> Connector::createSession(const std::string& connectionString,
		std::size_t timeout)
{
	return Poco::AutoPtr<Reach::Data::SessionImpl>(new SessionImpl(connectionString, timeout));
}


void Connector::addToFactory()
{
	Reach::Data::SessionFactory::instance().add(new Connector());
}


void Connector::removeFromFactory()
{
	Reach::Data::SessionFactory::instance().remove(KEY);
}


} } } // namespace Poco::Data::Test
