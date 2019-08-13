#pragma once

#include <string>

namespace Reach {

	class Container
	{
	public:
		Container(const std::string& name);
		~Container();

		std::string name() const;
	private:
		std::string _name;
	};

	inline std::string Container::name() const
	{
		return _name;
	}
}