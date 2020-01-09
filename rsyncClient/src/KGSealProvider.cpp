#include "stdafx.h"
#include "CDKG_GetKeyInfo_FJRS.h"
#include "KGSealProvider.h"
#include <cassert>
#include "Utility.h"

using namespace Reach;
using namespace Reach::ActiveX;

using Poco::Dynamic::Var;
using Poco::DynamicStruct;
// MIDL Compiler
/// MIDL KG_GetKeyInfo_FJRS.IDL /tlb KG_GetKeyInfo_FJRS.tlb /h KG_GetKeyInfo_FJRS.h /iid KG_GetKeyInfo_FJRS_i.c /Oicf

KGSealProvider::KGSealProvider()
	:_pKG_GetKeyInfo_FJRS(nullptr)
{
	utility_message("Enter KGSealProvider Kinggrid");

	CoInitialize(0);
	/// Com interface
	_pKG_GetKeyInfo_FJRS = new CDKG_GetKeyInfo_FJRS;
	if (!_pKG_GetKeyInfo_FJRS->CreateDispatch(_T("KG_GETKEYINFO_FJ.KG_GetKeyInfo_FJCtrl.1"))) {
		throw Poco::InvalidAccessException("Invalid argument", Poco::format("%s:\n CDKG_GetKeyInfo_FJRS", getProperty("Provider")));
	}

	setProperty("Provider", "KGSealProvider");
}

KGSealProvider::~KGSealProvider()
{
	poco_assert(_pKG_GetKeyInfo_FJRS);
	_pKG_GetKeyInfo_FJRS->ReleaseDispatch();
	delete _pKG_GetKeyInfo_FJRS;
	CoUninitialize();

	utility_message("Exit KGSealProvider Kinggrid");
}

void KGSealProvider::extract(const std::string& cert)
{
	readSeal();
	ExtractSealPicture();
}

void KGSealProvider::readSeal()
{
	poco_assert(_pKG_GetKeyInfo_FJRS);
	CString KeyInfo = _pKG_GetKeyInfo_FJRS->KGGetKeyInfo();
	_sealdata = Utility::GBKEncodingUTF8(KeyInfo.GetString());

	JSON_PARSE(_sealdata);

	bool status = ds["result"];
	if (!status)
		throw Poco::DataFormatException("Invalid seal data", Poco::format("%[1]s:\n%[0]s",ds.toString(), getProperty("Provider") ));
}

void KGSealProvider::ExtractSealPicture()
{
	JSON_PARSE(_sealdata);
	Poco::Dynamic::Var info = ds["seals"];
	poco_assert(info.size() > 0);
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
		ob.set("imgItem", "99001");/// ½ð¸ñÇ©ÕÂ
		ob.set("imgArea", "84");/// ÄÚÃÉ¹ÅCA 
		seals.add(ob);
	}

	std::ostringstream ostr;
	seals.stringify(ostr);
	setProperty("seals", ostr.str());
}