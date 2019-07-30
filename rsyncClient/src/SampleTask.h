#pragma once
#include "Poco/Task.h"
#include "Poco/Net/HTTPClientSession.h"

namespace Reach {

	using Poco::Task;
	using Poco::Net::HTTPClientSession;

	class SampleTask : public Task
	{
	public:
		SampleTask(std::string& host, short port);

		void runTask();
		
	private:
		HTTPClientSession session;
	};
}