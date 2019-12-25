#include "MQTTNotification.h"
#include "Poco/JSON/Parser.h"
#include "Poco/JSON/Object.h"
#include "Poco/Dynamic/Var.h"
#include "poco/DynamicStruct.h"
#include "Poco/Debugger.h"
#include <sstream>
#include <cassert>
#include "../Utility.h"

using namespace Poco;
using namespace Poco::JSON;
using namespace Poco::Dynamic;
using namespace Reach;

enum action
{
	LoginAuth = 1,
	EncryptAuth,
	DecryptAuth,
	SignedSealAuth,
	UnSignedSealAuth,
	GetCertAuth,
	GetSignResult = 44,
};

MQTTNotification::MQTTNotification(const std::string& msg)
	:_context(msg),
	_code(""),
	_msg("")
{
	const char* sJson = "{\"authResult\":\"\", \"authMsg\" : \"1\",\"transid\" : \"\",\"userId\" : \"\",\"mobile\" : \"\",\"userName\" : \"1\",\"action\" : \"\",\"token\" : \"\" ,\"signdMsg\" : \"\" ,\"certBase64\" : \"\", \"keySn\":\"\"}";
	DynamicStruct nameList = paraseString(sJson);

	DynamicStruct ds = paraseString(msg);
	if (ds.contains("code"))
	{
		_code = ds["code"].toString();
	}
	std::string error = ds["msg"].toString();
	//_msg = Utility::UTF8EncodingGBK(error);
	std::string data = "";
	if (ds.contains("data"))
	{
		data = ds["data"].toString();
	}
	DynamicStruct dast = paraseString(data);
	DynamicStruct::Iterator it = nameList.begin();
	for (; it != nameList.end(); ++it)
	{
		std::string  name = it->first;
		std::string value = "";
		if (dast.contains(name))
		{
			value = dast[name].toString();
			std::string sec = it->second;
			if (atoi(sec.data()) == 1)
			{
				;//value = Utility::UTF8EncodingGBK(value);
			}
		}
		_data[name] = value;
	}
}

DynamicStruct MQTTNotification::paraseString(const std::string& str)
{
	Parser sp;
	Var result = sp.parse(str);
	assert(result.type() == typeid(Object::Ptr));
	DynamicStruct dast = *result.extract<Object::Ptr>();
	return dast;
}


MQTTNotification::~MQTTNotification()
{

}
