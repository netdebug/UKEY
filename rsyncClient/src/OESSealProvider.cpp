#include "OESSealProvider.h"
#include "Poco/UUIDGenerator.h"
#include "Poco/UUID.h"
#include "Poco/Util/Application.h"
#include "Poco/Exception.h"
#include "Poco/JSON/Parser.h"
#include "Poco/JSON/Object.h"
#include "Poco/JSON/Array.h"
#include "Poco/DynamicStruct.h"
#include "Poco/Dynamic/Var.h"
#include "Poco/UUIDGenerator.h"
#include "Poco/Exception.h"
#include "Poco/MemoryStream.h"
#include "Poco/FileStream.h"
#include "Poco/StreamCopier.h"
#include "Poco/Base64Encoder.h"
#include "Poco/Crypto/X509Certificate.h"
#include "Poco/DateTimeFormatter.h"
#include "Windows.h"
#include "TCardCert.h"
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
using Poco::UUIDGenerator;
using Poco::Crypto::X509Certificate;
using Poco::Base64Encoder;
using Poco::Base64EncodingOptions;
using Poco::DateTimeFormatter;


OESSealProvider::OESSealProvider()
	:_sealdata(new Array)
{
	Application& app = Application::instance();
	try
	{
		sl.load("StampManageSystem.dll");
		TCardGetCert();
		readSeal();
		setName();
		set_vaild_date();
	}
	catch (Poco::LibraryLoadException& e)
	{
		poco_information_f1(app.logger(), "OESSealProvider : %s", e.message());
		throw Poco::Exception("OESSealProvider init failed!");
	}
	catch (Poco::Exception& e)
	{
		poco_information_f1(app.logger(), "OESSealProvider : %s", e.message());
	}
}

OESSealProvider::~OESSealProvider()
{
	sl.unload();
	//delete _sealdata;
}

void OESSealProvider::read(Object::Ptr JSONin, Object::Ptr JSONout)
{

}

Var OESSealProvider::read()
{
	Application& app = Application::instance();

	set_seal_data();

	return Poco::Dynamic::Var(_sealdata);
}

void OESSealProvider::set_seal_data()
{
	Parser sp;
	std::ifstream input("F:\\source\\RSTestRunner\\rsyncClient\\sealdata.json");
	Var tmp = sp.parse(input);
	DynamicStruct ds = *tmp.extract<Object::Ptr>();

	assert(result.type() == typeid(Object::Ptr));
	Object::Ptr object = result.extract<Object::Ptr>();
	Poco::Dynamic::Array dda = *object->getObject("sealinfos")->getArray("sealinfo");
	
	for (int i = 0; i < dda.size(); i++)
	{
		Poco::JSON::Object ob;
		ds["imgdata"] = dda[i]["sealdata"];
		ds["signname"] = dda[i]["sealname"];
		ds["imgItem"] = "82";/// 凯特签章
		ds["imgArea"] = "81";/// 福建CA 
		_sealdata->add(ds);
	}
}

void OESSealProvider::setName()
{
	assert(result.type() == typeid(Object::Ptr));
	Object::Ptr object = result.extract<Object::Ptr>();
	DynamicStruct ds = *object;
	setProperty("name", ds["sealinfos"]["sealbaseinfo"]["username"]);
}

void OESSealProvider::set_vaild_date()
{
	std::string pem;
	pem.append("-----BEGIN CERTIFICATE-----\n");
	pem.append(_certContent);
	pem.append("\n-----END CERTIFICATE-----\n");
	std::istringstream istr(pem);
	X509Certificate cert(istr);
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
			std::ofstream fs("OES_ReadSealData.json");
			fs.write(_content.data(), _content.size());
			fs.close();
			std::ifstream input("OES_ReadSealData_utf8.json");
			Parser ps;
			result = ps.parse(input);
			assert(result.type() == typeid(Object::Ptr));
			if (result.type() != typeid(Object::Ptr))
				throw Poco::Exception("the data is not a JSON Object!");
		}
	}
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
		_count = fn(_x509cer.data(), _x509cer.size(), (unsigned char*)tmp.begin(), &len);
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

void OESSealProvider::setProperty(const std::string& name, const std::string& value)
{
	if (name == "name")
	{
		_name = value;
	}
	else if (name == "code")
	{
		_code = value;
	}
	else if (name == "validStart")
	{
		_validStart = value;
	}
	else if (name == "validEnd")
	{
		_validEnd = value;
	}
	else
	{
		SealProvider::setProperty(name, value);
	}
}

std::string OESSealProvider::getProperty(const std::string& name) const
{
	if (name == "name")
	{
		return _name;
	}
	else if (name == "code")
	{
		return _code;
	}
	else if (name == "validStart")
	{
		return _validStart;
	}
	else if (name == "validEnd")
	{
		return _validEnd;
	}
	else
	{
		return SealProvider::getProperty(name);
	}
}