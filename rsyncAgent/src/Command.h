#pragma once

#include "Poco/Net/NameValueCollection.h"
#include "Poco/Debugger.h"
#include "JSONStringify.h"
#include "ErrorCode.h"
#include "SoFProvider.h"
#include "RequestHandleException.h"
#include "translater.h"
#include <string>

namespace Reach {

	using Reach::JSONStringify;
	using Poco::Debugger;
	using Poco::Net::NameValueCollection;
	
	class Command
	{
	public:
		Command& execute()
		{
			try
			{
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
				Debugger::message(format("RequestHandleException : <%s>:<%d>", e.displayText(),e.code()));
				translater& trans = translater::default();

				int error = SOF_GetLastError();
				std::string detail = trans.tr("SOFError", error);
				std::string message = trans.tr("error", e.code());

				response = JSONStringify(message, e.code());
				response.addObject("info", detail);
			}
			catch (Poco::Exception& e)
			{
				Debugger::message(format("RequestHandleException : <%s>:<%d>", e.displayText(), e.code()));

				translater& trans = translater::default();
				std::string message = trans.tr("error", RAR_UNKNOWNERR);
				JSONStringify(message, e.code());
				response.addObjectItem("info", e.message());
			}

			return *this;
		}

		void add(const std::string& name, const std::string& value)
		{
			colletion.add(name, value);
		}

		void add(const std::string& name, int value)
		{
			colletion.add(name, std::to_string(value));
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