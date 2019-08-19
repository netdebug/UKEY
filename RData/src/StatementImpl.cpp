//
// StatementImpl.cpp
//
// Library: Data
// Package: DataCore
// Module:  StatementImpl
//
// Copyright (c) 2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#include "Reach/Data/StatementImpl.h"
#include "Reach/Data/SessionImpl.h"
#include "Reach/Data/DataException.h"
#include "Poco/SharedPtr.h"
#include "Poco/DateTime.h"
#include "Poco/Exception.h"


using Poco::icompare;


namespace Reach {
namespace Data {

StatementImpl::StatementImpl(SessionImpl& rSession):
	_state(ST_INITIALIZED),
	_rSession(rSession),
	_ostr()
{
	if (!_rSession.isConnected())
		throw NotConnectedException(_rSession.connectionString());
}


StatementImpl::~StatementImpl()
{
}


std::size_t StatementImpl::execute(const bool& reset)
{
	return 0;
}

void StatementImpl::prepareFunc()
{

}

void StatementImpl::reset()
{
	_state = ST_RESET;
}

void StatementImpl::formatSQL(std::vector<Poco::Any>& arguments)
{
	std::string sql;
	Poco::format(sql, _ostr.str(), arguments);
	_ostr.str("");
	_ostr << sql;
}


} } // namespace Poco::Data
