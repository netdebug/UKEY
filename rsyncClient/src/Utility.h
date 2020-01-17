#pragma once
#include <string>
#include "Poco/Net/HTTPClientSession.h"
#include "Poco/JSON/Parser.h"
#include "Poco/JSON/Object.h"
#include "Poco/JSON/Array.h"
#include "Poco/DOM/Document.h"
#include "Poco/DOM/DOMParser.h"
#include "Poco/SAX/InputSource.h"
#include "Poco/DynamicStruct.h"
#include "Poco/Dynamic/Var.h"
#include <sstream>
#include <cassert>
#include <string>

#define JSON_PARSE(DATA) \
	Poco::JSON::Parser ps;														\
	Poco::Dynamic::Var res = ps.parse(DATA);									\
	poco_assert(res.type() == typeid(Poco::JSON::Object::Ptr));					\
	Poco::JSON::Object::Ptr object = res.extract<Poco::JSON::Object::Ptr>();	\
	poco_assert(object);														\
	Poco::DynamicStruct ds = *object;

#define JSON_ARRARY_PARSE(DATA) \
	Poco::JSON::Parser ps;														\
	Poco::Dynamic::Var res = ps.parse(DATA);									\
	poco_assert(res.type() == typeid(Poco::JSON::Array::Ptr));					\
	Poco::JSON::Array::Ptr object = res.extract<Poco::JSON::Array::Ptr>();		\
	poco_assert(object);														\
	Poco::Dynamic::Array da = *object;

#define XML_PARSE(XMLData)	\
	std::istringstream istr(XMLData);											\
	Poco::XML::InputSource source(istr);										\
	Poco::XML::DOMParser parser;												\
	parser.setFeature(Poco::XML::DOMParser::FEATURE_FILTER_WHITESPACE, true);	\
	Poco::AutoPtr<Poco::XML::Document> pDoc = parser.parse(&source);

#define utility_message_f1(fmt, arg) \
	Utility::message(Poco::format((fmt),(arg)));

#define utility_message(msg) \
	Utility::message(msg);

namespace Reach {
	namespace ActiveX {

		class Utility
		{
		public:
			static std::string get(const std::string & url);
			static void request(const std::string & url, const std::string & body = "");
			static std::string response();
			static std::wstring convert(const std::string& utf8);
			static std::string config(const std::string& name);
			static std::string formatUid(const std::string& entries);
			static std::string GBKEncodingUTF8(const std::string& text);
			static std::string UTF8EncodingGBK(const std::string & inEncoding);
			static std::string SuperRequest(const std::string& url, const std::string& body);
			static void message(const std::string& message);
			static std::string CodeFromDN(const std::string& cert);
		private:
			Utility();
			Utility(const Utility&);
			Utility& operator = (const Utility&);

			static Poco::Net::HTTPClientSession _session;
		};

	}
} ///Reach::ActiveX