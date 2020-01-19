#include "BCBSSealProvider.h"
#include "Utility.h"
#include "Poco/DOM/NodeList.h"
#include "Poco/DOM/NodeFilter.h"
#include "Poco/DOM/NodeIterator.h"
#include "GmEsealProvider.h"
#include "Poco/Format.h"

using namespace Reach;
using namespace Reach::ActiveX;
using namespace Poco::XML;

using Poco::format;

BCBSSealProvider::BCBSSealProvider()
{
	utility_message("Enter BCBSSealProvider eseals");
	setProperty("Provider", "BCBSSealProvider");
}

BCBSSealProvider::~BCBSSealProvider()
{
	utility_message("Exit BCBSSealProvider eseals");
}

void BCBSSealProvider::extract(const std::string& cert)
{
	if (!hasStamps())
		throw Poco::NotFoundException("The stamps were not Found!", "BCBSSealProvider");

	_areacode = Utility::CodeFromDN(cert);

	readSeal();
	ExtractSealPicture();
}

void BCBSSealProvider::ExtractSealPicture()
{
	utility_message_f1("eseals Seal :\n%s", _sealdata);
	poco_assert(!_sealdata.empty());

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
		Element* n = ele->getChildElement("sealname");
		Element* d = ele->getChildElement("sealdata");
		Element* w = ele->getChildElement("sealwidth");
		Element* h = ele->getChildElement("sealhight");
		poco_assert(n && d && w && h);

		Poco::JSON::Object ob;
		ob.set("imgdata", n->innerText());
		ob.set("signname", d->innerText());
		ob.set("width", w->innerText());
		ob.set("height", h->innerText());
		ob.set("imgext", "gif");
		ob.set("signType", "80");///第三方签章
		ob.set("imgArea", _areacode);
		ob.set("imgItem", "99004");/// 百城签章
		seals.add(ob);
	}

	std::ostringstream ostr;
	seals.stringify(ostr);
	setProperty("seals", ostr.str());
}

bool BCBSSealProvider::hasStamps()
{
	int k = IsUKIn();
	int c = GetSealCount();

	if (k == 0 && c > 0) 
		return true;

	return false;
}

void BCBSSealProvider::readSeal()
{
	static const int all_seal = -1;
	char* res = ReadSealData(all_seal);
	std::string content(res, strlen(res));
	_sealdata = Utility::GBKEncodingUTF8(content);

	if (_sealdata.empty())
		throw Poco::DataFormatException("Invalid seal data", Poco::format("%[1]s\n%[0]d", content, getProperty("Provider")));
}
