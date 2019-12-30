#pragma once
#include "Poco/Task.h"
#include "Poco/JSON/Object.h"
#include <string>
#include <cassert>
namespace Reach {
	class QZSyncWorker
		: public Poco::Task
	{
	public:
		QZSyncWorker();
		virtual void runTask();
	private:
		bool IsUSBKeyPresent();
		void composite();
		void updateStatus();
		void transfer();

		void setSync(std::string& keysn, bool flag = true);

		void log(const std::string& message);

		template<typename T>
		const T extract(std::istream& json)
		{
			Poco::JSON::Parser p;
			Poco::Dynamic::Var result = p.parse(json);
			assert(result.type() == typeid(T));
			return result.extract<T>();
		}
	private:
		Poco::JSON::Object::Ptr object;
		std::string _name;
		std::string _code;
		std::string _validStart;
		std::string _validEnd;
		std::string _keysn;
		std::string _md5;
		std::string _seals;
	};
}