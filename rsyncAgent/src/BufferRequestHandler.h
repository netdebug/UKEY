#pragma once

#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/JSON/Object.h"
#include "Poco/JSON/Query.h"
#include "Poco/Dynamic/Var.h"
#include "Poco/NumberFormatter.h"
#include "Poco/DynamicStruct.h"
#include "Poco/Data/SessionFactory.h"
#include "Poco/Data/Session.h"
#include "Poco/Data/RecordSet.h"
#include "Poco/Data/Column.h"
#include "Poco/Data/SQLite/Connector.h"
#include "Poco/Debugger.h"

namespace Reach {

	using Poco::Net::HTTPRequestHandler;
	using Poco::Net::HTTPServerRequest;
	using Poco::Net::HTTPServerResponse;
	using Poco::JSONOptions;
	using Poco::JSON::Object;
	using Poco::JSON::Query;
	using Poco::JSON::Array;
	using Poco::Dynamic::Var;
	using Poco::NumberFormatter;
	using Poco::DynamicStruct;
	using Poco::Data::Session;
	using Poco::Data::Statement;
	using Poco::Data::RecordSet;
	using Poco::Data::Column;
	using Poco::Data::Row;
	using Poco::Debugger;
	using Poco::format;
	using namespace Poco::Data::Keywords;

	class BufferRequestHandler : public HTTPRequestHandler
	{
	public:
		void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
		{
			Poco::Data::SQLite::Connector::registerConnector();
#ifdef _DEBUG
			Session session("SQLite", "C:\\Windows\\SysWOW64\\DeQLite.db");
#else
			Session session("SQLite", "DeQLite.db");
#endif // _DEBUG
			typedef Poco::Tuple <std::string, std::string, std::string> DeviceInfo;
			typedef std::vector<DeviceInfo> DeviceInfoSet;
			typedef DeviceInfoSet::const_iterator Iter;
			DeviceInfoSet devices;
			/// Sqlite table : "CREATE TABLE DeviceSet (Description VARCHAR(30), ENUMERATOR VARCHAR(32), HardwareID VARCHAR(200), InstanceID VARCHAR(32), ClassGUID VARCHAR(39))"
			//RecordSet rset(session, "SELECT Description, HardwareID, InstanceID FROM DeviceSet WHERE PRESENT = 1");
			session << "SELECT Description, HardwareID, InstanceID FROM DeviceSet WHERE PRESENT = 1", into(devices), now;

			std::string data;
			std::ostringstream out;
			Array A(JSONOptions::JSON_PRESERVE_KEY_ORDER);
			for (Iter it = devices.begin(); it != devices.end(); it++) {
				Object O(JSONOptions::JSON_PRESERVE_KEY_ORDER);
				O.set("Description", it->get<0>());
				O.set("HardwareID", it->get<1>());
				O.set("InstanceID", it->get<2>());
				A.add(O);
			}
	
			A.stringify(out);
			data = out.str();

			dbgview(format("DeviceSet tags %s\n", data));

			response.set("Access-Control-Allow-Origin", "*");
			response.set("Access-Control-Allow-Methods", "GET, POST, HEAD");
			response.sendBuffer(data.data(), data.length());
		}
		void dbgview(const std::string& message)
		{
#ifndef _DEBUG
			::OutputDebugStringA(message.c_str());
#endif // !_NDEBUG
			Debugger::message(message);
		}
	};
}