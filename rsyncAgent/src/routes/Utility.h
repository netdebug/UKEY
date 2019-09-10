#pragma once
#include <string>

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
	private:
		Utility();
		Utility(const Utility&);
		~Utility();
	};
}