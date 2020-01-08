#include "FT3000GMMedia.h"
#include "FCardCert.h"
#include "Utility.h"
#include "Poco/Base64Encoder.h"

using namespace Reach;
using namespace Reach::ActiveX;

using Poco::Base64Encoder;
using Poco::Base64EncodingOptions;

FT3000GMMedia::FT3000GMMedia()
{
	Utility::message("Enter FT3000GMMedia");
	setProperty("Provider", "FT3000GMMedia");
}

FT3000GMMedia::~FT3000GMMedia()
{
	Utility::message("Exit FT3000GMMedia");
}

void FT3000GMMedia::extract()
{
	FetchKeySN();
	GetCertBase64String();
	CertValidity();
	GetImgAreaFromDN();
}

void FT3000GMMedia::GetCertBase64String()
{
	int rv = 0;
	HANDLE hDev = NULL;
	std::string content;

	rv = InitFCard("USB1", &hDev);
	poco_assert(rv);

	BYTE no = 0;
	rv = FCardGetCertNo(&no, hDev);
	poco_assert(rv);

	rv = FCardSetCertNo(0x01, hDev);
	poco_assert(rv);

	DWORD len = 2048;
	std::vector<char> vCert(len, 0);
	rv = FCardReadCert((BYTE*)vCert.data(), &len, hDev);
	if (!rv && len > vCert.size()) {
		vCert.resize(len + 1);
		rv = FCardReadCert((BYTE*)vCert.data(), &len, hDev);
	}

	poco_assert(rv);

	vCert.resize(len);

	std::ostringstream ostr;
	Poco::Base64Encoder encoder(ostr);
	encoder.write(vCert.data(), vCert.size());
	encoder.close();

	setProperty("cert", ostr.str());
	rv = ExitFCard(hDev);
	poco_assert(rv);
}

void FT3000GMMedia::FetchKeySN()
{

}