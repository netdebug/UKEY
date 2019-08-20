//
// FJCAException.h
//
// Library: Data/FJCA
// Package: FJCA
// Module:  FJCAException
//
// Definition of FJCAException.
//
// Copyright (c) 2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef FJCA_FJCAException_INCLUDED
#define FJCA_FJCAException_INCLUDED


#include "Reach/Data/FJCA/FJCA.h"
#include "Reach/Data/DataException.h"


namespace Reach {
namespace Data {
namespace FJCA {


POCO_DECLARE_EXCEPTION(FJCA_API, FJCAException, Reach::Data::DataException)
POCO_DECLARE_EXCEPTION(FJCA_API, InvalidSQLStatementException, FJCAException)
POCO_DECLARE_EXCEPTION(FJCA_API, InternalDBErrorException, FJCAException)
POCO_DECLARE_EXCEPTION(FJCA_API, DBAccessDeniedException, FJCAException)
POCO_DECLARE_EXCEPTION(FJCA_API, ExecutionAbortedException, FJCAException)
POCO_DECLARE_EXCEPTION(FJCA_API, DBLockedException, FJCAException)
POCO_DECLARE_EXCEPTION(FJCA_API, TableLockedException, FJCAException)
POCO_DECLARE_EXCEPTION(FJCA_API, NoMemoryException, FJCAException)
POCO_DECLARE_EXCEPTION(FJCA_API, ReadOnlyException, FJCAException)
POCO_DECLARE_EXCEPTION(FJCA_API, InterruptException, FJCAException)
POCO_DECLARE_EXCEPTION(FJCA_API, IOErrorException, FJCAException)
POCO_DECLARE_EXCEPTION(FJCA_API, CorruptImageException, FJCAException)
POCO_DECLARE_EXCEPTION(FJCA_API, TableNotFoundException, FJCAException)
POCO_DECLARE_EXCEPTION(FJCA_API, DatabaseFullException, FJCAException)
POCO_DECLARE_EXCEPTION(FJCA_API, CantOpenDBFileException, FJCAException)
POCO_DECLARE_EXCEPTION(FJCA_API, LockProtocolException, FJCAException)
POCO_DECLARE_EXCEPTION(FJCA_API, SchemaDiffersException, FJCAException)
POCO_DECLARE_EXCEPTION(FJCA_API, RowTooBigException, FJCAException)
POCO_DECLARE_EXCEPTION(FJCA_API, ConstraintViolationException, FJCAException)
POCO_DECLARE_EXCEPTION(FJCA_API, DataTypeMismatchException, FJCAException)
POCO_DECLARE_EXCEPTION(FJCA_API, ParameterCountMismatchException, FJCAException)
POCO_DECLARE_EXCEPTION(FJCA_API, InvalidLibraryUseException, FJCAException)
POCO_DECLARE_EXCEPTION(FJCA_API, OSFeaturesMissingException, FJCAException)
POCO_DECLARE_EXCEPTION(FJCA_API, AuthorizationDeniedException, FJCAException)
POCO_DECLARE_EXCEPTION(FJCA_API, TransactionException, FJCAException)


} } } // namespace Poco::Data::FJCA


#endif
