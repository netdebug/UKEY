#pragma once
//typedef char* BSTR ;
//typedef long BOOL;
#include <string.h>
#include "GMCrypto.h"

#ifdef __cplusplus
extern "C" {
#endif

	typedef char * BSTR;
	int SOF_OpenDevice(void);
	int SOF_CloseDevice(void);
	long SOF_SetSignMethod(long SignMethod);
	long SOF_SetEncryptMethod(long EncryptMethod);
	long SOF_GetLastError();
	BSTR SOF_GenRandom(short RandomLen);
	BOOL SOF_Login(BSTR  ContainerName, BSTR  PassWd);
	long SOF_GetPinRetryCount(BSTR AppName);
	BSTR SOF_GetCertInfo(BSTR Base64EncodeCert, short Type);
	BSTR SOF_GetDeviceInfo(BSTR ContainerName, long type);
	BSTR SOF_SignData(BSTR ContainerName, BSTR InData);
	BOOL SOF_VerifySignedData(BSTR Base64EncodeCert, BSTR InData, BSTR SignValue);
	BOOL SOF_EncryptFile(BSTR Pwd, BSTR InFile, BSTR OutFile);
	BOOL SOF_DecryptFile(BSTR Pwd, BSTR InFile, BSTR OutFile);
	BSTR SOF_AsEncrypt(BSTR Base64Cert, BSTR InData);
	BSTR SOF_AsDecrypt(BSTR Base64Cert, BSTR Indata);
	BSTR SOF_ExportUserCert(BSTR ContainerName);
	BSTR SOF_ExportExChangeUserCert(BSTR ContainerName);
	BSTR SOF_GetUserList();
	
#ifdef __cplusplus
}
#endif

