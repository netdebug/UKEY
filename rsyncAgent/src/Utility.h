#pragma once

#include <string>

namespace Reach {

	class Utility
	{
	public:
		static std::string config(const std::string& name);
		static std::string timestamp();
		static std::string UniqueTransOrder();
		static bool result(const std::string & json);
		static bool testJSON(const std::string & buffer);
		static std::string cat(const std::string& delim, std::size_t pos, const std::string& str);
	private:
		Utility();
		Utility(const Utility&);
		Utility& operator = (const Utility&);
	};
}
