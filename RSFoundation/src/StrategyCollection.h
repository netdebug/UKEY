#pragma once

#include "UDevice.h"

namespace Reach {

	using Reach::UDevice;

	class EncryptStrategy
	{
	public:
		EncryptStrategy(UDevice& ud);
		void doUpdate();
	};

	class SignedStrategy
	{
	public:
		SignedStrategy(UDevice& ud);
		void doUpdate();
	};
}