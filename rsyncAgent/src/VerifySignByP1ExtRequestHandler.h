#pragma once

#include "UDevice.h"
#include "SoFProvider.h"
#include "SOFErrorCode.h"
#include "Command.h"
#include "RESTfulRequestHandler.h"
#include "RequestHandleException.h"
#include "Poco/Util/Application.h"
#include "Poco/String.h"
#include "Poco/Crypto/X509Certificate.h"
#include "Poco/Net/HTTPClientSession.h"
#include "Utility.h"
#include <string>
#include <cassert>

namespace Reach {

	using Poco::format;
	using Poco::Util::Application;
	using Poco::Crypto::X509Certificate;
	using Poco::Net::HTTPResponse;
	using Poco::Net::HTTPRequest;
	using Poco::Net::HTTPClientSession;
	using Poco::StreamCopier;

	///RS_VerifySignByP1Ext
	class VerifySignByP1Ext : public Command
	{
	public:
		VerifySignByP1Ext(const std::string& base64, const std::string& msg, const std::string& signature)
			:_cert(base64), _msg(msg), _signature(signature)
		{
			generator();
		}

		void run()
		{
			poco_information(Application::instance().logger(), "VerifySignByP1Ext");

			HTTPResponse response;
			HTTPRequest request(HTTPRequest::HTTP_POST, "/Fjreach/Fjreach.json");
			request.setContentLength((int)_buffer.length());

			HTTPClientSession session("114.115.172.176", 8080);
			session.sendRequest(request) << (_buffer);

			std::istream& receive = session.receiveResponse(response);
			std::ostringstream ostr;
			StreamCopier::copyStream(receive, ostr);

			_verify = Utility::result(ostr.str());

			if (!_verify) {
				throw RequestHandleException("VerifySignByP1Ext failed!", RAR_UNKNOWNERR);
			}
		}
	protected:
		void generator()
		{
			/// Note: TIMESTAMP is NOT Equual to TRANSID's
			std::string fmt(
				"{\n"
				"	\"BIZCODE\" : \"BIZ.RAWVERIFYCERT\",\n"
				"	\"DATA\" : {\n"
				"					\"msg\" : \"%s\",\n"
				"					\"signedData\" : \"%s\",\n"
				"					\"cert\" : \"%s\",\n"
				"					\"iAlgorithm\" : \"%s\"\n"
				"			},\n"
				"	\"SYSID\" : \"b253fca87f6711e995aa005056a72395\",\n"
				"		\"TIMESTAMP\" : \"%s\",\n"
				"		\"TRANSID\" : \"%s\",\n"
				"		\"UNIT\" : \"RSYZ\"\n"
				"}");

			
			decideAlgorithm(_cert);

			poco_information_f1(Application::instance().logger(), "VerifySignByP1Ext signatureAlgorithm: %s", _algorithm);
			format(_buffer, fmt, _msg, _signature, _cert, _algorithm,Utility::timestamp(), Utility::UniqueTransOrder());

			assert(Utility::testJSON(_buffer));
			poco_information_f1(Application::instance().logger(), "VerifySignByP1Ext JSON: %s", _buffer);
		}
	protected:
		void decideAlgorithm(const std::string& cert)
		{
			//1 RSA 2 SM2
			std::string PEM;
			PEM.append("-----BEGIN CERTIFICATE-----\n");
			PEM.append(Utility::cat("\n", 64, cert));
			PEM.append("-----END CERTIFICATE-----\n");
			std::istringstream certStream(PEM);
			X509Certificate x509(certStream);
			std::string algorithm = x509.signatureAlgorithm();
			if (algorithm.find("sm2") != std::string::npos)
				_algorithm = "2";
			else
				_algorithm = "1";
		}
	private:

		bool _verify;
		std::string _cert;
		std::string _msg;
		std::string _signature;
		std::string _buffer;
		std::string _algorithm;
	};

	class VerifySignByP1ExtRequestHandler : public RESTfulRequestHandler
	{
	public:
		void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
		{
			poco_information_f1(Application::instance().logger(), "Request from %s", request.clientAddress().toString());

			RESTfulRequestHandler::handleCORS(request, response);

			HTMLForm form(request, request.stream());
			std::string base64(form.get("certBase64", ""));
			std::string msg(form.get("msg", ""));
			std::string signature(form.get("signdMsg", ""));

			VerifySignByP1Ext command(base64, msg, signature);
			command.execute();

			return response.sendBuffer(command().data(), command().length());
		}
	};
}