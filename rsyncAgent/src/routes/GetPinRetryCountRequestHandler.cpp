#include "GetPinRetryCountRequestHandler.h"
#include "RequestHandleException.h"
#include "../Utility.h"
#include "Reach/Data/Session.h"

using namespace Reach;
using Reach::Data::Session;

GetPinRetryCount::GetPinRetryCount(const std::string& uid)
	:_uid(uid)
{}

void GetPinRetryCount::run()
{
	Session session(Utility::getSession());
	_retryCount = session.getPinRetryCount();

	add("retryCount", _retryCount);
}