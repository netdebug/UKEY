#include "ChangePassWdRequestHandler.h"
#include "RequestHandleException.h"
#include "ErrorCode.h"
#include "Reach/Data/Session.h"
#include "../Utility.h"

using namespace Reach;
using Reach::Data::Session;

ChangePassWd::ChangePassWd(const std::string& uid, const std::string& oldCode, const std::string& newCode)
	:_uid(uid), _oldCode(oldCode), _newCode(newCode)
{
}

void ChangePassWd::run()
{
	//UDevice::default();
	Session session(Utility::getSession());
	//if (!SOF_ChangePassWd(_uid, _oldCode, _newCode))
	if (_uid != session.contianer())
		throw RequestHandleException(RAR_UNIQUEIDUNCORRECT);

	if (!session.changePW(_oldCode, _newCode))
	{
		throw RequestHandleException("SOF_ChangePassWd failed", RAR_UNKNOWNERR);
	}
}