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
		void readSeal();
		void count();
		void testKeyIn();
		void ExtractSealPicture();
	private:

		int _count;
		bool _bPresent;
		std::string _sealdata;
	};
}