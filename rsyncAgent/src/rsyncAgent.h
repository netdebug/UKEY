//
// rsyncAgent.h
//
// This sample demonstrates the Application class.
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#include "Poco/Util/ServerApplication.h"
#include "Poco/Util/OptionSet.h"
#include <iostream>

namespace Reach {

	using Poco::Util::ServerApplication;
	using Poco::Util::OptionSet;

	class rsyncAgent
		: public ServerApplication
	{
	public:
		rsyncAgent();
		~rsyncAgent();

	protected:
		void initialize(Application& self);
		void uninitialize();
		void defineOptions(OptionSet& options);
		void handleHelp(const std::string& name, const std::string& value);
		void displayHelp();
		void printProperties();
		void printProperties(const std::string& base);

		int main(const ArgVec& args);

	private:
		bool _helpRequested;
	};
}