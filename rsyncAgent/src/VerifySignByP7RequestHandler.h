#pragma once

#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/HTTPServerRequest.h"

namespace Reach {

	using Poco::Net::HTTPRequestHandler;
	using Poco::Net::HTTPServerRequest;
	using Poco::Net::HTTPServerResponse;

	///RS_VerifySignByP7
	class VerifySignByP7
	{
	public:
		VerifySignByP7(const std::string& textual, const std::string& signature, int mode)
			:_textual(textual),_signature(signature), _mode(mode), _verify(false)
		{}
		VerifySignByP7& execute()
		{
			/////1 = Detached mode ,textual must be cleared!
			if (_mode)
				_textual.clear();

			_verify = SOF_VerifySignedMessage(_signature, _textual);
			return *this;
		}

		operator std::string()
		{
			if (!_verify) {
				JSONStringify data("unsuccessful", 3325);
				data.addNullObject();
				return data;
			}

			JSONStringify data;
			data.addNullObject();
			return data;
		}
	private:
		int _mode;///Attached = 0, Detached = 1
		bool _verify;
		std::string _textual;
		std::string _signature;
	};

	class VerifySignByP7RequestHandler : public HTTPRequestHandler
	{
	public:
		void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
		{
			Application& app = Application::instance();
			app.logger().information("VerifySignByP7RequestHandler Request from " + request.clientAddress().toString());

			std::string data;
			HTMLForm form(request, request.stream());
			if (!form.empty()) {
				std::string textual(form.get("msg", ""));
				std::string signature(form.get("signdMsg", ""));
				Var mode(form.get("flag", ""));
				VerifySignByP7 command(textual, signature, mode);
				data += command.execute();
			}
			return response.sendBuffer(data.data(), data.length());
		}
	};
}