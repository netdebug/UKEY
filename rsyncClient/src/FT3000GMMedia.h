#pragma once
#include "MediaBase.h"
#include <string>
#include "Poco/SharedLibrary.h"

namespace Reach {

	class FT3000GMMedia
		: public MediaBase
	{
	public:
		FT3000GMMedia();
		~FT3000GMMedia();
		void open();
		void close();
		bool hasCert(const std::string & type);
		virtual void extract();

	protected:
		virtual void GetCertBase64String();
		
		bool hasRSACert();
		bool hasECCCert();
		std::string readRSACert();
		std::string readECCCert();
		virtual void FetchKeySN();
		
	private:
		Poco::SharedLibrary sl;
		typedef void* HANDLE;
		HANDLE _hDev;
	};
}