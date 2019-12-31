#pragma once
#include <string>
#include "SealProvider.h"
#include "Poco/SharedLibrary.h"
#include "Poco/Util/Application.h"

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
		void ExtractSealPicture();
	private:
		Poco::SharedLibrary sl;

		int _count;
		bool _bPresent;
		std::string _sealdata;
	};
}