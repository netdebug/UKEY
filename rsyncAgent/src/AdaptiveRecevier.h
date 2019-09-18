#pragma once
#include "Poco/Task.h"
#include "Poco/NamedEvent.h"
#include "Poco/Mutex.h"

namespace Reach {

class AdaptiveRecevier 
	: public Poco::Task
{
public:
	AdaptiveRecevier();
	void runTask();
	virtual void cancel();
private:
	void CheckDeviceDBEnv();
	void dbgview(const std::string& message);
	
	Poco::NamedEvent _event;
	Poco::FastMutex _mutex;
};

}