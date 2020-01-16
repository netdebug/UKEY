#include "SNSealProvider.h"
#include "Utility.h"
#include "Poco/Util/Application.h"
#include "Poco/SAX/InputSource.h"
#include "Poco/DOM/DOMParser.h"
#include "Poco/DOM/Node.h"
#include "Poco/DOM/Document.h"
#include "Poco/DOM/NodeList.h"
#include "Poco/DOM/Element.h"

using namespace Reach;
using namespace Reach::ActiveX;
using Poco::Util::Application;
using Poco::XML::InputSource;
using Poco::XML::DOMParser;
using Poco::XML::Document;
using Poco::XML::Node;
using Poco::XML::NodeList;
using Poco::XML::Element;

SNSealProvider::SNSealProvider()
{
	utility_message("Enter SNSealProvider tongzhi");
	setProperty("Provider", "SNSealProvider");

	sl.load("SNCA_GetSeal.dll");
}

SNSealProvider::~SNSealProvider()
{
	sl.unload();

	utility_message("SNSealProvider tongzhi");
}

void SNSealProvider::extract(const std::string& cert)
{
	if (!hasStamps())
		throw Poco::NotFoundException("The stamps were not Found!", "SNSealProvider");

	_areacode = Utility::CodeFromDN(cert);
	readSeal();
	ExtractSealPicture();
}

void SNSealProvider::readSeal()
{
	static const int all_seal = -1;
	typedef char*(__stdcall *ReadSealData)(int idx);
	ReadSealData fn = (ReadSealData)sl.getSymbol("ReadSealData");
	char* res = fn(all_seal);
	std::string content(res, strlen(res));
	_sealdata = Utility::GBKEncodingUTF8(content);

	if (_sealdata.empty())
	{
		throw Poco::DataFormatException("Invalid seal data", Poco::format("%[1]s\n%[0]d", content, getProperty("Provider")));
	}
}

bool SNSealProvider::hasStamps()
{
	if (hasKey() && count() > 0)
		return true;

	return false;
}

int SNSealProvider::count()
{
	typedef int(__stdcall *GetSealCount)();
	std::string name("GetSealCount");

	GetSealCount fn = (GetSealCount)sl.getSymbol(name);
	int count = fn();

	utility_message_f1("dianju seal.count : -> %d", count);

	return count;
}

bool SNSealProvider::hasKey()
{
	typedef int(__stdcall *IsUKIn)();

	IsUKIn fn = (IsUKIn)sl.getSymbol("IsUKIn");
	int k = fn();

	utility_message_f1("dianju seal.keyin : -> %d", k);

	return (k == 0);
}

void SNSealProvider::ExtractSealPicture()
{
	utility_message_f1("tongzhi Seal :\n%s", _sealdata);
	poco_assert(!_sealdata.empty());

	XML_PARSE(_sealdata);
	Node* pUsername = pDoc->getNodeByPath("/sealinfos/sealbaseinfo/username");
	poco_assert(pUsername);
	setProperty("name", pUsername->innerText());
	NodeList* pSealinfo = pDoc->getElementsByTagName("sealinfo");
	poco_assert(pSealinfo);

	Poco::JSON::Array seals;
	for (int i = 0; i < pSealinfo->length(); ++i)
	{
		Element* ele = dynamic_cast<Element*>(pSealinfo->item(i));
		poco_assert(ele);
		Element* sealname = ele->getChildElement("sealname");
		Element* sealdata = ele->getChildElement("sealdata");
		Element* w = ele->getChildElement("sealwidth");
		Element* h = ele->getChildElement("sealhight");
		poco_assert(sealname && sealdata);
		Poco::JSON::Object obj;

		obj.set("imgdata", sealdata->innerText());
		obj.set("signname", sealname->innerText());
		obj.set("width", w->innerText());
		obj.set("height", h->innerText());
		obj.set("signType", "80");
		obj.set("imgext", "gif");
		obj.set("imgItem", _areacode);///Í¬ÖÇÎ°Òµ
		obj.set("imgArea", "87");/// 
		seals.add(obj);
	}
	std::ostringstream ostr;
	seals.stringify(ostr);
	setProperty("seals", ostr.str());
}
