#include "ReadSealDataRequestHandler.h"
#include "RequestHandleException.h"
#include "Reach/Data/Session.h"
#include "Utility.h"
#include <cassert>

using namespace Reach;
using Reach::Data::Session;

ReadSealData::ReadSealData(const std::string& uid)
	:_uid(uid)
{

}

void ReadSealData::run()
{
	Session session(Utility::getSession());

	if(_uid != session.contianer())
		throw RequestHandleException(RAR_UNIQUEIDUNCORRECT);

	session.readSealContent();
}