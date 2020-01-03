#include "KeyEncryptFileRequestHandler.h"
#include "RequestHandleException.h"
#include "Reach/Data/Session.h"
#include "Poco/FileStream.h"
#include "Poco/StreamCopier.h"
#include "../Utility.h"

using namespace Reach;

KeyEncryptFile::KeyEncryptFile(const std::string& fpPlain, const std::string& fpCipher, const std::string& cert)
	:_fpPlain(fpPlain), _fpCipher(fpCipher), _cert(cert)
{

}

void KeyEncryptFile::run()
{
	std::string plaintext, ciphertext;

	Poco::FileInputStream SI(_fpPlain);
	Poco::StreamCopier::copyToString(SI, plaintext);

	Session session(Utility::getSession());
	if (plaintext.empty())
		throw RequestHandleException(RAR_ERRNODECRYPT);

	ciphertext = session.encryptData(plaintext, _cert);

	ciphertext.append("@@@");
	ciphertext.append(_cert);

	Poco::FileOutputStream out(_fpCipher);
	out.write(ciphertext.data(), ciphertext.size());
	out.close();

	add("encRsKey", ciphertext);
}