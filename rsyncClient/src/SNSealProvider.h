#pragma once
#include "SealProvider.h"
#include "Poco/SharedLibrary.h"

namespace Reach {
	class SNSealProvider :
		public SealProvider
	{
	public:
		SNSealProvider();
		~SNSealProvider();
		virtual void extract(const std::string& cert);

	protected:
		void readSeal();
		bool hasStamps();
		int count();
		bool hasKey();
		void ExtractSealPicture();

	private:
		std::string _certContent;
		std::string _sealdata;
		std::string _areacode;

		Poco::SharedLibrary sl;

		int _count;
		bool _bPresent;
	};
}