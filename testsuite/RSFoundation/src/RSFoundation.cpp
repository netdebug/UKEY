//
// RSFoundation.cpp
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#include "RSFoundation.h"
#include "Poco/SharedLibrary.h"
#include "Poco/Exception.h"
#include "Poco/StreamCopier.h"
#include <stdio.h>
#include <sstream>
#include "SOFProvider.h"

using Poco::SharedLibrary;
using Poco::NotFoundException;
using Poco::LibraryLoadException;
using Poco::LibraryAlreadyLoadedException;

RSFoundation::RSFoundation(const std::string& name)
{
}


RSFoundation::~RSFoundation()
{
}

void RSFoundation::RS_ConfigParameters(const std::string& cmd, const std::string& val)
{
	//GetParamFromJSONFile;
}



std::string RSFoundation::RS_ConfigParameters(const std::string& cmd)
{
	//SetConfigParam
	//retrun JSONString
}


std::string RSFoundation::RS_GetUserList()
{
	int val = SOF_OpenDevice();
	poco_assert(0 == val);
	std::string list = SOF_GetUserList();
	//1||ContainerName1&&&user1
	//2||ContainerName2&&&user2
	std::string JSONString;
	JSONString toJSON(list);
	/*{
		"code":"0000",
			"msg" : "执行成功",
			"data" : {
			"userlist":[
				{
					"user1":"ContainerId1",
					"user2":"ContainerId2"
				}
			]
		}
	}*/
	val = SOF_CloseDevice();
	poco_assert(0 == val);
	return JSONString;
}


std::string RSFoundation::RS_GetCertBase64String(const std::string& containerId, short certType)
{
	enum certType
	{
		sign = 0,
		crypto
	};

	short certType;
	std::string certContent;
	std::string containerId("ContainerName");
	switch (certType)
	{
	case certType::sign:
		certContent = SOF_ExportUserCert((char*)containerId.c_str());
		break;
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
		certContent = SOF_ExportExChangeUserCert((char*)containerId.c_str());
		break;
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

	return toJSON(certContent);
}

std::string RSFoundation::RS_GetCertInfo(const std::string& certBase64, short type)
{
	std::string certItem;

	if (SGD_CERT_VERSION < type < SGD_CERT_DER_EXTENSIONS ||
		SGD_CERT_ISSUER_CN < type < SGD_CERT_SUBJECT_EMAIL)
	{
		certItem = SOF_GetCertInfo(certBase64, type);
	}

	if (SGD_EXT_AUTHORITYKEYIDENTIFIER_INFO < type < SGD_EXT_SELFDEFINED_EXTENSION_INFO)
	{
		certItem = SOF_GetCertInfoByOid(certBase64, type);
	}

	return toJSON(certItem);
}

std::string RSFoundation::RS_CertLogin(const std::string& containId, const std::string& password)
{
	std::string CId(containId);
	std::string PW(password);
	if (CId.empty() || PW.empty())
	{
		std::cout << "Message Box for user" << std::endl;
	}

	int retryCount = SOF_GetPinRetryCount(CId);
	assert(retryCount > 0);
	std::string JSONString << SOF_Login(CID, PW);

	return JSONString;
}

std::string RSFoundation::RS_GetPinRetryCount(const std::string& containerId)
{

	std::string CId(containId);
	int retryCount = SOF_GetPinRetryCount(CId);

	return toJSON(retryCount);
}

std::string RSFoundation::RS_KeyGetKeySn()
{
	std::cout << "Message Box for selection" << std::endl;
	std::string KEY_SN = SOF_GetDeviceInfo(containerId, SGD_DEVICE_SERIAL_NUMBER);
	return toJSON(KEY_SN);
}

std::string RSFoundation::RS_KeySignByP1(std::string& msg)
{
	std::string CId(containId);
	std::string signature = SOF_SignData(CId, msg);
	assert(!signature.empty);

	return toJSON(signature);
}

std::string RSFoundation::RS_VerifySignByP1(std::string& certBase64, std::string& msg, const std::string signature)
{
	bool val = SOF_VerifySignedData(certBase64, msg, signature);
	return toJSON(val);
}

std::string RSFoundation::RS_KeyEncryptData(std::string rsKey, std::string certBase64)
{
	std::string JSONString;
	return JSONString;
}

std::string RSFoundation::RS_KeyDecryptData(std::string& encRsKey)
{
	std::string JSONString;
	return JSONString;
}

std::string RSFoundation::RS_KeyEncryptByDigitalEnvelope(const std::string& sourceFilePath, const std::string& encFilePath, std::string certBase64)
{
	std::string JSONString;
	return JSONString;
}

std::string RSFoundation::RS_KeyDecryptByDigitalEnvelope(const std::string& encFilePath, const std::string& dncDirectory Path, std::string& encKeyPath)
{
	std::string JSONString;
	return JSONString;
}
