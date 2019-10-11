#include "OESSealProvider.h"
#include "Poco/UUIDGenerator.h"
#include "Poco/UUID.h"
#include "Poco/Util/Application.h"
#include "Poco/Exception.h"
#include "Poco/JSON/Parser.h"
#include "Poco/JSON/Object.h"
#include "Poco/DynamicStruct.h"
#include "Poco/Dynamic/Var.h"
#include "Poco/UUIDGenerator.h"
#include "Poco/Exception.h"
#include "Windows.h"
#include "TCardCert.h"
#include <cassert>

using namespace Reach;

using Poco::Util::Application;
using Poco::SharedLibrary;
using Poco::JSON::Object;
using Poco::JSON::Parser;
using Poco::DynamicStruct;
using Poco::Dynamic::Var;
using Poco::UUIDGenerator;

OESSealProvider::OESSealProvider()
{
	sl.load("StampManageSystem.dll");
	sl2.load("TCardCert.dll");
}

OESSealProvider::~OESSealProvider()
{
	sl.unload();
	sl2.unload();
}

void OESSealProvider::read(Object::Ptr JSONin, Object::Ptr JSONout)
{
	Application& app = Application::instance();

	getCerContent();
	readSeal();

	Parser ps;
	Var result = ps.parse(_content);
	assert(result.type() == typeid(Object::Ptr));
	Object::Ptr object = result.extract<Object::Ptr>();
	DynamicStruct ds = *object;
	setProperty("name", ds["sealinfos"]["sealbaseinfo"]["username"]);
	setProperty("code", UUIDGenerator::defaultGenerator().createRandom().toString());

	/// 证书有效期时间
	setProperty("validStart", "");
	setProperty("validEnd", "");

	*JSONout = *JSONin;  /// sealdata object copy template object
	
	{
		Poco::Dynamic::Array da = *object->getArray("sealinfo");
		Poco::JSON::Object ob;
		Poco::JSON::Array seals;
		for (int i = 0; i < da.size(); i++)
		{
			DynamicStruct ds = *JSONout;
			ds["imgdata"] = da[i]["sealdata"];
			ds["signname"] = da[i]["sealname"];
			ds["imgItem"] = "";
			ds["imgArea"] = "";
			seals.add(ds);
		}
		ob.set("seals", seals);

		*JSONout = ob;
	}
}

void OESSealProvider::readSeal()
{
	Application& app = Application::instance();

	static const std::string all_seal = "-1";
	typedef int (*OES_ReadSealData)(
		const char*signCertB64Data,
		const long certDataLen,
		const char*sealID,
		unsigned char*puchSealJson,
		long * puchSealJsonLen);

	std::string name("OES_ReadSealData");
	if (sl.hasSymbol(name))
	{
		long puchSealJsonLen = 0;
		OES_ReadSealData fn = (OES_ReadSealData)sl.getSymbol(name);
		int ret = fn(_x509cer.data(), _x509cer.length(), all_seal.data(), nullptr, &puchSealJsonLen);
		if(ret < 0 )
			throw Poco::Exception("readSeal get json length exception!");

		Poco::Buffer<unsigned char> puchSealJson(puchSealJsonLen);
		ret =  fn(_x509cer.data(), _x509cer.length(), all_seal.data(), puchSealJson.begin(), &puchSealJsonLen);
		if (ret < 0)
			throw Poco::Exception("readSeal exception!");

		_content.assign(puchSealJson.begin(), puchSealJson.end());
	}
}

void OESSealProvider::count()
{
	Application& app = Application::instance();

	typedef int(*OES_GetSealCount)(const char*signCert, const long DataLen, unsigned char*puchID, long*puchIDsLen);
	std::string name("OES_GetSealCount");
	if (sl.hasSymbol(name))
	{
		OES_GetSealCount fn = (OES_GetSealCount)sl.getSymbol(name);
		long bufferLen = 0;
		_count = fn(_x509cer.data(), _x509cer.length(), 0, &bufferLen);
		if (_count < 0)
			throw Poco::Exception("count exception!");

		poco_information_f1(app.logger(), "seal.data : -> %s", _count);
	}
}

void OESSealProvider::getCerContent()
{
	Application& app = Application::instance();

	int rv = 0;
	HANDLE hDev = NULL;

	rv = InitTCard("USB1", &hDev);

	if (!rv) throw Poco::SystemException("USB1");

	char no = '1';
	TCardSetCertNo(static_cast<BYTE>(no), hDev);
	
	DWORD len = 0;
	rv = TCardReadCert(0, &len, hDev);
	if (!rv) throw Poco::SystemException("TCardReadCert len");

	Poco::Buffer<BYTE> cer(len);
	rv = TCardReadCert(cer.begin(), &len, hDev);
	if (!rv) throw Poco::SystemException("TCardReadCert cer");
	_x509cer.append(cer.begin(), cer.end());
	poco_information_f1(app.logger(), "x509 : \n%s", cer);
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