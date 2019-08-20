//
// SOFStatementImpl.cpp
//
// Library: Data/SOF
// Package: SOF
// Module:  SOFStatementImpl
//
// Copyright (c) 2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#include "Reach/Data/SOF/SOFStatementImpl.h"
#include "Reach/Data/SOF/Utility.h"
#include "Reach/Data/SOF/SOFException.h"
#include "Poco/String.h"
#include <cstdlib>
#include <cstring>
#if defined(POCO_UNBUNDLED)
#include <SoFProvider.h>
#else
#include "SoFProvider.h"
#endif


namespace Reach {
namespace Data {
namespace SOF {


const int SOFStatementImpl::POCO_SQLITE_INV_ROW_CNT = -1;


SOFStatementImpl::SOFStatementImpl(Reach::Data::SessionImpl& rSession):
	StatementImpl(rSession),
	_stepCalled(false)
{
}
	

SOFStatementImpl::~SOFStatementImpl()
{
	try
	{
		clear();
	}
	catch (...)
	{
		poco_unexpected();
	}
}

void SOFStatementImpl::clear()
{
}

} } } // namespace Poco::Data::SOF
