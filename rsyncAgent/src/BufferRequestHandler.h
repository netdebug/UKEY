#pragma once

#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Logger.h"
#include "Poco/Util/Application.h"
#include "RESTfulRequestHandler.h"

namespace Reach {

	using Poco::Util::Application;

	class BufferRequestHandler : public RESTfulRequestHandler
	{
	public:
		void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
		{
			poco_information_f1(Application::instance().logger(), "Request from %s", request.clientAddress().toString());

			RESTfulRequestHandler::handleCORS(request, response);

			/*
			Poco::Data::SQLite::Connector::registerConnector();
			Reach::Data::SOF::Connector::registerConnector();
			Reach::Data::FJCA::Connector::registerConnector();

			Reach::Data::Session tty("SOF", "REST");
			poco_information_f3(Application::instance().logger(), "connector: %s, uri: %s, contianer:%s", tty.connector(), tty.uri(), tty.contianer());

			
			Reach::Data::Session tty1("FJCA", "REST");
			poco_information_f3(Application::instance().logger(), "connector: %s, uri: %s, contianer:%s" , tty1.connector(), tty1.uri(), tty1.contianer());
		

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
			*/

			std::string data("buffer request is deprecate!");
			response.sendBuffer(data.data(), data.length());
		}
	};
}