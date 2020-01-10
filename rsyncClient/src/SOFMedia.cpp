#include "SOFMedia.h"
#include "Utility.h"

using namespace Reach;
using namespace Reach::ActiveX;

SOFMedia::SOFMedia()
{
	GetContainerId();
}

SOFMedia::~SOFMedia()
{

}

void SOFMedia::extract()
{
	FetchKeySN();
	GetCertBase64String();
	CertValidity();
	GetImgAreaFromDN();
}