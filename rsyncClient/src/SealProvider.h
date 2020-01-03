#pragma once
#include <string>
#include "Poco/Configurable.h"
#include "Poco/RefCountedObject.h"

namespace Reach {

	class SealProvider 
		: public Poco::Configurable, public Poco::RefCountedObject
	{
	public:
		SealProvider();
		virtual ~SealProvider();
		virtual void extract(const std::string& cert) = 0;
		void setProperty(const std::string& name, const std::string& value);
		std::string getProperty(const std::string& name) const;
	protected:
		virtual void handleLastError(const std::string& result);
	private:
		std::string _name;
		std::string _keysn;
		std::string _seals;
		std::string _uid;
		std::string _Provider;
		const std::string _encType = "2";
	};
}