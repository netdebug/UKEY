#pragma once
#include "FJCAMedia.h"
#include <string>
#include "Poco/SharedLibrary.h"

namespace Reach {

	///
	/// HID\VID_5448&PID_0003&REV_0310
	///
	class HT5488003Media
		: public FJCAMedia
	{
	public:
		HT5488003Media();
		~HT5488003Media();
		void open();
		void close();

	protected:
		bool hasRSACert();
		bool hasECCCert();
		std::string readRSACert();
		std::string readECCCert();

	private:
		Poco::SharedLibrary sl;
		typedef void* HANDLE;
		HANDLE _hDev;
	};
}