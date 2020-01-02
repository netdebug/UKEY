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
		void readSeal();
		void count();
		void handleLastError(int code);
		void GetDeviceInfo(void* hDev);
		void ExtractSealPicture();
	private:
		BridgeKG_HARD_EXT ext;
		Poco::SharedLibrary sl;
		int _count;
		std::string _certContent;
		std::string _sealdata;
	};
}