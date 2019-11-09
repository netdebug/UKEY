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
		virtual void extract();
	protected:
		void readSeal();
		void count();
		void testKeyIn();
		void FetchKeySN();
		void TCardGetCert();
		void PeriodOfValidity();
		void ExtractSealPicture();
	private:
		Poco::SharedLibrary sl;

		std::string _name;
		std::string _code;
		std::string _validStart;
		std::string _validEnd;

		int _count;
		bool _bPresent;
		std::string _content;
	};
}