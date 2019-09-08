#include "GetPinRetryCountRequestHandler.h"
#include "RequestHandleException.h"
#include "Utility.h"

using namespace Reach;

GetPinRetryCount::GetPinRetryCount(const std::string& uid)
	:_uid(uid)
{}

void GetPinRetryCount::run()
{

	_retryCount = Utility::SOF_GetPinRetryCount(_uid);

	add("retryCount", _retryCount);
}