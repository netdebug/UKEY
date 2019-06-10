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

		JSONStringify& addObject(const std::string& k, const std::string& v);
		JSONStringify& addObject(const std::string& k, int v);
		JSONStringify& addNullObject();

		JSONStringify& addObjectItem(const std::string& k, const std::string& v);
		JSONStringify& addObjectItem(const std::string& k, int v);

		operator std::string();
	protected:
		void format();

	private:
		int code;
		std::string message;
		Poco::JSON::Object result;
	};
}

#endif // RS_JSONStringify_INCLUDE
