//
//typedef char* BSTR ;
//typedef long BOOL;
#include <string.h>
#include "GMCrypto.h"

#ifdef __cplusplus
extern "C" {
#endif

	typedef char * BSTR1;
	int SOF_OpenDevice(void);
	int SOF_CloseDevice(void);
	long SOF_SetSignMethod(long SignMethod);
	long SOF_SetEncryptMethod(long EncryptMethod);
	long SOF_GetLastError();
	BSTR1 SOF_GenRandom(short RandomLen);
	BOOL SOF_Login(BSTR1  ContainerName, BSTR1  PassWd);
	long SOF_GetPinRetryCount(BSTR1 AppName);
	BSTR1 SOF_GetCertInfo(BSTR1 Base64EncodeCert, short Type);
	BSTR1 SOF_SignData(BSTR1 ContainerName, BSTR1 InData);
	BOOL SOF_VerifySignedData(BSTR1 Base64EncodeCert, BSTR1 InData, BSTR1 SignValue);
	BOOL SOF_EncryptFile(BSTR1 Pwd, BSTR1 InFile, BSTR1 OutFile);
	BOOL SOF_DecryptFile(BSTR1 Pwd, BSTR1 InFile, BSTR1 OutFile);
	BSTR1 SOF_AsEncrypt(BSTR1 ContainerName, BSTR1 InData);
	BSTR1 SOF_AsDecrypt(BSTR1 ContainerName, BSTR1 Indata);
	BSTR1 SOF_ExportUserCert(BSTR1 ContainerName);
	BSTR1 SOF_ExportExChangeUserCert(BSTR1 ContainerName);
	BSTR1 SOF_GetUserList();
	
#ifdef __cplusplus
}
#endif


