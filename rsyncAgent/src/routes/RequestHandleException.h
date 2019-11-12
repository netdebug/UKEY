//
// RequestHandleException.h
//
// Library: Reach
// Package: Reach
// Module:  RequestHandleException
//
// Definition of the RequestHandleException class.
//
// Copyright (c) 2019, Reach Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef Reach_RequestHandleException_INCLUDED
#define Reach_RequestHandleException_INCLUDED

#include "Poco/Foundation.h"
#include "Poco/Exception.h"

namespace Reach {

POCO_DECLARE_EXCEPTION(, RequestHandleException, Poco::Exception)
POCO_DECLARE_EXCEPTION(, CloudCommandException, Poco::Exception)
}  // namespace Reach


#endif // Reach_RequestHandleException_INCLUDED
