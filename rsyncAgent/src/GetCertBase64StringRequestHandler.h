#pragma once

#include "UDevice.h"
#include "SoFProvider.h"
#include "SOFErrorCode.h"
#include "Command.h"
#include "RESTfulRequestHandler.h"
#include "RequestHandleException.h"
#include "Poco/Util/Application.h"
#include "Poco/Dynamic/Var.h"

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
			UDevice::default();

			enum certType { sign = 1, crypto };

			std::string _content;

			switch (_type){

				case certType::sign:
					_content = SOF_ExportUserCert(_uid);
					break;
				case certType::crypto:
					_content = SOF_ExportExChangeUserCert(_uid);
					break;
				default:
					throw RequestHandleException(RAR_ERRORCERTTYPE);
			}

			if (_content.empty())
				throw RequestHandleException(RAR_NOBASE64CERT);

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