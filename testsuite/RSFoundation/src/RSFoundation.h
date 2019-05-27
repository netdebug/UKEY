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

class RSFoundation
{
public:
	RSFoundation(const std::string& name);
	~RSFoundation();

	//14 RS Interfaces
	void RS_ConfigParameters(const std::string& cmd, const std::string& val);
	std::string RS_ConfigParameters(const std::string& cmd);
	std::string RS_GetUserList();
	std::string RS_GetCertBase64String(const std::string& containerId, short certType);
	std::string RS_GetCertInfo(const std::string& certBase64, short type);
	std::string RS_CertLogin(const std::string& containId, const std::string& password);
	std::string RS_GetPinRetryCount(const std::string& containerId);
	std::string RS_KeyGetKeySn();
	std::string RS_KeySignByP1(std::string& msg);
	std::string RS_VerifySignByP1(std::string& certBase64, std::string& msg, const std::string signature);
	std::string RS_KeyEncryptData(std::string rsKey, std::string certBase64);
	std::string RS_KeyDecryptData(std::string& encRsKey);
	std::string RS_KeyEncryptByDigitalEnvelope(const std::string& sourceFilePath, const std::string& encFilePath, std::string certBase64);
	std::string RS_KeyDecryptByDigitalEnvelope(const std::string& encFilePath, const std::string& dncDirectory Path, std::string& encKeyPath);

private:
	Poco::SharedLibrary sl;
};


#endif // RSFoundation_INCLUDED
