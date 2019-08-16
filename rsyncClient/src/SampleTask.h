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
		void QueryUSBKeyType(const std::string & data);
		bool IsFJCA();
		
	private:
		HTTPClientSession session;
		Poco::SharedPtr<UKeyDevice> _ukey;
		std::string _serialNumber;
		std::string _buffer_device;
		bool _fjca;
	};
}