#include "KeyDecryptByDigitalEnvelopeRequestHandler.h"
#include "RequestHandleException.h"
#include "ErrorCode.h"
#include "Poco/File.h"
#include "Poco/RegularExpression.h"
#include "../Utility.h"
#include <cassert>

using namespace Reach;

using Poco::File;
using Poco::RegularExpression;


KeyDecryptByDigitalEnvelope::KeyDecryptByDigitalEnvelope(std::string& uid, std::string& EncryptFile, std::string& OutDir, std::string& cryptogrphic)
	:_uid(uid), _cryptogrphic(cryptogrphic), _encrypt(EncryptFile), _decrypt_directory(OutDir),
	_decrypted(false)
{
	File fi(_encrypt);
	if (!fi.exists())
		throw Poco::FileNotFoundException(fi.path(), RAR_UNKNOWNERR);
}

void KeyDecryptByDigitalEnvelope::run()
{
	//UDevice::default();

	std::string pattern("(\\S+)@@@(\\S+)");
	int options = 0;

	RegularExpression re(pattern, options);
	RegularExpression::Match mtch;

	if (!re.match(_cryptogrphic, mtch))
		throw RequestHandleException("RS_KeyDecryptData enRsKey Exception!", RAR_ERRDECRYPTFILEFORMAT);

	std::vector<std::string> tags;
	re.split(_cryptogrphic, tags, options);
	assert(tags.size() > 2);
	std::string& encrypt = tags[1];
	std::string& cert = tags[2];

	std::string content = Utility::SOF_ExportExChangeUserCert(_uid);

	if (content != cert)
		throw RequestHandleException("certificate error", RAR_ERRDECRYPTCERT);

	///Asymmetric_key algorithm by private cert
	///_cryptogrphic = asymmetric_key_algorithm(_cert,_random_digital);
	_random_digital = Utility::SOF_AsDecrypt(_uid, encrypt);
	if (_random_digital.empty())
		throw Poco::LogicException(Utility::SOF_GetLastError());

	///Symmetric-key algorithm by _random_digital
	///_encrypt_data = symmetric-key_algorithm(_random_digital,_source_data);
	_decrypted = Utility::SOF_DecryptFile(_random_digital, _encrypt, _decrypt_directory);
	if (!_decrypted)
		throw RequestHandleException(RAR_UNKNOWNERR);
}