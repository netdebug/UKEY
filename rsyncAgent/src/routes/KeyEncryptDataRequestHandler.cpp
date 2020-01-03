#include "KeyEncryptDataRequestHandler.h"
#include "RequestHandleException.h"
#include "Reach/Data/Session.h"
#include "../Utility.h"

using namespace Reach;
using Reach::Data::Session;

KeyEncryptData::KeyEncryptData(const std::string& paintText, const std::string& base64)
	:_paintext(paintText), _base64(base64), _encrypt_data("")
{
}

void KeyEncryptData::run()
{
	Session session(Utility::getSession());
	if (_paintext.empty())
		throw RequestHandleException(RAR_ERRNODECRYPT);

	_encrypt_data = session.encryptData(_paintext, _base64);

	_encrypt_data.append("@@@");
	_encrypt_data.append(_base64);

	add("encRsKey", _encrypt_data);
}