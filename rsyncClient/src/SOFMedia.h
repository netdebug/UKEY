#pragma once

#include "MediaBase.h"

namespace Reach {

	class SOFMedia
		: public MediaBase
	{
	public:
		SOFMedia();
		~SOFMedia();
		virtual void extract();
	};
}