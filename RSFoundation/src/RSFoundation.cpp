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
#include "Poco/File.h"

#include <vector>
#include <iostream>
#include <stdio.h>
#include <sstream>
#include "UDevice.h"
#include "JSONStringify.h"
#include "GMCrypto.h"
#include "SoFProvider.h"
#include <cassert>

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

	enum certType { sign = 1, crypto };
	std::string certContent;

	switch (ctype)
	{
	case certType::sign:
	{
		certContent = SOF_ExportUserCert(uid);
	}
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
	{
		certContent = SOF_ExportExChangeUserCert(uid);
	}
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
	JSONStringify data;
	data.addObject("certBase64", certContent);
	return data;
}

std::string RSFoundation::RS_GetCertInfo(const std::string& base64, int type)
{
	//UDevice::default();

	std::string item;

	if (SGD_CERT_VERSION == type) {
		item = GetCertVersion(base64);
	}
	else if (SGD_CERT_VALID_TIME == type){
		item = GetCertVaildTime(base64);
	}
	else if (SGD_OID_IDENTIFY_NUMBER == type) {
		/// only support user id card
		item = GetCertOwnerID(base64);
	}
	else
	{
		item = SOF_GetCertInfo(base64, type);
	}
	
	/// Ignore specifi character (/f/n) 

	JSONStringify data;
	data.addObject("info", item);
	return data;
}

std::string RSFoundation::GetCertVersion(const std::string& base64)
{
	std::string item;
	item = SOF_GetCertInfo(base64, SGD_CERT_VERSION);

	///GB-T 20518-2006 信息安全技术 公钥基础设施 数字证书格式

	std::map<std::string, std::string> versions;
	versions["0"] = "V1";
	versions["1"] = "V2";
	versions["2"] = "V3";

	return versions[item];
}
#include "Poco/Timezone.h"
#include "Poco/Debugger.h"
#include "Poco/String.h"

using Poco::Timezone;
using Poco::DateTime;
using Poco::DateTimeFormat;
using Poco::DateTimeParser;
using Poco::DateTimeFormatter;
using Poco::Debugger;
using Poco::format;

std::string RSFoundation::GetCertVaildTime(const std::string& base64)
{
	std::string item;
	item = SOF_GetCertInfo(base64, SGD_CERT_VALID_TIME);
	/// 190313160000Z - 210314155959Z
	int options = 0;
	std::string pattern("(\\S+)-(\\S+)");
	std::string vaildtime;

	try {

		RegularExpression re(pattern, options);
		RegularExpression::Match mtch;
		if (!re.match(item, mtch))
			throw Poco::LogicException("GetCertVaildTime Exception!", 0x40);

		std::vector<std::string> tags;
		re.split(item, tags, options);

		std::string vaild_start = tags[1];
		std::string vaild_end = tags[2];
		Debugger::message(format("vaild_start : %s, vaild_start :%s", vaild_start, vaild_end));
		/// UTC to LocalTime +0800
		
		vaildtime.append(toLocalTime(vaild_start));
		vaildtime.append(" - ");
		vaildtime.append(toLocalTime(vaild_end));

		Debugger::message(format("vaildtime : %s", vaildtime));
	}
	catch (Poco::Exception&)
	{
	}
	
	return vaildtime;

}

#include "Poco/NumberParser.h"
using Poco::NumberParser;

std::string RSFoundation::toLocalTime(const std::string& time)
{
	int options = 0;
	std::string pattern("^([0-9]\\d{1})([0-9]\\d{1})([0-9]\\d{1})([0-9]\\d{1})([0-9]\\d{1})([0-9]\\d{1})Z");
	RegularExpression re(pattern, options);
	RegularExpression::Match mtch;
	if (!re.match(time, mtch))
		throw Poco::RegularExpressionException(100);
	///
	/// Match 1:	210314155959	     0	    12
	/// Group 1:	2103	     0	     4
	/// Group 2:	14	     4	     2
	/// Group 3:	15	     6	     2
	/// Group 4:	59	     8	     2
	/// Group 5:	59	    10	     2
	///
	std::vector<std::string> tags;
	re.split(time, tags, options);

	std::string prefix;
	int oct = std::stod(tags[1]);
	oct > 49 ? prefix = "19" : prefix = "20";
	std::string fmt = format("%s%s-%s-%s %s:%s", prefix, tags[1], tags[2], tags[3], tags[4], tags[5], tags[6]);

	Debugger::message(format("Timezone utcOffset: %d, tzd:: % d, name : %s", Timezone::utcOffset(), Timezone::tzd(), Timezone::name()));
	Debugger::message(time);
	int tzd = Timezone::tzd();
	DateTime dt = DateTimeParser::parse(DateTimeFormat::SORTABLE_FORMAT, fmt, tzd);
	std::string localtime = DateTimeFormatter::format(dt, DateTimeFormat::SORTABLE_FORMAT, Timezone::utcOffset());
	Debugger::message(localtime);
	return localtime;
}

std::string RSFoundation::GetCertOwnerID(const std::string& base64)
{
	std::string item;
	std::string pattern("(\\d+)");
	std::string special_oid("1.2.156.10260.4.1.1");
	item = SOF_GetCertInfoByOid(base64, special_oid);
	if (item.empty()) {
	
		item = SOF_GetCertInfo(base64, SGD_CERT_SUBJECT_CN);
		pattern = "@(\\d+)@";
	}

	item = toLegelID(item, pattern);
	/// erase 0 if is id card
	if (!item.empty() && item.at(0) == '0')
		item = item.replace(0, 1, "");

	return item;
}

std::string RSFoundation::toLegelID(const std::string& text, const std::string& pattern)
{
	/// SGD_CERT_SUBJECT_CN identify card (330602197108300018)
	/// CN = 041@0330602197108300018@测试个人一@00000001
	/// 十八位：^[1-9]\d{5}(18|19|([23]\d))\d{2}((0[1-9])|(10|11|12))(([0-2][1-9])|10|20|30|31)\d{3}[0-9Xx]$
	/// 十五位：^[1-9]\d{5}\d{2}((0[1-9])|(10|11|12))(([0-2][1-9])|10|20|30|31)\d{2}[0-9Xx]$
	//std::string pattern("@(\\d+)@");
	int options = 0;
	std::string id;

	try {
		RegularExpression re(pattern, options);
		RegularExpression::Match mtch;

		if (!re.match(text, mtch))
			throw Poco::LogicException("RS_KeyDecryptData uid Exception!", 0x40);

		std::vector<std::string> tags;
		re.split(text, tags, options);
		std::string id = tags[1];
	}
	catch (Poco::Exception&)
	{

	}
	
	return id;
}

std::string RSFoundation::RS_GetCertInfoEx(const std::string& base64, const std::string& oid)
{
	std::string item;

	item = SOF_GetCertInfoByOid(base64, oid);

	JSONStringify data;
	data.addObject("info", item);
	return data;
}

std::string RSFoundation::RS_VerifyIdentity(const std::string& base64, const std::string& authNo)
{
	UDevice::default();
	//需要服务端配合
	JSONStringify data;
	return data;
}

std::string RSFoundation::RS_CertLogin(const std::string& uid, const std::string& password)
{
	UDevice::default();
	if (uid.empty() || password.empty())
		throw Poco::InvalidArgumentException("Argument Invalid!", 0x34);

	int retryCount = SOF_GetPinRetryCount(uid);
	if (retryCount <= 0)
		throw Poco::LogicException("UKEY have been locked! containerId is", uid, 0x33);


	bool ok = SOF_Login(uid, password);
	if (!ok)
		throw Poco::LogicException("UKEY Login failed! containerId is", uid, 0x35);

	JSONStringify data;
	data.addObject("containerId", uid);
	return data;
}

std::string RSFoundation::RS_ChangePassWd(const std::string& uid, const std::string& oldCode, const std::string& newCode)
{
	UDevice::default();

	assert(!uid.empty());

	if (!SOF_ChangePassWd(uid, oldCode, newCode))
	{
		int error = SOF_GetLastError();
		throw Poco::LogicException("SOF_ChangePassWd failed", error);
	}

	JSONStringify data;
	return data;
}

std::string RSFoundation::RS_GetPinRetryCount(const std::string& uid)
{
	UDevice::default();

	int retryCount = SOF_GetPinRetryCount(uid);

	JSONStringify data;
	data.addObject("retryCount", retryCount);
	return data;
}

std::string RSFoundation::RS_KeyGetKeySn(const std::string& uid)
{
	UDevice::default();

	std::string SNkey = SOF_GetDeviceInfo(uid, SGD_DEVICE_SERIAL_NUMBER);

	if (SNkey.empty())
	{
		int error = SOF_GetLastError();
		throw Poco::LogicException("SOF_GetDeviceInfo Not Get UKEY SN", error);
	}

	JSONStringify data;
	data.addObject("containerId", uid);
	data.addObject("keySn", SNkey);
	return data;
}

std::string RSFoundation::RS_KeySignByP1(const std::string& uid, const std::string& msg)
{
	UDevice::default();

	std::string signature = SOF_SignData(uid, msg);
	if (signature.empty()) {
		int error = SOF_GetLastError();
		throw Poco::LogicException("SOF_SignData failed!", error);
	}

	JSONStringify data;
	data.addObject("signdMsg", signature);
	return data;
}

std::string RSFoundation::RS_VerifySignByP1(const std::string& base64, const std::string& msg, const std::string signature)
{
	bool val = SOF_VerifySignedData(base64, msg, signature);
	if (!val) {
		JSONStringify data("unsuccessful", 3325);
		data.addNullObject();
		return data;
	}

	JSONStringify data;
	data.addNullObject();
	return data;
}

std::string RSFoundation::RS_KeyDigitalSignByP1(const std::string& asn1Msg, const std::string& uid)
{
	UDevice::default();

	JSONStringify data;
	return data;
}

std::string RSFoundation::RS_VerifyDigitalSignByP1(const std::string& base64, const std::string& asn1Msg, const std::string& signature)
{
	UDevice::default();

	JSONStringify data;
	return data;
}

std::string RSFoundation::RS_KeySignByP7(const std::string& textual, const std::string& flag, const std::string& uid)
{
	enum { Attached = 0, Detached };

	UDevice::default();

	short mode = std::stoi(flag);
	std::string signature = SOF_SignMessage(mode, uid, textual);
	if (signature.empty())
	{
		JSONStringify data("unsuccessful", 3325);
		data.addNullObject();
		return data;
	}

	JSONStringify data;
	data.addObject("signdMsg", signature);
	return data;
}

std::string RSFoundation::RS_VerifySignByP7(const std::string& textual, const std::string& signature, const std::string& flag)
{
	enum { Attached = 0, Detached };

	short mode = std::stoi(flag);
	std::string orginal = textual;
	if (Attached == mode)//1 = Detached mode
		orginal.clear();

	if (!SOF_VerifySignedMessage(signature, orginal))
	{
		JSONStringify data("unsuccessful", 3325);
		data.addNullObject();
		return data;
	}

	JSONStringify data;
	data.addNullObject();
	return data;
}

std::string RSFoundation::RS_EncryptFile(std::string& srcfile, std::string& encfile)
{
	UDevice::default();

	assert(!srcfile.empty());

	Poco::File fi(srcfile);
	if (!fi.exists())
		throw Poco::FileExistsException("Source File Not Exists!", srcfile);

	std::string ck = SOF_GenRandom(UDevice::default().random());

	assert(!encfile.empty());

	if (!SOF_EncryptFile(ck, srcfile, encfile)) 
	{
		int error = SOF_GetLastError();
		throw Poco::LogicException("SOF_EncryptFile failed!", error);
	}

	JSONStringify data;
	data.addObject("symKey", ck);
	return data;
}

std::string RSFoundation::RS_DecryptFile(std::string& kv, std::string& encfile, std::string& decdir)
{
	UDevice::default();

	if (encfile.empty())
		throw Poco::FileNotFoundException("Source File Not Exists!", encfile);

	assert(!decdir.empty());

	if (!SOF_DecryptFile(kv, encfile, decdir))
	{
		int error = SOF_GetLastError();
		throw Poco::LogicException("SOF_DecryptFile failed!", error);
	}

	JSONStringify data;
	data.addNullObject();
	return data;
}

std::string RSFoundation::KeyEncryptData(std::string& paintText, std::string& base64)
{
	UDevice::default();

	assert(!paintText.empty() && !base64.empty());
	if (paintText.empty()) return "";
	if (base64.empty())
		throw Poco::LogicException("RS_KeyEncryptData certificate must not be empty!", 0x45);

	std::string encData = SOF_AsEncrypt(base64, paintText);
	if (encData.empty())
	{
		int error = SOF_GetLastError();
		throw Poco::LogicException("RS_KeyEncryptData failed!", error);
	}

	encData.append("@@@");
	encData.append(base64);

	return encData;
}

std::string RSFoundation::RS_KeyEncryptData(std::string paintText, std::string base64)
{
	UDevice::default();

	std::string encData = KeyEncryptData(paintText, base64);

	JSONStringify data;
	data.addObject("encRsKey", encData);
	return data;
}

std::string RSFoundation::KeyDecryptData(std::string& uid, std::string& encRsKey)
{
	UDevice::default();

	std::string pattern("(\\S+)@@@(\\S+)");
	int options = 0;

	RegularExpression re(pattern, options);
	RegularExpression::Match mtch;

	if (!re.match(encRsKey, mtch))
		throw Poco::LogicException("RS_KeyDecryptData enRsKey Exception!", 0x40);

	std::vector<std::string> tags;
	re.split(encRsKey, tags, options);
	std::string& enc = tags[1];
	std::string& cer = tags[2];

	assert(tags.size() > 2);
	std::string kc = SOF_ExportExChangeUserCert(uid);

	if (kc != cer)
		throw Poco::LogicException("certificate error");

	std::string decrypt = SOF_AsDecrypt(uid, enc);
	assert(!decrypt.empty());
	if (decrypt.empty())
	{
		int error = SOF_GetLastError();
		throw Poco::LogicException("SOF_AsDecrypt decrypt Exception", error);
	}

	return decrypt;
}

std::string RSFoundation::RS_KeyDecryptData(std::string& uid, std::string& encRsKey)
{
	UDevice::default();

	std::string decrypt = KeyDecryptData(uid, encRsKey);

	JSONStringify data;
	data.addObject("rsKey", decrypt);
	return data;
}

std::string RSFoundation::RS_KeyEncryptByDigitalEnvelope(const std::string& srcfile, const std::string& encfile, std::string base64)
{
	UDevice::default();

	assert(!srcfile.empty());

	Poco::File fi(srcfile);
	if (!fi.exists())
		throw Poco::FileExistsException("Source File Not Exists!", 0x40);

	std::string ck = SOF_GenRandom(UDevice::default().random());

	assert(!srcfile.empty());

	if (!SOF_EncryptFile(ck, srcfile, encfile))
	{
		int error = SOF_GetLastError();
		throw Poco::LogicException("SOF_EncryptFile encrypt file failed!", error);
	}

	std::string encData = RS_KeyEncryptData(base64, ck);

	JSONStringify data;
	data.addObject("rsKey", encData);
	return data;
}

std::string RSFoundation::RS_KeyDecryptByDigitalEnvelope(std::string& uid, std::string& encfile, std::string& decdir, std::string& encRsKey)
{
	UDevice::default();

	Poco::File encrypt(encfile);
	if (!encrypt.exists())
		throw Poco::FileExistsException("Encrypt File was not existd!", 0x40);

	std::string ck = KeyDecryptData(uid, encRsKey);

	if (!SOF_DecryptFile(ck, encfile, decdir))
	{
		int error = SOF_GetLastError();
		throw Poco::LogicException("SOF_DecryptFile decrypt file failed!", error);
	}
	
	JSONStringify data;
	data.addNullObject();
	return data;
}


std::string RSFoundation::GetSignMethod()
{
	UDevice::default();

	enum { none = 0 };
	unsigned long method = SOF_GetSignMethod();
	if (none == method)
	{
		int error = SOF_GetLastError();
		throw Poco::LogicException("SOF_GetSignMethod was failed!", error);
	}

	JSONStringify data;
	data.addObject("SignMethod", method);
	return data;
}

std::string RSFoundation::GetEncryptMethod()
{
	UDevice::default();

	enum { none = 0 };
	unsigned long method = SOF_GetEncryptMethod();
	if (none == method)
	{
		int error = SOF_GetLastError();
		throw Poco::LogicException("SOF_GetSignMethod was failed!", error);
	}

	JSONStringify data;
	data.addObject("EncryptMethod", method);
	return data;
}

std::string RSFoundation::SignFile(const std::string& uid, const std::string& toSign)
{
	UDevice::default();

	assert(!uid.empty());

	Poco::File fi(toSign);
	if (!fi.exists())
		throw Poco::LogicException("The file that need to sign does not exist!", 0x46);

	std::string signature = SOF_SignFile(uid, fi.path());
	if (signature.empty())
	{
		int error = SOF_GetLastError();
		throw Poco::LogicException("SOF_SignFile was failed!", error);
	}

	JSONStringify data;
	data.addObject("signature", signature);
	return data;
}

std::string RSFoundation::VerifySignedFile(const std::string& base64, const std::string& toVerify, const std::string& signature)
{
	UDevice::default();

	Poco::File fi(toVerify);
	if (!fi.exists())
		throw Poco::LogicException("The file that need to verify does not exist!", 0x46);

	bool val = SOF_VerifySignedFile(base64, fi.path(), signature);
	if (!val)
	{
		int error = SOF_GetLastError();
		throw Poco::LogicException("SOF_VerifySignedData failed!", error);
	}

	JSONStringify ok;
	ok.addNullObject();
	return ok;
}

std::string RSFoundation::DesEncrypt(const std::string& paintText/*, const std::string& base64*/)
{
	UDevice::default();

	std::string ck = SOF_GenRandom(UDevice::default().random());

	assert(!ck.empty());

	std::string encrypt = SOF_EncryptData(ck, paintText);
	if (encrypt.empty())
	{
		int error = SOF_GetLastError();
		throw Poco::LogicException("SOF_EncryptData failed!", error);
	}

	JSONStringify data;
	data.addNullObject();
	data.addObjectItem("encrypt", encrypt);
	data.addObjectItem("symKey", ck);
	return data;
}

std::string RSFoundation::DesDecrypt(const std::string& encryptText, const std::string& kv)
{
	UDevice::default();

	assert(!kv.empty());

	std::string decrypt = SOF_DecryptData(kv, encryptText);
	if (decrypt.empty())
	{
		int error = SOF_GetLastError();
		throw Poco::LogicException("SOF_DecryptData failed!", error);
	}

	JSONStringify data;
	data.addObject("decrypt", decrypt);
	return data;
}