//
// StatementImpl.h
//
// Library: Data
// Package: DataCore
// Module:  StatementImpl
//
// Definition of the StatementImpl class.
//
// Copyright (c) 2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef Data_StatementImpl_INCLUDED
#define Data_StatementImpl_INCLUDED


#include "Reach/Data/Data.h"
#include "Reach/Data/SessionImpl.h"
#include "Poco/RefCountedObject.h"
#include "Poco/String.h"
#include "Poco/Format.h"
#include "Poco/Exception.h"
#include "Poco/SharedPtr.h"
#include <vector>
#include <list>
#include <deque>
#include <string>
#include <sstream>


namespace Reach {
namespace Data {


class Data_API StatementImpl
	/// StatementImpl interface that subclasses must implement to define database dependent query execution.
	///
	/// StatementImpl's are noncopyable.
{
public:
	typedef Poco::SharedPtr<StatementImpl> Ptr;

	enum State
	{
		ST_INITIALIZED,
		ST_COMPILED,
		ST_BOUND,
		ST_PAUSED,
		ST_DONE,
		ST_RESET
	};

	StatementImpl(SessionImpl& rSession);
		/// Creates the StatementImpl.

	virtual ~StatementImpl();
		/// Destroys the StatementImpl.

	template <typename T> 
	void add(const T& t)
		/// Appends SQL statement (fragments).
	{
		_ostr << t;
	}

	std::string toString() const;
		/// Create a string version of the SQL statement.

	std::size_t execute(const bool& reset = true);
		/// Executes a statement. Returns the number of rows 
		/// extracted for statements returning data or number of rows 
		/// affected for all other statements (insert, update, delete).
		/// If reset is true (default), the underlying bound storage is
		/// reset and reused. In case of containers, this means they are
		/// cleared and resized to accomodate the number of rows returned by
		/// this execution step. When reset is false, data is appended to the
		/// bound containers during multiple execute calls.

	void reset();
		/// Resets the statement, so that we can reuse all bindings and re-execute again.

	State getState() const;
		/// Returns the state of the Statement.
		
protected:

	SessionImpl& session();
		/// Rteurns session associated with this statement.

private:
	void prepareFunc();
		/// Compiles the statement.

	void formatSQL(std::vector<Poco::Any>& arguments);
		/// Formats the SQL string by filling in placeholders with values from supplied vector.


	StatementImpl(const StatementImpl& stmt);
	StatementImpl& operator = (const StatementImpl& stmt);

	typedef std::vector<std::size_t> CountVec;

	State                    _state;
	SessionImpl&             _rSession;
	std::ostringstream       _ostr;

	friend class Statement; 
};


//
// inlines
//


inline std::string StatementImpl::toString() const
{
	return _ostr.str();
}


inline StatementImpl::State StatementImpl::getState() const
{
	return _state;
}


inline SessionImpl& StatementImpl::session()
{
	return _rSession;
}

} } // namespace Poco::Data


#endif // Data_StatementImpl_INCLUDED
