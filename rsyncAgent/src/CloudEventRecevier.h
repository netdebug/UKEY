#pragma once
#include "Poco/Task.h"
#include "Poco/NamedEvent.h"
#include "Poco/Mutex.h"
#include "MQTTAsyncClient.h"

namespace Reach {

	class CloudEventRecevier
		: public Poco::Task
	{
	public:
		CloudEventRecevier();
		void runTask();
	private:
		MQTTAsyncClient client;
	};

}