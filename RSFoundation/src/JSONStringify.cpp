//
// JSONStringify.cpp
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#include "JSONStringify.h"
#include "Poco/JSON/Object.h"
#include <iostream>

using namespace Reach;
using Poco::JSON_PRESERVE_KEY_ORDER;
using Poco::JSON::Object;

JSONStringify::JSONStringify():
	code(0),message("successful"), result(Poco::JSON_PRESERVE_KEY_ORDER)
{
	format();
}

JSONStringify::JSONStringify(std::string _message, int _code):
	code(_code), message(_message), result(Poco::JSON_PRESERVE_KEY_ORDER)
{
	format();
}

JSONStringify::~JSONStringify()
{

}

void JSONStringify::format()
{
	result.set("code", "0000");
	result.set("msg", message);
}

JSONStringify& JSONStringify::addObject(const std::string& k, const std::string& v)
{
	Object O(JSON_PRESERVE_KEY_ORDER);
	O.set(k, v);
	result.set("data", O);
	return *this;
}

JSONStringify& JSONStringify::addObject(const std::string& k, int v)
{
	Object O(JSON_PRESERVE_KEY_ORDER);
	O.set(k, v);
	result.set("data", O);
	return *this;
}

JSONStringify& JSONStringify::addNullObject()
{
	Object O(JSON_PRESERVE_KEY_ORDER);
	O.set("", "");
	result.set("data", O);
	return *this;
}

JSONStringify::operator std::string()
{
	std::ostringstream out;
	result.stringify(out);
	return out.str();
}
