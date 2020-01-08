#pragma once
#include "MediaBase.h"
#include "BridgeKG_HARD_EXT.h"

namespace Reach {
	
	class FJCAMedia
		: public MediaBase
		/// Haitai UKEY Device
	{
	public:
		FJCAMedia();
		~FJCAMedia();
		virtual void extract();

	protected:
		virtual void GetCertBase64String();
		virtual void FetchKeySN();
		virtual void handleLastError(int code);
	private:
		BridgeKG_HARD_EXT ext;
	};
}