#pragma once
#include "MediaBase.h"

namespace Reach {

	class FT3000GMMedia
		: public MediaBase
	{
	public:
		FT3000GMMedia();
		~FT3000GMMedia();

		virtual void extract();

	protected:
		virtual void GetCertBase64String();
		virtual void FetchKeySN();
	};
}