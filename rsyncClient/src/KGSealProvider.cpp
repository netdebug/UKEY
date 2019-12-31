#include "stdafx.h"
#include "CDKG_GetKeyInfo_FJRS.h"
#include "KGSealProvider.h"
#include "Utility.h"
#include "Poco/JSON/Parser.h"
#include "Poco/JSON/Object.h"
#include "Poco/Dynamic/Var.h"
#include "Poco/DynamicStruct.h"
#include "Poco/Net/HTMLForm.h"

#include <cassert>

#define JSON_PARSE(DATA) \
	Parser ps;											\
	Var res = ps.parse(DATA);							\
	assert(res.type() == typeid(Object::Ptr));			\
	Object::Ptr object = res.extract<Object::Ptr>();	\
	assert(object);										\
	DynamicStruct ds = *object;

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
	:app(Application::instance()),
	_pKG_GetKeyInfo_FJRS(nullptr)
{
	CoInitialize(0);
	/// Com interface
	_pKG_GetKeyInfo_FJRS = new CDKG_GetKeyInfo_FJRS;
	if (!_pKG_GetKeyInfo_FJRS->CreateDispatch(_T("KG_GETKEYINFO_FJ.KG_GetKeyInfo_FJCtrl.1")))
		throw Poco::InvalidAccessException("Invalid argument", "CDKG_GetKeyInfo_FJRS");
}

KGSealProvider::~KGSealProvider()
{
	assert(_pKG_GetKeyInfo_FJRS);
	_pKG_GetKeyInfo_FJRS->ReleaseDispatch();
	delete _pKG_GetKeyInfo_FJRS;
	CoUninitialize();
}

void KGSealProvider::extract()
{
	readSeal();
	GetContainerId();
	TCardGetCert();
	ExtractSealPicture();
	PeriodOfValidity();
	FetchKeySN();
	GeneratedCode();
	GeneratedMD5();
}

void KGSealProvider::readSeal()
{
	assert(_pKG_GetKeyInfo_FJRS);
	CString KeyInfo = _pKG_GetKeyInfo_FJRS->KGGetKeyInfo();
	_sealdata = Utility::GBKtoUTF8(KeyInfo.GetString());

	JSON_PARSE(_sealdata);

	bool status = ds["result"];
	if (!status) 
	throw Poco::DataFormatException("Invalid seal data", ds.toString());
}

void KGSealProvider::FetchKeySN()
{
	std::string result;

	HTMLForm params;
	params.set("containerId", _id);

	std::ostringstream body;
	params.write(body);
	result = Utility::SuperRequest("/RS_KeyGetKeySn", body.str());

	JSON_PARSE(result)

	if (ds["code"] != "0000") 
		handleLastError(result);

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

	JSON_PARSE(result);
	if (ds["code"] != "0000")
		handleLastError(result);

	std::string cert = ds["data"]["certBase64"].toString();
	setProperty("cert", cert);
}

void KGSealProvider::ExtractSealPicture()
{
	JSON_PARSE(_sealdata);
	Poco::Dynamic::Var info = ds["seals"];
	assert(info.size() > 0);
	if (info.size() > 0) setProperty("name", info[0]["username"]);

	Poco::JSON::Array seals;
	for (int i = 0; i < info.size(); i++)
	{
		Poco::JSON::Object ob;
		ob.set("imgdata", info[i]["imgdata"]);
		ob.set("signname", info[i]["signname"]);
		ob.set("height", info[i]["height"]);
		ob.set("width", info[i]["width"]);
		ob.set("imgext", info[i]["imgext"]);
		ob.set("signType", "80");
		ob.set("imgItem", "81");/// ½ð¸ñÇ©ÕÂ
		ob.set("imgArea", "84");/// ÄÚÃÉ¹ÅCA 
		seals.add(ob);
	}

	std::ostringstream ostr;
	seals.stringify(ostr);
	setProperty("seals", ostr.str());
}

void KGSealProvider::handleLastError(const std::string& result)
{
	JSON_PARSE(result);
	int code = ds["code"];
	switch (code) {
	case 9001:
		throw Poco::ProtocolException(ds.toString(),code);
	default:
		throw Poco::UnhandledException();
	}
}