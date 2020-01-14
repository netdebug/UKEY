#include "ConfigParametersRequestHandler.h"
#include "Objbase.h"
#include "Poco/Environment.h"
#include "Poco/FileStream.h"
//#include "Poco/Util/IniFileConfiguration.h"
#include "Poco/LineEndingConverter.h"
#include "Poco/String.h"
#include "Poco/AutoPtr.h"
#include "../../iWebAssist.h"
#include <cassert>
#include <comutil.h>

using namespace Reach;
//using Poco::AutoPtr;
using Poco::format;
using Poco::FileStream;
using Poco::Environment;
//using Poco::Util::IniFileConfiguration;

ConfigParameters::ConfigParameters(const std::string& cmd, const std::string& val)
:_cmd(cmd), _val(val)
{

}

void ConfigParameters::run()
{
	Application& app = Application::instance();
	app.config().setString(_cmd, _val);
	if (_cmd == "authCode") {
		writeKCode();
	}
}

void ConfigParameters::writeKCode()
{
	///
	/// %temp%\KCODE.ini
	/// AUTHORIZECODE=5D65B01305564D2CB5308B7C71D98994
	/// The function needs to find KCODE.ini by current user(eg. Administrator)
	/// CreateProcessAsUser
	/// 
	
#if defined(_INI)
	const std::string path = ".\\KCODE_DEBUG.ini";
	bool rv = WritePrivateProfileStringA("",
		"AUTHORIZECODE",
		_val.c_str(),
		path.c_str());
	poco_assert_msg(rv, format("WritePrivateProfileStringA %s", path).c_str());
#else
	const std::string path = Environment::get("TEMP").append("\\KCODE.ini");

	std::string authcode = format("AUTHORIZECODE=%s", _val);
	FileStream fs(path);
	fs.write(authcode.data(), authcode.size());
	fs.flush();
	fs.close();
#endif
}

void ConfigParameters::setWebAssist()
{
	::CoInitializeEx(0, COINIT_MULTITHREADED);

	CLSID clsid; IID iid; HRESULT hr;

	hr = CLSIDFromString(OLESTR("{E99768C0-3DE2-4C53-AA41-188550CA66AC}"), &clsid);
	if (FAILED(hr))
		throw Poco::Exception("clsid iWebAssist E99768C0-3DE2-4C53-AA41-188550CA66AC Failed!", 0x9999);

	hr = IIDFromString(OLESTR("{4240FB41-A213-42B6-8CB5-E6705C99B319}"), &iid);
	if (FAILED(hr))
		throw Poco::Exception("iid _DiWebAssist 4240FB41-A213-42B6-8CB5-E6705C99B319  Failed!", 0x9999);

	_DiWebAssist* pWebAssist = 0;
	if (!SUCCEEDED(::CoCreateInstance(clsid, 0, CLSCTX_INPROC_SERVER, iid, (void**)&pWebAssist)))
		throw Poco::Exception("CoCreateInstance pWebAssist Failed!", 0x9999);

	assert(pWebAssist);

	DISPID PropertyID[3] = { 0 };

	BSTR PropName[3];
	PropName[0] = SysAllocString(OLESTR("SetParamByName"));
	PropName[1] = SysAllocString(OLESTR("ParamName"));;
	PropName[2] = SysAllocString(OLESTR("ParamValue"));;

	hr = pWebAssist->GetIDsOfNames(IID_NULL, PropName, 3, LOCALE_SYSTEM_DEFAULT, PropertyID);
	assert(SUCCEEDED(hr));

	SysFreeString(PropName[0]);
	SysFreeString(PropName[1]);
	SysFreeString(PropName[2]);

	BSTR val = _com_util::ConvertStringToBSTR(_val.data());

	VARIANT avarParams[2];
	avarParams[1].vt = VT_BSTR | VT_BYREF;
	avarParams[1].pbstrVal = &val;

	BSTR authCode = _com_util::ConvertStringToBSTR("AUTHORIZECODE");

	avarParams[0].vt = VT_BSTR | VT_BYREF;
	avarParams[0].pbstrVal = &authCode;

	DISPPARAMS param = {
		avarParams,
		NULL,
		2,
		0
	};
	VARIANT result;
	hr = pWebAssist->Invoke(PropertyID[0], IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_METHOD, &param, &result, NULL, NULL);
	assert(SUCCEEDED(hr));

	::CoUninitialize();
}