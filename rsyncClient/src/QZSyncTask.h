#pragma once
#include "Poco/Task.h"
#include "Poco/JSON/Object.h"

namespace Reach {
	using Poco::Task;
	using Poco::JSON::Object;
	///签章同步流程类 当下只支持一把UKEY

	class QZSyncTask : public Task
	{
	public:
		QZSyncTask();
		void runTask();
	protected:
		bool IsUSBKeyPresent();
		bool IsNeedSend();
		bool hasAlreadySnyc();
		bool ExistRecordOnKGServer();
		void SendtoKGServer();
		void UpdateSyncStatus();
		
	private:
		void loadModel();
		bool success(const std::string& json);
		std::string submitToKGServer(const std::string& url, const std::string& data);

		std::string MD5(const std::string & sealinfo, const std::string & keysn);
		void ReadSealInfo();
		void GetKeySN();

		std::string _config;
		Object::Ptr _model;
		std::string _seal_data;
		std::string _ServerResponse;
	};
}