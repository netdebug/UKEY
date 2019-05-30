//
// RSFoundation.cpp
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//
#include "RSFoundation.h"

//#include "Poco/Foundation.h"
//#include "Poco/SharedLibrary.h"
#include "Poco/SharedLibrary.h"
#include "Poco/Exception.h"
#include "Poco/StreamCopier.h"
#include "Poco/RegularExpression.h"
#include "Poco/JSON/Object.h"
#include "Poco/JSON/Array.h"
#include "Poco/JSON/JSONException.h"

#include <vector>
#include <iostream>
#include <stdio.h>
#include <sstream>
#include "UDevice.h"
#include "JSONStringify.h"
#include "SoFProvider.h"

using Poco::JSON::Object;
using Poco::JSON::Array;
using Poco::RegularExpression;
using Poco::SharedLibrary;
using Poco::NotFoundException;
using Poco::LibraryLoadException;
using Poco::LibraryAlreadyLoadedException;

using namespace Reach;

class UCertificate;
class GmASCrypto;
class GmSM4Crypto;


RSFoundation::RSFoundation()
{
	
}


RSFoundation::~RSFoundation()
{

}

void RSFoundation::RS_ConfigParameters(const std::string& cmd, const std::string& val)
{
	throw Poco::NotImplementedException("RS_ConfigParameters Not Implmented!");
}



std::string RSFoundation::RS_GetParameters(const std::string& cmd)
{
	throw Poco::NotImplementedException("RS_ConfigParameters Not Implmented!");
	return "";
}

std::string RSFoundation::RS_GetUserList()
{
	UDevice::default();

	/* example
	{
		"code":"0000",
			"msg" : "执行成功",
			"data" : {
			"userlist":"BJCA-Application||806000119631708&&&BJCA-Application||806000119631714"
		}
	}
	*/
	std::string line = SOF_GetUserList();
	JSONStringify data;
	data.addObject("userlist", line);
	return data;
}

std::string RSFoundation::RS_GetCertBase64String(short ctype, const std::string& uid)
{
	UDevice::default();

	enum certType {	sign = 1,crypto};
	std::string certContent;
	
	switch (ctype)
	{
	case certType::sign:
	{
		char* _uid = const_cast<char*>(uid.c_str());
		char* cert = SOF_ExportUserCert(_uid);
		if (cert)
			certContent = cert;
		break;
	}
		/*
		{
			"code":"0000",
				"msg" : "执行成功",
				"data" : {
				"certBase64":{
					"MIIEeTCCBB6gAwIBAgIQaeIAAAAEYGCfrSk7jfL2BTAMBggqgRzPVQGDdQUAMGIxCzAJBg
					NVBAYTAkNOMRIwEAYDVQQIDAnnpo/lu7rnnIExLTArBgNVBAoMJEZ1amlhbiBEaWdpdGFsI
					ENlcnRpZmljYXRlIEF1dGhvcml0eTEQMA4GA1UEAwwHRkpDQVNNMjAeFw0xNzEyMDUxNjAw
					MDBaFw0yMTA2MjUwNjE3NDJaMIHCMQswCQYDVQQGEwJDTjESMBAGA1UECAwJ56aP5bu655y
					BMRIwEAYDVQQHDAnnpo/lt57luIIxGzAZBgNVBAsMEjkxMzUwMTAyMDUyMzA3MTUxRDEkMC
					IGA1UECwwb5q2k6K+B5Lmm5LuF5L2/55So5LqO5rWL6K+VMUgwRgYDVQQDDD/npo/lu7rnk
					Z7mnK/kv6Hmga/np5HmioDmnInpmZDlhazlj7jvvIjmtYvor5XkuJPnlKjlm5vljYHkuZ3v
					vIkwWTATBgcqhkjOPQIBBggqgRzPVQGCLQNCAASZg4Cn+l9fQlJiMMilCLzaUwvethF/bIY
					sOXtAuk1Fehwx9aeWRwsel8wLqpSfNo/DrOzmveKokwUKVeURx2Rbo4ICUTCCAk0wDAYDVR
					0TBAUwAwEBADAdBgNVHSUEFjAUBggrBgEFBQcDAgYIKwYBBQUHAwQwCwYDVR0PBAQDAgDAM
					CIGByqBHIbvQgEEFzYwMTZAMTA1OUAwMDAwMDA5OTkyMzIzMB8GA1UdIwQYMBaAFNOyMO38
					peg+Oq5so8pPvMgN4yZ1MIHSBgNVHR8EgcowgccwgcSggcGggb6GgY5sZGFwOi8vMjAyLjE
					wOS4xOTQuMjI5OjM4OS9DTj1GSkNBU00yLENOPUZKQ0FTTTIsIE9VPUNSTERpc3RyaWJ1dG
					VQb2ludHMsIGM9Y24/Y2VydGlmaWNhdGVSZXZvY2F0aW9uTGlzdD9iYXNlP29iamVjdGNsY
					XNzPWNSTERpc3RyaWJ1dGlvblBvaW50hitodHRwOi8vMjAyLjEwOS4xOTQuMjI5L2Rvd25s
					b2FkL0ZKQ0FTTTIuY3JsMIHXBggrBgEFBQcBAQSByjCBxzCBiwYIKwYBBQUHMAKGf2xkYXA
					6Ly8yMDIuMTA5LjE5NC4yMjk6Mzg5L0NOPUZKQ0FTTTIsQ049RkpDQVNNMiwgT1U9Y0FDZX
					J0aWZpY2F0ZXMsIGM9Y24/Y0FDZXJ0aWZpY2F0ZT9iYXNlP29iamVjdENsYXNzPWNlcnRpZ
					mljYXRpb25BdXRob3JpdHkwNwYIKwYBBQUHMAKGK2h0dHA6Ly8yMDIuMTA5LjE5NC4yMjkv
					ZG93bmxvYWQvRkpDQVNNMi5jZXIwHQYDVR0OBBYEFOZo0xaF7/oYQpurxFmcntNJFeutMAw
					GCCqBHM9VAYN1BQADRwAwRAIgNYSUg/izh/DRFosOAK7deiVgU5x7C03bxc2DdeiK3vUCIG
					BPWBb4Khcr/ki/rSXTOkr+8+URu/vG54T5KhboWqFV"
				}
			}
		}
		*/
	case certType::crypto:
	{
		char* _uid = const_cast<char*>(uid.c_str());
		char* cert = SOF_ExportExChangeUserCert(_uid);
		if (cert)
			certContent = cert;
		break;
	}
		/*
		{
			"code":"0000",
				"msg" : "执行成功",
				"data" : {
				"certBase64":{
					"MIIEWzCCA/+gAwIBAgIQaeIAAAAEYF+PCPsuL9T43zAMBggqgRzPVQGDdQUAMGIxCzAJBg
					NVBAYTAkNOMRIwEAYDVQQIDAnnpo/lu7rnnIExLTArBgNVBAoMJEZ1amlhbiBEaWdpdGFsI
					ENlcnRpZmljYXRlIEF1dGhvcml0eTEQMA4GA1UEAwwHRkpDQVNNMjAeFw0xNzEyMDUxNjAw
					MDBaFw0yMTA2MjUwNjE3NDJaMIHCMQswCQYDVQQGEwJDTjESMBAGA1UECAwJ56aP5bu655y
					BMRIwEAYDVQQHDAnnpo/lt57luIIxGzAZBgNVBAsMEjkxMzUwMTAyMDUyMzA3MTUxRDEkMC
					IGA1UECwwb5q2k6K+B5Lmm5LuF5L2/55So5LqO5rWL6K+VMUgwRgYDVQQDDD/npo/lu7rnk
					Z7mnK/kv6Hmga/np5HmioDmnInpmZDlhazlj7jvvIjmtYvor5XkuJPnlKjlm5vljYHkuZ3v
					vIkwWTATBgcqhkjOPQIBBggqgRzPVQGCLQNCAARVgM/gvWp4cQjIrBZrmtijlbvIIt3cxSx
					Zoz1mwEOSyHwRmC0rwJCuG8OkJ2CHo+VkoUIH7U8JBgSN1H2sgE38o4ICMjCCAi4wDAYDVR
					0TBAUwAwEBADALBgNVHQ8EBAMCADAwIgYHKoEchu9CAQQXNjAxNkAxMDU5QDAwMDAwMDk5O
					TIzMjMwHwYDVR0jBBgwFoAU07Iw7fyl6D46rmyjyk+8yA3jJnUwgdIGA1UdHwSByjCBxzCB
					xKCBwaCBvoaBjmxkYXA6Ly8yMDIuMTA5LjE5NC4yMjk6Mzg5L0NOPUZKQ0FTTTIsQ049Rkp
					DQVNNMiwgT1U9Q1JMRGlzdHJpYnV0ZVBvaW50cywgYz1jbj9jZXJ0aWZpY2F0ZVJldm9jYX
					Rpb25MaXN0P2Jhc2U/b2JqZWN0Y2xhc3M9Y1JMRGlzdHJpYnV0aW9uUG9pbnSGK2h0dHA6L
					y8yMDIuMTA5LjE5NC4yMjkvZG93bmxvYWQvRkpDQVNNMi5jcmwwgdcGCCsGAQUFBwEBBIHK
					MIHHMIGLBggrBgEFBQcwAoZ/bGRhcDovLzIwMi4xMDkuMTk0LjIyOTozODkvQ049RkpDQVN
					NMixDTj1GSkNBU00yLCBPVT1jQUNlcnRpZmljYXRlcywgYz1jbj9jQUNlcnRpZmljYXRlP2
					Jhc2U/b2JqZWN0Q2xhc3M9Y2VydGlmaWNhdGlvbkF1dGhvcml0eTA3BggrBgEFBQcwAoYra
					HR0cDovLzIwMi4xMDkuMTk0LjIyOS9kb3dubG9hZC9GSkNBU00yLmNlcjAdBgNVHQ4EFgQU
					5k/mbHyVr/97oPJnYIU8iReQ7TMwDAYIKoEcz1UBg3UFAANIADBFAiAxVV7Q9esYc2f+iKE
					nJ76j4nQUOpWnNftuuQrLrSWItwIhANuaYgpwpOjIbHdTMdv7Vx0HxQ5JZUAJZ7BAsD2pcT
					Hh"
				}
			}
		}
		*/
	}
	JSONStringify data;
	data.addObject("certBase64", certContent);
	return data;
}

std::string RSFoundation::RS_GetCertInfo(const std::string& base64, short type)
{
	UDevice::default();

	std::string item;

	if (SGD_CERT_VERSION < type < SGD_CERT_DER_EXTENSIONS ||
		SGD_CERT_ISSUER_CN < type < SGD_CERT_SUBJECT_EMAIL)
	{
		char* _base64 = const_cast<char*>(base64.c_str());
		char* data = SOF_GetCertInfo(_base64, type);
		if (data)
			item = data;
	}

	if (SGD_EXT_AUTHORITYKEYIDENTIFIER_INFO < type < SGD_EXT_SELFDEFINED_EXTENSION_INFO)
	{
		//certItem = SOF_GetCertInfoByOid(const_cast<char*>(certBase64.c_str()), type);
	}

	JSONStringify data;
	data.addObject("info", item);
	return data;
}

std::string RSFoundation::RS_CertLogin(const std::string& uid, const std::string& password)
{
	UDevice::default();

	if (uid.empty() || password.empty())
		throw Poco::InvalidArgumentException("Argument Invalid!",0x34);

	char* _uid = const_cast<char*>(uid.c_str());
	char* _pw = const_cast<char*>(password.c_str());
	int retryCount = SOF_GetPinRetryCount(_uid);
	if (retryCount <= 0)
		throw Poco::LogicException("UKEY have been locked! containerId is", uid, 0x33);

	if (!SOF_Login(_uid, _pw))
		throw Poco::LogicException("UKEY Login failed! containerId is", uid, 0x35);

	JSONStringify data;
	data.addObject("containerId", uid);
	return data;
}

std::string RSFoundation::RS_GetPinRetryCount(const std::string& uid)
{
	UDevice::default();
	
	char* _uid = const_cast<char*>(uid.c_str());
	int retryCount = SOF_GetPinRetryCount(_uid);

	JSONStringify data;
	data.addObject("retryCount", retryCount);
	return data;
}

std::string RSFoundation::RS_KeyGetKeySn(std::string& uid)
{
	UDevice::default();

	char* _uid = const_cast<char*>(uid.c_str());
	std::string SNkey = SOF_GetDeviceInfo(_uid, SGD_DEVICE_SERIAL_NUMBER);
	
	JSONStringify data;
	data.addObject("containerId", uid);
	data.addObject("keySn", SNkey);
	return data;
}

std::string RSFoundation::RS_KeySignByP1(std::string& uid, std::string& msg)
{
	UDevice::default();

	char* _uid = const_cast<char*>(uid.c_str());
	char* _msg = const_cast<char*>(msg.c_str());
	std::string signature = SOF_SignData(_uid, _msg);
	if (signature.empty())
		throw Poco::LogicException("SOF_SignData failed!", 0x36);

	JSONStringify data;
	data.addObject("signdMsg", signature);
	return data;
}

std::string RSFoundation::RS_VerifySignByP1(std::string& base64, std::string& msg, const std::string signature)
{
	UDevice::default();

	char* _base64 = const_cast<char*>(base64.c_str());
	char* _msg = const_cast<char*>(msg.c_str());
	char* _signature = const_cast<char*>(signature.c_str());

	bool val = SOF_VerifySignedData(_base64, _msg, _signature);
	if (val)
		throw Poco::LogicException("SOF_VerifySignedData failed", val);

	JSONStringify data;
	data.addNullObject();
	return data;
}

#include "Poco/File.h"
std::string RSFoundation::RS_EncryptFile(std::string& source, std::string& encrypt)
{
	Poco::File fi(source);
	if (!fi.exists()) 
		throw Poco::FileExistsException("Source File Not Exists!", 0x40);
		
	char* _src = const_cast<char*>(source.c_str());
	char* _enc = const_cast<char*>(encrypt.c_str());
	char* ck = SOF_GenRandom(32);
	SOF_SetEncryptMethod(SGD_SM4_CBC);

	if (!SOF_EncryptFile(ck, _src, _enc))
		throw Poco::LogicException("SOF_EncryptFile failed!",0x37);

	JSONStringify data;
	data.addObject("symKey", ck);
	return data;
}

std::string RSFoundation::RS_DecryptFile(std::string& kv, std::string& encrypt, std::string& decrypt)
{
	char* _enc = const_cast<char*>(encrypt.c_str());
	char* _dec = const_cast<char*>(decrypt.c_str());
	char* ck = const_cast<char*>(kv.c_str());

	if (!SOF_DecryptFile(ck, _enc, _dec))
		throw Poco::LogicException("SOF_DecryptFile failed!", 0x38);

	JSONStringify data;
	data.addNullObject();
	return data;
}

std::string RSFoundation::RS_KeyEncryptData(std::string paintText, std::string base64)
{
	char* _base64 = const_cast<char*>(base64.c_str());
	char* _text = const_cast<char*>(paintText.c_str());

	SOF_SetSignMethod(SGD_SM3_SM2);
	SOF_SetEncryptMethod(SGD_SM4_ECB);

	char* _encData = SOF_AsEncrypt(_base64, _text);
	if (!_encData)
		throw Poco::LogicException("RS_KeyEncryptData failed!", 0x39);

	std::string encData = _encData;
	encData.append("@@@");
	encData.append(base64);

	JSONStringify data;
	data.addObject("encRsKey", encData);
	return data;
}

std::string RSFoundation::RS_KeyDecryptData(std::string& uid, std::string& encRsKey)
{
	UDevice::default();
	
	std::string pattern("(\\S+)@@@(\\S+)");
	int options = 0;
	/*options += RegularExpression::RE_CASELESS;
	options += RegularExpression::RE_EXTENDED;*/

	RegularExpression re(pattern, options);
	RegularExpression::Match mtch;

	if (!re.match(encRsKey, mtch))
		throw Poco::LogicException("RS_KeyDecryptData enRsKey Exception!", 0x40);

	std::vector<std::string> tags;
	re.split(encRsKey, tags, options);

	char* _uid = const_cast<char*>(uid.c_str());
	char* _enc = const_cast<char*>(tags[1].c_str());

	std::string kc = SOF_ExportExChangeUserCert(_uid);
	if (kc != tags[2])
		throw Poco::LogicException("certificate error");
	
	/*SOF_SetSignMethod(SGD_SM3_SM2);
	SOF_SetEncryptMethod(SGD_SM4_ECB);*/
	
	char* _dec = SOF_AsDecrypt(_uid, _enc);
	if (!_dec)
		throw Poco::LogicException("SOF_AsDecrypt decrypt Exception", 0x41);

	JSONStringify data;
	data.addObject("rsKey", _dec);
	return data;
}

std::string RSFoundation::RS_KeyEncryptByDigitalEnvelope(const std::string& sourceFilePath, const std::string& encFilePath, std::string certBase64)
{
	std::string JSONString;
	return JSONString;
}

std::string RSFoundation::RS_KeyDecryptByDigitalEnvelope(const std::string& encFilePath, const std::string& dncDirectoryPath, std::string& encKeyPath)
{
	std::string JSONString;
	return JSONString;
}
