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
		void FetchKeySN();
		void GetContainerId();
		void TCardGetCert();
		void handleLastError(const std::string & result);
		void ExtractSealPicture();
	private:
		Poco::Util::Application& app;
		Poco::SharedLibrary sl;

		int _count;
		bool _bPresent;
		std::string _content;
		std::string _id;
		std::string _sealdata;

		const std::string _type = "2";
	};
}