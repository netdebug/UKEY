//
// RequestHandleException.cpp
//
// Library: Reach
// Package: Reach
// Module:  RequestHandleException
//
// Copyright (c) 2019, Reach Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#include "RequestHandleException.h"
#include <typeinfo>

namespace Reach {

POCO_IMPLEMENT_EXCEPTION(RequestHandleException, Poco::Exception, "RequestHandler Exception")
POCO_IMPLEMENT_EXCEPTION(CloudCommandException, Poco::Exception, "CloudCommand Exception")
} // namespace Reach
