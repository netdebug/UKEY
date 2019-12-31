#pragma once
#include <string>
#include "Poco/Net/HTTPClientSession.h"
#include "Poco/JSON/Parser.h"
#include "Poco/JSON/Object.h"
#include "Poco/JSON/Array.h"
#include "Poco/DynamicStruct.h"
#include "Poco/Dynamic/Var.h"
#include <cassert>

#define JSON_PARSE(DATA) \
	Poco::JSON::Parser ps;														\
	Poco::Dynamic::Var res = ps.parse(DATA);									\
	assert(res.type() == typeid(Poco::JSON::Object::Ptr));						\
	Poco::JSON::Object::Ptr object = res.extract<Poco::JSON::Object::Ptr>();	\
	assert(object);																\
	Poco::DynamicStruct ds = *object;

namespace Reach {
	namespace ActiveX {

		class Utility
		{
		public:
			static void get(const std::string & url);
			static void request(const std::string & url, const std::string & body = "");
			static std::string response();
			static std::wstring convert(const std::string& utf8);
			static std::string config(const std::string& name);
			static std::string formatUid(const std::string& entries);
			static std::string GBKEncodingUTF8(const std::string& text);
			static std::string UTF8EncodingGBK(const std::string & inEncoding);
			static std::string SuperRequest(const std::string& url, const std::string& body);
			static void message(const std::string& message);
		private:
			Utility();
			Utility(const Utility&);
			Utility& operator = (const Utility&);

			static Poco::Net::HTTPClientSession _session;
		};

	}
} ///Reach::ActiveX