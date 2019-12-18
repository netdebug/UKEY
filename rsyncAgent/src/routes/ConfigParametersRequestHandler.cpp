#include "ConfigParametersRequestHandler.h"
#include "Objbase.h"
#include "../../iWebAssist.h"
#include <cassert>
#include <comutil.h>

using namespace Reach;

ConfigParameters::ConfigParameters(const std::string& cmd, const std::string& val)
:_cmd(cmd), _val(val)
{

}

void ConfigParameters::run()
{
	Application& app = Application::instance();
	app.config().setString(_cmd, _val);
	if (_cmd == "authCode") {
		setWebAssist();
	}
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