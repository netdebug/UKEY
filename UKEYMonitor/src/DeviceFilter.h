#pragma once

#include <string>
#include "Poco/Dynamic/Var.h"

namespace Reach {

	using Poco::Dynamic::Var;

	class DeviceFilter
	{
	public:
		DeviceFilter(const std::string& enumerate_id, bool removed);
		~DeviceFilter();

	protected:
		void loadConfigure();
		void enqueue();
		bool isLegelDevice(const std::string& deivice_id);

	private:
		void dbgview(const std::string & message);

		std::string _enumerate;
		bool _removed;
		Poco::Dynamic::Array _data;
	};
}