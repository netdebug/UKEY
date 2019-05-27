//
// RSFoundation.h
//
// Definition of the RSFoundation class.
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef RSFoundation_INCLUDED
#define RSFoundation_INCLUDED


#include "Poco/Foundation.h"
#include "Poco/SharedLibrary.h"
#include <string>

namespace Reach {

		class RSFoundation
	{
	public:
		RSFoundation(const std::string& name);
		~RSFoundation();

		//14 RS Interfaces
		void RS_ConfigParameters(const std::string& cmd, const std::string& val);
		std::string RS_GetParameters(const std::string& cmd);
		std::string RS_GetUserList();
		std::string RS_GetCertBase64String(short ctype,  const std::string& uid);
		std::string RS_GetCertInfo(const std::string& base64, short type);
		std::string RS_CertLogin(const std::string& uid, const std::string& password);
		std::string RS_GetPinRetryCount(const std::string& uid);

		std::string RS_KeyGetKeySn(std::string& uid);
		std::string RS_KeySignByP1(std::string& uid, std::string& msg);
		std::string RS_VerifySignByP1(std::string& base64, std::string& msg, const std::string signature);
		//对称加解密
		std::string RS_EncryptFile(std::string& source, std::string& encrypt);
		std::string RS_DecryptFile(std::string& kv, std::string& encrypt, std::string& decrypt);
		//非对称加解密
		std::string RS_KeyEncryptData(std::string rsKey, std::string certBase64);
		std::string RS_KeyDecryptData(std::string& uid, std::string& encRsKey);
		//数字信封加解密
		std::string RS_KeyEncryptByDigitalEnvelope(const std::string& sourceFilePath, const std::string& encFilePath, std::string certBase64);
		std::string RS_KeyDecryptByDigitalEnvelope(const std::string& encFilePath, const std::string& dncDirectoryPath, std::string& encKeyPath);
	};
}


#endif // RSFoundation_INCLUDED
