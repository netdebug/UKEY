#include "CertLoginRequestHandler.h"
#include "RequestHandleException.h"
#include "Reach/Data/Session.h"
#include "../Utility.h"

using namespace Reach;
using Reach::Data::Session;
///RS_CertLogin

CertLogin::CertLogin(const std::string& uid, const std::string& password)
	:_uid(uid), _pwd(password)
{
}

void CertLogin::run()
{
	Session session(Utility::getSession());

	if (_uid.empty() || _pwd.empty())
		throw RequestHandleException(RAR_9010);

	if (_uid != session.contianer())
		throw RequestHandleException(RAR_UNIQUEIDUNCORRECT);

	int retryCount = session.getPinRetryCount();
	if (retryCount <= 0)
		throw RequestHandleException(_uid, RAR_UNKNOWNERR);

	if (!session.login(_pwd))
		throw RequestHandleException(_uid, RAR_9011);

	add("containerId", _uid);
}
