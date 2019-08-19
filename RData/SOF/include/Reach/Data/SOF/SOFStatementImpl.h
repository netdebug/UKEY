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
#include "Reach/Data/StatementImpl.h"
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
	SOFStatementImpl(Reach::Data::SessionImpl& rSession);
		/// Creates the SOFStatementImpl.

	~SOFStatementImpl();
		/// Destroys the SOFStatementImpl.
protected:

private:
	void clear();
		/// Removes the _pStmt

	typedef Poco::SharedPtr<std::string>        StrPtr;

	bool             _stepCalled;

	static const int POCO_SQLITE_INV_ROW_CNT;
};


} } } // namespace Poco::Data::SOF


#endif // Data_SOF_SOFStatementImpl_INCLUDED
