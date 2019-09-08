#include "VerifySignByP7RequestHandler.h"
#include "RequestHandleException.h"
#include "Utility.h"

using namespace Reach;

VerifySignByP7::VerifySignByP7(const std::string& textual, const std::string& signature, int mode)
	:_textual(textual), _signature(signature), _mode(mode), _verify(false)
{}

void VerifySignByP7::run()
{
	//UDevice::default();
	/////1 = Detached mode ,textual must be cleared!
	if (_mode)
		_textual.clear();

	_verify = Utility::SOF_VerifySignedMessage(_signature, _textual);
	if (!_verify) {
		throw RequestHandleException("SOF_VerifySignedMessage failed!", RAR_UNKNOWNERR);
	}
}