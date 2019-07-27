#include "DeviceEventFilter.h"
#include <Dbt.h>
#include <WinIoCtl.h>
#include <cassert>
#include "Poco/UnicodeConverter.h"
#include "Poco/Path.h"
#include "Poco/String.h"
#include "Poco/Util/Application.h"
#include "Poco/UUID.h"
#include "DeviceFilter.h"

using Poco::Util::Application;
using Poco::UnicodeConverter;

using namespace Reach;

GUID DeviceEventFilter::_Guid = { 0xA5DCBF10, 0x6530, 0x11D2, { 0x90, 0x1F, 0x00, 0xC0, 0x4F, 0xB9, 0x51, 0xED } };

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
		DEVICE_NOTIFY_SERVICE_HANDLE);
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
		if (lpdb->dbch_devicetype == DBT_DEVTYP_DEVICEINTERFACE)
		{
			PDEV_BROADCAST_DEVICEINTERFACE lpdbv = (PDEV_BROADCAST_DEVICEINTERFACE)lpdb;

			std::wstring wname((wchar_t*)lpdbv->dbcc_name, lstrlenW((wchar_t*)lpdbv->dbcc_name));
			std::string name;
			UnicodeConverter::toUTF8(wname, name);
			DeviceFilter(name,false);
		}
		break;
	case DBT_DEVICEREMOVECOMPLETE:
		if (lpdb->dbch_devicetype == DBT_DEVTYP_DEVICEINTERFACE)
		{
			PDEV_BROADCAST_DEVICEINTERFACE lpdbv = (PDEV_BROADCAST_DEVICEINTERFACE)lpdb;

			std::wstring wname((wchar_t*)lpdbv->dbcc_name, lstrlenW((wchar_t*)lpdbv->dbcc_name));
			std::string name;
			UnicodeConverter::toUTF8(wname, name);
			DeviceFilter(name,true);
		}
		break;
	}
}

