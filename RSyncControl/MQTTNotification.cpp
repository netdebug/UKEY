#include "MQTTNotification.h"
#include "Poco/JSON/Parser.h"
#include "Poco/JSON/Object.h"
#include "Poco/Dynamic/Var.h"
#include "poco/DynamicStruct.h"
#include "Poco/Debugger.h"
#include <sstream>
#include <cassert>
#include "Utility.h"

using namespace Poco;
using namespace Poco::JSON;
using namespace Poco::Dynamic;
using Reach::ActiveX::Utility;

enum action
{
	LoginAuth = 1,
	EncryptAuth,
	DecryptAuth,
	SignedSealAuth,
	UnSignedSealAuth,
	GetCertAuth,
	GetSignResult
};


MQTTNotification::MQTTNotification(const std::string& msg)
	:_context(msg),
	_authResult(""),
	_transid(""),
	_message("")
{
	Parser sp;
	Var result = sp.parse(msg);
	assert(result.type() == typeid(Object::Ptr));
	DynamicStruct ds = *result.extract<Object::Ptr>();
	_action = ds["action"];
	if (ds.contains("token")) {
		_token = ds["token"].toString();
	}
	if (ds.contains("msg"))
	{
		std::string retMsg = ds["msg"].toString();
		_message = Utility::UTF8EncodingGBK(retMsg);
	}
	if (ds.contains("transid"))
	{
		_transid = ds["transid"].toString();
	}
	if (ds.contains("authResult"))
	{
		_authResult = ds["authResult"].toString();
	}
}

MQTTNotification::~MQTTNotification()
{
}

MQTTNotificationEvent::MQTTNotificationEvent(const std::string & msg)
	:MQTTNotification(msg)
	,_userID(""),
	_userName(""),
	_mobile("")
{
	if (LoginAuth != action())
	{
		return;
	}
	Parser sp;
	Var result = sp.parse(msg);
	assert(result.type() == typeid(Object::Ptr));
	DynamicStruct ds = *result.extract<Object::Ptr>();
	if (ds.contains("userId")) {
		_userID = ds["userId"].toString();
	}
	if (ds.contains("mobile"))
	{
		_mobile = ds["mobile"].toString();
	}
	if (ds.contains("userName"))
	{
		std::string userName = ds["userName"].toString();
		_userName = Utility::UTF8EncodingGBK(userName);
	}
}

MQTTNotificationEvent::~MQTTNotificationEvent()
{

}
