#pragma once

#include "Poco/Util/Util.h"

namespace Reach {

	class DeviceEventFilter
	{
	public:
		DeviceEventFilter();
		~DeviceEventFilter();

		void registerNotification(HANDLE hRecipient);
		void unregisterNotification();
		void emit(DWORD eventType, LPVOID eventData);

		static DeviceEventFilter& default();
	private:
		void SQLitePath();

		static GUID _Guid;
		HDEVNOTIFY _notify;
		std::string _DeQLite;
	};
} //namespace Reach