#include "XSSealProvider.h"
#include "Utility.h"
#include "Poco/Net/HTMLForm.h"
#include "Poco/JSON/Parser.h"
#include "Poco/JSON/Object.h"

#include "Poco/Dynamic/Var.h"
#include "Poco/DynamicStruct.h"

#include "Poco/DOM/Document.h"
#include "Poco/DOM/DOMParser.h"
#include "Poco/DOM/NodeList.h"
#include "Poco/DOM/NodeFilter.h"
#include "Poco/DOM/NodeIterator.h"
#include "Poco/SAX/InputSource.h"
#include <fstream>
#include <cassert>

using namespace Poco::XML;
using namespace Poco::JSON;

using namespace Reach;
using namespace Reach::ActiveX;

using Poco::DynamicStruct;
using Poco::Net::HTMLForm;
using Poco::Util::Application;
using Poco::Dynamic::Var;

XSSealProvider::XSSealProvider()
	:app(Application::instance())
{
	try
	{
		sl.load("XSSealProviderLib.dll");
	}
	catch (Poco::LibraryLoadException& e)
	{
		poco_information_f1(app.logger(), "%s", e.message());
	}
}

XSSealProvider::~XSSealProvider()
{
	sl.unload();
}

void XSSealProvider::extract()
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

void XSSealProvider::ExtractSealPicture()
{
	std::istringstream istr(_sealdata);
	InputSource source(istr);
	DOMParser parser;
	parser.setFeature(DOMParser::FEATURE_FILTER_WHITESPACE, true);
	Poco::AutoPtr<Document> pDoc = parser.parse(&source);
	Node* pUsername = pDoc->getNodeByPath("/sealinfos/sealbaseinfo/username");
	assert(pUsername);
	setProperty("name", pUsername->innerText());
	poco_information_f1(app.logger(), "%s", pUsername->innerText());

	NodeList* pSealinfo = pDoc->getElementsByTagName("sealinfo");
	assert(pSealinfo);
	Poco::JSON::Array seals;
	for (int i = 0; pSealinfo && i < pSealinfo->length(); i++)
	{
		Element* ele = dynamic_cast<Element*>(pSealinfo->item(i));
		assert(ele);
		Element* sealname = ele->getChildElement("sealname");
		Element* sealdata = ele->getChildElement("sealdata");
		assert(sealdata && sealname);
		poco_information_f1(app.logger(), "index:%d", i);
		poco_information_f2(app.logger(), "%s:%s",
			sealname->tagName(), sealname->innerText());
		poco_information_f2(app.logger(), "%s:%s",
			sealdata->tagName(), sealdata->innerText());

		Poco::JSON::Object ob;
		ob.set("imgdata", sealdata->innerText());
		ob.set("signname", sealname->innerText());
		ob.set("imgItem", "83");/// ÏèêÉÇ©ÕÂ
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

	std::string name("ReadSealData");
	if (sl.hasSymbol(name))
	{
		ReadSealData fn = (ReadSealData)sl.getSymbol(name);
		char* res = fn(all_seal);
		_content.append(res);
		poco_information_f1(app.logger(), "seal.data : -> %s", _content);
		_sealdata = Utility::GBKtoUTF8(_content);
		poco_information_f1(app.logger(), "%s", _sealdata);
	}
}

void XSSealProvider::count()
{
	typedef int(*GetSealCount)();
	std::string name("GetSealCount");
	if (sl.hasSymbol(name))
	{
		GetSealCount fn = (GetSealCount)sl.getSymbol(name);
		_count = fn();
		poco_information_f1(app.logger(), "seal.count : -> %d", _count);
	}
}

void XSSealProvider::testKeyIn()
{
	typedef int(*IsUKIn)();
	std::string name("IsUKIn");
	if (sl.hasSymbol(name))
	{
		IsUKIn fn = (IsUKIn)sl.getSymbol(name);
		_bPresent = fn();
		poco_information_f1(app.logger(), "seal.count : -> %b", _bPresent);
	}
}

void XSSealProvider::FetchKeySN()
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

void XSSealProvider::GetContainerId()
{
	std::string result;
	result = Utility::SuperRequest("/RS_GetUserList", "");
	_id = Utility::formatUid(result);
}

void XSSealProvider::TCardGetCert()
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
	if (ds["code"] != "0000")
		throw Poco::Exception("XSSealProvider TCardGetCert Failed!", ds.toString());

	std::string cert = ds["data"]["certBase64"].toString();
	setProperty("cert", cert);
}