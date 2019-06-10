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
#include "Poco/JSON/Query.h"
#include "Poco/Dynamic/Var.h"
#include <iostream>
#include <cassert>
#include <set>

using namespace Reach;
using Poco::JSON_PRESERVE_KEY_ORDER;
using Poco::JSON::Object;
using Poco::JSON::Query;
using Poco::Dynamic::Var;

JSONStringify::JSONStringify() :
	code(0), message("successful"), result(Poco::JSON_PRESERVE_KEY_ORDER)
{
	format();
}

JSONStringify::JSONStringify(std::string _message, int _code) :
	code(_code), message(_message), result(Poco::JSON_PRESERVE_KEY_ORDER)
{
	format();
}

JSONStringify::~JSONStringify()
{

}

void JSONStringify::format()
{
	result.set("code", code);
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

JSONStringify& JSONStringify::addObjectItem(const std::string& k, const std::string& v)
{
	assert(result.has("data"));
	//{ d -> o }
	Query query(result);
	Object::Ptr d = query.findObject("data");
	assert(!d.isNull());
	Object t;
	t = std::move(*d);
	t.set(k, v);
	result.set("data", t);

	return *this;
}

JSONStringify& JSONStringify::addObjectItem(const std::string& k, int v)
{
	assert(result.has("data"));
	//{ d -> o }
	Query query(result);
	Object::Ptr d = query.findObject("data");
	assert(!d.isNull());
	Object t;
	t = std::move(*d);
	t.set(k, v);
	result.set("data", t);

	return *this;
}

JSONStringify::operator std::string()
{
	std::ostringstream out;
	result.stringify(out);
	return out.str();
}
