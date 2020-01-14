#pragma once
#include "SealProvider.h"
#include "Poco/SharedLibrary.h"



namespace Reach {
	class SKFSealProvider : 
		public SealProvider
	{
	public:
		SKFSealProvider();
		~SKFSealProvider();
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
		Poco::SharedLibrary sl;
	};
}

