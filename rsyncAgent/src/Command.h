#pragma once

#include "JSONStringify.h"
#include "SOFErrorCode.h"
#include "RequestHandleException.h"
#include <string>

namespace Reach {

	using Reach::JSONStringify;

	class Command
	{
	public:
		Command()
		{

		}

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
			catch (Poco::Exception& e) {
				///统一错误解析处理
				response = JSONStringify(e.message(), e.code());
				response.addNullObject();
			}
			return *this;
		}

		void add(const std::string& name, const std::string& value)
		{
			colletion.add(name, value);
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