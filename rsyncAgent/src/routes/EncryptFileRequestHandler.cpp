#include "EncryptFileRequestHandler.h"
#include "RequestHandleException.h"
#include "ErrorCode.h"
#include "Poco/File.h"
#include "Utility.h"
#include <cassert>

using namespace Reach;
using Poco::File;

EncryptFile::EncryptFile(const std::string& SourceFile, const std::string& EncryptFile)
	:_source(SourceFile), _encrypt(EncryptFile), _encrypted(false)
{
	File fi(_source);
	if (!fi.exists())
		throw RequestHandleException(RAR_UNKNOWNERR);
}
void EncryptFile::run()
{
	//UDevice::default();

	_random_digital = Utility::SOF_GenRandom(Utility::random());
	if (_random_digital.empty()) {
		throw RequestHandleException(RAR_UNKNOWNERR);
	}

	_encrypted = Utility::SOF_EncryptFile(_random_digital, _source, _encrypt);
	if (!_encrypted) {
		throw RequestHandleException(RAR_UNKNOWNERR);
	}

	add("symKey", _random_digital);
}