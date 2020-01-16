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

extern std::string SOF_GetCertInfoByOid(std::string Base64EncodeCert, std::string oid);

FJCAMedia::FJCAMedia()
{
}

FJCAMedia::~FJCAMedia()
{
}

void FJCAMedia::extract()
{
	GetCertBase64String();
	CertValidity();
	fetchKeySN();
}

bool Reach::FJCAMedia::hasCert(const std::string & type)
{
	if (type == "RSA")
		return hasRSACert();
	else if (type == "ECC")
		return hasECCCert();
	else
		poco_assert(0);

	return false;
}

void FJCAMedia::GetCertBase64String()
{
	std::string nakedCert;

	if (hasCert("RSA"))
		nakedCert = readRSACert();
	else if (hasCert("ECC"))
		nakedCert = readECCCert();
	else
		poco_assert(0);

	poco_assert(!nakedCert.empty());

	std::ostringstream ostr;
	Poco::Base64Encoder encoder(ostr);
	encoder.rdbuf()->setLineLength(0);
	encoder.write(nakedCert.data(), nakedCert.size());
	encoder.close();

	setProperty("cert", ostr.str());
}

void FJCAMedia::fetchKeySN()
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

void FJCAMedia::handleLastError(int code)
{
	switch (code) {
	case 0:
		throw Poco::IOException("IOException", getProperty("Provider"), code);
	default:
		throw Poco::UnhandledException("UnhandledException", getProperty("Provider"), code);
	}
}