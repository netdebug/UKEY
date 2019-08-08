//
// Statement.h
//
// Library: Data
// Package: DataCore
// Module:  Statement
//
// Definition of the Statement class.
//
// Copyright (c) 2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef Data_Statement_INCLUDED
#define Data_Statement_INCLUDED


#include "Reach/Data/Data.h"
#include "Reach/Data/StatementImpl.h"
#include "Poco/SharedPtr.h"
#include "Poco/Mutex.h"
#include "Poco/ActiveMethod.h"
#include "Poco/ActiveResult.h"
#include "Poco/Format.h"
#include <algorithm>


namespace Reach {
namespace Data {

class Session;


class Data_API Statement
	/// A Statement is used to execute SQL statements.
	/// It does not contain code of its own.
	/// Its main purpose is to forward calls to the concrete StatementImpl stored inside.
	/// Statement execution can be synchronous or asynchronous.
	/// Synchronous ececution is achieved through execute() call, while asynchronous is
	/// achieved through executeAsync() method call.
	/// An asynchronously executing statement should not be copied during the execution.
	///
	/// Note:
	///
	/// Once set as asynchronous through 'async' manipulator, statement remains
	/// asynchronous for all subsequent execution calls, both execute() and executeAsync().
	/// However, calling executAsync() on a synchronous statement shall execute
	/// asynchronously but without altering the underlying statement's synchronous nature.
	///
	/// Once asynchronous, a statement can be reverted back to synchronous state in two ways:
	///
	///   1) By calling setAsync(false)
	///   2) By means of 'sync' or 'reset' manipulators
	///
	/// See individual functions documentation for more details.
	///
	/// Statement owns the RowFormatter, which can be provided externaly through setFormatter()
	/// member function.
	/// If no formatter is externally supplied to the statement, the SimpleRowFormatter is lazy
	/// created and used.
{
public:
	typedef void (*Manipulator)(Statement&);

	typedef Poco::ActiveResult<std::size_t>                      Result;
	typedef Poco::SharedPtr<Result>                              ResultPtr;
	typedef Poco::ActiveMethod<std::size_t, bool, StatementImpl> AsyncExecMethod;
	typedef Poco::SharedPtr<AsyncExecMethod>                     AsyncExecMethodPtr;

	static const int WAIT_FOREVER = -1;

	Statement(StatementImpl::Ptr pImpl);
		/// Creates the Statement.

	explicit Statement(Session& session);
		/// Creates the Statement for the given Session.
		///
		/// The following:
		///
		///     Statement stmt(sess);
		///     stmt << "SELECT * FROM Table", ...
		///
		/// is equivalent to:
		///
		///     Statement stmt(sess << "SELECT * FROM Table", ...);
		///
		/// but in some cases better readable.

	~Statement();
		/// Destroys the Statement.

	Statement(const Statement& stmt);
		/// Copy constructor.
		/// If the statement has been executed asynchronously and has not been
		/// synchronized prior to copy operation (i.e. is copied while executing),
		/// this constructor shall synchronize it.

	Statement& operator = (const Statement& stmt);
		/// Assignment operator.

	void swap(Statement& other);
		/// Swaps the statement with another one.

	template <typename T>
	Statement& operator << (const T& t)
		/// Concatenates data with the SQL statement string.
	{
		_pImpl->add(t);
		return *this;
	}

	Statement& operator , (Manipulator manip);
		/// Handles manipulators, such as now, async, etc.

	Statement& operator , (char value);
		/// Adds the value to the list of values to be supplied to the SQL string formatting function.

	Statement& operator , (Poco::UInt8 value);
		/// Adds the value to the list of values to be supplied to the SQL string formatting function.

	Statement& operator , (Poco::Int8 value);
		/// Adds the value to the list of values to be supplied to the SQL string formatting function.

	Statement& operator , (Poco::UInt16 value);
		/// Adds the value to the list of values to be supplied to the SQL string formatting function.

	Statement& operator , (Poco::Int16 value);
		/// Adds the value to the list of values to be supplied to the SQL string formatting function.

	Statement& operator , (Poco::UInt32 value);
		/// Adds the value to the list of values to be supplied to the SQL string formatting function.

	Statement& operator , (Poco::Int32 value);
		/// Adds the value to the list of values to be supplied to the SQL string formatting function.

#ifndef POCO_LONG_IS_64_BIT
	Statement& operator , (long value);
		/// Adds the value to the list of values to be supplied to the SQL string formatting function.

	Statement& operator , (unsigned long value);
		/// Adds the value to the list of values to be supplied to the SQL string formatting function.
#endif
	Statement& operator , (Poco::UInt64 value);
		/// Adds the value to the list of values to be supplied to the SQL string formatting function.

	Statement& operator , (Poco::Int64 value);
		/// Adds the value to the list of values to be supplied to the SQL string formatting function.

	Statement& operator , (double value);
		/// Adds the value to the list of values to be supplied to the SQL string formatting function.

	Statement& operator , (float value);
		/// Adds the value to the list of values to be supplied to the SQL string formatting function.

	Statement& operator , (bool value);
		/// Adds the value to the list of values to be supplied to the SQL string formatting function.

	Statement& operator , (const std::string& value);
		/// Adds the value to the list of values to be supplied to the SQL string formatting function.

	Statement& operator , (const char* value);
		/// Adds the value to the list of values to be supplied to the SQL string formatting function.

	const std::string& toString() const;
		/// Creates a string from the accumulated SQL statement.

	std::size_t execute(bool reset = true);
		/// Executes the statement synchronously or asynchronously.
		/// Stops when either a limit is hit or the whole statement was executed.
		/// Returns the number of rows extracted from the database (for statements
		/// returning data) or number of rows affected (for all other statements).
		/// If reset is true (default), associated storage is reset and reused.
		/// Otherwise, the results from this execution step are appended.
		/// Reset argument has no meaning for unlimited statements that return all rows.
		/// If isAsync() returns  true, the statement is executed asynchronously
		/// and the return value from this function is zero.
		/// The result of execution (i.e. number of returned or affected rows) can be
		/// obtained by calling wait() on the statement at a later point in time.

	const Result& executeAsync(bool reset = true);
		/// Executes the statement asynchronously.
		/// Stops when either a limit is hit or the whole statement was executed.
		/// Returns immediately. Calling wait() (on either the result returned from this
		/// call or the statement itself) returns the number of rows extracted or number
		/// of rows affected by the statement execution.
		/// When executed on a synchronous statement, this method does not alter the
		/// statement's synchronous nature.

	void setAsync(bool async = true);
		/// Sets the asynchronous flag. If this flag is true, executeAsync() is called
		/// from the now() manipulator. This setting does not affect the statement's
		/// capability to be executed synchronously by directly calling execute().

	bool isAsync() const;
		/// Returns true if statement was marked for asynchronous execution.

	std::size_t wait(long milliseconds = WAIT_FOREVER);
		/// Waits for the execution completion for asynchronous statements or
		/// returns immediately for synchronous ones. The return value for
		/// asynchronous statement is the execution result (i.e. number of
		/// rows retrieved). For synchronous statements, the return value is zero.

	bool initialized();
		/// Returns true if the statement was initialized (i.e. not executed yet).

	bool paused();
		/// Returns true if the statement was paused (a range limit stopped it
		/// and there is more work to do).

	bool done();
		/// Returns true if the statement was completely executed or false if a range limit stopped it
		/// and there is more work to do. When no limit is set, it will always return true after calling execute().

	Statement& reset(Session& session);
		/// Resets the Statement so that it can be filled with a new SQL command.

protected:
	typedef StatementImpl::Ptr ImplPtr;

	ImplPtr impl() const;
		/// Returns pointer to statement implementation.

	Session session();
		/// Returns the underlying session.

private:

	const Result& doAsyncExec(bool reset = true);
		/// Asynchronously executes the statement.

	template <typename T>
	Statement& commaPODImpl(const T& val)
	{
		_arguments.push_back(val);
		return *this;
	}

	StatementImpl::Ptr _pImpl;

	// asynchronous execution related members
	bool                _async;
	mutable ResultPtr   _pResult;
	Poco::Mutex               _mutex;
	AsyncExecMethodPtr  _pAsyncExec;
	std::vector<Poco::Any>    _arguments;
	mutable std::string _stmtString;
};

//
// inlines

namespace Keywords {


//
// Manipulators
//

inline void Data_API now(Statement& statement)
	/// Enforces immediate execution of the statement.
	/// If _isAsync flag has been set, execution is invoked asynchronously.
{
	statement.execute();
}


inline void Data_API sync(Statement& statement)
	/// Sets the _isAsync flag to false, signalling synchronous execution.
	/// Synchronous execution is default, so specifying this manipulator
	/// only makes sense if async() was called for the statement before.
{
	statement.setAsync(false);
}


inline void Data_API async(Statement& statement)
	/// Sets the _async flag to true, signalling asynchronous execution.
{
	statement.setAsync(true);
}

} // namespace Keywords


//
// inlines
//

inline Statement& Statement::operator , (char value)
{
	return commaPODImpl(value);
}


inline Statement& Statement::operator , (Poco::UInt8 value)
{
	return commaPODImpl(value);
}


inline Statement& Statement::operator , (Poco::Int8 value)
{
	return commaPODImpl(value);
}


inline Statement& Statement::operator , (Poco::UInt16 value)
{
	return commaPODImpl(value);
}


inline Statement& Statement::operator , (Poco::Int16 value)
{
	return commaPODImpl(value);
}


inline Statement& Statement::operator , (Poco::UInt32 value)
{
	return commaPODImpl(value);
}


inline Statement& Statement::operator , (Poco::Int32 value)
{
	return commaPODImpl(value);
}


#ifndef POCO_LONG_IS_64_BIT
inline Statement& Statement::operator , (long value)
{
	return commaPODImpl(value);
}


inline Statement& Statement::operator , (unsigned long value)
{
	return commaPODImpl(value);
}
#endif


inline Statement& Statement::operator , (Poco::UInt64 value)
{
	return commaPODImpl(value);
}


inline Statement& Statement::operator , (Poco::Int64 value)
{
	return commaPODImpl(value);
}


inline Statement& Statement::operator , (double value)
{
	return commaPODImpl(value);
}


inline Statement& Statement::operator , (float value)
{
	return commaPODImpl(value);
}


inline Statement& Statement::operator , (bool value)
{
	return commaPODImpl(value);
}


inline Statement& Statement::operator , (const std::string& value)
{
	return commaPODImpl(value);
}


inline Statement& Statement::operator , (const char* value)
{
	return commaPODImpl(std::string(value));
}

inline Statement::ImplPtr Statement::impl() const
{
	return _pImpl;
}


inline const std::string& Statement::toString() const
{
	return _stmtString = _pImpl->toString();
}

inline bool Statement::initialized()
{
	return _pImpl->getState() == StatementImpl::ST_INITIALIZED;
}


inline bool Statement::paused()
{
	return _pImpl->getState() == StatementImpl::ST_PAUSED;
}


inline bool Statement::done()
{
	return _pImpl->getState() == StatementImpl::ST_DONE;
}

inline bool Statement::isAsync() const
{
	return _async;
}

inline void swap(Statement& s1, Statement& s2)
{
	s1.swap(s2);
}


} } // namespace Poco::Data


namespace std
{
	template<>
	inline void swap<Reach::Data::Statement>(Reach::Data::Statement& s1,
		Reach::Data::Statement& s2)
		/// Full template specalization of std:::swap for Statement
	{
		s1.swap(s2);
	}
}


#endif // Data_Statement_INCLUDED
