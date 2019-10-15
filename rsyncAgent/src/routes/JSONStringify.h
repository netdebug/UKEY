//
// JSONStringify.h
//
// Definition of the JSONStringify class.
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef RS_JSONStringify_INCLUDE
#define RS_JSONStringify_INCLUDE

#include "Poco/Foundation.h"
#include "Poco/JSON/Object.h"
#include <string>

namespace Reach {

	class JSONStringify
	{
	public:
		JSONStringify();
		JSONStringify(std::string _message, int _code);
		~JSONStringify();

		JSONStringify(const JSONStringify& other);
		JSONStringify& operator = (const JSONStringify& other);

		JSONStringify& addObject(const std::string& k, const std::string& v);
		JSONStringify& addObject(const std::string& k, int v);
		JSONStringify& addNullObject();

		JSONStringify& addObjectItem(const std::string& k, const std::string& v);
		JSONStringify& addObjectItem(const std::string& k, int v);

		JSONStringify& addDataItem(const std::string& k, const std::string& v);
		void clear();
		bool empty();
		std::string toString();
		operator std::string();
	protected:
		void format();

	private:
		int code;
		std::string message;
		Poco::JSON::Object result;
		const int JSONOptions = (Poco::JSONOptions::JSON_PRESERVE_KEY_ORDER);
	};
}

#endif // RS_JSONStringify_INCLUDE
