#include "OESSealProvider.h"
#include "Poco/Exception.h"
#include "Poco/StreamCopier.h"
#include "Poco/Base64Encoder.h"
#include "Windows.h"
#include "TCardCert.h"
#include "BridgeKG_HARD_EXT.h"
#include "Utility.h"
#include <fstream>
#include <cassert>

//using namespace Poco::JSON;

using namespace Reach;
using namespace Reach::ActiveX;

using Poco::Util::Application;
using Poco::Base64Encoder;
using Poco::Base64EncodingOptions;
using Poco::DateTimeFormatter;
using Poco::StreamCopier;

OESSealProvider::OESSealProvider()
{
	Utility::message("Enter OESSealProvider");

	sl.load("StampManageSystem.dll");

	setProperty("Provider", "OESSealProvider");
}

OESSealProvider::~OESSealProvider()
{
	sl.unload();

	Utility::message("Exit OESSealProvider");
}

void Reach::OESSealProvider::extract()
{
	GetCertBase64String();
	readSeal();
	ExtractSealPicture();
}

void OESSealProvider::ExtractSealPicture()
{
	JSON_PARSE(_sealdata);

	setProperty("name", ds["sealinfos"]["sealbaseinfo"]["username"]);

	Poco::Dynamic::Var info = ds["sealinfos"]["sealinfo"];
	Poco::JSON::Array seals;
	for (int i = 0; i < info.size(); i++)
	{
		Poco::JSON::Object ob;
		ob.set("imgdata", info[i]["sealdata"]);
		ob.set("signname", info[i]["sealname"]);
		ob.set("height", "4.00");
		ob.set("width", "4.00");
		ob.set("imgext", "gif");
		ob.set("signType", "80");///第三方签章
		ob.set("imgItem", "82");/// 凯特签章
		ob.set("imgArea", "81");/// 福建CA 
		seals.add(ob);
	}

	std::ostringstream ostr;
	seals.stringify(ostr);
	setProperty("seals", ostr.str());
}

#include "Poco/String.h"
void OESSealProvider::readSeal()
{
	static const std::string all_seal = "-1";
	typedef int(__stdcall *OES_ReadSealData)(
		const char*signCertB64Data,
		const long certDataLen,
		const char*sealID,
		unsigned char*puchSealJson,
		long * puchSealJsonLen);

	long len = 0;
	OES_ReadSealData fn = (OES_ReadSealData)sl.getSymbol("OES_ReadSealData");
	fn(_certContent.data(), _certContent.size(), all_seal.data(), nullptr, &len);
	if (len > 0) {
		std::vector<char> seal_data(len, 0);
		fn(_certContent.data(), _certContent.size(), all_seal.data(), (unsigned char*)seal_data.data(), &len);
		std::string content;
		content.assign(seal_data.begin(), seal_data.end());/// \0 end
		_sealdata = Utility::GBKEncodingUTF8(content);
	}

	if (_sealdata.empty())
		throw Poco::DataFormatException("Invalid seal data", Poco::format("%[1]s\n%[0]s", _sealdata, getProperty("Provider")));
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
			throw Poco::Exception("count exception!", Poco::format("%[1]s\n%[0]d", _count, getProperty("Provider")));

		poco_information_f1(app.logger(), "seal.data : -> %s", _count);
	}
}

void OESSealProvider::GetCertBase64String()
{
	int rv = 0;
	HANDLE hDev = NULL;
	std::string content;

	rv = InitTCard("USB1", &hDev);
	//if (!rv) throw Poco::LogicException("USB1");
	if (!rv) handleLastError(rv);

	BYTE no = 0;
	rv = TCardGetCertNo(&no, hDev);
	//if (!rv && !no) throw Poco::LogicException("OESSealProvider cerification not found!");
	if (!rv) handleLastError(rv);

	rv = TCardSetCertNo(0x01, hDev);
	//if (!rv) throw Poco::LogicException("OESSealProvider cerification not found!");
	if (!rv) handleLastError(rv);

	DWORD len = 1024;
	std::vector<char> vCert(len, 0);
	rv = TCardReadCert((BYTE*)vCert.data(), &len, hDev);
	if (!rv && len > vCert.size()) {
		vCert.resize(len + 1);
		rv = TCardReadCert((BYTE*)vCert.data(), &len, hDev);
	}
	//if (!rv) throw Poco::LogicException("TCardReadCert failed!");
	if (!rv) handleLastError(rv);

	vCert.resize(len);

	std::ostringstream ostr;
	Poco::Base64Encoder encoder(ostr);
	encoder.write(vCert.data(), vCert.size());
	encoder.close();

	

	_certContent = ostr.str();
	setProperty("cert", _certContent);
	rv = ExitTCard(hDev);
}

void OESSealProvider::handleLastError(int code)
{
	switch (code) {
	case 0:
		throw Poco::IOException("IOException", getProperty("Provider"), code);
	default:
		throw Poco::UnhandledException("UnhandledException", getProperty("Provider"), code);
	}
}

void OESSealProvider::FetchKeySN()
{
	BridgeKG_HARD_EXT ext;
	ext.WebConnectDev();
	std::string keysn = ext.WebGetSerial();
	setProperty("keysn", keysn);
	ext.WebDisconnectDev();
}

void OESSealProvider::GetDeviceInfo(void* hDev)
{
	typedef struct {
		char	szDeviceInfo[256];
		char	szVID[4];
		char	szPID[4];
		char	szSN[20];
		char	szPD[8];
		char	szPI[20];
		char	szAF[20];
		char	szLabel[20];
		DWORD	pdwTotalSpace;
		DWORD	pdwFreeSpace;
	} _device_info, *p_device_info;

	_device_info deviceinfo = { 0 };
	std::memset(&deviceinfo, 0, sizeof(deviceinfo));

	bool rv = TCardGetDeviceInfo(
		deviceinfo.szDeviceInfo,
		deviceinfo.szVID,
		deviceinfo.szPID,
		deviceinfo.szSN,
		deviceinfo.szPD,
		deviceinfo.szPI,
		deviceinfo.szAF,
		deviceinfo.szLabel,
		&deviceinfo.pdwTotalSpace, &deviceinfo.pdwFreeSpace, hDev);

	if (!rv) handleLastError(rv);
}