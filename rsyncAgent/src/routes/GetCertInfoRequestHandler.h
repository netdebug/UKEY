#pragma once

#include "Command.h"
#include "RESTfulRequestHandler.h"
#include "Poco/Util/Application.h"
#include "Poco/Dynamic/Var.h"

using Poco::Util::Application;
using Poco::Dynamic::Var;

namespace Reach {

	///RS_GetCertInfo
	class GetCertInfo : public Command
	{
	public:
		GetCertInfo(const std::string& base64, int type);
		virtual void run();
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