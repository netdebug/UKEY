#include "XSSealProvider.h"
#include "Poco/SharedLibrary.h"
#include "Poco/XML/XMLStream.h"
#include <cassert>

using namespace Reach;
using Poco::SharedLibrary;

typedef char* (*ReadSealData)(int nIndex);

XSSealProvider::XSSealProvider()
{
	SharedLibrary sl;
	std::string fnName("ReadSealData");
	sl.load("XSSealProviderLib.dll");
	if (sl.hasSymbol(fnName)) {
		fnPtr = (ReadSealData)sl.getSymbol(fnName);
		assert(fnPtr);
		_content = fnPtr(XSSealProvider::all_seal);
	}
}

std::string XSSealProvider::read()
{
	std::string content = fnPtr(XSSealProvider::all_seal);
	return content;
}