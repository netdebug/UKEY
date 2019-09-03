#ifndef _SOFPROVIDER_H_
#define _SOFPROVIDER_H_

#include <string>
#include <vector>

#ifdef __cplusplus
extern "C" {
#endif
	int SOF_OpenDevice(void);

	int SOF_CloseDevice(void);

	long SOF_SetSignMethod(long SignMethod);

	long SOF_SetEncryptMethod(long EncryptMethod);

	long SOF_GetLastError();

	BOOL SOF_VerifySignedMessage(const char * MessageData, char * InData);
#ifdef __cplusplus
}
#endif

std::string SOF_ExportUserCert(std::string ContainerName);

std::string SOF_GetUserList();

std::string SOF_GenRandom(short RandomLen);

BOOL SOF_Login(std::string ContainerName, std::string PassWd);

long SOF_GetPinRetryCount(std::string AppName);

std::string SOF_ExportExChangeUserCert(std::string ContainerName);

std::string SOF_GetCertInfo(std::string Base64EncodeCert, short Type);

std::string SOF_SignData(std::string ContainerName, std::string InData);

BOOL SOF_VerifySignedData(std::string Base64EncodeCert, std::string InData, std::string SignValue);

BOOL SOF_EncryptFile(std::string Pwd, std::string InFile, std::string OutFile);

BOOL SOF_DecryptFile(std::string Pwd, std::string InFile, std::string OutFile);

std::string SOF_GetVersion();

std::string SOF_GetDeviceInfo(std::string ContainerName, long type);

std::string SOF_AsEncrypt(std::string Base64EncodeCert, std::string Indata);

std::string SOF_AsDecrypt(std::string ContainerName, std::string InData);

unsigned long SOF_GetSignMethod();

unsigned long SOF_GetEncryptMethod();

BOOL SOF_ChangePassWd(std::string ContainerName, std::string OldPassWd, std::string NewPassWd);

std::string SOF_EncryptData(std::string Pwd, std::string InData);

std::string SOF_DecryptData(std::string Pwd, std::string InData);

std::string SOF_SignFile(std::string ContainerName, std::string InFile);

BOOL SOF_VerifySignedFile(std::string Base64EncodeCert, std::string InFile, std::string SignValue);

std::string SOF_SignMessage(short flag, std::string ContainerName, std::string InData);

BOOL SOF_VerifySignedMessage(std::string MessageData, std::string InData);

std::string SOF_GetInfoFromSignedMessage(std::string SignedMessage, short type);

std::string SOF_GetCertInfoByOid(std::string Base64EncodeCert, std::string oid);

std::vector <std::string> SOF_GetDeviceCapability(std::string containerName, int type);

std::string SOF_GetDeviceList();

int SOF_OpenDevice(std::string name, int Type);

int SOF_CloseDevice(std::string name, int Type);
#endif
