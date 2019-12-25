#pragma once
#include "Poco/Task.h"
#include "Poco/Mutex.h"
#include "Poco/SharedPtr.h"

namespace Reach {

	class MQTTAsyncClient;
	class CloudEventRecevier
		: public Poco::Task
	{
	public:
		CloudEventRecevier();
		~CloudEventRecevier();

		virtual void runTask();
		virtual void cancel();

	private:
		MQTTAsyncClient* _mqtt;
	};

}