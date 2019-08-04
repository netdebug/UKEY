#pragma once

#include "JSONStringify.h"
#include "SOFErrorCode.h"
#include "RequestHandleException.h"
#include <string>

namespace Reach {

	using Reach::JSONStringify;

	template<typename TRS>
	class Command
	{
	public:
		Command& execute()
		{
			try
			{
				rs.execute(response);
				/// 业务逻辑不允许 response 为空
				if (response.empty()) {
					int error = SOF_GetLastError();
					throw RequestHandleException(error);
				}
			}
			catch (Poco::Exception& e) {
				///统一错误解析处理
				response = JSONStringify("unsuccessful", e.code());
				response.addNullObject();
			}
			return *this;
		}

		std::string operator ()()
		{
			return response.toString();
		}

	private:
		JSONStringify response;
		TRS rs;
	};
}