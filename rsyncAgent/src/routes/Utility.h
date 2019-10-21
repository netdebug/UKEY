#pragma once
#include <string>
#include "Reach/Data/Session.h"
#include "Reach/Data/SessionContainer.h"

using Reach::Data::Session;
using Reach::Data::SessionContainer;

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
		static bool SOF_VerifySignedMessage(const std::string&, const std::string&);
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
	private:
		Utility();
		Utility(const Utility&);
		~Utility();
	};
}