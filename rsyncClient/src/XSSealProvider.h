#pragma once
#include <string>
#include "SealProvider.h"
#include "Poco/SharedLibrary.h"

namespace Reach {
	class XSSealProvider 
		: public SealProvider
	{
	public:
		XSSealProvider();
		~XSSealProvider();
		virtual void read(Object::Ptr JSONin, Object::Ptr JSONout);
		virtual void setProperty(const std::string& name, const std::string& value);
		virtual std::string getProperty(const std::string& name) const;
	protected:
		void readSeal();
		void count();
		void testKeyIn();
	private:
		Poco::SharedLibrary sl;

		std::string _name;
		std::string _code;
		std::string _validStart;
		std::string _validEnd;

		int _count;
		bool _bPresent;
		std::string _content;
	};
}