#include "FJCAMedia.h"
#include "TCardCert.h"
#include "Utility.h"
#include "Poco/Base64Encoder.h"
#include <vector>
#include <sstream>

using namespace Reach;
using namespace Reach::ActiveX;

using Poco::Base64Encoder;
using Poco::Base64EncodingOptions;

FJCAMedia::FJCAMedia()
{
	Utility::message("Enter FJCAMedia");
	setProperty("Provider", "FJCAMedia");
}

FJCAMedia::~FJCAMedia()
{
	Utility::message("Exit FJCAMedia");
}

void FJCAMedia::extract()
{
	FetchKeySN();
	GetCertBase64String();
	CertValidity();
}

void FJCAMedia::GetCertBase64String()
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

	setProperty("cert", ostr.str());
	rv = ExitTCard(hDev);
}

void FJCAMedia::FetchKeySN()
{
	ext.WebConnectDev();
	std::string keysn = ext.WebGetSerial();
	setProperty("keysn", keysn);
	ext.WebDisconnectDev();
}

void FJCAMedia::handleLastError(int code)
{
	switch (code) {
	case 0:
		throw Poco::IOException("IOException", getProperty("Provider"), code);
	default:
		throw Poco::UnhandledException("UnhandledException", getProperty("Provider"), code);
	}
}