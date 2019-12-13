#include "MQTTAsyncClient.h"
#include <openssl/hmac.h>
#include <openssl/bio.h>
#include "Poco/JSON/Parser.h"
#include "Poco/JSON/Object.h"
#include "Poco/Dynamic/Var.h"
#include "Poco/DynamicStruct.h"
#include "Poco/Format.h"
#include "Poco/Util/Application.h"
#include "Poco/NotificationCenter.h"
#include "MQTTNotification.h"
#include "Poco/Debugger.h"
#include <cassert>
#include "Poco/UUIDGenerator.h"
#include "Poco/Net/HTMLForm.h"
#include "Utility.h"

using namespace Reach;
using namespace Poco;
using namespace Poco::Dynamic;
using namespace Poco::JSON;
using Poco::Net::HTMLForm;
using Reach::ActiveX::Utility;

bool MQTTAsyncClient::connected = false;

MQTTAsyncClient::MQTTAsyncClient(bool useSSL)
	:host("post-cn-0pp10v4bb05.mqtt.aliyuncs.com"),
	port(1883),
	groupId("GID_fjreach"),
	_useSSL(useSSL)
{
	initialize();

	deviceId = UUIDGenerator::defaultGenerator().create().toString();
	clientIdUrl = Poco::format("%s@@@%s", groupId, deviceId);
	
	setConfigParameters();
	int rc = 0;
	if (rc = MQTTAsync_createWithOptions(&client, serverURI.data(),
		clientIdUrl.data(),
		MQTTCLIENT_PERSISTENCE_NONE, NULL,
		&create_opts) != MQTTASYNC_SUCCESS) {
		throw Poco::Exception("MQTTAsync_createWithOptions");
	}

	if (rc = MQTTAsync_setCallbacks(client, client,
		&MQTTAsyncClient::connectionLost,
		&MQTTAsyncClient::messageArrived,
		&MQTTAsyncClient::deliveryComplete) != MQTTASYNC_SUCCESS)
	{
		throw Poco::Exception("MQTTAsync_setCallbacks");
	}

	Poco::Debugger::message("MQTTAsyncClient start");
}

MQTTAsyncClient::~MQTTAsyncClient()
{
	MQTTAsync_destroy(&client);
}

void MQTTAsyncClient::initialize()
{
	createOpts();
	connectOpts();
}

void MQTTAsyncClient::createOpts()
{
	create_opts = MQTTAsync_createOptions_initializer;
	create_opts.sendWhileDisconnected = 0;
	create_opts.maxBufferedMessages = 10;

	if (_useSSL) {
		serverURI = Poco::format("ssl://%s:%u", host, port);
	}
	else {
		serverURI = Poco::format("tcp://%s:%u", host, port);
	}
}

void MQTTAsyncClient::connectOpts()
{
	conn_opts = MQTTAsync_connectOptions_initializer;
	conn_opts.MQTTVersion = MQTTVERSION_3_1_1;
	//conn_opts.keepAliveInterval = keepAliveInterval;
	conn_opts.cleansession = true;
	/*conn_opts.username = user;
	conn_opts.password = password;*/
	conn_opts.onSuccess = &MQTTAsyncClient::onSuccess;
	conn_opts.onFailure = &MQTTAsyncClient::onFailure;
	conn_opts.context = &client;

	if (_useSSL) {
		ssl_opts = MQTTAsync_SSLOptions_initializer;
		conn_opts.ssl = &ssl_opts;
	}
	else {
		conn_opts.ssl = NULL;
	}
	conn_opts.automaticReconnect = 1;
	conn_opts.connectTimeout = 3;
}

void MQTTAsyncClient::deliveryComplete(void* context, token token)
{
#ifdef OCX
	Poco::Debugger::message("send message %d success\n");
#else
	Application& app = Application::instance();
	poco_information_f1(app.logger(), "send message %d success\n", token);
#endif // OCX

}

int MQTTAsyncClient::messageArrived(void* context, char* topicName, int topicLen, message* msg)
{
	std::string topic(topicName, topicLen);
	std::string message((char*)msg->payload, msg->payloadlen);

#ifdef OCX
	Poco::Debugger::message(format("recv message from: %s, body is %s", topic, message));
#else
	Application& app = Application::instance();
	poco_information_f2(app.logger(), "recv message from: %s, body is %s", topic, message);
#endif // OCX

	NotificationCenter::defaultCenter().postNotification(new MQTTNotification(message));
	MQTTAsync_freeMessage(&msg);
	MQTTAsync_free(topicName);
	return 1;
}

void MQTTAsyncClient::connectionLost(void* context, char* cause)
{
	connected = false;
#ifdef OCX
	Poco::Debugger::message("connect lost \n");
#else
	Application& app = Application::instance();
	poco_information(app.logger(), "connect lost \n");
#endif // OCX
}

void MQTTAsyncClient::onSuccess(void* context, successData* response)
{
	connected = true;
#ifdef OCX
	Poco::Debugger::message("connect success \n");
#else
	Application& app = Application::instance();
	poco_information(app.logger(), "connect success \n");
#endif // OCX
}

void MQTTAsyncClient::onFailure(void* context, failureData* response)
{
	connected = false;
#ifdef OCX
	Poco::Debugger::message(format("connect failed, rc %d, message:%s\n",
		response ? response->code : -1,
		response->message));
#else
	Application& app = Application::instance();
	poco_information_f2(app.logger(),
		"connect failed, rc %d, message:%s\n",
		response ? response->code : -1,
		response->message);
#endif // OCX
}

void MQTTAsyncClient::connect(const char* user, const char* password, bool useSSL, int keepAliveInterval = 60)
{
	conn_opts.username = user;// generatorUsername("LTAIQklBFtjieSla", "post-cn-0pp10v4bb05").data();
	conn_opts.password = password;// generatorPassword("FXUysOR0be9K4PIBOVXytKoEFlVTNI").data();
	conn_opts.keepAliveInterval = keepAliveInterval;

	int rc = 0;
	if ((rc = MQTTAsync_connect(client, &conn_opts)) != MQTTASYNC_SUCCESS) {
#ifdef OCX
	Poco::Debugger::message(format("Failed to start connect, return code %d\n", rc));
#else
	Application& app = Application::instance();
	poco_information_f1(app.logger(), "Failed to start connect, return code %d\n", rc);
#endif // OCX
		throw Poco::Exception("Failed to start connect, return code %d\n");
	}
}

void MQTTAsyncClient::connect(const std::string& accessKey, const std::string& instanceId, const std::string& secretKey)
{
	std::string user = generatorUsername(accessKey, instanceId);
	std::string password = generatorPassword(secretKey);

	connect(user.data(), password.data(), false);
}

void MQTTAsyncClient::connect(const std::string& user, const std::string& password)
{
	connect(user.data(), password.data(), false);
}

std::string MQTTAsyncClient::generatorPassword(const std::string& secretKey)
{
	std::string password;
	std::size_t len = 0;
	unsigned char tempData[100] = { 0 };

	HMAC(EVP_sha1(), secretKey.data(), secretKey.length(), reinterpret_cast<const unsigned char*>(clientIdUrl.data()), clientIdUrl.length(), tempData, &len);

	char resultData[100] = { 0 };
	int passWordLen = EVP_EncodeBlock((unsigned char *)resultData, tempData, len);

	password.assign(resultData, passWordLen);
	return password;
}

std::string MQTTAsyncClient::generatorUsername(const std::string& accessKey, const std::string& instanceId)
{
	std::string name;
	name.swap(Poco::format("Signature|%s|%s", accessKey, instanceId));
	return name;
}

void Reach::MQTTAsyncClient::setConfigParameters()
{
	HTMLForm params;
	params.set("cmd", "clientId");
	params.set("val", deviceId);

	std::ostringstream body;
	params.write(body);
	std::string result = Utility::SuperRequest("/RS_ConfigParameters", body.str());
}
