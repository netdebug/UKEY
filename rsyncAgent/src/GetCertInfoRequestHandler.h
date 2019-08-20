#pragma once

#include "UDevice.h"
#include "SoFProvider.h"
#include "SOFErrorCode.h"
#include "Command.h"
#include "GMCrypto.h"
#include "RESTfulRequestHandler.h"
#include "RequestHandleException.h"
#include "Poco/Util/Application.h"

#include "Poco/RegularExpression.h"
#include "Poco/Timezone.h"
#include "Poco/Debugger.h"
#include "Poco/String.h"
#include "Poco/NumberParser.h"
#include "Reach/Data/Session.h"
using Poco::NumberParser;

namespace Reach {

	using Poco::Util::Application;
	using Poco::RegularExpression;
	using Poco::Timezone;
	using Poco::DateTime;
	using Poco::DateTimeFormat;
	using Poco::DateTimeParser;
	using Poco::DateTimeFormatter;
	using Poco::LocalDateTime;
	using Poco::Debugger;
	using Poco::format;
	///RS_GetCertInfo
	class GetCertInfo : public Command
	{
	public:
		GetCertInfo(const std::string& base64, int type)
			:_base64(base64), _type(type)
		{}

		void run()
		{
			Reach::Data::Session session("SOF", "REST");

			_item = session.getCertInfo(_base64, _type);

			add("info", _item);
		}
		///base64 \/×ªÒå×Ö·û
	private:
		std::string _item;
		std::string _base64;
		int _type;
	};

	class GetCertInfoRequestHandler : public RESTfulRequestHandler
	{
	public:
		void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
		{
			poco_information_f1(Application::instance().logger(), "Request from %s", request.clientAddress().toString());

			RESTfulRequestHandler::handleCORS(request, response);

			HTMLForm form(request, request.stream());
			std::string base64(form.get("certBase64", ""));
			Var type(form.get("type", ""));

			GetCertInfo command(base64, type);
			command.execute();

			return response.sendBuffer(command().data(), command().length());
		}
	};
}