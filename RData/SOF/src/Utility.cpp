//
// Utility.cpp
//
// Library: Data/SOF
// Package: SOF
// Module:  Utility
//
// Implementation of Utility
//
// Copyright (c) 2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#include "Reach/Data/SOF/Utility.h"
#include "Reach/Data/SOF/SOFException.h"
#include "Poco/NumberFormatter.h"
#include "Poco/String.h"
#include "Poco/Any.h"
#include "Poco/Exception.h"
#include "GMCrypto.h"
#include "SoFProvider.h"



#ifndef SOF_OPEN_URI
#define SOF_OPEN_URI 0
#endif


namespace Reach {
namespace Data {
namespace SOF {


const int Utility::THREAD_MODE_SINGLE = 0;
const int Utility::THREAD_MODE_MULTI = 1;
const int Utility::THREAD_MODE_SERIAL = 2;
int Utility::_threadMode = THREAD_MODE_SINGLE;

const int Utility::OPERATION_INSERT = 1;
const int Utility::OPERATION_DELETE = 2;
const int Utility::OPERATION_UPDATE = 3;

const std::string Utility::SOF_DATE_FORMAT = "%Y-%m-%d";
const std::string Utility::SOF_TIME_FORMAT = "%H:%M:%S";
//Utility::TypeMap Utility::_types;
Poco::Mutex Utility::_mutex;


Utility::SOFMutex::SOFMutex(sqlite3* pDB)//: _pMutex(sqlite3_db_mutex(pDB))
{
	//sqlite3_mutex_enter(_pMutex);
}


Utility::SOFMutex::~SOFMutex()
{
	//sqlite3_mutex_leave(_pMutex);
}


Utility::Utility()
{
	/*
	if (_types.empty())
	{
		_types.insert(TypeMap::value_type("", MetaColumn::FDT_STRING));
		_types.insert(TypeMap::value_type("BOOL", MetaColumn::FDT_BOOL));
		_types.insert(TypeMap::value_type("BOOLEAN", MetaColumn::FDT_BOOL));
		_types.insert(TypeMap::value_type("BIT", MetaColumn::FDT_BOOL));
		_types.insert(TypeMap::value_type("UINT8", MetaColumn::FDT_UINT8));
		_types.insert(TypeMap::value_type("UTINY", MetaColumn::FDT_UINT8));
		_types.insert(TypeMap::value_type("UINTEGER8", MetaColumn::FDT_UINT8));
		_types.insert(TypeMap::value_type("INT8", MetaColumn::FDT_INT8));
		_types.insert(TypeMap::value_type("TINY", MetaColumn::FDT_INT8));
		_types.insert(TypeMap::value_type("INTEGER8", MetaColumn::FDT_INT8));
		_types.insert(TypeMap::value_type("UINT16", MetaColumn::FDT_UINT16));
		_types.insert(TypeMap::value_type("USHORT", MetaColumn::FDT_UINT16));
		_types.insert(TypeMap::value_type("UINTEGER16", MetaColumn::FDT_UINT16));
		_types.insert(TypeMap::value_type("INT16", MetaColumn::FDT_INT16));
		_types.insert(TypeMap::value_type("SHORT", MetaColumn::FDT_INT16));
		_types.insert(TypeMap::value_type("INTEGER16", MetaColumn::FDT_INT16));
		_types.insert(TypeMap::value_type("UINT", MetaColumn::FDT_UINT32));
		_types.insert(TypeMap::value_type("UINT32", MetaColumn::FDT_UINT32));
		_types.insert(TypeMap::value_type("UINTEGER", MetaColumn::FDT_UINT64));
		_types.insert(TypeMap::value_type("UINTEGER32", MetaColumn::FDT_UINT32));
		_types.insert(TypeMap::value_type("INT", MetaColumn::FDT_INT32));
		_types.insert(TypeMap::value_type("INT32", MetaColumn::FDT_INT32));
		_types.insert(TypeMap::value_type("INTEGER", MetaColumn::FDT_INT64));
		_types.insert(TypeMap::value_type("INTEGER32", MetaColumn::FDT_INT32));
		_types.insert(TypeMap::value_type("UINT64", MetaColumn::FDT_UINT64));
		_types.insert(TypeMap::value_type("ULONG", MetaColumn::FDT_INT64));
		_types.insert(TypeMap::value_type("UINTEGER64", MetaColumn::FDT_UINT64));
		_types.insert(TypeMap::value_type("INT64", MetaColumn::FDT_INT64));
		_types.insert(TypeMap::value_type("LONG", MetaColumn::FDT_INT64));
		_types.insert(TypeMap::value_type("INTEGER64", MetaColumn::FDT_INT64));
		_types.insert(TypeMap::value_type("TINYINT", MetaColumn::FDT_INT8));
		_types.insert(TypeMap::value_type("SMALLINT", MetaColumn::FDT_INT16));
		_types.insert(TypeMap::value_type("BIGINT", MetaColumn::FDT_INT64));
		_types.insert(TypeMap::value_type("LONGINT", MetaColumn::FDT_INT64));
		_types.insert(TypeMap::value_type("COUNTER", MetaColumn::FDT_UINT64));
		_types.insert(TypeMap::value_type("AUTOINCREMENT", MetaColumn::FDT_UINT64));
		_types.insert(TypeMap::value_type("REAL", MetaColumn::FDT_DOUBLE));
		_types.insert(TypeMap::value_type("FLOA", MetaColumn::FDT_DOUBLE));
		_types.insert(TypeMap::value_type("FLOAT", MetaColumn::FDT_DOUBLE));
		_types.insert(TypeMap::value_type("DOUB", MetaColumn::FDT_DOUBLE));
		_types.insert(TypeMap::value_type("DOUBLE", MetaColumn::FDT_DOUBLE));
		_types.insert(TypeMap::value_type("DECIMAL", MetaColumn::FDT_DOUBLE));
		_types.insert(TypeMap::value_type("NUMERIC", MetaColumn::FDT_DOUBLE));
		_types.insert(TypeMap::value_type("CHAR", MetaColumn::FDT_STRING));
		_types.insert(TypeMap::value_type("CLOB", MetaColumn::FDT_STRING));
		_types.insert(TypeMap::value_type("TEXT", MetaColumn::FDT_STRING));
		_types.insert(TypeMap::value_type("VARCHAR", MetaColumn::FDT_STRING));
		_types.insert(TypeMap::value_type("NCHAR", MetaColumn::FDT_STRING));
		_types.insert(TypeMap::value_type("NCLOB", MetaColumn::FDT_STRING));
		_types.insert(TypeMap::value_type("NTEXT", MetaColumn::FDT_STRING));
		_types.insert(TypeMap::value_type("NVARCHAR", MetaColumn::FDT_STRING));
		_types.insert(TypeMap::value_type("LONGVARCHAR", MetaColumn::FDT_STRING));
		_types.insert(TypeMap::value_type("BLOB", MetaColumn::FDT_BLOB));
		_types.insert(TypeMap::value_type("DATE", MetaColumn::FDT_DATE));
		_types.insert(TypeMap::value_type("TIME", MetaColumn::FDT_TIME));
		_types.insert(TypeMap::value_type("DATETIME", MetaColumn::FDT_TIMESTAMP));
		_types.insert(TypeMap::value_type("TIMESTAMP", MetaColumn::FDT_TIMESTAMP));
	}
	*/
}


std::string Utility::lastError(sqlite3* pDB)
{
	std::string errStr;
	SOFMutex m(pDB);
	/*const char* pErr = sqlite3_errmsg(pDB);
	if (pErr) errStr = pErr;*/
	return errStr;
}


//MetaColumn::ColumnDataType Utility::getColumnType(sqlite3_stmt* pStmt, std::size_t pos)
//{
//	poco_assert_dbg (pStmt);
//
//	// Ensure statics are initialized
//	{
//		Poco::Mutex::ScopedLock lock(_mutex);
//		static Utility u;
//	}
//
//	const char* pc = sqlite3_column_decltype(pStmt, (int) pos);
//	std::string sqliteType = pc ? pc : "";
//	Poco::toUpperInPlace(sqliteType);
//	sqliteType = sqliteType.substr(0, sqliteType.find_first_of(" ("));
//
//	TypeMap::const_iterator it = _types.find(Poco::trimInPlace(sqliteType));
//	if (_types.end() == it)	throw Poco::NotFoundException();
//
//	return it->second;
//}


void Utility::throwException(sqlite3* pDB, int rc, const std::string& addErrMsg)
{
	/*
	switch (rc)
	{
	case SOF_OK:
		break;
	case SOF_ERROR:
		throw InvalidSQLStatementException(lastError(pDB), addErrMsg);
	case SOF_INTERNAL:
		throw InternalDBErrorException(lastError(pDB), addErrMsg);
	case SOF_PERM:
		throw DBAccessDeniedException(lastError(pDB), addErrMsg);
	case SOF_ABORT:
		throw ExecutionAbortedException(lastError(pDB), addErrMsg);
	case SOF_BUSY:
	case SOF_BUSY_RECOVERY:
#if defined(SOF_BUSY_SNAPSHOT)
	case SOF_BUSY_SNAPSHOT:
#endif
		throw DBLockedException(lastError(pDB), addErrMsg);
	case SOF_LOCKED:
		throw TableLockedException(lastError(pDB), addErrMsg);
	case SOF_NOMEM:
		throw NoMemoryException(lastError(pDB), addErrMsg);
	case SOF_READONLY:
		throw ReadOnlyException(lastError(pDB), addErrMsg);
	case SOF_INTERRUPT:
		throw InterruptException(lastError(pDB), addErrMsg);
	case SOF_IOERR:
		throw IOErrorException(lastError(pDB), addErrMsg);
	case SOF_CORRUPT:
		throw CorruptImageException(lastError(pDB), addErrMsg);
	case SOF_NOTFOUND:
		throw TableNotFoundException(lastError(pDB), addErrMsg);
	case SOF_FULL:
		throw DatabaseFullException(lastError(pDB), addErrMsg);
	case SOF_CANTOPEN:
		throw CantOpenDBFileException(lastError(pDB), addErrMsg);
	case SOF_PROTOCOL:
		throw LockProtocolException(lastError(pDB), addErrMsg);
	case SOF_EMPTY:
		throw InternalDBErrorException(lastError(pDB), addErrMsg);
	case SOF_SCHEMA:
		throw SchemaDiffersException(lastError(pDB), addErrMsg);
	case SOF_TOOBIG:
		throw RowTooBigException(lastError(pDB), addErrMsg);
	case SOF_CONSTRAINT:
		throw ConstraintViolationException(lastError(pDB), addErrMsg);
	case SOF_MISMATCH:
		throw DataTypeMismatchException(lastError(pDB), addErrMsg);
	case SOF_MISUSE:
		throw InvalidLibraryUseException(lastError(pDB), addErrMsg);
	case SOF_NOLFS:
		throw OSFeaturesMissingException(lastError(pDB), addErrMsg);
	case SOF_AUTH:
		throw AuthorizationDeniedException(lastError(pDB), addErrMsg);
	case SOF_FORMAT:
		throw CorruptImageException(lastError(pDB), addErrMsg);
	case SOF_NOTADB:
		throw CorruptImageException(lastError(pDB), addErrMsg);
	case SOF_RANGE:
		throw InvalidSQLStatementException(lastError(pDB), addErrMsg);
	case SOF_ROW:
		break; // sqlite_step() has another row ready
	case SOF_DONE:
		break; // sqlite_step() has finished executing
	default:
		throw SOFException(Poco::format("Unknown error code: %d", rc), addErrMsg);
	}
	*/
}


bool Utility::fileToMemory(sqlite3* pInMemory, const std::string& fileName)
{
	/*
	int rc;
	sqlite3* pFile;
	sqlite3_backup* pBackup;

	rc = sqlite3_open_v2(fileName.c_str(), &pFile, SOF_OPEN_READONLY | SOF_OPEN_URI, NULL);
	if(rc == SOF_OK )
	{
		pBackup = sqlite3_backup_init(pInMemory, "main", pFile, "main");
		if( pBackup )
		{
			sqlite3_backup_step(pBackup, -1);
			sqlite3_backup_finish(pBackup);
		}
		rc = sqlite3_errcode(pFile);
	}

	sqlite3_close(pFile);
	return SOF_OK == rc;
	*/
	return false;
}


bool Utility::memoryToFile(const std::string& fileName, sqlite3* pInMemory)
{
	/*
	int rc;
	sqlite3* pFile;
	sqlite3_backup* pBackup;

	rc = sqlite3_open_v2(fileName.c_str(), &pFile, SOF_OPEN_READWRITE | SOF_OPEN_CREATE | SOF_OPEN_URI, NULL);
	if(rc == SOF_OK )
	{
		pBackup = sqlite3_backup_init(pFile, "main", pInMemory, "main");
		if( pBackup )
		{
			sqlite3_backup_step(pBackup, -1);
			sqlite3_backup_finish(pBackup);
		}
		rc = sqlite3_errcode(pFile);
	}

	sqlite3_close(pFile);
	return SOF_OK == rc;
	*/
	return false;
}


bool Utility::isThreadSafe()
{
	return false;
	//return 0 != sqlite3_threadsafe();
}


int Utility::getThreadMode()
{
	return _threadMode;
}


bool Utility::setThreadMode(int mode)
{
#if (SOF_THREADSAFE != 0)
	if (SOF_OK == sqlite3_shutdown())
	{
		if (SOF_OK == sqlite3_config(mode))
		{
			_threadMode = mode;
			if (SOF_OK == sqlite3_initialize())
				return true;
		}
		sqlite3_initialize();
	}
#endif
	return false;
}


void* Utility::eventHookRegister(sqlite3* pDB, UpdateCallbackType callbackFn, void* pParam)
{
	/*
	typedef void(*pF)(void*, int, const char*, const char*, sqlite3_int64);
	return sqlite3_update_hook(pDB, reinterpret_cast<pF>(callbackFn), pParam);
	*/
	return 0;
}


void* Utility::eventHookRegister(sqlite3* pDB, CommitCallbackType callbackFn, void* pParam)
{
	// return sqlite3_commit_hook(pDB, callbackFn, pParam);
	return 0;
}


void* Utility::eventHookRegister(sqlite3* pDB, RollbackCallbackType callbackFn, void* pParam)
{
	// return sqlite3_rollback_hook(pDB, callbackFn, pParam);
	return 0;
}


// NOTE: Utility::dbHandle() has been moved to SessionImpl.cpp,
// as a workaround for a failing AnyCast with Clang.
// See <https://github.com/pocoproject/poco/issues/578>
// for a discussion.


} } } // namespace Poco::Data::SOF
