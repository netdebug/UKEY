//
// UDevice.h
//
// Definition of the UDevice class.
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef RS_UDevice_INCLUDE
#define RS_UDevice_INCLUDE

#include "Poco/Foundation.h"
#include "Poco/Logger.h"
#include "Poco/LogStream.h"
//#include "Poco/SharedLibrary.h"
namespace Reach {

	using Poco::LogStream;
	
	class UDevice
	{
	public:
		UDevice();
		~UDevice();

		void open();
		void close();
		bool isopen();
		int random();

		static UDevice& default();

	protected:
		void InitialMethods();
	private:
		//Poco::SharedLibrary sl;
		bool bOpened;
		const int success = 0;
		bool initial;
		int random_size;
		LogStream ls;
	};
}

#endif // RS_UDevice_INCLUDE
