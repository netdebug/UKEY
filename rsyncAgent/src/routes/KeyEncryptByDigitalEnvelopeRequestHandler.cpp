#include "KeyEncryptByDigitalEnvelopeRequestHandler.h"
#include "RequestHandleException.h"
#include "Poco/File.h"
#include "../Utility.h"

using namespace Reach;

using Poco::File;

KeyEncryptByDigitalEnvelope::KeyEncryptByDigitalEnvelope(const std::string& SourceFile, const std::string& EncryptFile, std::string cert)
	:_source(SourceFile), _encrypt(EncryptFile), _cert(cert),
	_encrypted(false), _random_digital(""), _cryptogrphic("")
{
	if (_cert.empty())
		throw RequestHandleException(_cert, RAR_ERRENCRYPTBASE64CERT);

	File fi(_source);
	if (!fi.exists())
		throw RequestHandleException(fi.path(), RAR_ERRNOENCRYPT);

}

void KeyEncryptByDigitalEnvelope::run()
{
	//UDevice::default();

	///Symmetric-key algorithm by _random_digital
	///_encrypt_data = symmetric-key_algorithm(_random_digital,_source_data);
	_random_digital = Utility::SOF_GenRandom(Utility::random());
	_encrypted = Utility::SOF_EncryptFile(_random_digital, _source, _encrypt);
	if (!_encrypted)
		throw Poco::LogicException("SOF_EncryptFile failed!", Utility::SOF_GetLastError());

	///Asymmetric_key algorithm by public cert
	///_cryptogrphic = asymmetric_key_algorithm(_cert,_random_digital);
	_cryptogrphic = Utility::SOF_AsEncrypt(_cert, _random_digital);
	if (_cryptogrphic.empty()) {
		throw RequestHandleException("SOF_AsEncrypt failed!", RAR_ENCYPTFAILED);
	}

	_cryptogrphic.append("@@@");
	_cryptogrphic.append(_cert);

	add("rsKey", _cryptogrphic);
}