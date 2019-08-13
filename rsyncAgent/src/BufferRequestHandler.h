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
#include "Poco/Logger.h"
#include "Poco/Util/Application.h"
#include "RESTfulRequestHandler.h"


namespace Reach {

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
	using Poco::Util::Application;
	using Poco::Data::SessionFactory;
	using Poco::format;
	using namespace Poco::Data::Keywords;

	class BufferRequestHandler : public RESTfulRequestHandler
	{
		typedef Poco::Tuple <std::string, std::string, std::string> DeviceInfo;
		typedef std::vector<DeviceInfo> DeviceInfoSet;
		typedef DeviceInfoSet::const_iterator Iter;

	public:
		void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
		{
			poco_information_f1(Application::instance().logger(), "Request from %s", request.clientAddress().toString());

			RESTfulRequestHandler::handleCORS(request, response);

			Poco::Data::SQLite::Connector::registerConnector();
#ifdef _DEBUG
			Session session("SQLite", "C:\\Windows\\SysWOW64\\DeQLite.db");
#else
			Session session("SQLite", "DeQLite.db");
#endif // _DEBUG
			
			DeviceInfoSet devices;
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