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
			static std::string SuperRequestGBK(const std::string& url, const std::string& body);
			static std::string SuperRequest(const std::string& url, const std::string& body);
			static std::string UTF8EncodingGBK(const std::string& inEncoding);
			static std::string UTF8JSONStreamGBK(const std::string & inString);
			static std::string GBKJSONStreamUTF8(const std::string & inString);
			static std::string GBKEncodingUTF8(const std::string& inEncoding);
		private:
			Utility();
			Utility(const Utility&);
			Utility& operator = (const Utility&);

			static Poco::Net::HTTPClientSession _session;
		};

	}
} ///Reach::ActiveX