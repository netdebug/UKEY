#pragma once

#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Logger.h"
#include "Poco/Util/Application.h"
#include "routes/RESTfulRequestHandler.h"
#include "Poco/JSON/Object.h"
#include "Poco/Data/Session.h"
#include "Poco/Data/SQLite/Connector.h"

using namespace Poco::Data::Keywords;

namespace Reach {

	using Poco::Util::Application;

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

			//Poco::Data::SQLite::Connector::registerConnector();
#ifdef _DEBUG
			Poco::Data::Session session("SQLite", "C:\\Windows\\SysWOW64\\DeQLite.db");
#else
			Poco::Data::Session session("SQLite", "DeQLite.db");
#endif // _DEBUG

			DeviceInfoSet devices;
			session << "SELECT Description, HardwareID, InstanceID FROM DeviceSet WHERE PRESENT = 1", into(devices), now;

			std::string data;
			std::ostringstream out;
			Poco::JSON::Array A(Poco::JSONOptions::JSON_PRESERVE_KEY_ORDER);
			for (Iter it = devices.begin(); it != devices.end(); it++) {
				Poco::JSON::Object O(Poco::JSONOptions::JSON_PRESERVE_KEY_ORDER);
				O.set("Description", it->get<0>());
				O.set("HardwareID", it->get<1>());
				O.set("InstanceID", it->get<2>());
				A.add(O);
			}

			A.stringify(out);
			data = out.str();

			response.sendBuffer(data.data(), data.length());

			/*std::string data("buffer request is deprecate!");
			response.sendBuffer(data.data(), data.length());*/
		}
	};
}