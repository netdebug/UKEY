#include "XSSealProvider.h"
#include "Utility.h"
#include "Poco/DOM/NodeList.h"
#include "Poco/DOM/NodeFilter.h"
#include "Poco/DOM/NodeIterator.h"
#include "Poco/Util/Application.h"
#include <fstream>
#include <cassert>

using namespace Poco::XML;

using namespace Reach;
using namespace Reach::ActiveX;

using Poco::Util::Application;

XSSealProvider::XSSealProvider()
{
	utility_message("Enter XSSealProvider share-sun");

	sl.load("XSSealProviderLib.dll");

	setProperty("Provider", "XSSealProvider");
}

XSSealProvider::~XSSealProvider()
{
	sl.unload();

	utility_message("Exit XSSealProvider share-sun");
}

void XSSealProvider::extract(const std::string& cert)
{
	if (!hasStamps())
		throw Poco::NotFoundException("The stamps were not Found!", "XSSealProvider");

	_areacode = Utility::CodeFromDN(cert);

	readSeal();
	ExtractSealPicture();
}

void XSSealProvider::ExtractSealPicture()
{
	utility_message_f1("share-sun :\n%s" , _sealdata);
	XML_PARSE(_sealdata);

	Node* pUsername = pDoc->getNodeByPath("/sealinfos/sealbaseinfo/username");
	poco_assert(pUsername);
	setProperty("name", pUsername->innerText());

	NodeList* pSealinfo = pDoc->getElementsByTagName("sealinfo");
	poco_assert(pSealinfo);
	Poco::JSON::Array seals;
	for (int i = 0; pSealinfo && i < pSealinfo->length(); i++)
	{
		Element* ele = dynamic_cast<Element*>(pSealinfo->item(i));
		poco_assert(ele);
		Element* sealname = ele->getChildElement("sealname");
		Element* sealdata = ele->getChildElement("sealdata");
		poco_assert(sealdata && sealname);

		Poco::JSON::Object ob;
		ob.set("imgdata", sealdata->innerText());
		ob.set("signname", sealname->innerText());
		ob.set("height", "4.00");
		ob.set("width", "4.00");
		ob.set("imgext", "gif");
		ob.set("signType", "80");///µÚÈý·½Ç©ÕÂ
		ob.set("imgItem", _areacode);/// ÏèêÉÇ©ÕÂ
		ob.set("imgArea", "82");/// BJCA or CFCA
		seals.add(ob);
	}

	std::ostringstream ostr;
	seals.stringify(ostr);
	setProperty("seals", ostr.str());
}

void XSSealProvider::readSeal()
{
	static const int all_seal = -1;
	typedef char* (*ReadSealData)(int nIndex);

	ReadSealData fn = (ReadSealData)sl.getSymbol("ReadSealData");
	char* res = fn(all_seal);
	std::string content(res,strlen(res));
	_sealdata = Utility::GBKEncodingUTF8(content);

	if (_sealdata.empty())
	throw Poco::DataFormatException("Invalid seal data", Poco::format("%[1]s\n%[0]d", content, getProperty("Provider")));
}


bool XSSealProvider::hasStamps()
{
	if (hasKey() && count() > 0)
		return true;

	return false;
}

int XSSealProvider::count()
{
	typedef int(__stdcall *GetSealCount)();
	std::string name("GetSealCount");

	GetSealCount fn = (GetSealCount)sl.getSymbol(name);
	int count = fn();

	utility_message_f1("dianju seal.count : -> %d", count);

	return count;
}

bool XSSealProvider::hasKey()
{
	typedef int(__stdcall *IsUKIn)();

	IsUKIn fn = (IsUKIn)sl.getSymbol("IsUKIn");
	int k = fn();

	utility_message_f1("dianju seal.keyin : -> %d", k);

	return (k == 0);
}