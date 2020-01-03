#include "KeyStatusRequestHandler.h"
#include "Reach/Data/Session.h"
#include "RequestHandleException.h"
#include "../Utility.h"

using namespace Reach;
using Reach::Data::Session;

KeyStatus::KeyStatus(const std::string& uid)
	:_uid(uid), _isLogined(false)
{

}

void KeyStatus::run()
{
	Session session(Utility::getSession());

	if (_uid != session.contianer())
		throw RequestHandleException(RAR_UNIQUEIDUNCORRECT);

	std::string signature;
	signature = session.signByP1("KeyStatus");

	_isLogined = !signature.empty();

	if(!_isLogined)
		throw RequestHandleException(RAR_9028);
}