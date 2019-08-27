#pragma once

#include "Poco/Net/NameValueCollection.h"
#include "Poco/Debugger.h"
#include "Poco/String.h"
#include "JSONStringify.h"
#include "ErrorCode.h"
#include "SoFProvider.h"
#include "RequestHandleException.h"
#include "translater.h"
#include <string>

namespace Reach {

	using Reach::JSONStringify;
	using Poco::Debugger;
	using Poco::format;
	using Poco::Net::NameValueCollection;
	
	class Command
	{
	public:
		Command& execute()
		{
			try{
				this->run();
				toJSON();
				/// 业务逻辑不允许 response 为空
				if (response.empty()) {
					int error = SOF_GetLastError();
					throw RequestHandleException(RAR_UNKNOWNERR);
				}
			}
			catch (RequestHandleException& e) {
				///统一错误解析处理
				sendErrorResponse(e.className() ,e.code());
			}
			catch (Poco::Exception& e) {
				sendErrorResponse(e.className(), RAR_UNKNOWNERR);
			}

			return *this;
		}

		std::string getEngine()
		{
			Application& app = Application::instance();
			return app.config().getString("engine.mode", "SOF");
		}

		void add(const std::string& name, const std::string& value)
		{
			colletion.add(name, value);
		}

		void add(const std::string& name, int value)
		{
			colletion.add(name, std::to_string(value));
		}

		void sendErrorResponse(const std::string& msg, int code)
		{
			Debugger::message(format("%s : <%s>:<%d>", msg, msg, code));
			translater& trans = translater::default();
			std::string message, detail;

			try 
			{
				message = trans.tr("error", code);
				detail  = trans.tr("SOFError", SOF_GetLastError());
			}
			catch (Poco::NotFoundException&)
			{
				message = trans.tr("error", RAR_UNKNOWNERR);
			}

			response = JSONStringify(message, code);
			response.addObject("info", detail);
		}

		std::string operator ()()
		{
			return response.toString();
		}

		virtual void run() = 0;
	protected:
		void toJSON()
		{
			typedef NameValueCollection::ConstIterator Iter;
			for (Iter it = colletion.begin(); it != colletion.end(); it++) {
				Debugger::message(format("object item <%s>:<%s> ", it->first, it->second));
				response.addObject(it->first, it->second);
			}
		}
	private:
		JSONStringify response;
		NameValueCollection colletion;
	};
}