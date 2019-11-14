#include "KeyEncryptFileRequestHandler.h"
#include "KeyEncryptDataRequestHandler.h"
#include <fstream>
#include <sstream>
using namespace Reach;

KeyEncryptFile::KeyEncryptFile(const std::string& fpPlain, const std::string& fpCipher, const std::string& cert)
	:_fpPlain(fpPlain), _fpCipher(fpCipher), _cert(cert)
{
	std::ifstream ifs;
	

	ifs.open(fpPlain, std::ios::binary);
	filebuf << ifs.rdbuf();
	ifs.close();

	_KED = new KeyEncryptData(filebuf.str(), cert);

	
}

void KeyEncryptFile::run()
{
	_KED->run();

	std::ofstream ofs;

	ofs.open(_fpCipher, std::ios::binary);
	ofs << filebuf.str();
	ofs.close();
	
}