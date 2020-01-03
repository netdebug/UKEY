#include "KeySignByP1RequestHandler.h"
#include "Reach/Data/Session.h"
#include "RequestHandleException.h"
#include "../Utility.h"

using namespace Reach;
using Reach::Data::Session;

KeySignByP1::KeySignByP1(const std::string& uid, const std::string& msg)
	:_uid(uid), _msg(msg)
{
}

void KeySignByP1::run()
{
	//Reach::Data::Session session("SOF", "REST");
	//Session session(getEngine(), "REST");
	Session session(Utility::getSession());

	if (_uid != session.contianer())
		throw RequestHandleException(RAR_UNIQUEIDUNCORRECT);

	_signature = session.signByP1(_msg);

	if (_signature.empty()) {
		throw RequestHandleException("SOF_SignData failed!", RAR_UNKNOWNERR);
	}

	add("signdMsg", _signature);
}