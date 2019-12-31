#pragma once
#include <string>
#include "SealProvider.h"
#include "Poco/SharedLibrary.h"
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
		virtual void GetCertBase64String();
		virtual void FetchKeySN();

		void handleLastError(int code);
		void GetDeviceInfo(void* hDev);
		void ExtractSealPicture();
	private:
	
		Poco::SharedLibrary sl;
		int _count;
		std::string _certContent;
		std::string _sealdata;
	};
}