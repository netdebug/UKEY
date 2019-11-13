#include "KeyEncryptFileRequestHandler.h"

using namespace Reach;

KeyEncryptFile::KeyEncryptFile(const std::string& fpPlain, const std::string& fpCipher, const std::string& cert)
	:_fpPlain(fpPlain), _fpCipher(fpCipher), _cert(cert)
{

}

void KeyEncryptFile::run()
{

}