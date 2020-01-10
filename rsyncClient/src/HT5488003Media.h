#pragma once
#include "MediaBase.h"
#include <string>
#include "Poco/SharedLibrary.h"

namespace Reach {

	class HT5488003Media
		: public MediaBase
	{
	public:
		HT5488003Media();
		~HT5488003Media();
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