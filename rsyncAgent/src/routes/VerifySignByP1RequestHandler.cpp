#include "VerifySignByP1RequestHandler.h"
#include "Reach/Data/Session.h"
#include "RequestHandleException.h"

using namespace Reach;
using Reach::Data::Session;

VerifySignByP1::VerifySignByP1(const std::string& base64, const std::string& msg, const std::string& signature)
	:_base64(base64), _msg(msg), _signature(signature)
{
}

void VerifySignByP1::run()
{
	//Reach::Data::Session session("SOF", "REST");
	Session session(getEngine(), "REST");
	_val = session.verifySignByP1(_base64, _msg, _signature);

	if (!_val) {
		throw RequestHandleException("SOF_VerifySignedData failed!", RAR_UNKNOWNERR);
	}
}