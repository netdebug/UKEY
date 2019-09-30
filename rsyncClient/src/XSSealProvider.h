#pragma once
#include <string>

namespace Reach {
	class XSSealProvider
	{
	public:
		XSSealProvider();
		std::string read();

	private:
		typedef char* (*ReadSealData)(int nIndex);
		static const int all_seal = -1;
		ReadSealData fnPtr;
		std::string _content;
	};
}