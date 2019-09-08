#include "DecryptFileRequestHandler.h"
#include "RequestHandleException.h"
#include "ErrorCode.h"
#include "Utility.h"
#include <cassert>

using namespace Reach;

DecryptFile::DecryptFile(std::string& SymKey, std::string& EncryptFile, std::string& OutDir)
:_kv(SymKey), _encrypt(EncryptFile), _decrypt_directory(OutDir)
{
	assert(!_decrypt_directory.empty());
	if (_encrypt.empty())
		throw RequestHandleException(RAR_UNKNOWNERR);
}
void DecryptFile::run()
{
	//UDevice::default();
	_decrypted = Utility::SOF_DecryptFile(_kv, _encrypt, _decrypt_directory);
	if (!_decrypted)
		throw RequestHandleException(RAR_UNKNOWNERR);
}
