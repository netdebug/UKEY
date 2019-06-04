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


//#include "Poco/Foundation.h"
//#include "Poco/SharedLibrary.h"
#include <string>

#if defined(RSFoundation_EXPORTS)
#define RSFoundation_API __declspec(dllexport)
#else
#define RSFoundation_API __declspec(dllimport)
#endif

namespace Reach {

	class RSFoundation_API RSFoundation
	{
	public:
		RSFoundation();
		~RSFoundation();

		//14 RS Interfaces
		void RS_ConfigParameters(const std::string& cmd, const std::string& val);
		std::string RS_GetParameters(const std::string& cmd);
		std::string RS_GetUserList();
		std::string RS_GetCertBase64String(short ctype, const std::string& uid);
		//证书信息和有效性验证
		std::string RS_GetCertInfo(const std::string& base64, short type);
		std::string RS_VerifyIdentity(const std::string& base64, const std::string& authNo);
		//用户密码服务S
		std::string RS_CertLogin(const std::string& uid, const std::string& password);
		std::string RS_ChangePassWd(const std::string& oldCode, const std::string& newCode);
		std::string RS_GetPinRetryCount(const std::string& uid);
		//签名和验签
		std::string RS_KeyGetKeySn(const std::string& uid);

		std::string RS_KeySignByP1(const std::string& uid, const std::string& msg);
		std::string RS_VerifySignByP1(const std::string& base64, const std::string& msg, const std::string signature);

		std::string RS_KeyDigitalSignByP1(const std::string& asn1Msg, const std::string& uid);
		std::string RS_VerifyDigitalSignByP1(const std::string& base64, const std::string& asn1Msg, const std::string& signature);

		std::string RS_KeySignByP7(const std::string& uid, const std::string& asn1Msg, const std::string& flag);
		std::string RS_VerifySignByP7(const std::string& base64, const std::string& asn1Msg, const std::string& signature);
		//对称加解密
		std::string RS_EncryptFile(std::string& srcfile, std::string& encfile);
		std::string RS_DecryptFile(std::string& kv, std::string& encfile, std::string& decdir);
		//非对称加解密
		std::string RS_KeyEncryptData(std::string paintText, std::string base64);
		std::string RS_KeyDecryptData(std::string& uid, std::string& encRsKey);
		//数字信封加解密
		std::string RS_KeyEncryptByDigitalEnvelope(const std::string& srcfile, const std::string& encfile, std::string base64);
		std::string RS_KeyDecryptByDigitalEnvelope(const std::string& encfile, const std::string& decdir, std::string& encKeyfile);
	};
}


#endif // RSFoundation_INCLUDED
