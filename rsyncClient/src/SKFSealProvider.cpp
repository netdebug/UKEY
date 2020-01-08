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
using Poco::Util::Application;
using Poco::XML::InputSource;
using Poco::XML::DOMParser;
using Poco::XML::Document;
using Poco::XML::Node;
using Poco::XML::NodeList;
using Poco::XML::Element;

Reach::SKFSealProvider::SKFSealProvider()
{
	Utility::message("Enter SKFSealProvider");
	sl.load("HWPostil.ocx");
	setProperty("Provider", "OESSealProvider");
}

Reach::SKFSealProvider::~SKFSealProvider()
{
	sl.unload();
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
	Application& app = Application::instance();
	typedef int(__stdcall *GetSealCount)();
	std::string name("GetSealCount");

	GetSealCount fn = (GetSealCount)sl.getSymbol(name);
	_count = fn();

	poco_information_f1(app.logger(), "seal.count : -> %d", _count);
}

void Reach::SKFSealProvider::keyin()
{
	Application& app = Application::instance();
	typedef int(__stdcall *IsUKIn)();
	std::string name("IsUKIn");

	IsUKIn fn = (IsUKIn)sl.getSymbol(name);
	_bPresent = fn() == 0;

	poco_information_f1(app.logger(), "seal.keyin : -> %b", _bPresent);
}

void Reach::SKFSealProvider::ExtractSealPicture()
{
	Application& app = Application::instance();

	//poco_information_f1(app.logger(), "xs :\n%s", _sealdata);

	std::istringstream istr(_sealdata);
	InputSource soure(istr);
	DOMParser parser;
	parser.setFeature(DOMParser::FEATURE_FILTER_WHITESPACE, true);
	Poco::AutoPtr<Document> pDoc = parser.parse(&soure);
	Node* pUsername = pDoc->getNodeByPath("/sealinfos/sealbaseinfo/username");
	assert(pUsername);
	setProperty("name", pUsername->innerText());

	NodeList* pSealinfo = pDoc->getElementsByTagName("sealinfo");
	assert(pSealinfo);

	Poco::JSON::Array seals;
	for (int i = 0; i < pSealinfo->length(); i++)
	{
		Element* ele = dynamic_cast<Element*>(pSealinfo->item(i));
		assert(ele);

		Element* sealname = ele->getChildElement("sealname");
		Element* sealdata = ele->getChildElement("sealdata");
		Element* sealwidth = ele->getChildElement("sealwidth");
		Element* sealhight = ele->getChildElement("sealhight");
		assert(sealdata&&sealname);

		Poco::JSON::Object obj;
		obj.set("imgdata", sealdata->innerText());
		obj.set("signname", sealname->innerText());
		obj.set("width", "4.00");
		obj.set("hight", "4.00");
		obj.set("signType", "80");
		obj.set("imgext", "gif");
		obj.set("imgItem", "85");/// µã¾Û
		obj.set("imgArea", "87");/// ÉÂÎ÷CA
		seals.add(obj);
	}
	std::ostringstream ostr;
	seals.stringify(ostr);
	setProperty("seals", ostr.str());
}

