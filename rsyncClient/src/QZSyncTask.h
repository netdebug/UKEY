#pragma once
#include "Poco/Task.h"
#include "Poco/JSON/Object.h"

namespace Reach {
	class SealProvider;
	using Poco::Task;
	using Poco::JSON::Object;
	///签章同步流程类 当下只支持一把UKEY

	class QZSyncTask : public Task
	{
		typedef std::vector<SealProvider*> SealProviderList;
		typedef SealProviderList::iterator SealProviderIter;
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
		std::string CommonRequest(const std::string& url, const std::string& data, const std::string& method = "POST");
		void MD5();
		void ReadSealInfo();
		void GetKeySN();
		void GetContainerId();
		void GetSignedCert();

		const int type_signed_cer = 1;

		std::string _config;
		Object::Ptr _templateJSON;
		std::string _keysn;
		std::string _md5;
		std::string _seal_data;
		std::string _serialNumber;
		std::string _ServerResponse;
		std::string _cid;
		std::string _x509cert;
		std::string _name;
		std::string _code;
		std::string _validStart;
		std::string _validEnd;

		Poco::FastMutex _mutex;

		SealProviderList providers;
	};
}