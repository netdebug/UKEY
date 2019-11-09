#include "XSSealProvider.h"
#include "Poco/XML/XMLStream.h"
#include "Poco/JSON/Object.h"
#include "Poco/Util/Application.h"
#include "Poco/DynamicStruct.h"
#include "Poco/DOM/Document.h"
#include "Poco/DOM/DOMParser.h"
#include "Poco/SAX/InputSource.h"
#include "Poco/UUIDGenerator.h"
#include "Poco/UUID.h"

#include <cassert>

using namespace Reach;
using Poco::JSON::Object;
using Poco::Util::Application;
using Poco::DynamicStruct;
using Poco::XML::Document;
using Poco::XML::InputSource;
using Poco::XML::DOMParser;
using Poco::XML::XMLReader;
using Poco::XML::Node;
using Poco::UUIDGenerator;
using Poco::UUID;

typedef char* (*ReadSealData)(int nIndex);

XSSealProvider::XSSealProvider()
{
	sl.load("XSSealProviderLib.dll");
}

XSSealProvider::~XSSealProvider()
{
	sl.unload();
}

void XSSealProvider::extract()
{
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
	Application& app = Application::instance();
	

	readSeal();

	static const std::string simple =
		"<config>\r\n"
		"\t<prop1>value1</prop1>\r\n"
		"\t<prop2>value2</prop2>\r\n"
		"</config>\r\n";

	std::istringstream istr(_content);
	InputSource source(istr);
	DOMParser parser;
	parser.setFeature(DOMParser::FEATURE_FILTER_WHITESPACE, true);
	Poco::AutoPtr<Document> pDoc = parser.parse(&source);
	Node* pSealbaseinfo = pDoc->getNodeByPath("/sealinfos/sealbaseinfo");
	Node* pSealinfo = pDoc->getNodeByPath("/sealinfos/sealinfo");

	setProperty("name", pSealbaseinfo->getNodeByPath("username")->innerText());
	//setProperty("code", UUIDGenerator::defaultGenerator().createRandom().toString());

	/// 证书有效期时间
	setProperty("validStart", "");
	setProperty("validEnd", "");

	DynamicStruct ds;

	ds["imgdata"] = pSealinfo->getNodeByPath("sealdata");
	ds["signname"] = pSealinfo->getNodeByPath("sealname");
	ds["imgItem"] = "";
	ds["imgArea"] = "";

	poco_information_f2(app.logger(), "pSealbaseinfo: %s, pSealinfo:%s", pSealbaseinfo->innerText(), pSealinfo->innerText());
}

void XSSealProvider::readSeal()
{
	Application& app = Application::instance();

	static const int all_seal = -1;
	typedef char* (*ReadSealData)(int nIndex);

	std::string name("ReadSealData");
	if (sl.hasSymbol(name))
	{
		ReadSealData fn = (ReadSealData)sl.getSymbol(name);
		char* res = fn(all_seal);
		_content.append(res);
		poco_information_f1(app.logger(),"seal.data : -> %s", _content);
	}
}

void XSSealProvider::count()
{
	Application& app = Application::instance();

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
	Application& app = Application::instance();

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

}

void XSSealProvider::TCardGetCert()
{

}

void XSSealProvider::PeriodOfValidity()
{

}