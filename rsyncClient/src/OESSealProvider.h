#pragma once
#include <string>
#include "Poco/Configurable.h"
#include "SealProvider.h"
#include "Poco/SharedLibrary.h"

namespace Reach {
	using Poco::JSON::Object;
	class OESSealProvider
		: public SealProvider
	{
	public:
		OESSealProvider();
		~OESSealProvider();

		virtual void read(Object::Ptr JSONin, Object::Ptr JSONout);
		virtual void setProperty(const std::string& name, const std::string& value);
		virtual std::string getProperty(const std::string& name) const;
	protected:
		void readSeal();
		void count();
		void getCerContent();
	private:
		std::string _x509cer;

		std::string _name;
		std::string _code;
		std::string _validStart;
		std::string _validEnd;

		Poco::SharedLibrary sl;
		Poco::SharedLibrary sl2;

		int _count;
		std::string _content;
	};
}