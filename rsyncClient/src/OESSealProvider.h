#pragma once
#include <string>
#include "Poco/Configurable.h"
#include "SealProvider.h"
#include "Poco/SharedLibrary.h"
#include "Poco/Dynamic/Var.h"
#include "Poco/Util/Application.h"

namespace Reach {
	class OESSealProvider
		: public SealProvider
	{
	public:
		OESSealProvider();
		~OESSealProvider();
		virtual void extract();
	protected:
		void readSeal();
		void count();
		void TCardGetCert();
		void PeriodOfValidity();
		void FetchKeySN();
		void ExtractSealPicture();
		std::string GBKtoUTF8(const std::string& text);
	private:
	
		Poco::Util::Application& app;
		Poco::SharedLibrary sl;
		int _count;
		std::string _content;
		std::string _certContent;
		std::string _sealdata;
	};
}