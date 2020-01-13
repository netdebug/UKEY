#include "FT3000GMMedia.h"
#include "FCardCert.h"
#include "Utility.h"
#include "Poco/Base64Encoder.h"

using namespace Reach;
using namespace Reach::ActiveX;

using Poco::Base64Encoder;
using Poco::Base64EncodingOptions;

FT3000GMMedia::FT3000GMMedia()
	:_hDev(0)
{
	Utility::message("Enter FT3000GMMedia");
	setProperty("Provider", "FT3000GMMedia");
	sl.load("FJCA_FCardCert.dll");
}

FT3000GMMedia::~FT3000GMMedia()
{
	close();
	sl.unload();
	Utility::message("Exit FT3000GMMedia");
}

void FT3000GMMedia::open()
{
	typedef BOOL (*InitFCard)(
		IN char			*szDevName,
		OUT DEVHANDLE	*phDev
	);

	InitFCard pfn = (InitFCard)sl.getSymbol("InitFCard");
	poco_assert(pfn);

	int rv = 0;
	rv = (*pfn)("USB1", &_hDev);
	poco_assert(rv);
}

void FT3000GMMedia::close()
{
	if (!_hDev) return;

	typedef BOOL (*ExitFCard)(
		IN DEVHANDLE	hDev
	);

	ExitFCard pfn = (ExitFCard)sl.getSymbol("ExitFCard");
	poco_assert(pfn);

	int rv = 0;
	rv = (*pfn)(_hDev);
	poco_assert(rv);
}

bool FT3000GMMedia::hasRSACert()
{
	typedef BOOL (*FCardGetCertNo)(
		OUT BYTE		*pbCertNo,
		IN DEVHANDLE	hDev
	);

	FCardGetCertNo pfn = (FCardGetCertNo)sl.getSymbol("FCardGetCertNo");
	poco_assert(pfn);

	BYTE no = 0;
	int rv = 0;

	rv = (*pfn)(&no, _hDev);
	poco_assert(rv);
	if (no > 0) 
		return true;
	return false;
}

bool FT3000GMMedia::hasECCCert()
{
	typedef BOOL (*FCardECCGetCertNo)(
		OUT BYTE		*pbCertNo,
		IN DEVHANDLE	hDev
	);

	FCardECCGetCertNo pfn = (FCardECCGetCertNo)sl.getSymbol("FCardECCGetCertNo");
	poco_assert(pfn);

	BYTE no = 0;
	int rv = 0;

	rv = (*pfn)(&no, _hDev);
	poco_assert(rv);
	if (no > 0)
		return true;
	return false;
}

std::string FT3000GMMedia::readRSACert()
{
	typedef BOOL (*FCardSetCertNo)(
		IN BYTE			byCertNo,
		IN DEVHANDLE	hDev
	);

	FCardSetCertNo set = (FCardSetCertNo)sl.getSymbol("FCardSetCertNo");
	poco_assert(set);

	typedef BOOL (*FCardReadCert)(
		OUT BYTE		*pbCert,
		IN OUT DWORD	*pdwCertLen,
		IN DEVHANDLE	hDev
	);

	FCardReadCert read = (FCardReadCert)sl.getSymbol("FCardReadCert");
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

	std::string text;
	std::move(vCert.begin(), vCert.end(), std::back_inserter(text));

	return text;
}

std::string FT3000GMMedia::readECCCert()
{
	typedef BOOL (*FCardECCSetCertNo)(
		IN BYTE			byCertNo,
		IN DEVHANDLE	hDev
	);
	FCardECCSetCertNo eccSet = (FCardECCSetCertNo)sl.getSymbol("FCardECCSetCertNo");
	poco_assert(eccSet);

	typedef BOOL (*FCardECCReadCert)(
		OUT BYTE		*pbCert,
		IN OUT DWORD	*pdwCertLen,
		IN DEVHANDLE	hDev
	);
	FCardECCReadCert eccRead = (FCardECCReadCert)sl.getSymbol("FCardECCReadCert");

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

	std::string text;
	std::move(vCert.begin(), vCert.end(), std::back_inserter(text));

	return text;
}
