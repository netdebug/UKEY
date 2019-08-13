#pragma once
#include <string>

namespace Reach {

	class Certificate
	{
	public:
		Certificate(const std::string& name);
		~Certificate();

		std::string Certificate::name() const;
	private:
		std::string _name;
	};

	inline std::string Certificate::name() const
	{
		return _name;
	}
}