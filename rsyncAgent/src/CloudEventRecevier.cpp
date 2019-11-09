#include "CloudEventRecevier.h"
#include "Poco/Util/Application.h"
#include "Poco/Format.h"
#include "Poco/Thread.h"
#include "Poco/JSON/Parser.h"
#include "Poco/Dynamic/Var.h"
#include "Poco/DynamicStruct.h"
#include "Poco/StreamConverter.h"
#include "Poco/StreamCopier.h"
#include <cassert>
#include <sstream>
#include <openssl/hmac.h>
#include <openssl/bio.h>

using namespace Reach;
using namespace Poco;
using namespace Poco::JSON;
using namespace Poco::Dynamic;
using Poco::Util::Application;

CloudEventRecevier::CloudEventRecevier()
	: Task("CloudEventRecevier"),
	client(MQTTAsyncClient(false))
{
}

void CloudEventRecevier::runTask()
{
	std::cout << "CloudEventRecevier TID - " << Poco::Thread::currentTid();
	client.connect("LTAIQklBFtjieSla", "post-cn-0pp10v4bb05", "FXUysOR0be9K4PIBOVXytKoEFlVTNI");
	while (!sleep(10 * 60 * 1000)) {
		std::cout << "CloudEventRecevier TID after sleep - " << Poco::Thread::currentTid();
		if (isCancelled()) break;
	}
}