#include "DeviceEventFilter.h"
#include <Dbt.h>
#include <WinIoCtl.h>
#include <cassert>

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

//GUID DeviceEventFilter::_Guid = { 0x25dbce51, 0x6c8f, 0x4a72, \
//					  0x8a,0x6d,0xb5,0x4c,0x2b,0x4f,0xc8,0x35 };

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
		DEVICE_NOTIFY_SERVICE_HANDLE /*| DEVICE_NOTIFY_ALL_INTERFACE_CLASSES*/);
}

void DeviceEventFilter::unregisterNotification()
{
	UnregisterDeviceNotification(_notify);
}

#include "Poco/String.h"
#include "Poco/RegularExpression.h"
#include "Poco/Debugger.h"
#include "Poco/UnicodeConverter.h"
using Poco::format;
using Poco::Debugger;
using Poco::RegularExpression;
using Poco::UnicodeConverter;

void DeviceEventFilter::enqueue(const std::string& dbcc_name)
{
	/// pDevInf->dbcc_name: 
	/// \\?\USB#Vid_04e8&Pid_503b#0002F9A9828E0F06#{a5dcbf10-6530-11d2-901f-00c04fb951ed}
	/// Vid: USB\Vid_04e8&Pid_503b\0002F9A9828E0F06
	/// Class: USB
	std::string pattern("\\?\\\\(\\S+)#(\\S+)#(\\S+)#(\\S+)");
	int options = 0;
	try
	{
		RegularExpression re(pattern, options);
		RegularExpression::Match mtch;

		if (!re.match(dbcc_name, mtch))
			return;

		std::vector<std::string> tags;
		re.split(dbcc_name, tags, options);


		for (int i = 0; i < tags.size(); i++) {
			Debugger::message(format("lpdbv->dbcc_name tags %d : %s", i, tags[i]));
		}
	}
	catch (Poco::RegularExpressionException& e)
	{
		Debugger::message(format("lpdbv->dbcc_name tags %d : %s", e.code(), e.message()));
	}
	

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

			//int n = lstrlenW((wchar_t*)lpdbv->dbcc_name);
			std::wstring wname((wchar_t*)lpdbv->dbcc_name, lstrlenW((wchar_t*)lpdbv->dbcc_name));
			std::string name;
			UnicodeConverter::toUTF8(wname, name);
			enqueue(name);
		}
		break;
	case DBT_DEVICEREMOVECOMPLETE:
		if (lpdb->dbch_devicetype == DBT_DEVTYP_DEVICEINTERFACE)
		{
			PDEV_BROADCAST_DEVICEINTERFACE lpdbv = (PDEV_BROADCAST_DEVICEINTERFACE)lpdb;

			std::wstring wname((wchar_t*)lpdbv->dbcc_name, lstrlenW((wchar_t*)lpdbv->dbcc_name));
			std::string name;
			UnicodeConverter::toUTF8(wname, name);
			enqueue(name);
		}
		break;
	}
}

