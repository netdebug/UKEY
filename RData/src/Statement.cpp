//
// Statement.cpp
//
// Library: Data
// Package: DataCore
// Module:  Statement
//
// Copyright (c) 2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#include "Reach/Data/Statement.h"
#include "Reach/Data/DataException.h"
#include "Reach/Data/Session.h"
#include "Poco/Any.h"
#include "Poco/Tuple.h"
#include "Poco/ActiveMethod.h"
#include <algorithm>


namespace Reach {
namespace Data {


Statement::Statement(StatementImpl::Ptr pImpl):
	_pImpl(pImpl),
	_async(false)
{
	poco_check_ptr (pImpl);
}


Statement::Statement(Session& session):
	_async(false)
{
	reset(session);
}


Statement::Statement(const Statement& stmt):
	_pImpl(stmt._pImpl),
	_async(stmt._async),
	_pResult(stmt._pResult),
	_pAsyncExec(stmt._pAsyncExec),
	_arguments(stmt._arguments)
{
}


Statement::~Statement()
{
}


Statement& Statement::operator = (const Statement& stmt)
{
	Statement tmp(stmt);
	swap(tmp);
	return *this;
}


void Statement::swap(Statement& other)
{
	using std::swap;
	
	swap(_pImpl, other._pImpl);
	swap(_async, other._async);
	swap(_pAsyncExec, other._pAsyncExec);
	swap(_pResult, other._pResult);
	_arguments.swap(other._arguments);
}


Statement& Statement::reset(Session& session)
{
	Statement stmt(session.createStatementImpl());
	swap(stmt);
	return *this;
}


std::size_t Statement::execute(bool reset)
{
	Poco::Mutex::ScopedLock lock(_mutex);
	bool isDone = done();
	if (initialized() || paused() || isDone)
	{
		if (_arguments.size()) 
		{
			_pImpl->formatSQL(_arguments);
			_arguments.clear();
		}

		if (!isAsync())
		{
			if (isDone) _pImpl->reset();
			return _pImpl->execute(reset);
		}
		else
		{
			doAsyncExec();
			return 0;
		}
	} 
	else throw Poco::InvalidAccessException("Statement still executing.");
}


const Statement::Result& Statement::executeAsync(bool reset)
{
	Poco::Mutex::ScopedLock lock(_mutex);
	if (initialized() || paused() || done())
		return doAsyncExec(reset);
	else
		throw Poco::InvalidAccessException("Statement still executing.");
}


const Statement::Result& Statement::doAsyncExec(bool reset)
{
	if (done()) _pImpl->reset();
	if (!_pAsyncExec)
		_pAsyncExec = new AsyncExecMethod(_pImpl, &StatementImpl::execute);
	_pResult = new Result((*_pAsyncExec)(reset));
	return *_pResult;
}


void Statement::setAsync(bool async)
{
	_async = async;
	if (_async && !_pAsyncExec)
		_pAsyncExec = new AsyncExecMethod(_pImpl, &StatementImpl::execute);
}


std::size_t Statement::wait(long milliseconds)
{
	if (!_pResult) return 0;
	bool success = true;
	if (WAIT_FOREVER != milliseconds)
		success = _pResult->tryWait(milliseconds);
	else
		_pResult->wait();

	if (_pResult->exception())
		throw *_pResult->exception();
	else if (!success)
		throw Poco::TimeoutException("Statement timed out.");

	return _pResult->data();
}

Statement& Statement::operator , (Manipulator manip)
{
	manip(*this);
	return *this;
}

Session Statement::session()
{
	Poco::AutoPtr<SessionImpl> ps(&impl()->session(), true); 
	return Session(ps);
}


} } // namespace Reach::Data
