#include "MQTTNotification.h"
#include "Poco/JSON/Parser.h"
#include "Poco/JSON/Object.h"
#include "Poco/Dynamic/Var.h"
#include "poco/DynamicStruct.h"
#include "Poco/Debugger.h"
#include <sstream>
#include <cassert>

using namespace Poco;
using namespace Poco::JSON;
using namespace Poco::Dynamic;

MQTTNotification::MQTTNotification(const std::string& message)
	:context(message),
	authResult(""),
	transid(""),
	message("")
{
	Parser sp;
	Var result = sp.parse(message);
	assert(result.type() == typeid(Object::Ptr));
	DynamicStruct ds = *result.extract<Object::Ptr>();
	action = ds["action"];
	if (ds.contains("token")) {
		token = ds["token"].toString();
	}
}

MQTTNotification::~MQTTNotification()
{
}
