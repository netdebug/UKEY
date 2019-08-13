#pragma once
#include "Poco/SharedPtr.h"
#include <string>

namespace Reach {

	class Container;
	class Certificate;
	class UKeyDevice
	{
	public:
		UKeyDevice(const std::string entries);
		~UKeyDevice();

		std::string containerName() const;
		std::string certificateName() const;
	protected:
		void extract();
	private:
		Poco::SharedPtr<Reach::Container> _container;
		Poco::SharedPtr<Reach::Certificate> _certificate;
		std::string _entries;
	};
}
