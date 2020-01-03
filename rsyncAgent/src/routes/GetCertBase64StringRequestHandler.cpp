#include "GetCertBase64StringRequestHandler.h"
#include "RequestHandleException.h"
#include "Reach/Data/Session.h"
#include "../Utility.h"

using namespace Reach;
using Reach::Data::Session;

GetCertBase64String::GetCertBase64String(short ctype, const std::string& uid)
	:_type(ctype), _uid(uid)
{
}

void GetCertBase64String::run()
{
	//Session session(getEngine(), "REST");
	Session session(Utility::getSession());

	if (_uid != session.contianer())
		throw RequestHandleException(RAR_UNIQUEIDUNCORRECT);

	_content = session.getCertBase64String(_type);

	add("certBase64", _content);
}