#pragma once
#include "MediaBase.h"
#include "BridgeKG_HARD_EXT.h"

namespace Reach {
	
	class FJCAMedia
		: public MediaBase
	{
	public:
		FJCAMedia();
		virtual ~FJCAMedia();

		virtual void extract();
		bool hasCert(const std::string & type);
		void GetCertBase64String();
		void fetchKeySN();
	protected:
		virtual bool hasRSACert() = 0;
		virtual bool hasECCCert() = 0;
		virtual std::string readRSACert() = 0;
		virtual std::string readECCCert() = 0;

		virtual void handleLastError(int code);
	};
}