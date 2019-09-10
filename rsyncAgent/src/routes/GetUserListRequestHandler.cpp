#include "GetUserListRequestHandler.h"
#include "RequestHandleException.h"
#include "Reach/Data/Session.h"
#include "Reach/Data/DataException.h"
#include "ErrorCode.h"

using namespace Reach;
using Reach::Data::Session;

void GetUserList::run()
{
	Session session(getEngine(), "REST");
	_line = session.getUserList();

	if (_line.empty())
		throw RequestHandleException(RAR_NOUNIQUEID);

	add("userlist", _line);
}