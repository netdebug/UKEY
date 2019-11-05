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
#include "Poco/RegularExpression.h"
#include "Poco/StreamCopier.h"
#include "Poco/FileStream.h"
#include "Poco/URI.h"
//#include "SealProvider.h"
#include "XSSealProvider.h"
#include "KGSealProvider.h"
#include "OESSealProvider.h"
#include <cassert>

using namespace Reach;
using namespace Poco::Dynamic;
using namespace Poco::JSON;

using Poco::format;
using Poco::DynamicStruct;
using Poco::DateTimeFormatter;
using Poco::StreamCopier;
using Poco::FileInputStream;
using Poco::Util::Application;
using Poco::Net::HTTPRequest;
using Poco::Net::HTTPResponse;
using Poco::Net::HTTPClientSession;
using Poco::RegularExpression;
using Poco::URI;

QZSyncTask::QZSyncTask()
	:Task("QZSyncTask"),
	_config("QZSyncTask.json"),
	_x509cert("")
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

		_templateJSON = result.extract<Object::Ptr>();
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
			MD5();

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

	return ostr.str();
}

std::string QZSyncTask::CommonRequest(const std::string& url, const std::string& data, const std::string& method)
{
	Application& app = Application::instance();

	URI uri(url);
	std::ostringstream ostr;
	try
	{
		HTTPResponse response;
		HTTPRequest request(HTTPRequest::HTTP_POST, uri.getPath());
		request.setContentLength((int)data.length());

		HTTPClientSession session(uri.getHost(), uri.getPort());
		session.sendRequest(request) << (data);

		std::istream& receive = session.receiveResponse(response);

		StreamCopier::copyStream(receive, ostr);
	}
	catch (Poco::Exception& e)
	{
		poco_information_f1(app.logger(), "CommonRequest Error:\n%s", e.message());
	}

	poco_information_f1(app.logger(), "receiveResponse:\n%s", ostr.str());
	return ostr.str();
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
	DynamicStruct ds = *_templateJSON->getObject("checkKeyInfo");
	std::string url = ds["url"];
	ds["fmt"]["keysn"] = _keysn;
	ds["fmt"]["dataMD5"] = _md5;
	std::string data = ds["fmt"].toString();

	std::string response = submitToKGServer(url, data);

	Parser parser;
	Var v = parser.parse(response);
	assert(v.type() == typeid(Object::Ptr));

	Object::Ptr object = v.extract<Object::Ptr>();
	DynamicStruct dds = *object;

	return (dds["code"] == "0" || dds["code"] == "0");
}

void QZSyncTask::SendtoKGServer()
{
	DynamicStruct ds = *_templateJSON->getObject("sendKeySealInfo");
	
	ds["fmt"]["keysn"] = _keysn;
	ds["fmt"]["dataMD5"] = _md5;
	ds["fmt"]["username"] = _name;
	ds["fmt"]["usercode"] = _code;
	ds["fmt"]["validStart"] = _validStart;
	ds["fmt"]["validEnd"] = _validEnd;

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
	std::string response =  submitToKGServer(url, data);

	if (success(response)) {
		UpdateSyncStatus();
	}
}

void QZSyncTask::UpdateSyncStatus()
{

}

void QZSyncTask::MD5()
{
	std::string data;
	data.append(_keysn);
	data.append("&&");
	data.append(_seal_data);

	Poco::MD5Engine engine;
	engine.update(data);
	_md5 = Poco::DigestEngine::digestToHex(engine.digest());
}

void QZSyncTask::ReadSealInfo()
{
	/// 解析签章数据，读取多个base64图片信息，中间&&拼接
	Application& app = Application::instance();

	OESSealProvider oes;
	
	_name = oes.getProperty("name");
	_code = oes.getProperty("code");
	_validStart = oes.getProperty("validStart");
	_validEnd = oes.getProperty("validEnd");
	Var result = oes.read();
	poco_information_f1(app.logger(), "%s", result.convert<std::string>());

	//
	/*assert(result.type() == typeid(Array::Ptr));
	Array::Ptr data = result.extract<Array::Ptr>();
	assert(!data.isNull());
	Poco::Dynamic::Array dda = *data;
	for (int i = 0; i < dda.size(); i++) {
		dda[i].toString();
	}*/
}

void QZSyncTask::GetContainerId()
{
	std::string receive = CommonRequest("http://127.0.0.1:11200/RS_GetUserList", "");

	Parser json;
	Var result = json.parse(receive);
	DynamicStruct ds = *result.extract<Object::Ptr>();

	std::string _userlist = ds["data"]["userlist"].toString();
	std::string pattern("(\\S+)\\|\\|(\\S+)[&&&]*");
	RegularExpression re(pattern);
	RegularExpression::Match mtch;

	if (!re.match(_userlist, mtch)) {
		throw Poco::RegularExpressionException(pattern, _userlist);
	}

	std::vector<std::string> tags;
	re.split(_userlist, tags, 0);
	assert(tags.size() > 1);
	_cid = tags[2];
}

void QZSyncTask::GetKeySN()
{
	GetContainerId();
	std::string body(format("containerId=%s", _cid));
	std::string receive = CommonRequest("http://127.0.0.1:11200/RS_KeyGetKeySn", body);
	Parser json;
	Var result = json.parse(receive);
	DynamicStruct ds = *result.extract<Object::Ptr>();

	_serialNumber = ds["data"]["keySn"].toString();
}

void QZSyncTask::GetSignedCert()
{
	std::string body(format("containerId=%s&certType=$d", _cid, type_signed_cer));
	std::string receive = CommonRequest("http://127.0.0.1:11200/RS_GetCertBase64String", body);
	Parser json;
	Var result = json.parse(receive);
	DynamicStruct ds = *result.extract<Object::Ptr>();

	_x509cert = ds["data"]["keySn"].toString();
}

