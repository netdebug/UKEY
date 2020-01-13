#pragma once
#include "FJCAMedia.h"
#include <string>
#include "Poco/SharedLibrary.h"

namespace Reach {

	///
	/// USB\VID_096E&PID_0309&REV_0100
	/// USB\VID_096E&PID_0309&REV_3200
	///

	class FT3000GMMedia
		: public FJCAMedia
	{
	public:
		FT3000GMMedia();
		~FT3000GMMedia();
		void open();
		void close();

	protected:
		virtual bool hasRSACert();
		virtual bool hasECCCert();
		virtual std::string readRSACert();
		virtual std::string readECCCert();

	private:
		Poco::SharedLibrary sl;
		typedef void* HANDLE;
		HANDLE _hDev;
	};
}