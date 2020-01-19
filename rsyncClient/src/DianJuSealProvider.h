#pragma once
#include "SealProvider.h"
#include "Poco/SharedLibrary.h"

namespace Reach {
	class DianJuSealProvider : 
		public SealProvider
	{
	public:
		DianJuSealProvider();
		~DianJuSealProvider();
		virtual void extract(const std::string& cert);

	protected:
		void readSeal();
		bool hasStamps();
		void ExtractSealPicture();
	private:
		int count();
		bool hasKey();
	private:
		std::string _certContent;
		std::string _sealdata;
		std::string _areacode;
		Poco::SharedLibrary sl;
	};
}

