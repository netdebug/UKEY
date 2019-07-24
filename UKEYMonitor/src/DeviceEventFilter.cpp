#include "DeviceEventFilter.h"
#include <Dbt.h>
#include <WinIoCtl.h>

using namespace Reach;

char FirstDriveFromMask(ULONG unitmask)
{
	char i;

	for (i = 0; i < 26; ++i)
	{
		if (unitmask & 0x1)
			break;
		unitmask = unitmask >> 1;
	}

	return(i + 'A');
}

#include "Poco/Util/Application.h"
#include "Poco/UUID.h"
using Poco::Util::Application;

GUID DeviceEventFilter::_Guid = { 0x25dbce51, 0x6c8f, 0x4a72,
					  0x8a,0x6d,0xb5,0x4c,0x2b,0x4f,0xc8,0x35 };

HDEVNOTIFY DeviceEventFilter::_notify = 0;

DeviceEventFilter::DeviceEventFilter()
{
}

DeviceEventFilter::~DeviceEventFilter()
{
}

void DeviceEventFilter::registerNotification(HANDLE hRecipient)
{
	DEV_BROADCAST_DEVICEINTERFACE NotificationFilter;

	ZeroMemory(&NotificationFilter, sizeof(NotificationFilter));
	NotificationFilter.dbcc_size =
		sizeof(DEV_BROADCAST_DEVICEINTERFACE);
	NotificationFilter.dbcc_devicetype = DBT_DEVTYP_DEVICEINTERFACE;
	memcpy(&(NotificationFilter.dbcc_classguid),
		&(_Guid),
		sizeof(struct _GUID));
	_notify = RegisterDeviceNotificationW(hRecipient,
		&NotificationFilter,
		DEVICE_NOTIFY_SERVICE_HANDLE | DEVICE_NOTIFY_ALL_INTERFACE_CLASSES);
}

void DeviceEventFilter::unregisterNotification()
{
	UnregisterDeviceNotification(_notify);
}

void DeviceEventFilter::emit(DWORD eventType, LPVOID eventData)
{
	PDEV_BROADCAST_HDR lpdb = (PDEV_BROADCAST_HDR)eventData;

	switch (eventType)
	{
	case DBT_DEVICEARRIVAL:
		if (lpdb->dbch_devicetype == DBT_DEVTYP_HANDLE)
		{
			PDEV_BROADCAST_HANDLE lpdbv = (PDEV_BROADCAST_HANDLE)lpdb;

			Application& app = Application::instance();
			app.logger().information("eventguid :", lpdbv->dbch_eventguid);
			/*if (lpdbv->dbch_eventguid & DBTF_MEDIA)
			{
				StringCchPrintf(szMsg, sizeof(szMsg) / sizeof(szMsg[0]),
					TEXT("Drive %c: Media has arrived.\n"),
					FirstDriveFromMask(lpdbv->dbcv_unitmask));

				//MessageBox(hwnd, szMsg, TEXT("WM_DEVICECHANGE"), MB_OK);
			}
			*/
		}
		break;
	case DBT_DEVICEREMOVECOMPLETE:
		if (lpdb->dbch_devicetype == DBT_DEVTYP_HANDLE)
		{
			PDEV_BROADCAST_HANDLE lpdbv = (PDEV_BROADCAST_HANDLE)lpdb;

			Application& app = Application::instance();
			app.logger().information("eventguid :", lpdbv->dbch_eventguid);
		}
		break;
	}
}

