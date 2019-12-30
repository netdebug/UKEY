#pragma once
#include <string>
#include "SealProvider.h"
#include "Poco/Util/Application.h"

class CDKG_GetKeyInfo_FJRS;

namespace Reach {

	class KGSealProvider
		: public SealProvider
	{
	public:
		KGSealProvider();
		virtual ~KGSealProvider();
		virtual void extract();
	protected:
		void readSeal();
		void FetchKeySN();
		void GetContainerId();
		void TCardGetCert();
		void ExtractSealPicture();
		void handleLastError(const std::string & result);
	private:
		CDKG_GetKeyInfo_FJRS*  _pKG_GetKeyInfo_FJRS;
	private:
		Poco::Util::Application& app;

		static const int all_seal = -1;
		std::string _content;
		std::string _id;
		std::string _sealdata;

		const std::string _type = "2";
	};
}