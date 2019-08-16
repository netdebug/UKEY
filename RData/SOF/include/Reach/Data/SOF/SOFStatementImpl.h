//
// SOFStatementImpl.h
//
// Library: Data/SOF
// Package: SOF
// Module:  SOFStatementImpl
//
// Definition of the SOFStatementImpl class.
//
// Copyright (c) 2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef Data_SOF_SOFStatementImpl_INCLUDED
#define Data_SOF_SOFStatementImpl_INCLUDED


#include "Reach/Data/SOF/SOF.h"
//#include "Reach/Data/SOF/Binder.h"
//#include "Reach/Data/SOF/Extractor.h"
#include "Reach/Data/StatementImpl.h"
//#include "Reach/Data/MetaColumn.h"
#include "Poco/SharedPtr.h"


extern "C"
{
	typedef struct sqlite3 sqlite3;
	typedef struct sqlite3_stmt sqlite3_stmt;
}


namespace Reach {
namespace Data {
namespace SOF {


class SOF_API SOFStatementImpl: public Reach::Data::StatementImpl
	/// Implements statement functionality needed for SOF
{
public:
	SOFStatementImpl(Poco::Data::SessionImpl& rSession, sqlite3* pDB);
		/// Creates the SOFStatementImpl.

	~SOFStatementImpl();
		/// Destroys the SOFStatementImpl.

protected:
	std::size_t columnsReturned() const;
		/// Returns number of columns returned by query.

	int affectedRowCount() const;
		/// Returns the number of affected rows.
		/// Used to find out the number of rows affected by insert, delete or update.
		/// All changes are counted, even if they are later undone by a ROLLBACK or ABORT. 
		/// Changes associated with creating and dropping tables are not counted.

	const MetaColumn& metaColumn(std::size_t pos) const;
		/// Returns column meta data.

	bool hasNext();
		/// Returns true if a call to next() will return data.

	std::size_t next();
		/// Retrieves the next row from the resultset and returns 1.
		/// Will throw, if the resultset is empty.

	bool canBind() const;
		/// Returns true if a valid statement is set and we can bind.

	bool canCompile() const;
		/// Returns true if statement can compile.

	void compileImpl();
		/// Compiles the statement, doesn't bind yet.
		/// Returns true if the statement was succesfully compiled.
		/// The way SOF handles batches of statmeents is by compiling
		/// one at a time and returning a pointer to the next one.
		/// The remainder of the statement is kept in a string
		/// buffer pointed to by _pLeftover member.

	void bindImpl();
		/// Binds parameters

	AbstractExtraction::ExtractorPtr extractor();
		/// Returns the concrete extractor used by the statement.

	AbstractBinding::BinderPtr binder();
		/// Returns the concrete binder used by the statement.

private:
	void clear();
		/// Removes the _pStmt

	typedef Poco::SharedPtr<Binder>             BinderPtr;
	typedef Poco::SharedPtr<Extractor>          ExtractorPtr;
	typedef Poco::Data::AbstractBindingVec      Bindings;
	typedef Poco::Data::AbstractExtractionVec   Extractions;
	typedef std::vector<Poco::Data::MetaColumn> MetaColumnVec;
	typedef std::vector<MetaColumnVec>          MetaColumnVecVec;
	typedef Poco::SharedPtr<std::string>        StrPtr;
	typedef Bindings::iterator                  BindIt;

	sqlite3*         _pDB;
	sqlite3_stmt*    _pStmt;
	bool             _stepCalled;
	int              _nextResponse;
	BinderPtr        _pBinder;
	ExtractorPtr     _pExtractor;
	MetaColumnVecVec _columns;
	int              _affectedRowCount;
	StrPtr           _pLeftover;
	BindIt           _bindBegin;
	bool             _canBind;
	bool             _isExtracted;
	bool             _canCompile;

	static const int POCO_SQLITE_INV_ROW_CNT;
};


//
// inlines
//
inline AbstractExtraction::ExtractorPtr SOFStatementImpl::extractor()
{
	return _pExtractor;
}


inline AbstractBinding::BinderPtr SOFStatementImpl::binder()
{
	return _pBinder;
}


inline bool SOFStatementImpl::canBind() const
{
	return _canBind;
}


inline bool SOFStatementImpl::canCompile() const
{
	return _canCompile;
}


} } } // namespace Poco::Data::SOF


#endif // Data_SOF_SOFStatementImpl_INCLUDED
