#include "OESSealProvider.h"
#include "Poco/Util/Application.h"
#include "Poco/Exception.h"
#include "Poco/JSON/Parser.h"
#include "Poco/JSON/Object.h"
#include "Poco/JSON/Array.h"
#include "Poco/DynamicStruct.h"
#include "Poco/Dynamic/Var.h"
#include "Poco/Exception.h"
#include "Poco/StreamCopier.h"
#include "Poco/Base64Encoder.h"
#include "Poco/Crypto/X509Certificate.h"
#include "Poco/DateTimeFormatter.h"
#include "Windows.h"
#include "TCardCert.h"
#include "BridgeKG_HARD_EXT.h"
#include <cassert>
#include <fstream>
using namespace Reach;

using Poco::Util::Application;
using Poco::SharedLibrary;
using Poco::JSON::Object;
using Poco::JSON::Array;
using Poco::JSON::Parser;
using Poco::DynamicStruct;
using Poco::Dynamic::Var;
using Poco::Crypto::X509Certificate;
using Poco::Base64Encoder;
using Poco::Base64EncodingOptions;
using Poco::DateTimeFormatter;

OESSealProvider::OESSealProvider()
	:app(Application::instance())
{
	try
	{
		sl.load("StampManageSystem.dll");
	}
	catch (Poco::LibraryLoadException& e)
	{
		poco_information_f1(app.logger(), "%s", e.message());
	}
}

OESSealProvider::~OESSealProvider()
{
	sl.unload();
}

void Reach::OESSealProvider::extract()
{
	TCardGetCert();
	readSeal();
	ExtractSealPicture();
	PeriodOfValidity();
	FetchKeySN();
	GeneratedCode();
	GeneratedMD5();
}

void OESSealProvider::ExtractSealPicture()
{
	Parser ps;
	Var result = ps.parse(_sealdata);
	std::cout << result.type().name();
	assert(result.type() == typeid(Object::Ptr));
	if (result.type() != typeid(Object::Ptr))
		throw Poco::Exception("the data is not a JSON Object!");

	Object::Ptr object = result.extract<Object::Ptr>();
	DynamicStruct ds = *object;
	setProperty("name", ds["sealinfos"]["sealbaseinfo"]["username"]);

	Poco::Dynamic::Var info = ds["sealinfos"]["sealinfo"];
	Poco::JSON::Array seals;
	for (int i = 0; i < info.size(); i++)
	{
		Poco::JSON::Object ob;
		ob.set("imgdata", info[i]["sealdata"]);
		ob.set("signname", info[i]["sealname"]);
		ob.set("imgItem", "82");/// 凯特签章
		ob.set("imgArea", "81");/// 福建CA 
		seals.add(ob);
	}
	
	std::ostringstream ostr;
	seals.stringify(ostr);
	setProperty("seals", ostr.str());
}

void OESSealProvider::PeriodOfValidity()
{
	std::stringstream ss;
	ss << "-----BEGIN CERTIFICATE-----\n"
		<< _certContent
		<< "\n-----END CERTIFICATE-----\n";

	X509Certificate cert(ss);
	std::string fmt("%Y-%m-%d");
	std::string validStart = DateTimeFormatter::format(cert.validFrom(), fmt);
	std::string validEnd = DateTimeFormatter::format(cert.expiresOn(), fmt);
	/// 证书有效期时间
	setProperty("validStart", validStart);
	setProperty("validEnd", validEnd);
}

void OESSealProvider::readSeal()
{
	Application& app = Application::instance();

	static const std::string all_seal = "-1";
	typedef int (__stdcall *OES_ReadSealData)(
		const char*signCertB64Data,
		const long certDataLen,
		const char*sealID,
		unsigned char*puchSealJson,
		long * puchSealJsonLen);

	std::string name("OES_ReadSealData");
	if (sl.hasSymbol(name))
	{
		long len = 0;
		OES_ReadSealData fn = (OES_ReadSealData)sl.getSymbol(name);
		fn(_certContent.data(), _certContent.size(), all_seal.data(), nullptr, &len);
		if (len > 0 ){
			std::vector<char> seal_data(len + 1, 0);
			fn(_certContent.data(), _certContent.size(), all_seal.data(), (unsigned char*)seal_data.data(), &len);
			_content.assign(seal_data.data(), seal_data.size());
			if(_content.empty())
				throw Poco::Exception("readSeal get json length exception!");
			_sealdata = GBKtoUTF8(_content);
		}
	}
}

#include "Poco/ASCIIEncoding.h"
#include "Poco/StreamConverter.h"

using namespace Poco;
using Poco::OutputStreamConverter;

std::string OESSealProvider::GBKtoUTF8(const std::string& text)
{
	std::ostringstream ostr;
#ifdef TEST
	UTF8Encoding utf8Encoding;
	ASCIIEncoding asciiEncoding;

	OutputStreamConverter converter(ostr, utf8Encoding, asciiEncoding);
	converter << text;

#else
	std::ofstream fs("OES_ReadSealData.json");
	fs.write(text.data(), text.size());
	fs.close();

	std::ifstream input("OES_ReadSealData_utf8.json");
	Poco::StreamCopier::copyStream(input, ostr);
	
#endif // TEST
	return ostr.str();
}

void OESSealProvider::count()
{
	Application& app = Application::instance();

	typedef int(__stdcall *OES_GetSealCount)(const char*signCert, const long DataLen, unsigned char* puchID, long* puchIDsLen);
	std::string name("OES_GetSealCount");
	if (sl.hasSymbol(name))
	{
		OES_GetSealCount fn = (OES_GetSealCount)sl.getSymbol(name);
		long len = 2048;
		Poco::Buffer<char> tmp(len);
		_count = fn(_certContent.data(), _certContent.size(), (unsigned char*)tmp.begin(), &len);
		if (_count < 0) 
			throw Poco::Exception("count exception!");

		poco_information_f1(app.logger(), "seal.data : -> %s", _count);
	}
}

void OESSealProvider::TCardGetCert()
{
	int rv = 0;
	HANDLE hDev = NULL;
	std::string content;

	rv = InitTCard("USB1", &hDev);
	if (!rv) throw Poco::LogicException("USB1");

	BYTE no = 0;
	rv = TCardGetCertNo(&no, hDev);
	if (!rv && !no) throw Poco::LogicException("OESSealProvider cerification not found!");

	rv = TCardSetCertNo(0x01, hDev);
	if (!rv) throw Poco::LogicException("OESSealProvider cerification not found!");

	DWORD len = 1024;
	std::vector<char> vCert(len, 0);
	rv = TCardReadCert((BYTE*)vCert.data(), &len, hDev);
	if (!rv && len > vCert.size()) {
		vCert.resize(len + 1);
		rv = TCardReadCert((BYTE*)vCert.data(), &len, hDev);
	}
	if (!rv) throw Poco::LogicException("TCardReadCert failed!");

	vCert.resize(len);

	std::ostringstream ostr;
	Poco::Base64Encoder encoder(ostr);
	encoder.write(vCert.data(), vCert.size());
	encoder.close();

	_certContent = ostr.str();
	rv = ExitTCard(hDev);
}

void OESSealProvider::FetchKeySN()
{
	BridgeKG_HARD_EXT ext;
	ext.WebConnectDev();
	std::string keysn = ext.WebGetSerial();
	setProperty("keysn", keysn);
	ext.WebDisconnectDev();
}