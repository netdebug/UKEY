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
		virtual void extract() = 0;
		virtual void setProperty(const std::string& name, const std::string& value);
		virtual std::string getProperty(const std::string& name) const;
		virtual void GeneratedMD5();
		virtual void GeneratedCode();
		virtual void PeriodOfValidity();
	private:
		std::string _name;
		std::string _code;
		std::string _validStart;
		std::string _validEnd;
		std::string _keysn;
		std::string _seals;
		std::string _md5;
		std::string _cert;
	};
}