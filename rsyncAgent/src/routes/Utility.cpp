#include "Utility.h"
#include "Poco/Exception.h"

using namespace Reach;

Utility::~Utility()
{

}

std::string Utility::SOF_GenRandom(int size)
{
	throw Poco::NotImplementedException("SOF_GenRandom");
	return "";
}

bool Utility::SOF_EncryptFile(std::string&, std::string&, std::string&)
{
	throw Poco::NotImplementedException("SOF_EncryptFile");
	return false;
}

std::string Utility::SOF_ExportExChangeUserCert(const std::string&)
{
	throw Poco::NotImplementedException("SOF_ExportExChangeUserCert");
	return "";
}

std::string Utility::SOF_AsDecrypt(std::string&, std::string&)
{
	throw Poco::NotImplementedException("SOF_AsDecrypt");
	return "";
}

std::string Utility::SOF_AsEncrypt(std::string &, std::string &)
{
	throw Poco::NotImplementedException("SOF_AsEncrypt");
	return "";
}

bool Utility::SOF_DecryptFile(std::string&, std::string, std::string)
{
	throw Poco::NotImplementedException("SOF_DecryptFile");
	return false;
}

int Utility::random()
{
	throw Poco::NotImplementedException("random");
	return 16;
}

int Utility::SOF_GetPinRetryCount(const std::string&)
{
	throw Poco::NotImplementedException("SOF_GetPinRetryCount");
	return 0;
}

std::string Utility::SOF_SignMessage(short, std::string&, std::string&)
{
	throw Poco::NotImplementedException("SOF_SignMessage");
	return "";
}

bool Utility::SOF_VerifySignedMessage(const std::string&, const std::string&)
{
	throw Poco::NotImplementedException("SOF_VerifySignedMessage");
	return false;
}

int Utility::SOF_GetLastError()
{
	return 0xA000001;
}
