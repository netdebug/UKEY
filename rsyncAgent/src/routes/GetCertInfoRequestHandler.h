#pragma once

#include "Command.h"
#include "RESTfulRequestHandler.h"
#include "Poco/Util/Application.h"
#include "Poco/Dynamic/Var.h"
#include "Poco/Crypto/X509Certificate.h"
#include "Poco/SharedPtr.h"

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
	protected:
		void load();
		void parse();
	private:
		void keysn();
		void enterprise();
		void personal();
		void decode_utf8(const std::string & text);
		void extract(const std::string & text);
		void extract(const std::string & text, const std::string & tag);
		void x509_validFrom_expiresOn();
		std::string cat(const std::string & delim, std::size_t pos, const std::string & str);
		std::string GetCertOwnerID(const std::string & base64);
		std::string toLegelID(const std::string & text, const std::string & pattern);
	private:
		std::string _item;
		std::string _cer;
		int _type;
		Poco::SharedPtr<Poco::Crypto::X509Certificate> x509ptr;
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