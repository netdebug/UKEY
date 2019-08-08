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


const std::string StatementImpl::VECTOR = "vector";
const std::string StatementImpl::LIST = "list";
const std::string StatementImpl::DEQUE = "deque";
const std::string StatementImpl::UNKNOWN = "unknown";


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
	std::size_t lim = 0;
	/*
	if (reset) resetExtraction();

	if (!_rSession.isConnected())
	{
		_state = ST_DONE;
		throw NotConnectedException(_rSession.connectionString());
	}

	std::size_t lim = 0;
	if (_lowerLimit > _extrLimit.value())
		throw LimitException("Illegal Statement state. Upper limit must not be smaller than the lower limit.");

	do
	{
		compile();
		if (_extrLimit.value() == Limit::LIMIT_UNLIMITED)
			lim += executeWithoutLimit();
		else
			lim += executeWithLimit();
	} while (canCompile());

	if (_extrLimit.value() == Limit::LIMIT_UNLIMITED)
		_state = ST_DONE;

	if (lim < _lowerLimit)
		throw LimitException("Did not receive enough data.");

	assignSubTotal(reset);
	*/
	return lim;
}

void StatementImpl::compile()
{
	/*
	if (_state == ST_INITIALIZED || 
		_state == ST_RESET || 
		_state == ST_BOUND)
	{
		compileImpl();
		_state = ST_COMPILED;

		if (!extractions().size() && !isStoredProcedure())
		{
			std::size_t cols = columnsReturned();
			if (cols) makeExtractors(cols);
		}

		fixupExtraction();
		fixupBinding();
	}
	*/
}


void StatementImpl::bind()
{
	/*if (_state == ST_COMPILED)
	{
		bindImpl();
		_state = ST_BOUND;
	}
	else if (_state == ST_BOUND)
	{
		if (!hasNext())
		{
			if (canBind()) bindImpl();
			else _state = ST_DONE;
		}
	}*/
}


void StatementImpl::reset()
{
	/*resetBinding();
	resetExtraction();*/
	_state = ST_RESET;
}


} } // namespace Reach::Data
