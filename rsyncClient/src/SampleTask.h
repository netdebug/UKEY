#pragma once
#include "Poco/Task.h"
#include "Poco/Net/HTTPClientSession.h"
#include "Poco/SharedPtr.h"
#include <string>

namespace Reach {

	using Poco::Task;
	using Poco::Net::HTTPClientSession;

	class UKeyDevice;
	class SampleTask : public Task
	{
	public:
		SampleTask(std::string& host, short port);

		void runTask();

	private:
		void getUserList();
		void getKeySN();
		void sendKeySNByActiveX();
		bool IsUSBKeyPresent();
		
	private:
		HTTPClientSession session;
		std::string _userlist;
		Poco::SharedPtr<UKeyDevice> _ukey;
	};
}