#include "GetCertInfoRequestHandler.h"
#include "RequestHandleException.h"
#include "Reach/Data/Session.h"

using namespace Reach;
using Reach::Data::Session;

GetCertInfo::GetCertInfo(const std::string& base64, int type)
	:_base64(base64), _type(type)
{
}

void GetCertInfo::run()
{
	/// FJCA SOF all use this
	Session session("SOF", "REST");

	_item = session.getCertInfo(_base64, _type);

	add("info", _item);
}