#include "HT5488003Media.h"
#include "TCardCert.h"
#include "Utility.h"
#include "Poco/Base64Encoder.h"

using namespace Reach;
using namespace Reach::ActiveX;

using Poco::Base64Encoder;
using Poco::Base64EncodingOptions;

extern std::string SOF_GetCertInfoByOid(std::string Base64EncodeCert, std::string oid);

HT5488003Media::HT5488003Media()
	:_hDev(0)
{
	Utility::message("Enter HT5488003Media");
	setProperty("Provider", "HT5488003Media");
	sl.load("FJCA_TCardCert.dll");
	open();
}

HT5488003Media::~HT5488003Media()
{
	close();
	sl.unload();
	Utility::message("Exit HT5488003Media");
}

void HT5488003Media::extract()
{
	GetCertBase64String();
	CertValidity();
	FetchKeySN();
	GetImgAreaFromDN();
}

void HT5488003Media::GetCertBase64String()
{
	if (hasCert("RSA"))
		setProperty("cert", readRSACert());
	else if (hasCert("ECC"))
		setProperty("cert", readECCCert());
	else
		poco_assert(0);
}

void HT5488003Media::open()
{
	typedef BOOL(*InitTCard)(
		IN char			*szDevName,
		OUT DEVHANDLE	*phDev
		);

	InitTCard pfn = (InitTCard)sl.getSymbol("InitTCard");
	poco_assert(pfn);

	int rv = 0;
	rv = (*pfn)("USB1", &_hDev);
	poco_assert(rv);
}

void HT5488003Media::close()
{
	typedef BOOL(*ExitTCard)(
		IN DEVHANDLE	hDev
		);

	ExitTCard pfn = (ExitTCard)sl.getSymbol("ExitTCard");
	poco_assert(pfn);

	int rv = 0;
	rv = (*pfn)(_hDev);
	poco_assert(rv);
}

bool HT5488003Media::hasCert(const std::string& type)
{
	if (type == "RSA")
		return hasRSACert();
	else if (type == "ECC")
		return hasECCCert();
	else
		poco_assert(0);

	return false;
}

bool HT5488003Media::hasRSACert()
{
	typedef BOOL(*TCardGetCertNo)(
		OUT BYTE		*pbCertNo,
		IN DEVHANDLE	hDev
		);

	TCardGetCertNo pfn = (TCardGetCertNo)sl.getSymbol("TCardGetCertNo");
	poco_assert(pfn);

	BYTE no = 0;
	int rv = 0;

	rv = (*pfn)(&no, _hDev);
	poco_assert(rv);
	if (no > 0)
		return true;
	return false;
}

bool HT5488003Media::hasECCCert()
{
	typedef BOOL(*TCardECCGetCertNo)(
		OUT BYTE		*pbCertNo,
		IN DEVHANDLE	hDev
		);

	TCardECCGetCertNo pfn = (TCardECCGetCertNo)sl.getSymbol("TCardECCGetCertNo");
	poco_assert(pfn);

	BYTE no = 0;
	int rv = 0;

	rv = (*pfn)(&no, _hDev);
	poco_assert(rv);
	if (no > 0)
		return true;
	return false;
}

std::string HT5488003Media::readRSACert()
{
	typedef BOOL(*TCardSetCertNo)(
		IN BYTE			byCertNo,
		IN DEVHANDLE	hDev
		);

	TCardSetCertNo set = (TCardSetCertNo)sl.getSymbol("TCardSetCertNo");
	poco_assert(set);

	typedef BOOL(*TCardReadCert)(
		OUT BYTE		*pbCert,
		IN OUT DWORD	*pdwCertLen,
		IN DEVHANDLE	hDev
		);

	TCardReadCert read = (TCardReadCert)sl.getSymbol("TCardReadCert");
	poco_assert(read);

	int rv = 0;

	rv = (*set)(0x01, _hDev);
	poco_assert(rv);

	DWORD len = 2048;
	std::vector<char> vCert(len, 0);
	rv = (*read)((BYTE*)vCert.data(), &len, _hDev);
	if (!rv && len > vCert.size()) {
		vCert.resize(len + 1);
		rv = (*read)((BYTE*)vCert.data(), &len, _hDev);
	}

	poco_assert(rv);
	vCert.resize(len);

	std::ostringstream ostr;
	Poco::Base64Encoder encoder(ostr);
	encoder.rdbuf()->setLineLength(0);
	encoder.write(vCert.data(), vCert.size());
	encoder.close();

	return ostr.str();
}

std::string HT5488003Media::readECCCert()
{
	typedef BOOL(*TCardECCSetCertNo)(
		IN BYTE			byCertNo,
		IN DEVHANDLE	hDev
		);
	TCardECCSetCertNo eccSet = (TCardECCSetCertNo)sl.getSymbol("TCardECCSetCertNo");
	poco_assert(eccSet);

	typedef BOOL(*TCardECCReadCert)(
		OUT BYTE		*pbCert,
		IN OUT DWORD	*pdwCertLen,
		IN DEVHANDLE	hDev
		);
	TCardECCReadCert eccRead = (TCardECCReadCert)sl.getSymbol("TCardECCReadCert");

	int rv = 0;

	rv = (*eccSet)(0x01, _hDev);
	poco_assert(rv);

	DWORD len = 2048;
	std::vector<char> vCert(len, 0);
	rv = (*eccRead)((BYTE*)vCert.data(), &len, _hDev);
	if (!rv && len > vCert.size()) {
		vCert.resize(len + 1);
		rv = (*eccRead)((BYTE*)vCert.data(), &len, _hDev);
	}

	poco_assert(rv);
	vCert.resize(len);

	std::ostringstream ostr;
	Poco::Base64Encoder encoder(ostr);
	encoder.rdbuf()->setLineLength(0);
	encoder.write(vCert.data(), vCert.size());
	encoder.close();

	return ostr.str();
}

void HT5488003Media::FetchKeySN()
{
	std::string cert = getProperty("cert");
	std::string text = SOF_GetCertInfoByOid(cert, "1.2.156.112578.1");
	utility_message(text);

	text = text.substr(text.rfind('@') + 1);
	utility_message(text);
	if (text.size() > 12)
		text = text.substr(0, 12);

	utility_message(text);
	setProperty("keysn", text);
}