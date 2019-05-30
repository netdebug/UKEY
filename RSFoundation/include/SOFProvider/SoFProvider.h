#ifndef _SOFPROVIDER_H_
#define _SOFPROVIDER_H_

#include <string>

#ifdef __cplusplus
extern "C" {
#endif
	int SOF_OpenDevice(void);

	int SOF_CloseDevice(void);

	long SOF_SetSignMethod (long SignMethod);

	long SOF_SetEncryptMethod (long EncryptMethod);

	long SOF_GetLastError();
#ifdef __cplusplus
}
#endif

std::string SOF_ExportUserCert(std::string ContainerName);

std::string SOF_GetUserList();

std::string SOF_GenRandom(short RandomLen);

BOOL SOF_Login(std::string ContainerName,std::string PassWd);

long SOF_GetPinRetryCount(std::string AppName);

std::string SOF_ExportExChangeUserCert(std::string ContainerName);

std::string SOF_GetCertInfo(std::string Base64EncodeCert, short Type);

std::string SOF_SignData(std::string ContainerName,std::string InData);

BOOL SOF_VerifySignedData(std::string Base64EncodeCert, std::string InData, std::string SignValue);

BOOL SOF_EncryptFile(std::string Pwd, std::string InFile, std::string OutFile);

BOOL SOF_DecryptFile(std::string Pwd, std::string InFile, std::string OutFile);

std::string SOF_GetVersion();

std::string SOF_GetDeviceInfo(std::string ContainerName,long type);

std::string SOF_AsEncrypt(std::string Base64EncodeCert, std::string Indata);

std::string SOF_AsDecrypt(std::string ContainerName, std::string InData);

#endif


