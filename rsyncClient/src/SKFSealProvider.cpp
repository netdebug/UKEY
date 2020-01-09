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

Reach::SKFSealProvider::SKFSealProvider()
{
	utility_message("Enter SKFSealProvider dianju");

	sl.load("HWPostil.ocx");

	setProperty("Provider", "SKFSealProvider");
}

Reach::SKFSealProvider::~SKFSealProvider()
{
	sl.unload();

	utility_message("Exit SKFSealProvider dianju");
}

void Reach::SKFSealProvider::extract(const std::string& cert)
{
	_certContent = cert;
	readSeal();
	ExtractSealPicture();
}

void Reach::SKFSealProvider::readSeal()
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

void Reach::SKFSealProvider::count()
{
	typedef int(__stdcall *GetSealCount)();
	std::string name("GetSealCount");

	GetSealCount fn = (GetSealCount)sl.getSymbol(name);
	_count = fn();

	utility_message_f1("dianju seal.count : -> %d", _count);
}

void Reach::SKFSealProvider::keyin()
{
	typedef int(__stdcall *IsUKIn)();
	std::string name("IsUKIn");

	IsUKIn fn = (IsUKIn)sl.getSymbol(name);
	_bPresent = fn() == 0;

	utility_message_f1("dianju seal.keyin : -> %b", _bPresent);
}

void Reach::SKFSealProvider::ExtractSealPicture()
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
		obj.set("imgItem", "99005");/// 点聚
		obj.set("imgArea", "87");///
		seals.add(obj);
	}
	std::ostringstream ostr;
	seals.stringify(ostr);
	setProperty("seals", ostr.str());
}

