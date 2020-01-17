#include "SKFSealProvider.h"
#include "Utility.h"
#include "Poco/Util/Application.h"
#include <iosfwd>

#include "Poco/SAX/InputSource.h"
#include "Poco/DOM/DOMParser.h"
#include "Poco/DOM/Document.h"
#include "Poco/DOM/Node.h"
#include "Poco/DOM/NodeList.h"
#include "Poco/DOM/Element.h"

using namespace Reach;
using namespace Reach::ActiveX;
using namespace Poco::XML;

SKFSealProvider::SKFSealProvider()
{
	utility_message("Enter SKFSealProvider dianju");

	sl.load("HWPostil.ocx");

	setProperty("Provider", "SKFSealProvider");
}

SKFSealProvider::~SKFSealProvider()
{
	poco_assert(sl.isLoaded());

	//sl.unload();

	utility_message("Exit SKFSealProvider dianju");
}

void SKFSealProvider::extract(const std::string& cert)
{
	if (!hasStamps())
		throw Poco::NotFoundException("The stamps were not Found!", "SKFSealProvider");

	_certContent = cert;
	_areacode = Utility::CodeFromDN(cert);

	readSeal();
	ExtractSealPicture();
}

void SKFSealProvider::readSeal()
{
	static const int all_seal = -1;
	typedef char* (__stdcall *ReadSealData)(int nIndex);
	ReadSealData fn = (ReadSealData)sl.getSymbol("ReadSealData");
	char* res = fn(all_seal);
	std::string content(res, strlen(res));
	_sealdata = Utility::GBKEncodingUTF8(content);

	if (_sealdata.empty())
		throw Poco::DataFormatException("Invalid seal data", Poco::format("%[1]s\n%[0]d", content, getProperty("Provider")));
}

bool SKFSealProvider::hasStamps()
{
	if (hasKey() && count() > 0)
		return true;

	return false;
}


int SKFSealProvider::count()
{
	typedef int(__stdcall *GetSealCount)();
	std::string name("GetSealCount");

	GetSealCount fn = (GetSealCount)sl.getSymbol(name);
	int count = fn();

	utility_message_f1("dianju seal.count : -> %d", count);

	return count;
}

bool SKFSealProvider::hasKey()
{
	typedef int(__stdcall *IsUKIn)();

	IsUKIn fn = (IsUKIn)sl.getSymbol("IsUKIn");
	int k  = fn();

	utility_message_f1("dianju seal.keyin : -> %d", k);

	return (k == 0);
}

void SKFSealProvider::ExtractSealPicture()
{
	utility_message_f1("dianju Seal :\n%s", _sealdata);
	XML_PARSE(_sealdata);
	Node* pUsername = pDoc->getNodeByPath("/sealinfos/sealbaseinfo/username");
	poco_assert(pUsername);
	setProperty("name", pUsername->innerText());

	NodeList* pSealinfo = pDoc->getElementsByTagName("sealinfo");
	poco_assert(pSealinfo);

	Poco::JSON::Array seals;
	for (int i = 0; i < pSealinfo->length(); i++)
	{
		Element* ele = dynamic_cast<Element*>(pSealinfo->item(i));
		poco_assert(ele);

		Element* sealname = ele->getChildElement("sealname");
		Element* sealdata = ele->getChildElement("sealdata");
		poco_assert(sealdata && sealname);

		Poco::JSON::Object obj;
		obj.set("imgdata", sealdata->innerText());
		obj.set("signname", sealname->innerText());
		obj.set("width", "4.00");
		obj.set("hight", "4.00");
		obj.set("signType", "80");///第三方签章
		obj.set("imgext", "gif");
		obj.set("imgItem", _areacode);/// 点聚
		obj.set("imgArea", "87");///
		seals.add(obj);
	}
	std::ostringstream ostr;
	seals.stringify(ostr);
	setProperty("seals", ostr.str());
}

