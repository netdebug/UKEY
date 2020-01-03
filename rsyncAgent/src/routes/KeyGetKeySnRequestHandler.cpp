#include "KeyGetKeySnRequestHandler.h"
#include "RequestHandleException.h"
#include "Reach/Data/Session.h"
#include "../Utility.h"

using namespace Reach;
using Reach::Data::Session;

KeyGetKeySn::KeyGetKeySn(const std::string& uid)
	:_uid(uid)
{

}

void KeyGetKeySn::run()
{
	//Session session(getEngine(), "REST");
	Session session(Utility::getSession());

	if (_uid != session.contianer())
		throw RequestHandleException(RAR_UNIQUEIDUNCORRECT);

	_SNkey = session.getSerialNumber();

	add("containerId", _uid);
	add("keySn", _SNkey);
}