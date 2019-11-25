#include "EncryptFileRequestHandler.h"
#include "RequestHandleException.h"
#include "ErrorCode.h"
#include "Poco/File.h"
#include "Poco/FileStream.h"
#include "Poco/Crypto/CipherFactory.h"
#include "Poco/Crypto/CipherKey.h"
#include "Poco/Crypto/Cipher.h"
#include "Poco/Crypto/CryptoStream.h"
#include "Poco/Base64Encoder.h"
#include "Poco/StreamCopier.h"
#include "Poco/String.h"
#include "Utility.h"
#include <cassert>

using namespace Reach;
using Poco::File;
using Poco::Crypto::CipherFactory;
using Poco::Crypto::Cipher;
using Poco::Crypto::CipherKey;
using Poco::Crypto::CryptoOutputStream;
using Poco::Base64Encoder;

EncryptFile::EncryptFile(const std::string& SourceFile, const std::string& EncryptFile)
	:_sink(SourceFile), _sank(EncryptFile), _encrypted(false)
{
	if(_sink.bad())
		throw RequestHandleException(RAR_UNKNOWNERR);

	generateKey();
}

void EncryptFile::generateKey()
{
	Application& app = Application::instance();
	///TODO: SMS4-CBC - Further write to config()
	//CipherKey ckey("SMS4-CBC");
	CipherKey ckey("aes256");
	CipherFactory& factory = CipherFactory::defaultFactory();
	_pCipher = factory.createCipher(ckey);

	std::ostringstream keyStream;
	Base64Encoder encoder(keyStream);

	std::string delim("IV$");
	encoder.write(reinterpret_cast<const char*>(&ckey.getKey()[0]), ckey.keySize());
	encoder << delim;
	encoder.write(reinterpret_cast<const char*>(&ckey.getIV()[0]), ckey.ivSize());
	encoder.close();

	_symKey = keyStream.str();

	poco_information_f1(app.logger(), "EncryptFile CipherKey::ByteVec:\n%s", _symKey);
}

void EncryptFile::run()
{
	Application& app = Application::instance();

	CryptoOutputStream encryptorStream(_sank, _pCipher->createEncryptor());
	Poco::StreamCopier::copyStream(_sink, encryptorStream);
	encryptorStream.close();

	add("symKey", _symKey);
}