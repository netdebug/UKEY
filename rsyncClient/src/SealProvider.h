#pragma once
#include <string>
#include "Poco/Configurable.h"
#include "Poco/RefCountedObject.h"
#include "Poco/JSON/Object.h"

namespace Reach {
	using Poco::JSON::Object;
	class SealProvider 
		: public Poco::Configurable, public Poco::RefCountedObject
	{
	public:
		SealProvider();
		virtual ~SealProvider();

		virtual void read(Object::Ptr JSONin, Object::Ptr JSONout) = 0;

		virtual void setProperty(const std::string& name, const std::string& value);

		virtual std::string getProperty(const std::string& name) const;
	};
}