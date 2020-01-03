#include "KeyDecryptFileRequestHandler.h"
#include "Poco/Base64Decoder.h"
#include "Poco/StreamCopier.h"
#include "Poco/RegularExpression.h"
#include "Poco/FileStream.h"
#include "../Utility.h"
#include <cassert>


using namespace Reach;
using Poco::Base64Decoder;
using Poco::StreamCopier;
using Poco::RegularExpression;
using Poco::FileInputStream;
using Poco::FileOutputStream;

KeyDecryptFile::KeyDecryptFile(const std::string& fpPlain, const std::string& fpCipher, const std::string& uid)
	:_fpPlain(fpPlain), _fpCipher(fpCipher), _uid(uid)
{

}

void KeyDecryptFile::run()
{
	std::string _encrypt_data, _decrypt_data;
	FileInputStream in(_fpCipher);
	assert(in.good());
	in >> _encrypt_data;

	Session session(Utility::getSession());

	if (_uid != session.contianer())
		throw RequestHandleException(RAR_UNIQUEIDUNCORRECT);

	std::string pattern("(\\S+)@@@(\\S+)");
	int options = 0;

	RegularExpression re(pattern, options);
	RegularExpression::Match mtch;

	if (!re.match(_encrypt_data, mtch))
		throw RequestHandleException("KeyDecryptData enRsKey Exception!", RAR_ERRDECRYPTFILEFORMAT);

	std::vector<std::string> tags;
	re.split(_encrypt_data, tags, options);
	std::string& encrypt = tags[1];
	std::string& cert = tags[2];

	assert(tags.size() > 2);
	//std::string content = SOF_ExportExChangeUserCert(_uid);
	enum certType { sign = 1, crypto };
	std::string content = session.getCertBase64String(certType::crypto);

	if (content != cert)
		throw RequestHandleException("certificate error", RAR_ERRDECRYPTCERT);

	_decrypt_data = session.decryptData(encrypt);
	if (_decrypt_data.empty())
		throw RequestHandleException(RAR_DECRYPTFAILED);


	FileOutputStream out(_fpPlain);
	out << _decrypt_data;
	out.close();

	add("rsKey", _decrypt_data);
}