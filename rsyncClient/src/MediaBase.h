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
		virtual void extract() = 0;

		void setProperty(const std::string& name, const std::string& value);
		std::string getProperty(const std::string& name) const;
	protected:
		virtual void GetCertBase64String();
		virtual void CertValidity();
		virtual void FetchKeySN();
		virtual void handleLastError(const std::string& result);
	private:
		void GetContainerId();
	private:
		std::string _keysn;
		std::string _cert;
		std::string _validStart;
		std::string _validEnd;

		std::string _uid;
		std::string _Provider;
		const std::string _signType = "1";
	};
}
