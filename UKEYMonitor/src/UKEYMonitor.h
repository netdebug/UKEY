//
// UKEYMonitor.h
//
// This sample demonstrates the Application class.
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#include "USBAssistDetect.h"
#include "Poco/Util/OptionSet.h"
#include <iostream>

namespace Reach {

	using Poco::Util::OptionSet;

	class UKEYMonitor
		: public USBAssistDetect
	{
	public:
		UKEYMonitor();
		~UKEYMonitor();

	protected:
		void initialize(Application& self);
		void uninitialize();
		void defineOptions(OptionSet& options);
		void handleHelp(const std::string& name, const std::string& value);
		void displayHelp();
		void printProperties();
		void printProperties(const std::string& base);

		int main(const ArgVec& args);

		static void __stdcall ServiceControlHandler(DWORD control, DWORD eventType, LPVOID eventData, LPVOID context);
		static void deviceEventNotify(DWORD eventType, LPVOID eventData);

		void RegisterUKEYNotification();

	private:
		bool _helpRequested;
		static SERVICE_STATUS        _serviceStatus;
		static SERVICE_STATUS_HANDLE _serviceStatusHandle;
		static HDEVNOTIFY _notify;
	};
}