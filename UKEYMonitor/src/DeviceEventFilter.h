#pragma once

#include "Poco/Util/Util.h"

namespace Reach {

	class DeviceEventFilter
	{
	public:
		DeviceEventFilter();
		~DeviceEventFilter();

		static void registerNotification(HANDLE hRecipient);
		static void unregisterNotification();
		static void emit(DWORD eventType, LPVOID eventData);

	private:
		DWORD _eventType;
		LPVOID _eventData;

		static GUID _Guid;
		static HDEVNOTIFY _notify;
	};
} //namespace Reach