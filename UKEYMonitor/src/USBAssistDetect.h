#pragma once

#include "Poco/Util/Util.h"
#include "Poco/Util/Application.h"
#include "Poco/Event.h"
#include "Poco/NamedEvent.h"

namespace Reach {

	using Poco::Util::OptionSet;
	using Poco::Util::Application;

	class USBAssistDetect
		:public Application
	{
	public:
		USBAssistDetect();
		~USBAssistDetect();

		bool isInteractive() const;
		/// Returns true if the application runs from the command line.
		/// Returns false if the application runs as a Unix daemon
		/// or Windows service.

		int run(int argc, char** argv);
		/// Runs the application by performing additional initializations
		/// and calling the main() method.

		int run(const std::vector<std::string>& args);
		/// Runs the application by performing additional initializations
		/// and calling the main() method.

#if defined(POCO_WIN32_UTF8) && !defined(POCO_NO_WSTRING)
		int run(int argc, wchar_t** argv);
		/// Runs the application by performing additional initializations
		/// and calling the main() method.
		///
		/// This Windows-specific version of init is used for passing
		/// Unicode command line arguments from wmain().
#endif

		static void terminate();

	protected:
		int run();
		void waitForTerminationRequest();
		void defineOptions(OptionSet& options);
	private:

		enum Action
		{
			SRV_RUN,
			SRV_REGISTER,
			SRV_UNREGISTER
		};
		static BOOL __stdcall ConsoleCtrlHandler(DWORD ctrlType);
		static DWORD __stdcall ServiceControlHandler(DWORD control, DWORD eventType, LPVOID eventData, LPVOID context);
		static void __stdcall ServiceMain(DWORD argc, LPWSTR* argv);

		bool hasConsole();
		bool isService();
		void registerService();
		void unregisterService();
		void handleRegisterService(const std::string& name, const std::string& value);
		void handleUnregisterService(const std::string& name, const std::string& value);
		void handleDisplayName(const std::string& name, const std::string& value);
		void handleDescription(const std::string& name, const std::string& value);
		void handleStartup(const std::string& name, const std::string& value);

		Action      _action;
		std::string _displayName;
		std::string _description;
		std::string _startup;

		static Poco::Event           _terminated;
		static Poco::NamedEvent      _terminate;
		static SERVICE_STATUS        _serviceStatus;
		static SERVICE_STATUS_HANDLE _serviceStatusHandle;
	};
} //namespace Reach

#define MAIN(App) \
	int wmain(int argc, wchar_t** argv)	\
	{									\
		try 							\
		{								\
			App app;					\
			return app.run(argc, argv);	\
		}								\
		catch (Poco::Exception& exc)	\
		{								\
			std::cerr << exc.displayText() << std::endl;	\
			return Poco::Util::Application::EXIT_SOFTWARE; 	\
		}								\
	}