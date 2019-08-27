#pragma once

#include "UDevice.h"
#include "SoFProvider.h"
#include "SOFErrorCode.h"
#include "Command.h"
#include "RESTfulRequestHandler.h"
#include "RequestHandleException.h"
#include "Poco/Util/Application.h"
#include "Poco/Dynamic/Var.h"
#include "Reach/Data/Session.h"

namespace Reach {

	using Poco::Util::Application;
	using Poco::Dynamic::Var;

	///RS_GetCertBase64String
	class GetCertBase64String : public Command
	{
	public:
		GetCertBase64String(short ctype, const std::string& uid)
			:_type(ctype), _uid(uid)
		{}

		void run()
		{
			//Reach::Data::Session session("SOF", "REST");
			Reach::Data::Session session(getEngine(), "REST");

			if (_uid != session.contianer())
				throw RequestHandleException(RAR_UNIQUEIDUNCORRECT);

			_content = session.getCertBase64String(_type);

			add("certBase64", _content);
		}
	protected:


	private:
		std::string _content;
		short _type;
		std::string _uid;
	};


	class GetCertBase64StringRequestHandler : public RESTfulRequestHandler
	{
	public:
		void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
		{
			poco_information_f1(Application::instance().logger(), "Request from %s", request.clientAddress().toString());

			RESTfulRequestHandler::handleCORS(request, response);

			HTMLForm form(request, request.stream());
			Var type(form.get("certType", ""));
			std::string uid(form.get("containerId", ""));

			GetCertBase64String command(type, uid);
			command.execute();

			return response.sendBuffer(command().data(), command().length());
		}
	};
}