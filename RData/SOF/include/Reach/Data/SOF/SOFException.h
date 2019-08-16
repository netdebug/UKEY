//
// SOFException.h
//
// Library: Data/SOF
// Package: SOF
// Module:  SOFException
//
// Definition of SOFException.
//
// Copyright (c) 2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef SOF_SOFException_INCLUDED
#define SOF_SOFException_INCLUDED


#include "Reach/Data/SOF/SOF.h"
#include "Reach/Data/DataException.h"


namespace Reach {
namespace Data {
namespace SOF {


POCO_DECLARE_EXCEPTION(SOF_API, SOFException, Reach::Data::DataException)
POCO_DECLARE_EXCEPTION(SOF_API, InvalidSQLStatementException, SOFException)
POCO_DECLARE_EXCEPTION(SOF_API, InternalDBErrorException, SOFException)
POCO_DECLARE_EXCEPTION(SOF_API, DBAccessDeniedException, SOFException)
POCO_DECLARE_EXCEPTION(SOF_API, ExecutionAbortedException, SOFException)
POCO_DECLARE_EXCEPTION(SOF_API, DBLockedException, SOFException)
POCO_DECLARE_EXCEPTION(SOF_API, TableLockedException, SOFException)
POCO_DECLARE_EXCEPTION(SOF_API, NoMemoryException, SOFException)
POCO_DECLARE_EXCEPTION(SOF_API, ReadOnlyException, SOFException)
POCO_DECLARE_EXCEPTION(SOF_API, InterruptException, SOFException)
POCO_DECLARE_EXCEPTION(SOF_API, IOErrorException, SOFException)
POCO_DECLARE_EXCEPTION(SOF_API, CorruptImageException, SOFException)
POCO_DECLARE_EXCEPTION(SOF_API, TableNotFoundException, SOFException)
POCO_DECLARE_EXCEPTION(SOF_API, DatabaseFullException, SOFException)
POCO_DECLARE_EXCEPTION(SOF_API, CantOpenDBFileException, SOFException)
POCO_DECLARE_EXCEPTION(SOF_API, LockProtocolException, SOFException)
POCO_DECLARE_EXCEPTION(SOF_API, SchemaDiffersException, SOFException)
POCO_DECLARE_EXCEPTION(SOF_API, RowTooBigException, SOFException)
POCO_DECLARE_EXCEPTION(SOF_API, ConstraintViolationException, SOFException)
POCO_DECLARE_EXCEPTION(SOF_API, DataTypeMismatchException, SOFException)
POCO_DECLARE_EXCEPTION(SOF_API, ParameterCountMismatchException, SOFException)
POCO_DECLARE_EXCEPTION(SOF_API, InvalidLibraryUseException, SOFException)
POCO_DECLARE_EXCEPTION(SOF_API, OSFeaturesMissingException, SOFException)
POCO_DECLARE_EXCEPTION(SOF_API, AuthorizationDeniedException, SOFException)
POCO_DECLARE_EXCEPTION(SOF_API, TransactionException, SOFException)


} } } // namespace Poco::Data::SOF


#endif
