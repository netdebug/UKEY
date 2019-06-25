//
// UpdateTask.cpp
//
// This sample demonstrates the ServerApplication class.
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#include "Poco/Task.h"

namespace Reach {

	using Poco::Task;

	class UpdateTask : public Task
	{
	public:
		UpdateTask();
		~UpdateTask();

		void runTask();
	private:
		unsigned long millisecond;//millisecond - 1 mins
	};
}