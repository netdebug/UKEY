//
// SessionImpl.cpp
//
// Library: Data/SOF
// Package: SOF
// Module:  SessionImpl
//
// Copyright (c) 2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#include "Reach/Data/SOF/SessionImpl.h"
#include "Reach/Data/SOF/Utility.h"
#include "Reach/Data/SOF/SOFStatementImpl.h"
#include "Reach/Data/SOF/SOFException.h"
#include "Reach/Data/Session.h"
#include "Poco/Stopwatch.h"
#include "Poco/String.h"
#include "Poco/Mutex.h"
#include "Reach/Data/DataException.h"
#include "SoFProvider.h"
#include "SOFErrorCode.h"

#include <cstdlib>


#ifndef SOF_OPEN_URI
#define SOF_OPEN_URI 0
#endif


namespace Reach {
namespace Data {
namespace SOF {


const std::string SessionImpl::DEFERRED_BEGIN_TRANSACTION("BEGIN DEFERRED");
const std::string SessionImpl::COMMIT_TRANSACTION("COMMIT");
const std::string SessionImpl::ABORT_TRANSACTION("ROLLBACK");


SessionImpl::SessionImpl(const std::string& fileName, std::size_t loginTimeout):
	Reach::Data::AbstractSessionImpl<SessionImpl>(fileName, loginTimeout),
	_connector(Connector::KEY),
	_pDB(0),
	_connected(false),
	_isTransaction(false)
{
	open();
	setConnectionTimeout(loginTimeout);
	setProperty("handle", _pDB);
	addFeature("autoCommit", 
		&SessionImpl::autoCommit, 
		&SessionImpl::isAutoCommit);
	addProperty("connectionTimeout", &SessionImpl::setConnectionTimeout, &SessionImpl::getConnectionTimeout);
}


SessionImpl::~SessionImpl()
{
	try
	{
		close();
	}
	catch (...)
	{
		poco_unexpected();
	}
}


Reach::Data::StatementImpl* SessionImpl::createStatementImpl()
{
	poco_check_ptr (_pDB);
	return new SOFStatementImpl(*this, _pDB);
}


void SessionImpl::begin()
{
	Poco::Mutex::ScopedLock l(_mutex);
	SOFStatementImpl tmp(*this, _pDB);
	tmp.add(DEFERRED_BEGIN_TRANSACTION);
	tmp.execute();
	_isTransaction = true;
}


void SessionImpl::commit()
{
	Poco::Mutex::ScopedLock l(_mutex);
	SOFStatementImpl tmp(*this, _pDB);
	tmp.add(COMMIT_TRANSACTION);
	tmp.execute();
	_isTransaction = false;
}


void SessionImpl::rollback()
{
	Poco::Mutex::ScopedLock l(_mutex);
	SOFStatementImpl tmp(*this, _pDB);
	tmp.add(ABORT_TRANSACTION);
	tmp.execute();
	_isTransaction = false;
}


void SessionImpl::setTransactionIsolation(Poco::UInt32 ti)
{
	if (ti != Session::TRANSACTION_READ_COMMITTED)
		throw Poco::InvalidArgumentException("setTransactionIsolation()");
}


Poco::UInt32 SessionImpl::getTransactionIsolation()
{
	return Session::TRANSACTION_READ_COMMITTED;
}


bool SessionImpl::hasTransactionIsolation(Poco::UInt32 ti)
{
	if (ti == Session::TRANSACTION_READ_COMMITTED) return true;
	return false;
}


bool SessionImpl::isTransactionIsolation(Poco::UInt32 ti)
{
	if (ti == Session::TRANSACTION_READ_COMMITTED) return true;
	return false;
}


void SessionImpl::open(const std::string& connect)
{
	if (connect != connectionString())
	{
		if (isConnected())
			throw Poco::InvalidAccessException("Session already connected");

		if (!connect.empty())
			setConnectionString(connect);
	}

	poco_assert_dbg (!connectionString().empty());

	try
	{
		int rc = 0;
		size_t tout = getLoginTimeout();
		Poco::Stopwatch sw; sw.start();
		while (true)
		{
			/*rc = sqlite3_open_v2(connectionString().c_str(), &_pDB,
				SOF_OPEN_READWRITE | SOF_OPEN_CREATE | SOF_OPEN_URI, NULL);*/
			if (rc == SAR_OK) break;
			if (sw.elapsedSeconds() >= tout)
			{
				close();
				Utility::throwException(_pDB, rc);
			}
			else Poco::Thread::sleep(10);
		}
	} 
	catch (SOFException& ex)
	{
		throw ConnectionFailedException(ex.displayText());
	}

	_connected = true;
}


void SessionImpl::close()
{
	if (_pDB)
	{
		//sqlite3_close(_pDB);
		_pDB = 0;
	}

	_connected = false;
}


bool SessionImpl::isConnected()
{
	return _connected;
}


void SessionImpl::setConnectionTimeout(std::size_t timeout)
{
	int tout = static_cast<int>(1000 * timeout);
	//int rc = sqlite3_busy_timeout(_pDB, tout);
	int rc = 0;
	if (rc != 0) Utility::throwException(_pDB, rc);
	_timeout = tout;
}


void SessionImpl::setConnectionTimeout(const std::string& prop, const Poco::Any& value)
{
	setConnectionTimeout(Poco::RefAnyCast<std::size_t>(value));
}


Poco::Any SessionImpl::getConnectionTimeout(const std::string& prop)
{
	return Poco::Any(_timeout/1000);
}


void SessionImpl::autoCommit(const std::string&, bool)
{
	// The problem here is to decide whether to call commit or rollback
	// when autocommit is set to true. Hence, it is best not to implement
	// this explicit call and only implicitly support autocommit setting.
	throw Poco::NotImplementedException(
		"SOF autocommit is implicit with begin/commit/rollback.");
}


bool SessionImpl::isAutoCommit(const std::string&)
{
	Poco::Mutex::ScopedLock l(_mutex);
	//return (0 != sqlite3_get_autocommit(_pDB));
	return false;
}


// NOTE: Utility::dbHandle() has been moved here from Utility.cpp
// as a workaround for a failing AnyCast with Clang.
// See <https://github.com/pocoproject/poco/issues/578>
// for a discussion.
sqlite3* Utility::dbHandle(const Session& session)
{
	return Poco::AnyCast<sqlite3*>(session.getProperty("handle"));
}


} } } // namespace Reach::Data::SOF
