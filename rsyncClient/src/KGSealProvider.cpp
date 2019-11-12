#include "KGSealProvider.h"
#include "Utility.h"
#include "Poco/JSON/Parser.h"
#include "Poco/JSON/Object.h"

#include "Poco/Dynamic/Var.h"
#include "Poco/DynamicStruct.h"

#include "Poco/Net/HTMLForm.h"
#include <Windows.h>
#include <comdef.h>
#include "KG_GetKeyInfo_FJRS.h"
#include <cassert>

using namespace Reach;
using namespace Reach::ActiveX;

using namespace Poco::JSON;

using Poco::Net::HTMLForm;
using Poco::Util::Application;
using Poco::Dynamic::Var;
using Poco::DynamicStruct;
// MIDL Compiler
/// MIDL KG_GetKeyInfo_FJRS.IDL /tlb KG_GetKeyInfo_FJRS.tlb /h KG_GetKeyInfo_FJRS.h /iid KG_GetKeyInfo_FJRS_i.c /Oicf

KGSealProvider::KGSealProvider()
	:app(Application::instance())
{
	/// Com interface
	HRESULT	hr;
	hr = CoInitialize(0);
	assert(SUCCEEDED(hr));

	hr = CoCreateInstance(CLSID_KG_GetKeyInfo_FJRS,
		NULL,
		CLSCTX_INPROC_SERVER,
		DIID__DKG_GetKeyInfo_FJRS,
		(void**)&_ext);

	assert(SUCCEEDED(hr));

}

KGSealProvider::~KGSealProvider()
{
	::CoUninitialize();
}

void KGSealProvider::extract()
{
	GetContainerId();
	TCardGetCert();
	readSeal();
	ExtractSealPicture();
	PeriodOfValidity();
	FetchKeySN();
	GeneratedCode();
	GeneratedMD5();
}

#include "CDKG_GetKeyInfo_FJRS.h"
void KGSealProvider::readSeal()
{
	/*CoInitialize(NULL);
	CDKG_GetKeyInfo_FJRS  KG_GetKeyInfo_FJRS;
	BOOL bRet = FALSE;
	CoCreateInstance(KG_GetKeyInfo_FJRS.GetClsid(),
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_IKG_HARD_EXT,
		(void**)&_ext);
	bRet = KG_GetKeyInfo_FJRS.CreateControl(KG_GetKeyInfo_FJRS.GetClsid(), _T("Test"), WS_CHILD | WS_DLGFRAME, rect, CWnd::FromHandle(hWnd), 100);
	CString KeyInfo = _T("");
	KeyInfo = KG_GetKeyInfo_FJRS.KGGetKeyInfo();
	MessageBox(KeyInfo, _T("KG_GetKeyInfo_FJRS"), MB_OK);
	CoUninitialize();*/
}

void KGSealProvider::FetchKeySN()
{
	std::string result;

	HTMLForm params;
	params.set("containerId", _id);

	std::ostringstream body;
	params.write(body);
	result = Utility::SuperRequest("/RS_KeyGetKeySn", body.str());

	Parser ps;
	Var res = ps.parse(result);
	assert(res.type() == typeid(Object::Ptr));
	Object::Ptr object = res.extract<Object::Ptr>();
	assert(object);
	DynamicStruct ds = *object;
	assert(ds["code"] == "0000");
	setProperty("keysn", ds["data"]["keySn"].toString());
}

void KGSealProvider::GetContainerId()
{
	std::string result;
	result = Utility::SuperRequest("/RS_GetUserList", "");
	_id = Utility::formatUid(result);
}

void KGSealProvider::TCardGetCert()
{
	HTMLForm params;
	params.set("containerId", _id);
	params.set("certType", _type);

	std::ostringstream body;
	params.write(body);
	std::string result = Utility::SuperRequest("/RS_GetCertBase64String", body.str());

	Parser ps;
	Var res = ps.parse(result);
	assert(res.type() == typeid(Object::Ptr));
	Object::Ptr object = res.extract<Object::Ptr>();
	assert(object);
	DynamicStruct ds = *object;
	assert(ds["code"] == "0000");
	std::string cert = ds["data"]["certBase64"].toString();
	setProperty("cert", cert);
}

void KGSealProvider::ExtractSealPicture()
{

}