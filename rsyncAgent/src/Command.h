#pragma once

#include "Poco/Net/NameValueCollection.h"
#include "Poco/Debugger.h"
#include "JSONStringify.h"
#include "SOFErrorCode.h"
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
					throw RequestHandleException(error);
				}
			}
			catch (RequestHandleException& e) {
				///统一错误解析处理
				Debugger::message(format("RequestHandleException : <%s>:<%d>", e.displayText(),e.code()));

				translater& trans = translater::default();
				std::string message = trans.tr("error", e.code());
				response = JSONStringify(message, e.code());
				response.addNullObject();
			}
			catch (Poco::Exception& e)
			{
				response = JSONStringify(e.message(), e.code());
				response.addNullObject();
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