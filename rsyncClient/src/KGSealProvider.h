#pragma once
#include <string>
#include "SealProvider.h"
#include "Poco/Util/Application.h"

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

	private:
		Poco::Util::Application& app;

		static const int all_seal = -1;
		std::string _content;
		std::string _id;
		std::string _sealdata;

		const std::string _type = "2";
	};
}