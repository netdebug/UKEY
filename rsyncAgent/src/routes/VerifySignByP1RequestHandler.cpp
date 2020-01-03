#include "VerifySignByP1RequestHandler.h"
#include "Reach/Data/Session.h"
#include "RequestHandleException.h"
#include "../Utility.h"

using namespace Reach;
using Reach::Data::Session;

extern bool __stdcall FJCA_VerifySign(const char *orgdata, const char *signdata, const char *signcert);

VerifySignByP1::VerifySignByP1(const std::string& base64, const std::string& msg, const std::string& signature)
	:_base64(base64), _msg(msg), _signature(signature), _val(false)
{
}

void VerifySignByP1::run()
{	
	Application& app = Application::instance();
	std::string scheme = app.config().getString("engine.mode", "");
	if (scheme.empty()) {
		_val = FJCA_VerifySign(_msg.c_str(), _signature.c_str(), _base64.c_str());
	}
	else
	{
		Session session(Utility::getSession());
		_val = session.verifySignByP1(_base64, _msg, _signature);

	}

	if (!_val) {
		throw RequestHandleException("SOF_VerifySignedData failed!", RAR_UNKNOWNERR);
	}
}