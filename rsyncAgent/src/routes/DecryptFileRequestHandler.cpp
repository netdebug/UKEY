#include "DecryptFileRequestHandler.h"
#include "RequestHandleException.h"
#include "ErrorCode.h"
#include "Utility.h"
#include "Poco/FileStream.h"
#include "Poco/Crypto/CipherFactory.h"
#include "Poco/Crypto/CipherKey.h"
#include "Poco/Crypto/Cipher.h"
#include "Poco/Crypto/CryptoStream.h"
#include "Poco/Base64Encoder.h"
#include "Poco/Base64Decoder.h"
#include "Poco/StringTokenizer.h"
#include "Poco/StreamCopier.h"
#include <cassert>

using namespace Reach;
using Poco::Crypto::CipherFactory;
using Poco::Crypto::Cipher;
using Poco::Crypto::CipherKey;
using Poco::Crypto::CryptoOutputStream;
using Poco::Base64Decoder;
using Poco::StringTokenizer;

DecryptFile::DecryptFile(std::string& SymKey, std::string& EncryptFile, std::string& OutFile)
:_kv(SymKey), _encrypt(EncryptFile), _decrypt(OutFile)
{
	assert(!_decrypt.empty());
	if (_encrypt.empty())
		throw RequestHandleException(RAR_UNKNOWNERR);
}
void DecryptFile::run()
{
	Application& app = Application::instance();

	std::istringstream istr(_kv);
	Base64Decoder decoder(istr);
	std::string s;
	Poco::StreamCopier::copyToString(decoder,s);
	StringTokenizer st(s, "IV$", StringTokenizer::TOK_IGNORE_EMPTY);
	assert(st.count() == 2);
	
	CipherKey::ByteVec key(st[0].begin(), st[0].end());
	CipherKey::ByteVec iv(st[1].begin(), st[1].end());
	///TODO: SMS4-CBC - Further write to config()
	CipherKey ckey("SMS4-CBC", key, iv);
	CipherFactory& factory = CipherFactory::defaultFactory();
	Cipher* pCipher = factory.createCipher(ckey);
	
	Poco::FileOutputStream sank(_decrypt);
	CryptoOutputStream decryptor(sank, pCipher->createDecryptor());

	Poco::FileInputStream source(_encrypt);
	Poco::StreamCopier::copyStream(source, decryptor);

	decryptor.close();
	sank.close();

	poco_information_f1(app.logger(), "EncryptFile CipherKey::ByteVec:\n%s", _kv);
}
