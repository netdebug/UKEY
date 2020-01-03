#include "KeySignByP7RequestHandler.h"
#include "RequestHandleException.h"
#include "Reach/Data/Session.h"
#include "../Utility.h"

using namespace Reach;
using Reach::Data::Session;

KeySignByP7::KeySignByP7(const std::string& textual, int mode, const std::string& uid)
	:_textual(textual), _mode(mode), _uid(uid)
{
}

void KeySignByP7::run()
{
	//UDevice::default();
	Session session(Utility::getSession());

	if (_uid != session.contianer())
		throw RequestHandleException(RAR_UNIQUEIDUNCORRECT);

	_signature = session.signByP7(_textual, _mode);

	if (_signature.empty()) {
		throw RequestHandleException("SOF_SignMessage failed!", RAR_UNKNOWNERR);
	}

	add("signdMsg", _signature);
}