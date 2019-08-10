#pragma once

#include <string>

namespace Reach {

	class Utility
	{
	public:
		static std::string config(const std::string& name);
	private:
		Utility();
		Utility(const Utility&);
		Utility& operator = (const Utility&);
	};
}
