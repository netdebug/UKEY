#pragma once
#include <string>
#include "SealProvider.h"

namespace Reach {
	class BCBSSealProvider
		: public SealProvider
	{
	public:
		BCBSSealProvider();
		~BCBSSealProvider();
		virtual void extract(const std::string& cert);
	protected:
		bool hasStamps();
		void readSeal();
		void ExtractSealPicture();
	private:
		std::string _sealdata;
		std::string _areacode;
	};
}