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
		void setProperty(const std::string& name, const std::string& value);
		std::string getProperty(const std::string& name) const;
		void GeneratedMD5();
		void GeneratedCode();
		virtual void FetchKeySN();
	protected:
		virtual void PeriodOfValidity();
		virtual void GetContainerId();
		virtual void handleLastError(const std::string& result);
		virtual void GetCertBase64String();
	private:
		std::string _name;
		std::string _code;
		std::string _validStart;
		std::string _validEnd;
		std::string _keysn;
		std::string _seals;
		std::string _md5;
		std::string _cert;
		std::string _uid;
		std::string _Provider;
		const std::string _encType = "2";
	};
}