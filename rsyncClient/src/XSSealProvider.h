#pragma once
#include <string>
#include "SealProvider.h"
#include "Poco/SharedLibrary.h"

namespace Reach {
	class XSSealProvider 
		: public SealProvider
	{
	public:
		XSSealProvider();
		~XSSealProvider();
		virtual void extract(const std::string& cert);
	protected:
		void readSeal();
		bool hasStamps();
		int count();
		bool hasKey();
		void ExtractSealPicture();
	private:
		Poco::SharedLibrary sl;
		std::string _sealdata;
		std::string _areacode;
	};
}