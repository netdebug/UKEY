#include "KeyDecryptFileRequestHandler.h"

using namespace Reach;

KeyDecryptFile::KeyDecryptFile(const std::string& fpPlain, const std::string& fpCipher, const std::string& uid)
	:_fpPlain(fpPlain), _fpCipher(fpCipher), _uid(uid)
{

}

void KeyDecryptFile::run()
{

}