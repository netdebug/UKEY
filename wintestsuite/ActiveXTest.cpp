//
// ActiveXTest.cpp
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//

#include "stdafx.h"
#include "ActiveXTest.h"
#include "CppUnit/TestCaller.h"
#include "CppUnit/TestSuite.h"
#include "Poco/Exception.h"
//#include "Debug/rs_certsafe.tlh"
#include "CDRS_CertSafe0.h"
#include "Poco/JSON/Parser.h"
#include "Poco/Dynamic/Var.h"
#include "CppUnit/TestCase.h"
#include "Poco/Windows936Encoding.h"
#include "Poco/TextConverter.h"

//#include <atlcomcli.h>
//#include <atlbase.h>
//#include <atlcom.h>
//#include <Windows.h>

using Poco::JSON::Parser;
using Poco::Dynamic::Var;
using Poco::JSON::Object;
using Poco::DynamicStruct;

CLSID clsid = { 0xF84C8F57, 0x5A05, 0x4D8C, { 0x82, 0x6D, 0x29, 0x58, 0x9C, 0x7A, 0x12, 0x1C } };
std::string id = "B68CB8DB-AEF3-443B-9376-6741DA07538A";// 网证通
ActiveXTest::ActiveXTest(const std::string& name): CppUnit::TestCase(name)
{
}


ActiveXTest::~ActiveXTest()
{
}
// 获取keysn
void ActiveXTest::RS_KeyGetKeySn()
{

	std::cout << "RS_KeyGetKeySn" << std::endl;
	CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
	CDRS_CertSafe0 a;
	a.CreateDispatch(clsid);
	CString ret = a.RS_KeyGetKeySn();
	std::cout << ret << std::endl;
	std::string code = parseCode(ret.AllocSysString());
	assert(code == "0000");
	CoUninitialize();
}
// 获取KeySnExt
void ActiveXTest::RS_KeyGetKeySnExt()
{
	std::cout << "RS_KeyGetKeySnExt" << std::endl;
	CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
	CDRS_CertSafe0 a;
	a.CreateDispatch(clsid);
	CString ret = a.RS_KeyGetKeySnExt(id.data());
	std::cout << ret << std::endl;
	std::string code = parseCode(ret.AllocSysString());
	assert(code == "0000");
	CoUninitialize();
}

// 获取Userlist
void ActiveXTest::RS_GetUserList()
{
	std::cout << "RS_GetUserList" << std::endl;
	CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
	HRESULT hr;
	_DRS_CertSafe *spUnk = NULL;
	hr = ::CoCreateInstance(clsid, NULL, CLSCTX_ALL, __uuidof(_DRS_CertSafe), (LPVOID *)&spUnk);
	ATLASSERT(SUCCEEDED(hr));
	BSTR ret = spUnk->RS_GetUserList();
	std::cout << ret << std::endl;
	std::string code = parseCode(ret);
	assert(code == "0000");
	spUnk->Release();
	CoUninitialize();
}
std::string signBase64 = "MIID8jCCA5igAwIBAgILEKCWvfcPkyrTtBcwCgYIKoEcz1UBg3UwYjELMAkGA1UEBhMCQ04xJDAiBgNVBAoMG05FVENBIENlcnRpZmljYXRlIEF1dGhvcml0eTEtMCsGA1UEAwwkTkVUQ0EgU00yIFRFU1QwMSBhbmQgRXZhbHVhdGlvbiBDQTAxMB4XDTE5MTEwMTA0NTYwNloXDTI0MTEwMTA0NTYwNlowgdExCzAJBgNVBAYTAkNOMQ8wDQYDVQQIDAZGdWppYW4xMzAxBgNVBAcMKuemj+W7uuecgeemj+W3nuW4gum8k+alvOWMuua5luS4nOi3rzE4OOWPtzE9MDsGA1UECgw056aP5bu655Ge5pyv5L+h5oGv56eR5oqA5pyJ6ZmQ5YWs5Y+477yIU00y5rWL6K+VMe+8iTE9MDsGA1UEAww056aP5bu655Ge5pyv5L+h5oGv56eR5oqA5pyJ6ZmQ5YWs5Y+477yIU00y5rWL6K+VMe+8iTBZMBMGByqGSM49AgEGCCqBHM9VAYItA0IABEOVcp4GW4xHJhxmyt1mouSpHvVcb/JqNy7+bymEi7zBqPar8h0vySkn3ji2H3vkq2OEc5aEacRnHtKV4G5DBH6jggHDMIIBvzAMBgNVHRMBAf8EAjAAMB0GA1UdDgQWBBS0ZwUNWlLjcPiqTwdbYfC7KW59ejAfBgNVHSMEGDAWgBQMe+ticwN1+oxKJAz2jzshZX4X6TBrBgNVHSAEZDBiMGAGCisGAQQBgZJIDQowUjBQBggrBgEFBQcCARZEaHR0cDovL3d3dy5jbmNhLm5ldC9jcy9rbm93bGVkZ2Uvd2hpdGVwYXBlci9jcHMvbmV0Q0F0ZXN0Y2VydGNwcy5wZGYwMwYDVR0fBCwwKjAooCagJIYiaHR0cDovL3Rlc3QuY25jYS5uZXQvY3JsL1NNMkNBLmNybDAOBgNVHQ8BAf8EBAMCBsAwNAYKKwYBBAGBkkgBDgQmDCQzYjBiZDcxZjJjNDYxYWY3MzdhOTI4YWE4M2EyYWNhMUBTMDIwgYYGCCsGAQUFBwEBBHoweDBNBggrBgEFBQcwAYZBaHR0cDovLzE5Mi4xNjguMC43OS9vY3NwY29uc29sZS9vY3NwL29jc3BfY2hlY2tfdXNlcmNlcnRfc3RhdGUuZG8wJwYIKwYBBQUHMAGGG2h0dHA6Ly8xNzIuMC4wLjE6ODAvdGVzdHVybDAKBggqgRzPVQGDdQNIADBFAiEAgOVZet9aulV1KfGFByY+MQezh5hXnhLIjxEgICHMf/4CIAlCCRHrTnDsRiuFbI8LWtJLxvgCu3Cc63OZ+FucYBnY";
std::string encBase64 = "MIID8TCCA5igAwIBAgILILfVFgOOoeveuAswCgYIKoEcz1UBg3UwYjELMAkGA1UEBhMCQ04xJDAiBgNVBAoMG05FVENBIENlcnRpZmljYXRlIEF1dGhvcml0eTEtMCsGA1UEAwwkTkVUQ0EgU00yIFRFU1QwMSBhbmQgRXZhbHVhdGlvbiBDQTAxMB4XDTE5MTEwMTA0NTYwNloXDTI0MTEwMTA0NTYwNlowgdExCzAJBgNVBAYTAkNOMQ8wDQYDVQQIDAZGdWppYW4xMzAxBgNVBAcMKuemj+W7uuecgeemj+W3nuW4gum8k+alvOWMuua5luS4nOi3rzE4OOWPtzE9MDsGA1UECgw056aP5bu655Ge5pyv5L+h5oGv56eR5oqA5pyJ6ZmQ5YWs5Y+477yIU00y5rWL6K+VMe+8iTE9MDsGA1UEAww056aP5bu655Ge5pyv5L+h5oGv56eR5oqA5pyJ6ZmQ5YWs5Y+477yIU00y5rWL6K+VMe+8iTBZMBMGByqGSM49AgEGCCqBHM9VAYItA0IABCZM0faflDXiAajk0HhubUqLkosCRtjxGlc2MLj/ZPRQ1evez0ntYFT4iwesUeguiBssjSCvuezItw6Dmt6I3ZajggHDMIIBvzAMBgNVHRMBAf8EAjAAMB0GA1UdDgQWBBQObmj8QBOlCe/4nQyRKYhzh1xjlDAfBgNVHSMEGDAWgBQMe+ticwN1+oxKJAz2jzshZX4X6TBrBgNVHSAEZDBiMGAGCisGAQQBgZJIDQowUjBQBggrBgEFBQcCARZEaHR0cDovL3d3dy5jbmNhLm5ldC9jcy9rbm93bGVkZ2Uvd2hpdGVwYXBlci9jcHMvbmV0Q0F0ZXN0Y2VydGNwcy5wZGYwMwYDVR0fBCwwKjAooCagJIYiaHR0cDovL3Rlc3QuY25jYS5uZXQvY3JsL1NNMkNBLmNybDAOBgNVHQ8BAf8EBAMCAzgwNAYKKwYBBAGBkkgBDgQmDCQzYjBiZDcxZjJjNDYxYWY3MzdhOTI4YWE4M2EyYWNhMUBTMDIwgYYGCCsGAQUFBwEBBHoweDBNBggrBgEFBQcwAYZBaHR0cDovLzE5Mi4xNjguMC43OS9vY3NwY29uc29sZS9vY3NwL29jc3BfY2hlY2tfdXNlcmNlcnRfc3RhdGUuZG8wJwYIKwYBBQUHMAGGG2h0dHA6Ly8xNzIuMC4wLjE6ODAvdGVzdHVybDAKBggqgRzPVQGDdQNHADBEAiBvp6o+fPO8UIsSIvGhR2VuaOAF8HcbaF4JRLRGbrHd0QIgNxfHRBRmGgNLKRPXV5SfluQ0NNljsq8KAGtYZk9U2sA=";
void ActiveXTest::RS_GetCertBase64String()
{
	std::cout << "RS_GetCertBase64String" << std::endl;
	CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
	HRESULT hr;
	_DRS_CertSafe *spUnk = NULL;
	hr = ::CoCreateInstance(clsid, NULL, CLSCTX_ALL, __uuidof(_DRS_CertSafe), (LPVOID *)&spUnk);
	ATLASSERT(SUCCEEDED(hr));
	// 签名
	BSTR ret = spUnk->RS_GetCertBase64String(id.data(), 1);
	std::cout << ret << std::endl;
	std::string code = parseCode(ret);
	assert(code == "0000");
	signBase64 = parseCertBase64(ret, "certBase64");
	// 加密
	ret = spUnk->RS_GetCertBase64String(id.data(), 2);
	std::cout << ret << std::endl;
	code = parseCode(ret);
	assert(code == "0000");
	encBase64 = parseCertBase64(ret, "certBase64");

	spUnk->Release();
	CoUninitialize();

}
//登录
void ActiveXTest::RS_CertLogin()
{
	std::cout << "RS_CertLogin" << std::endl;
	CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
	CDRS_CertSafe0 a;
	a.CreateDispatch(clsid);
	CString ret = a.RS_CertLogin(id.data(), "");
	std::cout << ret << std::endl;
	std::string code = parseCode(ret.AllocSysString());
	assert(code == "0000");
	CoUninitialize();
}
// 获取剩余次数
void ActiveXTest::RS_GetPinRetryCount()
{
	std::cout << "RS_GetPinRetryCount" << std::endl;
	CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
	CDRS_CertSafe0 a;
	a.CreateDispatch(clsid);
	CString ret = a.RS_GetPinRetryCount(id.data());
	std::cout << ret << std::endl;
	std::string code = parseCode(ret.AllocSysString());
	assert(code == "0000");
	CoUninitialize();
}
//修改密码
void ActiveXTest::RS_ChangePassWd()
{
	std::cout << "RS_ChangePassWd" << std::endl;
	CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
	CDRS_CertSafe0 a;
	a.CreateDispatch(clsid);
	CString ret = a.RS_ChangePassWd(id.data(), "", "");
	std::cout << ret << std::endl;
	std::string code = parseCode(ret.AllocSysString());
	assert(code == "0000");
	CoUninitialize();
}

std::string signMsg1 = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAADO/jxQPm/UaysTi7QxQv3LPpXG7UBlJ1ZGja0CamzXOwAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAUocai4lKE534TgtDchsWV5dBjrjVC8xTFmaMyx3JQ1g=";
// p1签名
void ActiveXTest::RS_KeySignByP1()
{
	std::cout << "RS_KeySignByP1" << std::endl;
	CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
	HRESULT hr;
	_DRS_CertSafe *spUnk = NULL;
	hr = ::CoCreateInstance(clsid, NULL, CLSCTX_ALL, __uuidof(_DRS_CertSafe), (LPVOID *)&spUnk);
	ATLASSERT(SUCCEEDED(hr));
	BSTR ret = spUnk->RS_KeySignByP1("123ABC一二三", id.data());//signdMsg
	std::cout << ret << std::endl;
	std::string code = parseCode(ret);
	assert(code == "0000");
	signMsg1 = parseCertBase64(ret, "signdMsg");
	spUnk->Release();
	CoUninitialize();
}
// p1验签
void ActiveXTest::RS_VerifySignByP1()
{
	std::cout << "RS_VerifySignByP1" << std::endl;
	CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
	HRESULT hr;
	_DRS_CertSafe *spUnk = NULL;
	hr = ::CoCreateInstance(clsid, NULL, CLSCTX_ALL, __uuidof(_DRS_CertSafe), (LPVOID *)&spUnk);
	ATLASSERT(SUCCEEDED(hr));
	BSTR ret = spUnk->RS_VerifySignByP1(signBase64.data(), "123ABC一二三", signMsg1.data());
	std::cout << ret << std::endl;
	std::string code = parseCode(ret);
	assert(code == "0000");
	spUnk->Release();
	CoUninitialize();
}

std::string encStr = "7t3u3bQAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAFKmDw5f+j4kSaEuvd1TU52KfwHSEVte4lmZO5lR2/WOAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABJ6YsFCAL4uKUJ5F9f4XEQq0bkqH6x7uIwBB324+y8cUg34N8Z5kPHTs8mdhhYp6FfaMAGz5jPh82/0/mKgLTMEAAAACPl6kwAT6cLOvkaCTJbTNndDt0OEAAAAGOUXGDfDTXXRVL9YtdCV2A=@@@MIID8TCCA5igAwIBAgILILfVFgOOoeveuAswCgYIKoEcz1UBg3UwYjELMAkGA1UEBhMCQ04xJDAiBgNVBAoMG05FVENBIENlcnRpZmljYXRlIEF1dGhvcml0eTEtMCsGA1UEAwwkTkVUQ0EgU00yIFRFU1QwMSBhbmQgRXZhbHVhdGlvbiBDQTAxMB4XDTE5MTEwMTA0NTYwNloXDTI0MTEwMTA0NTYwNlowgdExCzAJBgNVBAYTAkNOMQ8wDQYDVQQIDAZGdWppYW4xMzAxBgNVBAcMKuemj+W7uuecgeemj+W3nuW4gum8k+alvOWMuua5luS4nOi3rzE4OOWPtzE9MDsGA1UECgw056aP5bu655Ge5pyv5L+h5oGv56eR5oqA5pyJ6ZmQ5YWs5Y+477yIU00y5rWL6K+VMe+8iTE9MDsGA1UEAww056aP5bu655Ge5pyv5L+h5oGv56eR5oqA5pyJ6ZmQ5YWs5Y+477yIU00y5rWL6K+VMe+8iTBZMBMGByqGSM49AgEGCCqBHM9VAYItA0IABCZM0faflDXiAajk0HhubUqLkosCRtjxGlc2MLj/ZPRQ1evez0ntYFT4iwesUeguiBssjSCvuezItw6Dmt6I3ZajggHDMIIBvzAMBgNVHRMBAf8EAjAAMB0GA1UdDgQWBBQObmj8QBOlCe/4nQyRKYhzh1xjlDAfBgNVHSMEGDAWgBQMe+ticwN1+oxKJAz2jzshZX4X6TBrBgNVHSAEZDBiMGAGCisGAQQBgZJIDQowUjBQBggrBgEFBQcCARZEaHR0cDovL3d3dy5jbmNhLm5ldC9jcy9rbm93bGVkZ2Uvd2hpdGVwYXBlci9jcHMvbmV0Q0F0ZXN0Y2VydGNwcy5wZGYwMwYDVR0fBCwwKjAooCagJIYiaHR0cDovL3Rlc3QuY25jYS5uZXQvY3JsL1NNMkNBLmNybDAOBgNVHQ8BAf8EBAMCAzgwNAYKKwYBBAGBkkgBDgQmDCQzYjBiZDcxZjJjNDYxYWY3MzdhOTI4YWE4M2EyYWNhMUBTMDIwgYYGCCsGAQUFBwEBBHoweDBNBggrBgEFBQcwAYZBaHR0cDovLzE5Mi4xNjguMC43OS9vY3NwY29uc29sZS9vY3NwL29jc3BfY2hlY2tfdXNlcmNlcnRfc3RhdGUuZG8wJwYIKwYBBQUHMAGGG2h0dHA6Ly8xNzIuMC4wLjE6ODAvdGVzdHVybDAKBggqgRzPVQGDdQNHADBEAiBvp6o+fPO8UIsSIvGhR2VuaOAF8HcbaF4JRLRGbrHd0QIgNxfHRBRmGgNLKRPXV5SfluQ0NNljsq8KAGtYZk9U2sA=";
//非对称加密数据
void ActiveXTest::RS_KeyEncryptData()
{
	std::cout << "RS_KeyEncryptData" << std::endl;
	CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
	CDRS_CertSafe0 a;
	a.CreateDispatch(clsid);
	CString ret = a.RS_KeyEncryptData("123ABC一二三", encBase64.data());
	std::cout << ret << std::endl;
	std::string code = parseCode(ret.AllocSysString());
	assert(code == "0000");
	encStr = parseCertBase64(ret.AllocSysString(), "encRsKey");
	CoUninitialize();
}
//非对称解密数据
void ActiveXTest::RS_KeyDecryptData()
{
	std::cout << "RS_KeyDecryptData" << std::endl;
	CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
	HRESULT hr;
	_DRS_CertSafe *spUnk = NULL;
	hr = ::CoCreateInstance(clsid, NULL, CLSCTX_ALL, __uuidof(_DRS_CertSafe), (LPVOID *)&spUnk);
	ATLASSERT(SUCCEEDED(hr));
	BSTR ret = spUnk->RS_KeyDecryptData(encStr.data(), id.data());//signdMsg
	std::cout << ret << std::endl;
	
	std::string code = parseCode(ret);
	assert(code == "0000");

	std::string rskey = parseCertBase64(ret, "rsKey");
	std::string gbkstring = UTF8EncodingGBK(rskey);
	assert(gbkstring == "123ABC一二三");
	spUnk->Release();
	CoUninitialize();
}
//获取证书信息
void ActiveXTest::RS_GetCertInfo(){
	std::cout << "RS_GetCertInfo" << std::endl;
	CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
	HRESULT hr;
	_DRS_CertSafe *spUnk = NULL;
	hr = ::CoCreateInstance(clsid, NULL, CLSCTX_ALL, __uuidof(_DRS_CertSafe), (LPVOID *)&spUnk);
	ATLASSERT(SUCCEEDED(hr));
	BSTR ret = spUnk->RS_GetCertInfo(signBase64.data(), "1");
	std::cout << ret << std::endl;
	std::string code = parseCode(ret);
	assert(code == "0000");
	spUnk->Release();
	CoUninitialize();
}

std::string signMsg7 = "MIIFEQYKKoEcz1UGAQQCAqCCBQEwggT9AgEBMQ4wDAYIKoEcz1UBgxEFADAMBgoqgRzPVQYBBAIBoIID9jCCA/IwggOYoAMCAQICCxCglr33D5Mq07QXMAoGCCqBHM9VAYN1MGIxCzAJBgNVBAYTAkNOMSQwIgYDVQQKDBtORVRDQSBDZXJ0aWZpY2F0ZSBBdXRob3JpdHkxLTArBgNVBAMMJE5FVENBIFNNMiBURVNUMDEgYW5kIEV2YWx1YXRpb24gQ0EwMTAeFw0xOTExMDEwNDU2MDZaFw0yNDExMDEwNDU2MDZaMIHRMQswCQYDVQQGEwJDTjEPMA0GA1UECAwGRnVqaWFuMTMwMQYDVQQHDCrnpo/lu7rnnIHnpo/lt57luILpvJPmpbzljLrmuZbkuJzot68xODjlj7cxPTA7BgNVBAoMNOemj+W7uueRnuacr+S/oeaBr+enkeaKgOaciemZkOWFrOWPuO+8iFNNMua1i+ivlTHvvIkxPTA7BgNVBAMMNOemj+W7uueRnuacr+S/oeaBr+enkeaKgOaciemZkOWFrOWPuO+8iFNNMua1i+ivlTHvvIkwWTATBgcqhkjOPQIBBggqgRzPVQGCLQNCAARDlXKeBluMRyYcZsrdZqLkqR71XG/yajcu/m8phIu8waj2q/IdL8kpJ944th975KtjhHOWhGnEZx7SleBuQwR+o4IBwzCCAb8wDAYDVR0TAQH/BAIwADAdBgNVHQ4EFgQUtGcFDVpS43D4qk8HW2HwuylufXowHwYDVR0jBBgwFoAUDHvrYnMDdfqMSiQM9o87IWV+F+kwawYDVR0gBGQwYjBgBgorBgEEAYGSSA0KMFIwUAYIKwYBBQUHAgEWRGh0dHA6Ly93d3cuY25jYS5uZXQvY3Mva25vd2xlZGdlL3doaXRlcGFwZXIvY3BzL25ldENBdGVzdGNlcnRjcHMucGRmMDMGA1UdHwQsMCowKKAmoCSGImh0dHA6Ly90ZXN0LmNuY2EubmV0L2NybC9TTTJDQS5jcmwwDgYDVR0PAQH/BAQDAgbAMDQGCisGAQQBgZJIAQ4EJgwkM2IwYmQ3MWYyYzQ2MWFmNzM3YTkyOGFhODNhMmFjYTFAUzAyMIGGBggrBgEFBQcBAQR6MHgwTQYIKwYBBQUHMAGGQWh0dHA6Ly8xOTIuMTY4LjAuNzkvb2NzcGNvbnNvbGUvb2NzcC9vY3NwX2NoZWNrX3VzZXJjZXJ0X3N0YXRlLmRvMCcGCCsGAQUFBzABhhtodHRwOi8vMTcyLjAuMC4xOjgwL3Rlc3R1cmwwCgYIKoEcz1UBg3UDSAAwRQIhAIDlWXrfWrpVdSnxhQcmPjEHs4eYV54SyI8RICAhzH/+AiAJQgkR605w7EYrhWyPC1rSS8b4ArtwnOtzmfhbnGAZ2DGB3zCB3AIBATBxMGIxCzAJBgNVBAYTAkNOMSQwIgYDVQQKDBtORVRDQSBDZXJ0aWZpY2F0ZSBBdXRob3JpdHkxLTArBgNVBAMMJE5FVENBIFNNMiBURVNUMDEgYW5kIEV2YWx1YXRpb24gQ0EwMQILEKCWvfcPkyrTtBcwDAYIKoEcz1UBgxEFADANBgkqgRzPVQGCLQEFAARHMEUCIQD5Il+BqZ6R13oodl3Qrgmwi317ATGja3EIFi60QVmVvwIgRI9teezgvIdsjsFpJvErLJVPvpTzGqy5SfnK+9GajIc=";
// p7签名
void ActiveXTest::RS_KeySignByP7(){
	std::cout << "RS_KeySignByP7" << std::endl;
	CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
	HRESULT hr;
	_DRS_CertSafe *spUnk = NULL;
	hr = ::CoCreateInstance(clsid, NULL, CLSCTX_ALL, __uuidof(_DRS_CertSafe), (LPVOID *)&spUnk);
	ATLASSERT(SUCCEEDED(hr));
	BSTR ret = spUnk->RS_KeySignByP7("123ABC一二三", "1",id.data());//signdMsg
	std::cout << ret << std::endl;
	std::string code = parseCode(ret);
	assert(code == "0000");
	signMsg7 = parseCertBase64(ret, "signdMsg");
	spUnk->Release();
	CoUninitialize();
}
// p7验签
void ActiveXTest::RS_VerifySignByP7(){
	std::cout << "RS_VerifySignByP7" << std::endl;
	CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
	HRESULT hr;
	_DRS_CertSafe *spUnk = NULL;
	hr = ::CoCreateInstance(clsid, NULL, CLSCTX_ALL, __uuidof(_DRS_CertSafe), (LPVOID *)&spUnk);
	ATLASSERT(SUCCEEDED(hr));
	BSTR ret = spUnk->RS_VerifySignByP7("123ABC一二三", signMsg7.data(), "1");
	std::cout << ret << std::endl;
	std::string code = parseCode(ret);
	assert(code == "0000");
	spUnk->Release();
	CoUninitialize();
}
std::string transid = "1000020191231023032174787047520";
std::string codeStr = "{ \"action\" : \"1\", \"authIdent\" : \"fc4740d6ed0a4053b2ee26179b93a7ab100120191231102955\" }";
//云签登录生成二维码
void ActiveXTest::RS_CloudLoginAuth(){
	//RS_GetTransid();
	std::cout << "RS_CloudLoginAuth" << std::endl;
	CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
	HRESULT hr;
	_DRS_CertSafe *spUnk = NULL;
	hr = ::CoCreateInstance(clsid, NULL, CLSCTX_ALL, __uuidof(_DRS_CertSafe), (LPVOID *)&spUnk);
	ATLASSERT(SUCCEEDED(hr));
	
	BSTR ret = spUnk->RS_CloudLoginAuth(transid.data());
	std::cout << ret << std::endl;
	std::string code = parseCode(ret);
	assert(code == "0000");
	//获取data数据生成二维码
	codeStr = parseData(ret);
	CoUninitialize();
}
//云签签章授权生成二维码
void ActiveXTest::RS_CloudSealAuth(){
	std::cout << "RS_CloudSealAuth" << std::endl;
	CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
	HRESULT hr;
	_DRS_CertSafe *spUnk = NULL;
	hr = ::CoCreateInstance(clsid, NULL, CLSCTX_ALL, __uuidof(_DRS_CertSafe), (LPVOID *)&spUnk);
	ATLASSERT(SUCCEEDED(hr));
	BSTR ret = spUnk->RS_CloudSealAuth(transid.data());
	std::cout << ret << std::endl;
	std::string code = parseCode(ret);
	assert(code == "0000");
	//获取data数据生成二维码
	codeStr = parseData(ret);
	CoUninitialize();
}

std::string tokenL = "";
std::string tokenS = "";
std::string keysn = "";
//获取授权接口
void ActiveXTest::RS_CloudGetAuth(){
	std::cout << "RS_CloudGetAuth" << std::endl;
	CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
	HRESULT hr;
	_DRS_CertSafe *spUnk = NULL;
	hr = ::CoCreateInstance(clsid, NULL, CLSCTX_ALL, __uuidof(_DRS_CertSafe), (LPVOID *)&spUnk);
	ATLASSERT(SUCCEEDED(hr));
	BSTR ret = spUnk->RS_CloudGetAuth(transid.data());
	std::cout << ret << std::endl;
	std::string code = parseCode(ret);
	assert(code == "0000");
	tokenL = parseCertBase64(ret, "token");
	keysn = parseCertBase64(ret, "keySn");
	CoUninitialize();
}
// 获取签章列表
void ActiveXTest::RS_CloudGetSealList(){
	std::cout << "RS_CloudGetSealList" << std::endl;
	CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
	HRESULT hr;
	_DRS_CertSafe *spUnk = NULL;
	hr = ::CoCreateInstance(clsid, NULL, CLSCTX_ALL, __uuidof(_DRS_CertSafe), (LPVOID *)&spUnk);
	ATLASSERT(SUCCEEDED(hr));
	BSTR ret = spUnk->RS_CloudGetSealList(tokenS.data());
	std::cout << ret << std::endl;
	std::string code = parseCode(ret);
	assert(code == "0000");
	CoUninitialize();
}

// p7签名
void ActiveXTest::RS_CloudSignByP7(){
	//RS_CloudGetAuth();		// 获取授权结果
	//RS_CloudGetSealList();	// 获取签章列表
	//RS_GetTransid();		// 新的transid
	std::cout << "RS_CloudSignByP7" << std::endl;
	CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
	HRESULT hr;
	_DRS_CertSafe *spUnk = NULL;
	hr = ::CoCreateInstance(clsid, NULL, CLSCTX_ALL, __uuidof(_DRS_CertSafe), (LPVOID *)&spUnk);
	ATLASSERT(SUCCEEDED(hr));
	BSTR ret = spUnk->RS_CloudSignByP7("123一二三abc", keysn.data(), transid.data(), tokenS.data());
	std::cout << ret << std::endl;
	std::string code = parseCode(ret);
	assert(code == "0000");
	CoUninitialize();
}

// 获取签名结果
void ActiveXTest::RS_CloudGetSignResult()
{
	std::cout << "RS_CloudGetSignResult" << std::endl;
	CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
	HRESULT hr;
	_DRS_CertSafe *spUnk = NULL;
	hr = ::CoCreateInstance(clsid, NULL, CLSCTX_ALL, __uuidof(_DRS_CertSafe), (LPVOID *)&spUnk);
	ATLASSERT(SUCCEEDED(hr));
	//这个id要和p7id一样
	BSTR ret = spUnk->RS_CloudGetSignResult(transid.data());
	std::cout << ret << std::endl;
	std::string code = parseCode(ret);
	assert(code == "0000");
	CoUninitialize();
}

// 注销授权接口
void ActiveXTest::RS_CloudLogoutAuth(){
	std::cout << "RS_CloudLogoutAuth" << std::endl;
	CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
	HRESULT hr;
	_DRS_CertSafe *spUnk = NULL;
	hr = ::CoCreateInstance(clsid, NULL, CLSCTX_ALL, __uuidof(_DRS_CertSafe), (LPVOID *)&spUnk);
	ATLASSERT(SUCCEEDED(hr));
	BSTR ret = spUnk->RS_CloudLogoutAuth(tokenL.data());
	std::cout << ret << std::endl;
	std::string code = parseCode(ret);
	assert(code == "0000");
	CoUninitialize();
}

std::string tokenE = "";
// 加密授权接口
void ActiveXTest::RS_CloudEncryptAuth(){
	std::cout << "RS_CloudEncryptAuth" << std::endl;
	CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
	HRESULT hr;
	_DRS_CertSafe *spUnk = NULL;
	hr = ::CoCreateInstance(clsid, NULL, CLSCTX_ALL, __uuidof(_DRS_CertSafe), (LPVOID *)&spUnk);
	ATLASSERT(SUCCEEDED(hr));
	BSTR ret = spUnk->RS_CloudEncryptAuth(transid.data());
	std::cout << ret << std::endl;
	std::string code = parseCode(ret);
	assert(code == "0000");
	//获取data数据生成二维码
	codeStr = parseData(ret);
	CoUninitialize();
}

std::string tokenD = "";
// 界面授权接口
void ActiveXTest::RS_CloudDevryptAuth() {
	std::cout << "RS_CloudDevryptAuth" << std::endl;
	CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
	HRESULT hr;
	_DRS_CertSafe *spUnk = NULL;
	hr = ::CoCreateInstance(clsid, NULL, CLSCTX_ALL, __uuidof(_DRS_CertSafe), (LPVOID *)&spUnk);
	ATLASSERT(SUCCEEDED(hr));
	BSTR ret = spUnk->RS_CloudDevryptAuth(transid.data());
	std::cout << ret << std::endl;
	std::string code = parseCode(ret);
	assert(code == "0000");
	//获取data数据生成二维码
	codeStr = parseData(ret);
	CoUninitialize();
}

std::string encSymkey = "";
// 非对称加密数据
void ActiveXTest::RS_CloudEncryptData(){
	//RS_GetTransid();
	std::cout << "RS_CloudEncryptData" << std::endl;
	CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
	HRESULT hr;
	_DRS_CertSafe *spUnk = NULL;
	hr = ::CoCreateInstance(clsid, NULL, CLSCTX_ALL, __uuidof(_DRS_CertSafe), (LPVOID *)&spUnk);
	ATLASSERT(SUCCEEDED(hr));
	BSTR ret = spUnk->RS_CloudEncryptData("123一二三abc", transid.data(), tokenE.data());
	std::cout << ret << std::endl;
	std::string code = parseCode(ret);
	assert(code == "0000");
	encSymkey = parseCertBase64(ret, "encSymKey");
	CoUninitialize();
}
// 非对称解密数据
void ActiveXTest::RS_CloudDevryptData(){
	std::cout << "RS_CloudDevryptData" << std::endl;
	CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
	HRESULT hr;
	_DRS_CertSafe *spUnk = NULL;
	hr = ::CoCreateInstance(clsid, NULL, CLSCTX_ALL, __uuidof(_DRS_CertSafe), (LPVOID *)&spUnk);
	ATLASSERT(SUCCEEDED(hr));
	BSTR ret = spUnk->RS_CloudDevryptData(encSymkey.data(), "",transid.data(), tokenD.data());
	std::cout << ret << std::endl;
	std::string code = parseCode(ret);
	assert(code == "0000");
	std::string sym = parseCertBase64(ret, "symKey");
	assert(sym == "123一二三abc");
	CoUninitialize();
}
// 对称加密文件
void ActiveXTest::RS_CloudEncryptFile() {
	std::cout << "RS_CloudEncryptFile" << std::endl;
	CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
	HRESULT hr;
	_DRS_CertSafe *spUnk = NULL;
	hr = ::CoCreateInstance(clsid, NULL, CLSCTX_ALL, __uuidof(_DRS_CertSafe), (LPVOID *)&spUnk);
	ATLASSERT(SUCCEEDED(hr));
	BSTR ret = spUnk->RS_CloudEncryptFile("F:\\Test\\doc.txt", "F:\\Test\\enc.txt", transid.data(), tokenE.data());
	std::cout << ret << std::endl;
	std::string code = parseCode(ret);
	assert(code == "0000");
	CoUninitialize();
}
// 对称解密文件
void ActiveXTest::RS_CloudDevryptFile(){
	std::cout << "RS_CloudDevryptFile" << std::endl;
	CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
	HRESULT hr;
	_DRS_CertSafe *spUnk = NULL;
	hr = ::CoCreateInstance(clsid, NULL, CLSCTX_ALL, __uuidof(_DRS_CertSafe), (LPVOID *)&spUnk);
	ATLASSERT(SUCCEEDED(hr));
	BSTR ret = spUnk->RS_CloudDevryptFile("F:\\Test\\enc.txt", "F:\\Test\\dnc.txt", "",transid.data(), tokenD.data());
	std::cout << ret << std::endl;
	std::string code = parseCode(ret);
	assert(code == "0000");
	CoUninitialize();
}

// 接收非对称解密结果
void ActiveXTest::RS_CloudReceiveDevryptResult(){
	std::cout << "RS_CloudReceiveDevryptResult" << std::endl;
	CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
	HRESULT hr;
	_DRS_CertSafe *spUnk = NULL;
	hr = ::CoCreateInstance(clsid, NULL, CLSCTX_ALL, __uuidof(_DRS_CertSafe), (LPVOID *)&spUnk);
	ATLASSERT(SUCCEEDED(hr));
	BSTR ret = spUnk->RS_CloudReceiveDevryptResult(transid.data(), tokenD.data());
	std::cout << ret << std::endl;
	std::string code = parseCode(ret);
	assert(code == "0000");
	CoUninitialize();
}

//获取企业证书信息
void ActiveXTest::RS_CloudGetCompanyCert(){
	std::cout << "RS_CloudGetCompanyCert" << std::endl;
	CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
	HRESULT hr;
	_DRS_CertSafe *spUnk = NULL;
	hr = ::CoCreateInstance(clsid, NULL, CLSCTX_ALL, __uuidof(_DRS_CertSafe), (LPVOID *)&spUnk);
	ATLASSERT(SUCCEEDED(hr));
	BSTR ret = spUnk->RS_CloudGetCompanyCert(transid.data(), tokenE.data());//或者tokenD
	std::cout << ret << std::endl;
	std::string code = parseCode(ret);
	assert(code == "0000");
	CoUninitialize();
}

//证书授权接口
std::string tokenC = "";
void ActiveXTest::RS_CloudGetCertAuth(){
	std::cout << "RS_CloudEncryptFile" << std::endl;
	CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
	HRESULT hr;
	_DRS_CertSafe *spUnk = NULL;
	hr = ::CoCreateInstance(clsid, NULL, CLSCTX_ALL, __uuidof(_DRS_CertSafe), (LPVOID *)&spUnk);
	ATLASSERT(SUCCEEDED(hr));
	BSTR ret = spUnk->RS_CloudGetCertAuth(transid.data());
	std::cout << ret << std::endl;
	std::string code = parseCode(ret);
	assert(code == "0000");
	//获取data数据生成二维码
	codeStr = parseData(ret);
	CoUninitialize();
}
// 获取证书公钥信息接口
void ActiveXTest::RS_CloudGetCertBase64(){
	std::cout << "RS_CloudGetCertBase64" << std::endl;
	CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
	HRESULT hr;
	_DRS_CertSafe *spUnk = NULL;
	hr = ::CoCreateInstance(clsid, NULL, CLSCTX_ALL, __uuidof(_DRS_CertSafe), (LPVOID *)&spUnk);
	ATLASSERT(SUCCEEDED(hr));
	BSTR ret = spUnk->RS_CloudGetCertBase64(transid.data(), tokenC.data());
	std::cout << ret << std::endl;
	std::string code = parseCode(ret);
	assert(code == "0000");
	CoUninitialize();
}
void ActiveXTest::RS_CloudLogout(){
	std::cout << "RS_CloudLogout" << std::endl;
	CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
	HRESULT hr;
	_DRS_CertSafe *spUnk = NULL;
	hr = ::CoCreateInstance(clsid, NULL, CLSCTX_ALL, __uuidof(_DRS_CertSafe), (LPVOID *)&spUnk);
	ATLASSERT(SUCCEEDED(hr));
	BSTR ret = spUnk->RS_CloudLogout("");
	std::cout << ret << std::endl;
	std::string code = parseCode(ret);
	assert(code == "0000");
	CoUninitialize();
}
//获取key状态
void ActiveXTest::RS_KeyStatus(){
	std::cout << "RS_KeyStatus" << std::endl;
	CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
	CDRS_CertSafe0 a;
	a.CreateDispatch(clsid);
	CString ret = a.RS_KeyStatus(id.data());
	std::cout << ret << std::endl;
	std::string code = parseCode(ret.AllocSysString());
	assert(code == "0000");
	CoUninitialize();
}
//配置参数设置
void ActiveXTest::RS_ConfigParameters(){
	std::cout << "RS_ConfigParameters" << std::endl;
	CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
	CDRS_CertSafe0 a;
	a.CreateDispatch(clsid);
	CString ret = a.RS_ConfigParameters("rsigncloud", "http://192.168.1.243:8080/rssigncloud/post.json");
	std::cout << ret << std::endl;
	std::string code = parseCode(ret.AllocSysString());
	assert(code == "0000");
	CoUninitialize();
}
// 获取配置参数
void ActiveXTest::RS_GetParameters(){
	std::cout << "RS_GetParameters" << std::endl;
	CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
	CDRS_CertSafe0 a;
	a.CreateDispatch(clsid);
	CString ret = a.RS_GetParameters("rsigncloud");
	std::cout << ret << std::endl;
	std::string code = parseCode(ret.AllocSysString());
	assert(code == "0000");
	CoUninitialize();
}

//生成二维码
void ActiveXTest::RS_GreateQRCode()
{
	std::cout << "RS_GreateQRCode" << std::endl;
	CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
	CDRS_CertSafe0 a;
	a.CreateDispatch(clsid);
	CString ret = a.RS_GreateQRCode(codeStr.data(), "F:\\Test\\111.bmp");
	std::cout << ret << std::endl;
	std::string code = parseCode(ret.AllocSysString());
	assert(code == "0000");
	CoUninitialize();
}

void ActiveXTest::RS_GetTransid()
{
	std::cout << "RS_GetTransid" << std::endl;
	CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
	CDRS_CertSafe0 a;
	a.CreateDispatch(clsid);
	CString ret = a.RS_GetTransid("10000");
	std::cout << ret << std::endl;
	std::string code = parseCode(ret.AllocSysString());
	assert(code == "0000");
	transid = parseCertBase64(ret.AllocSysString(), "transid");
	CoUninitialize();
}

std::string symKey = "9uyoXQYg0EH1obobOWfmYYZaedWwx8OGl3NEaCFb5ygk0x9kMkvqV2KqyhaiSxKP/g==";
void ActiveXTest::RS_EncryptFile(){
	std::cout << "RS_EncryptFile" << std::endl;
	CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
	CDRS_CertSafe0 a;
	a.CreateDispatch(clsid);
	CString ret = a.RS_EncryptFile("F:\\Test\\doc.txt", "F:\\Test\\enc.txt");
	std::cout << ret << std::endl;
	std::string code = parseCode(ret.AllocSysString());
	assert(code == "0000");
	symKey = parseCertBase64(ret.AllocSysString(), "symKey");
	CoUninitialize();
}
void ActiveXTest::RS_DevryptFile(){
	std::cout << "RS_DevryptFile" << std::endl;
	CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
	CDRS_CertSafe0 a;
	a.CreateDispatch(clsid);
	CString ret = a.RS_DevryptFile(symKey.data(), "F:\\Test\\enc.txt", "F:\\Test\\dnc.txt");
	std::cout << ret << std::endl;
	std::string code = parseCode(ret.AllocSysString());
	assert(code == "0000");
	CoUninitialize();
}
void ActiveXTest::RS_VerifyIdentity(){
	std::cout << "RS_VerifyIdentity" << std::endl;
	CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
	HRESULT hr;
	_DRS_CertSafe *spUnk = NULL;
	hr = ::CoCreateInstance(clsid, NULL, CLSCTX_ALL, __uuidof(_DRS_CertSafe), (LPVOID *)&spUnk);
	ATLASSERT(SUCCEEDED(hr));
	BSTR ret = spUnk->RS_VerifyIdentity(signBase64.data(), "");
	std::cout << ret << std::endl;
	std::string code = parseCode(ret);
	assert(code == "0000");
	spUnk->Release();
	CoUninitialize();

}
void ActiveXTest::RS_KeyEncryptFile(){

	std::cout << "RS_KeyEncryptFile" << std::endl;
	CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
	HRESULT hr;
	_DRS_CertSafe *spUnk = NULL;
	hr = ::CoCreateInstance(clsid, NULL, CLSCTX_ALL, __uuidof(_DRS_CertSafe), (LPVOID *)&spUnk);
	ATLASSERT(SUCCEEDED(hr));
	BSTR ret = spUnk->RS_KeyEncryptFile("F:\\Test\\keydoc.txt", "F:\\Test\\keyenc.txt", encBase64.data());
	std::cout << ret << std::endl;
	std::string code = parseCode(ret);
	assert(code == "0000");
	spUnk->Release();
	CoUninitialize();
}
void ActiveXTest::RS_KeyDecryptFile(){
	std::cout << "RS_KeyDecryptFile" << std::endl;
	CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
	HRESULT hr;
	_DRS_CertSafe *spUnk = NULL;
	hr = ::CoCreateInstance(clsid, NULL, CLSCTX_ALL, __uuidof(_DRS_CertSafe), (LPVOID *)&spUnk);
	ATLASSERT(SUCCEEDED(hr));
	BSTR ret = spUnk->RS_KeyDecryptFile("F:\\Test\\keyenc.txt", "F:\\Test\\keydnc.txt", id.data());
	std::cout << ret << std::endl;
	std::string code = parseCode(ret);
	assert(code == "0000");
	spUnk->Release();
	CoUninitialize();
}

void ActiveXTest::CodeSample()
{
	std::string code = "code";


	//assert(!code.empty());
	//assert(code == "sample");

	std::cout << "ActiveXTest test function" << std::endl;
	CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
	RS_GetTransid();
	RS_CloudLoginAuth();
	RS_GreateQRCode();
	/*HRESULT hr;
	_DRS_CertSafe *spUnk = NULL;
	hr = ::CoCreateInstance(clsid, NULL, CLSCTX_ALL, __uuidof(_DRS_CertSafe), (LPVOID *)&spUnk);
	ATLASSERT(SUCCEEDED(hr));
	BSTR ret;
	try
	{
		ret = spUnk->RS_GetUserList();
		int a;
	}
	catch (_com_error& e)
	{
		const wchar_t* pDes = e.Description();
		const char* pMsg = e.ErrorMessage();
		wprintf(L"create instance fail message = %s!%s", pDes, pMsg);
	}
	
	//CComDispatchDriver spDisp(spUnk);
	CComVariant result, vOrg, vSig, vResult;
	/ *LPOLESTR pwFunName = L"RS_GetUserList";
	DISPID dispID;
	pDisp->GetIDsOfNames(IID_NULL, &pwFunName, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
	DISPPARAMS dispparams = { NULL, NULL, 0, 0 };
	hr = pDisp->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_METHOD, &dispparams, NULL, NULL, NULL);* /
	//spDisp.Invoke0(L"RS_GetUserList", &result);
	BSTR ul = result.bstrVal;
	spUnk->Release();*/
	CoUninitialize();
}


void ActiveXTest::setUp()
{
}


void ActiveXTest::tearDown()
{
}


std::string ActiveXTest::parseCode(BSTR str)
{
	std::string retStr = _com_util::ConvertBSTRToString(str); //解析返回值
	retStr = GBKEncodingUTF8(retStr);
	Parser ps;
	Var res = ps.parse(retStr);
	assert(res.type() == typeid(Object::Ptr));

	Object::Ptr object = res.extract<Object::Ptr>();
	assert(object);
	DynamicStruct ds = *object;
	return ds["code"].toString();
}

std::string ActiveXTest::parseData(BSTR str)
{
	std::string retStr = _com_util::ConvertBSTRToString(str); //解析返回值
	retStr = GBKEncodingUTF8(retStr);
	Parser ps;
	Var res = ps.parse(retStr);
	assert(res.type() == typeid(Object::Ptr));

	Object::Ptr object = res.extract<Object::Ptr>();
	assert(object);
	DynamicStruct ds = *object;
	std::string data = ds["data"].toString();
	return UTF8EncodingGBK(data);
}

std::string ActiveXTest::parseCertBase64(BSTR str, std::string name)
{
	std::string retStr = _com_util::ConvertBSTRToString(str); //解析返回值
	retStr = GBKEncodingUTF8(retStr);
	Parser ps;
	Var res = ps.parse(retStr);
	assert(res.type() == typeid(Object::Ptr));

	Object::Ptr object = res.extract<Object::Ptr>();
	assert(object);
	DynamicStruct ds = *object;
	std::string data = ds["data"][name].toString();
	return UTF8EncodingGBK(data);
}

std::string ActiveXTest::GBKEncodingUTF8(const std::string & inEncoding)
{
	std::string outstring;
	Poco::UTF8Encoding utf8;
	Poco::Windows936Encoding gbk;
	Poco::TextConverter coverter(gbk, utf8);
	coverter.convert(inEncoding, outstring);
	return outstring;
}

std::string ActiveXTest::UTF8EncodingGBK(const std::string& instring)
{
	std::string outstring;
	Poco::UTF8Encoding utf8;
	Poco::Windows936Encoding gbk;
	Poco::TextConverter coverter(utf8, gbk);
	coverter.convert(instring, outstring);
	return outstring;
}

CppUnit::Test* ActiveXTest::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("ActiveXTest");
	CppUnit_addTest(pSuite, ActiveXTest, CodeSample);
	CppUnit_addTest(pSuite, ActiveXTest, RS_KeyGetKeySn); // 获取keysn
	CppUnit_addTest(pSuite, ActiveXTest, RS_KeyGetKeySnExt);
	CppUnit_addTest(pSuite, ActiveXTest, RS_GetUserList);
	CppUnit_addTest(pSuite, ActiveXTest, RS_GetCertBase64String);
	CppUnit_addTest(pSuite, ActiveXTest, RS_CertLogin);
	CppUnit_addTest(pSuite, ActiveXTest, RS_GetPinRetryCount);
	CppUnit_addTest(pSuite, ActiveXTest, RS_ChangePassWd);
	CppUnit_addTest(pSuite, ActiveXTest, RS_GetTransid);
	CppUnit_addTest(pSuite, ActiveXTest, RS_KeySignByP1);
	CppUnit_addTest(pSuite, ActiveXTest, RS_VerifySignByP1);
	CppUnit_addTest(pSuite, ActiveXTest, RS_KeySignByP7);
	CppUnit_addTest(pSuite, ActiveXTest, RS_VerifySignByP7);
	CppUnit_addTest(pSuite, ActiveXTest, RS_KeyEncryptData); 
	CppUnit_addTest(pSuite, ActiveXTest, RS_KeyDecryptData); 
	CppUnit_addTest(pSuite, ActiveXTest, RS_GetCertInfo);
	CppUnit_addTest(pSuite, ActiveXTest, RS_EncryptFile);
	CppUnit_addTest(pSuite, ActiveXTest, RS_DevryptFile);
	CppUnit_addTest(pSuite, ActiveXTest, RS_KeyEncryptFile); 
	CppUnit_addTest(pSuite, ActiveXTest, RS_KeyDecryptFile); 
	CppUnit_addTest(pSuite, ActiveXTest, RS_KeyStatus);
	CppUnit_addTest(pSuite, ActiveXTest, RS_ConfigParameters);
	CppUnit_addTest(pSuite, ActiveXTest, RS_GetParameters);
	CppUnit_addTest(pSuite, ActiveXTest, RS_CloudLoginAuth);
	CppUnit_addTest(pSuite, ActiveXTest, RS_CloudSealAuth);
	CppUnit_addTest(pSuite, ActiveXTest, RS_GreateQRCode);
	CppUnit_addTest(pSuite, ActiveXTest, RS_CloudEncryptData);
	CppUnit_addTest(pSuite, ActiveXTest, RS_CloudDevryptData);
	CppUnit_addTest(pSuite, ActiveXTest, RS_CloudEncryptFile);
	CppUnit_addTest(pSuite, ActiveXTest, RS_CloudDevryptFile);
	CppUnit_addTest(pSuite, ActiveXTest, RS_CloudEncryptAuth);
	CppUnit_addTest(pSuite, ActiveXTest, RS_CloudDevryptAuth); 
	CppUnit_addTest(pSuite, ActiveXTest, RS_CloudGetCompanyCert); 
	CppUnit_addTest(pSuite, ActiveXTest, RS_CloudGetCertAuth);
	CppUnit_addTest(pSuite, ActiveXTest, RS_CloudGetCertBase64);
	return pSuite;
}
