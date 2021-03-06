//
// Connector.cpp
//
// Library: Data/SOF
// Package: SOF
// Module:  Connector
//
// Copyright (c) 2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#include "Reach/Data/SOF/Connector.h"
#include "Reach/Data/SOF/SessionImpl.h"
#include "Reach/Data/SessionFactory.h"
#if defined(POCO_UNBUNDLED)
#include <SoFProvider.h>
#else
#include "SoFProvider.h"
#endif


namespace Reach {
namespace Data {
namespace SOF {


const std::string Connector::KEY("SOF");


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


void Connector::registerConnector()
{
	Reach::Data::SessionFactory::instance().add(new Connector());
}


void Connector::unregisterConnector()
{
	Reach::Data::SessionFactory::instance().remove(KEY);
}

} } } // namespace Poco::Data::SOF
