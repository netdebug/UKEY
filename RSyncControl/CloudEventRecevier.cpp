#include "CloudEventRecevier.h"
#include "Poco/Format.h"
#include "Poco/Thread.h"
#include "MQTTAsyncClient.h"

#include <cassert>
#include <sstream>
#include <openssl/hmac.h>
#include <openssl/bio.h>

using namespace Reach;
using namespace Poco;
using Poco::format;
//using namespace Poco::JSON;
//using namespace Poco::Dynamic;

CloudEventRecevier::CloudEventRecevier()
	: Task("CloudEventRecevier"),
	_mqtt(new MQTTAsyncClient(false))
{
}

CloudEventRecevier::~CloudEventRecevier()
{
	assert(_mqtt);
	delete _mqtt;
	_mqtt = nullptr;
}

void CloudEventRecevier::runTask()
{
	while (!sleep(2000)){
		assert(_mqtt);
		if (!_mqtt->isConnected()){
			_mqtt->connect("LTAIQklBFtjieSla", "post-cn-0pp10v4bb05", "FXUysOR0be9K4PIBOVXytKoEFlVTNI");
			OutputDebugStringA(format("Start thread <%lu>:<%s>\n", Thread::currentTid(), name()).c_str());
			sleep(1000);
		}

		OutputDebugStringA(format("Testing thread sleep <%lu>:<%s>:<%d>\n", Thread::currentTid(), name(), (int)state()).c_str());

		if (isCancelled()){
			OutputDebugStringA(format("Cancelling thread sleep <%lu>:<%s>\n", Thread::currentTid(), name()).c_str());
			break;
		}
	}
	
	/*while (!sleep(10 * 60 * 1000)) {
		std::cout << "CloudEventRecevier TID after sleep - " << Poco::Thread::currentTid();
		if (isCancelled()) break;
	}*/
}

void CloudEventRecevier::cancel()
{
	Task::cancel();
	assert(_mqtt);
	_mqtt->disconnect();
	OutputDebugStringA(format("Cancel thread sleep <%lu>:<%s>\n", Thread::currentTid(), name()).c_str());
}