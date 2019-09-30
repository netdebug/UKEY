#include "QZSyncTask.h"
#include "Poco/Util/Application.h"
#include "Poco/DateTimeFormatter.h"
#include "Poco/MD5Engine.h"
#include "Poco/DigestEngine.h"
#include "Poco/JSON/Parser.h"
#include "Poco/Dynamic/Var.h"
#include "Poco/Dynamic/Struct.h"
#include "Poco/Net/HTTPRequest.h"
#include "Poco/Net/HTTPResponse.h"
#include "Poco/Net/HTTPClientSession.h"
#include "Poco/StreamCopier.h"
#include "Poco/FileStream.h"
#include "Poco/URI.h"
#include "XSSealProvider.h"
#include <cassert>

using namespace Reach;
using namespace Poco::Dynamic;
using namespace Poco::JSON;

using Poco::DynamicStruct;
using Poco::DateTimeFormatter;
using Poco::StreamCopier;
using Poco::FileInputStream;
using Poco::Util::Application;
using Poco::Net::HTTPRequest;
using Poco::Net::HTTPResponse;
using Poco::Net::HTTPClientSession;
using Poco::URI;

QZSyncTask::QZSyncTask()
	:Task("QZSyncTask"),
	_config("QZSyncTask.json")
{
	loadModel();
}

void QZSyncTask::loadModel()
{
	Application& app = Application::instance();

	try
	{
		FileInputStream in(_config);
		Parser parser;
		Var result = parser.parse(in);
		assert(result.type() == typeid(Object::Ptr));

		_model = result.extract<Object::Ptr>();
	}
	catch (JSONException& e)
	{
		poco_information_f1(app.logger(), "JSONException:\n%s", e.displayText());
	}
}

void QZSyncTask::runTask()
{
	Application& app = Application::instance();

	while (!sleep(2000))
	{
		app.logger().trace("busy doing QZSyncTask... " + DateTimeFormatter::format(app.uptime()));

		if (IsUSBKeyPresent()) {
			ReadSealInfo();
			GetKeySN();
			std::string md5 = MD5(sealinfo, keysn);

			if (IsNeedSend()) {
				SendtoKGServer();
			}
		}
	}
}

bool QZSyncTask::IsUSBKeyPresent()
{
	return true;
}

bool QZSyncTask::IsNeedSend()
{
	if (hasAlreadySnyc())
		return false;
	if (ExistRecordOnKGServer())
		return false;

	return true;
}

bool QZSyncTask::hasAlreadySnyc()
{
	//checkKGServer(keysn, md5)
	return false;
}

std::string QZSyncTask::submitToKGServer(const std::string& url, const std::string& data)
{
	Application& app = Application::instance();
	poco_information_f2(app.logger(), "post : %s\n sendRequest:\n%s", url, data);

	URI uri(url);

	HTTPRequest request(HTTPRequest::HTTP_POST, uri.getPath());
	request.setContentLength((int)data.length());
	HTTPClientSession session(uri.getHost(), uri.getPort());
	session.sendRequest(request) << data;
	poco_information_f3(app.logger(), "session : %s:[%u] {%s}", uri.getHost(), uri.getPort(), uri.getPath());

	HTTPResponse response;
	std::istream& out = session.receiveResponse(response);
	std::ostringstream ostr;
	StreamCopier::copyStream(out, ostr);

	poco_information_f1(app.logger(), "receiveResponse:\n%s", ostr.str());
}

bool QZSyncTask::success(const std::string& json)
{
	Parser parser;
	Var result = parser.parse(json);
	assert(result.type() == typeid(Object::Ptr));

	Object::Ptr object = result.extract<Object::Ptr>();
	DynamicStruct ds = *object;

	return (ds["code"] == "0");
}

bool QZSyncTask::ExistRecordOnKGServer()
{
	DynamicStruct ds = *_model->getObject("checkKeyInfo");
	std::string url = ds["url"];
	ds["fmt"]["keysn"] = "000006946797";
	ds["fmt"]["dataMD5"] = "124556789456123";
	std::string data = ds["fmt"].toString();

	std::string result = submitToKGServer(url, data);

	Parser parser;
	Var v = parser.parse(result);
	assert(v.type() == typeid(Object::Ptr));

	Object::Ptr object = v.extract<Object::Ptr>();
	DynamicStruct ds = *object;

	return (ds["code"] == "0" && (std::string(ds["message"]).find(",") != std::string::npos));
}

void QZSyncTask::SendtoKGServer()
{
	DynamicStruct ds = *_model->getObject("sendKeySealInfo");
	
	ds["fmt"]["keysn"] = "000006946797";
	ds["fmt"]["dataMD5"] = "124556789456123";
	ds["fmt"]["username"] = "欧阳立123";
	ds["fmt"]["usercode"] = "ouyangli123";
	ds["fmt"]["validStart"] = "2019-09-22";
	ds["fmt"]["validEnd"] = "2019-10-21";

	Var result = ds["fmt"]["seals"];
	
	assert(result.type() == typeid(Poco::JSON::Array::Ptr));
	assert(!result.isEmpty());

	Poco::JSON::Array::Ptr ar = result.extract<Poco::JSON::Array::Ptr>();

	for (int i = 0; i < 3; ++i)
	{
		Object object = ds["sealdata"].extract<Poco::JSON::Object>();

		object.set("imgdata" , "R0lGODdhXgBeAMIAAP8AAP////9/f/8/P/+/vwAAAAAAAAAAACwAAAAAXgBeAAAD/hi6Cv4wykmrvTcAxhn+YCh+3TJCwqk6RLM63SsEw/CKi317ciCkN9ACSCFaTL3fRBcyToaVmfOpwQyqEul01pwxqb6KYvr8eL8OrcRllh7H4nDwoY7UUT5ydoYF6zd9c2NbeVmFQoERUBRsc4A1hkp2hySJECWYjg+NeJKdf2uWm5gxmoBFlHSpGXJgaGl8pqcTd6qeGHCMnHSxprtpqwC1F266oj+tjr/CwcMWxWBF0MrHzcFRAQQ/29ukCgTgyYLVt8Dlz97pDKAny87O2OvcfHnzAuHsI+7W5/Fxx9PGQZp0Dh4qUYAAigsyKBKhfgf/SVu4g9/DfKoQItlD/vFFQ4JTPppRRxJjCJG2Ql47SNKbSUQFgykYOFIbt4Eb7QRkaDHUiJ2jsNTQgYyArHerriBERUTbJTZIkC09gbTcDKMiik3bCEXq0Z4OauQ6KWcrVDheTdFz2O1bu7LZuA2RGiatprWTSmDVB7dlCruaFmUcQpMvUQ425aLtZarFzE/UbL1pteyF0kE/WkDkK1niKFksHHfYDEKs0GyTn4JGcU90ZRCAZ75ihnrUyxt4ZTAGIBoNvS9jV+N53aZ22HTgImgWbog4BmROLo+m1RF07hX4omybbY65sG2i7c3jHvQ29anPW6pfmSPIbhWu04m3l63wg8tzlHpffd3j/sr9KvBhni6kAZhVcEkMaKA0ai1owQDbOQgghPOUJKFw9Kz330/orRZfeNyIxiENFeh3YQsE0JQTDM7ltVckEdRwD2G+kPiUjUG9haMiO0rHQY0cvcibW1ldJYFpPMpRw3LURKfUF5cJWQlHRgwDFHyy5UWTaSmS1xwmVa5y5QnSOSHai9JJyVIJX1hZHZkMCOmai2QlGWN7ACz5JpnhJCJjhxe0oOIu8fGwGoT73bFinn0y4OUKMs4n3qNM/dWfTsL5qGGBw2GS4oUJaYjYBZqSYp89slCISnJfEoPnBCJm2IGa/C0a2o6h7GkCPY61xek4omTnmU5tJcIGfona/poQKKL6lGOy4AjABIQiTvaNpIs2ouwIAxS6Hq0POPZotqe1SKqo8qRnHKxiDpIDpRigaJ8pUUrLRGZZdkuKglTAe0OjpgaF2a91LihrnPeaWxG/Icj4FBlj1liPpARHYxt14KqlITj+PssiGUpFy7AVB6vTcUI3UlBoxRgaqq4G3Z7pFLEZnswcgvFks4BRrnXJ7mOg5gUbB57QNe+tIwdGA7zbFgfofpph1DQiQbcaL5P+JT3HpUuEvI0KOAc9NQTeloCO1sCKQOGMo4FiJC77jf1Vh0+DHTZzJrLinWALOif3Cnwb6PffOqJN1malgBY4gCjdmLjSuDIuEwMJAQAAOw=="
		);
		object.set("signname", "欧阳立123");
		object.set("imgItem" ,"01");
		object.set("imgArea" ,"10");
		ar->add(object);
	}
	
	std::string url = ds["url"];
	std::string data = ds["fmt"].toString();
	std::string result =  submitToKGServer(url, data);

	if (success(result)) {
		UpdateSyncStatus();
	}
}

void QZSyncTask::UpdateSyncStatus()
{

}

std::string QZSyncTask::MD5(const std::string& sealinfo, const std::string& keysn)
{
	std::string data;
	data.append(keysn);
	data.append("&&");
	data.append(sealinfo);

	Poco::MD5Engine engine;
	engine.update(data);
	return Poco::DigestEngine::digestToHex(engine.digest());
}

void QZSyncTask::ReadSealInfo()
{
	/// 解析签章数据，读取多个base64图片信息，中间&&拼接
	Application& app = Application::instance();

	XSSealProvider provider;
	std::string result = provider.read();
	Parser parser;
	Var v = parser.parse(result);
	assert(v.type() == typeid(Object::Ptr));
	Object::Ptr object = v.extract<Object::Ptr>();
	DynamicStruct ds = *object;

	_seal_data = ds.toString();
	poco_information_f1(app.logger(), "%s%s", _seal_data);
}

void QZSyncTask::GetKeySN()
{
	return "pseudo key serial number.";
}