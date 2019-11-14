#include "KeyDecryptFileRequestHandler.h"
#include<fstream>
using namespace Reach;

KeyDecryptFile::KeyDecryptFile(const std::string& fpPlain, const std::string& fpCipher, const std::string& uid)
	:_fpPlain(fpPlain), _fpCipher(fpCipher), _uid(uid)
{

	std::ofstream ifs;

	ifs.open(fpPlain, std::ios::binary);
	filebuf << ifs.rdbuf();

	_KDD = new KeyDecryptData(filebuf.str(), uid);

	ifs.close();
}

void KeyDecryptFile::run()
{
	_KDD->run();

	std::ofstream ofs;

	ofs.open(_fpCipher, std::ios::binary);
	ofs << filebuf.str();
	ofs.close();

}