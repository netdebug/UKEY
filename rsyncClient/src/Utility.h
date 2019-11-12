#pragma once
#include <string>
#include "Poco/Net/HTTPClientSession.h"

namespace Reach {
	namespace ActiveX {

		class Utility
		{
		public:
			static void get(const std::string & url);
			static void request(const std::string & url, const std::string & body = "");
			static std::string response();
			static std::wstring convert(const std::string& utf8);
			static std::string formatUid(const std::string& entries);
			static std::string GBKtoUTF8(const std::string& text);
			static std::string SuperRequest(const std::string& url, const std::string& body);
		private:
			Utility();
			Utility(const Utility&);
			Utility& operator = (const Utility&);

			static Poco::Net::HTTPClientSession _session;
		};

	}
} ///Reach::ActiveX