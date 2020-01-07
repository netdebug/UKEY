#pragma once
#include <string>
#include "Reach/Data/Session.h"
#include "Reach/Data/SessionContainer.h"
#include "Poco/DynamicStruct.h"

using Reach::Data::Session;
using Reach::Data::SessionContainer;

#define JSON_PARSE(DATA) \
	Poco::JSON::Parser ps;														\
	Poco::Dynamic::Var res = ps.parse(DATA);									\
	assert(res.type() == typeid(Poco::JSON::Object::Ptr));						\
	Poco::JSON::Object::Ptr object = res.extract<Poco::JSON::Object::Ptr>();	\
	assert(object);																\
	Poco::DynamicStruct ds = *object;

namespace Reach {

	class Utility
	{
	public:
		static std::string SOF_GenRandom(int size);
		static bool SOF_EncryptFile(std::string &, std::string &, std::string &);
		static std::string SOF_ExportExChangeUserCert(const std::string &);
		static std::string SOF_AsDecrypt(std::string &, std::string &);
		static std::string SOF_AsEncrypt(std::string &, std::string &);
		static bool SOF_DecryptFile(std::string &, std::string, std::string);
		static int random();
		static int SOF_GetPinRetryCount(const std::string &);
		static std::string SOF_SignMessage(short, std::string&, std::string&);
		static bool verifySignByP7(const std::string&, const std::string&);
		static int SOF_GetLastError();
		static std::string GetCertInfoByOid(const std::string& cer, const std::string& oid);
		static SessionContainer& getSC();
		static Session getSession();
		static std::string config(const std::string& name);
		static std::string timestamp();
		static std::string UniqueTransOrder();
		static bool resultFormLocal(const std::string & json);
		static bool resultFormNet(const std::string & json);
		static bool result(const std::string& json, const std::string& key);
		static bool testJSON(const std::string & buffer);
		static std::string cat(const std::string& delim, std::size_t pos, const std::string& str);
		static std::string Utility::sendRequest(const std::string& url, const std::string& data);
		static std::string v_encrypt_by_sm2(const std::string & plaintext, const std::string & pubkey);
	private:
		static int sm2_encrypt(const unsigned char * message, const int message_len, const unsigned char * pub_key, unsigned char * c1, unsigned char * c3, unsigned char * c2);
		static std::string getOpenSSLError();
	private:
		Utility();
		Utility(const Utility&);
		~Utility();
	};
}