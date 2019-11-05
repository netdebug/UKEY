#pragma once
#include <string>
#include "Poco/Configurable.h"
#include "SealProvider.h"
#include "Poco/SharedLibrary.h"
#include "Poco/Dynamic/Var.h"

namespace Reach {
	using Poco::Dynamic::Var;
	using Poco::JSON::Array;
	class OESSealProvider
		: public SealProvider
	{
	public:
		OESSealProvider();
		~OESSealProvider();

		virtual void read(Object::Ptr JSONin, Object::Ptr JSONout);
		Var read();
		void set_seal_data();
		virtual void setProperty(const std::string& name, const std::string& value);
		virtual std::string getProperty(const std::string& name) const;
	protected:
		void readSeal();
		void count();
		void TCardGetCert();
		void set_vaild_date();
		void setName();
	private:
	
		std::string _x509cer;

		Poco::SharedLibrary sl;
		Poco::SharedLibrary sl2;

		int _count;
		std::string _content;
		std::string _certContent;
		std::string _name;
		std::string _code;
		std::string _validStart;													
		std::string _validEnd;
		Array::Ptr _sealdata;
		Var result;
	};
}