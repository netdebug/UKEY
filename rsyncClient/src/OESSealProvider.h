#pragma once
#include <string>
#include "SealProvider.h"
#include "Poco/SharedLibrary.h"
#include "Poco/Util/Application.h"
#include "BridgeKG_HARD_EXT.h"

namespace Reach {
	class OESSealProvider
		: public SealProvider
	{
	public:
		OESSealProvider();
		~OESSealProvider();
		virtual void extract(const std::string& cert);
	protected:
		bool hasStamps();
		void readSeal();
		//void GetDeviceInfo(void* hDev);
		void ExtractSealPicture();
	private:
		int count();
		void handleLastError(int code);
	private:
		BridgeKG_HARD_EXT ext;
		Poco::SharedLibrary sl;
		std::string _certContent;
		std::string _sealdata;
		std::string _areacode;
	};
}