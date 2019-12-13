#include "stdafx.h"
#include "KGSealProvider.h"
#include "Utility.h"
#include "Poco/JSON/Parser.h"
#include "Poco/JSON/Object.h"
#include "Poco/Dynamic/Var.h"
#include "Poco/DynamicStruct.h"
#include "Poco/Net/HTMLForm.h"
#include <cassert>
#include "CDKG_GetKeyInfo_FJRS.h"

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
	
}

KGSealProvider::~KGSealProvider()
{
	
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
	CDKG_GetKeyInfo_FJRS  KG_GetKeyInfo_FJRS;
	BOOL bRet = FALSE;
	bRet = KG_GetKeyInfo_FJRS.CreateDispatch(_T("KG_GETKEYINFO_FJ.KG_GetKeyInfo_FJCtrl.1"));
	CString KeyInfo = _T("");
	KeyInfo = KG_GetKeyInfo_FJRS.KGGetKeyInfo();
	_content = KeyInfo.GetString();
	_sealdata = Utility::GBKtoUTF8(_content);
	poco_information_f1(app.logger(), "%s", _sealdata);
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
	Parser ps;
	Var result = ps.parse(_sealdata);
	std::cout << result.type().name();
	assert(result.type() == typeid(Object::Ptr));
	if (result.type() != typeid(Object::Ptr))
		throw Poco::Exception("the data is not a JSON Object!");

	Object::Ptr object = result.extract<Object::Ptr>();
	DynamicStruct ds = *object;
	Poco::Dynamic::Var info = ds["seals"];
	assert(info.size() > 0);
	if (info.size() > 0) setProperty("name", info[0]["username"]);

	Poco::JSON::Array seals;
	for (int i = 0; i < info.size(); i++)
	{
		Poco::JSON::Object ob;
		ob.set("imgdata", info[i]["imgdata"]);
		ob.set("signname", info[i]["signname"]);
		ob.set("imgItem", "81");/// ½ð¸ñÇ©ÕÂ
		ob.set("imgArea", "84");/// ÄÚÃÉ¹ÅCA 
		seals.add(ob);
	}

	std::ostringstream ostr;
	seals.stringify(ostr);
	setProperty("seals", ostr.str());
}