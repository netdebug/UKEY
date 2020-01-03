#pragma once

#include "Poco/Util/Application.h"
#include "Poco/Random.h"
#include "Poco/DateTimeFormatter.h"
#include "Poco/LocalDateTime.h"
#include "../Command.h"
#include "../RESTfulRequestHandler.h"


namespace Reach {

	using Poco::Util::Application;
	using Poco::Random;
	using Poco::LocalDateTime;
	using Poco::DateTimeFormatter;
	///RS_ConfigParameters
	class GetTransid : public Command
	{
	public:
		GetTransid(const std::string& joinCode)
			:_joinCode(joinCode)
		{
		}

		void run()
		{
			_transid.append(_joinCode);
			_transid.append(Utility::UniqueTransOrder());

			add("transid", _transid);
		}
	private:
		std::string _joinCode;
		std::string _transid;
	};

	class GetTransidRequestHandler : public RESTfulRequestHandler
	{
	public:
		void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
		{
			poco_information_f1(Application::instance().logger(), "Request from %s", request.clientAddress().toString());
			RESTfulRequestHandler::handleCORS(request, response);

			HTMLForm form(request, request.stream());
			std::string joinCode = form.get("joinCode", "");
			GetTransid command(joinCode);
			command.execute();

			return response.sendBuffer(command().data(), command().length());
		}
	};
}