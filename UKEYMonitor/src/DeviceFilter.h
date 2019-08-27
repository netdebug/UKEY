#pragma once

#include <string>
#include "Poco/Dynamic/Var.h"
#include "Poco/Tuple.h"

namespace Reach {

	using Poco::Dynamic::Var;

	class DeviceFilter
	{
	public:
		DeviceFilter(const std::string& enumerate_id, bool removed);
		~DeviceFilter();
		std::string current();

	protected:
		void loadConfigure();
		void enqueue();
		bool isLegelDevice(const std::string& deivice_id);

	private:
		typedef Poco::Tuple<std::string, std::string, std::string, std::string, std::string, std::string> DeviceInfoType;
		enum
		{
			description,
			enumerator,
			hardware_id,
			instance_id,
			class_guid,
			engine_mode
		};

		void updateDeviceStatus(const DeviceInfoType & info, bool present);
		void resetRESTfulService();
		void dbgview(const std::string & message);

		std::string _description;
		std::string _enumerate;
		std::string _engine;
		bool _presented;
		Poco::Dynamic::Array _data;
		void SQLitePath();
	};
}