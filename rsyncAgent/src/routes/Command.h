#pragma once

#include "Poco/Net/NameValueCollection.h"
#include "Poco/Debugger.h"
#include "Poco/String.h"
#include "JSONStringify.h"
#include "ErrorCode.h"
#include "RequestHandleException.h"
#include "translater.h"
#include <string>

namespace Reach {
	class Command
	{
	public:
		Command();
		Command& execute();
		std::string operator ()();
	protected:
		virtual ~Command();
		virtual void run() = 0;
		std::string getEngine();
		void add(const std::string& name, int value);
		void add(const std::string& name, const std::string& value);
	private:
		void sendErrorResponse(const std::string& msg, int code);
		void sendErrorResponseEx(const std::string & msg, int code);
		void toJSON();

		JSONStringify response;
		Poco::Net::NameValueCollection colletion;
	};
}