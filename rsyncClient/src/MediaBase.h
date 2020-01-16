#pragma once
#include <string>
#include "Poco/Configurable.h"
#include "Poco/RefCountedObject.h"

namespace Reach {

	class MediaBase
		: Poco::Configurable, public Poco::RefCountedObject
	{
	public:
		MediaBase();
		virtual ~MediaBase();
		virtual void open() = 0;
		virtual void extract() = 0;
		virtual void close() = 0;

		void setProperty(const std::string& name, const std::string& value);
		std::string getProperty(const std::string& name) const;
	protected:
		virtual void CertValidity();
	private:
		std::string _keysn;
		std::string _cert;
		std::string _validStart;
		std::string _validEnd;

		std::string _Provider;
	};
}
