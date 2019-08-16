//
// SOFException.cpp
//
// Library: Data/SQLite
// Package: SQLite
// Module:  SOFException
//
// Copyright (c) 2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#include "Reach/Data/SOF/SOFException.h"
#include <typeinfo>


namespace Reach {
namespace Data {
namespace SOF {


POCO_IMPLEMENT_EXCEPTION(SOFException, Reach::Data::DataException, "SOF exception")
POCO_IMPLEMENT_EXCEPTION(InvalidSQLStatementException, SOFException, "Invalid SQL statement")
POCO_IMPLEMENT_EXCEPTION(InternalDBErrorException, SOFException, "Internal DB error")
POCO_IMPLEMENT_EXCEPTION(DBAccessDeniedException, SOFException, "DB access denied")
POCO_IMPLEMENT_EXCEPTION(ExecutionAbortedException, SOFException, "Execution aborted")
POCO_IMPLEMENT_EXCEPTION(DBLockedException, SOFException, "DB locked")
POCO_IMPLEMENT_EXCEPTION(TableLockedException, SOFException, "Table locked")
POCO_IMPLEMENT_EXCEPTION(NoMemoryException, SOFException, "Out of Memory")
POCO_IMPLEMENT_EXCEPTION(ReadOnlyException, SOFException, "Read only")
POCO_IMPLEMENT_EXCEPTION(InterruptException, SOFException, "Interrupt")
POCO_IMPLEMENT_EXCEPTION(IOErrorException, SOFException, "I/O error")
POCO_IMPLEMENT_EXCEPTION(CorruptImageException, SOFException, "Corrupt image")
POCO_IMPLEMENT_EXCEPTION(TableNotFoundException, SOFException, "Table not found")
POCO_IMPLEMENT_EXCEPTION(DatabaseFullException, SOFException, "Database full")
POCO_IMPLEMENT_EXCEPTION(CantOpenDBFileException, SOFException, "Can't open DB file")
POCO_IMPLEMENT_EXCEPTION(LockProtocolException, SOFException, "Lock protocol")
POCO_IMPLEMENT_EXCEPTION(SchemaDiffersException, SOFException, "Schema differs")
POCO_IMPLEMENT_EXCEPTION(RowTooBigException, SOFException, "Row too big")
POCO_IMPLEMENT_EXCEPTION(ConstraintViolationException, SOFException, "Constraint violation")
POCO_IMPLEMENT_EXCEPTION(DataTypeMismatchException, SOFException, "Data type mismatch")
POCO_IMPLEMENT_EXCEPTION(ParameterCountMismatchException, SOFException, "Parameter count mismatch")
POCO_IMPLEMENT_EXCEPTION(InvalidLibraryUseException, SOFException, "Invalid library use")
POCO_IMPLEMENT_EXCEPTION(OSFeaturesMissingException, SOFException, "OS features missing")
POCO_IMPLEMENT_EXCEPTION(AuthorizationDeniedException, SOFException, "Authorization denied")
POCO_IMPLEMENT_EXCEPTION(TransactionException, SOFException, "Transaction exception")


} } } // namespace Poco::Data::SOF
