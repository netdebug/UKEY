#include "SOFMedia.h"
#include "Utility.h"

using namespace Reach;
using namespace Reach::ActiveX;

SOFMedia::SOFMedia()
{
}

SOFMedia::~SOFMedia()
{

}

void SOFMedia::extract()
{
	FetchKeySN();
	GetCertBase64String();
	CertValidity();
}