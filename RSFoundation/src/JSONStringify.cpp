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
#include <iomanip>
#include <sstream>
#include <set>

using namespace Reach;
using Poco::JSON::Object;
using Poco::JSON::Query;
using Poco::Dynamic::Var;

JSONStringify::JSONStringify() :
	code(0), message("successful"), result(JSONOptions)
{
	format();
}

JSONStringify::JSONStringify(std::string _message, int _code) :
	code(_code), message(_message), result(JSONOptions)
{
	format();
}

JSONStringify::~JSONStringify()
{

}

void JSONStringify::format()
{
	std::stringstream _;
	_ << std::setw(4) << std::left << std::setfill('0') << code;

	result.set("code", _.str());
	result.set("msg", message);
}

JSONStringify& JSONStringify::addObject(const std::string& k, const std::string& v)
{
	Object O(JSONOptions);
	O.set(k, v);
	result.set("data", O);
	return *this;
}

JSONStringify& JSONStringify::addObject(const std::string& k, int v)
{
	Object O(JSONOptions);
	O.set(k, v);
	result.set("data", O);
	return *this;
}

JSONStringify& JSONStringify::addNullObject()
{
	Object O(JSONOptions);
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
	Object t(JSONOptions);
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
	Object t(JSONOptions);
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
