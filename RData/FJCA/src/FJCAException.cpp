//
// FJCAException.cpp
//
// Library: Data/SQLite
// Package: SQLite
// Module:  FJCAException
//
// Copyright (c) 2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#include "Reach/Data/FJCA/FJCAException.h"
#include <typeinfo>


namespace Reach {
namespace Data {
namespace FJCA {


POCO_IMPLEMENT_EXCEPTION(FJCAException, Reach::Data::DataException, "FJCA exception")
POCO_IMPLEMENT_EXCEPTION(InvalidSQLStatementException, FJCAException, "Invalid SQL statement")
POCO_IMPLEMENT_EXCEPTION(InternalDBErrorException, FJCAException, "Internal DB error")
POCO_IMPLEMENT_EXCEPTION(DBAccessDeniedException, FJCAException, "DB access denied")
POCO_IMPLEMENT_EXCEPTION(ExecutionAbortedException, FJCAException, "Execution aborted")
POCO_IMPLEMENT_EXCEPTION(DBLockedException, FJCAException, "DB locked")
POCO_IMPLEMENT_EXCEPTION(TableLockedException, FJCAException, "Table locked")
POCO_IMPLEMENT_EXCEPTION(NoMemoryException, FJCAException, "Out of Memory")
POCO_IMPLEMENT_EXCEPTION(ReadOnlyException, FJCAException, "Read only")
POCO_IMPLEMENT_EXCEPTION(InterruptException, FJCAException, "Interrupt")
POCO_IMPLEMENT_EXCEPTION(IOErrorException, FJCAException, "I/O error")
POCO_IMPLEMENT_EXCEPTION(CorruptImageException, FJCAException, "Corrupt image")
POCO_IMPLEMENT_EXCEPTION(TableNotFoundException, FJCAException, "Table not found")
POCO_IMPLEMENT_EXCEPTION(DatabaseFullException, FJCAException, "Database full")
POCO_IMPLEMENT_EXCEPTION(CantOpenDBFileException, FJCAException, "Can't open DB file")
POCO_IMPLEMENT_EXCEPTION(LockProtocolException, FJCAException, "Lock protocol")
POCO_IMPLEMENT_EXCEPTION(SchemaDiffersException, FJCAException, "Schema differs")
POCO_IMPLEMENT_EXCEPTION(RowTooBigException, FJCAException, "Row too big")
POCO_IMPLEMENT_EXCEPTION(ConstraintViolationException, FJCAException, "Constraint violation")
POCO_IMPLEMENT_EXCEPTION(DataTypeMismatchException, FJCAException, "Data type mismatch")
POCO_IMPLEMENT_EXCEPTION(ParameterCountMismatchException, FJCAException, "Parameter count mismatch")
POCO_IMPLEMENT_EXCEPTION(InvalidLibraryUseException, FJCAException, "Invalid library use")
POCO_IMPLEMENT_EXCEPTION(OSFeaturesMissingException, FJCAException, "OS features missing")
POCO_IMPLEMENT_EXCEPTION(AuthorizationDeniedException, FJCAException, "Authorization denied")
POCO_IMPLEMENT_EXCEPTION(TransactionException, FJCAException, "Transaction exception")


} } } // namespace Poco::Data::FJCA
