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

namespace Reach {

	using Poco::Logger;
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
		static void defaultSignMethod();
		static void defaultEncryptMethod();
	protected:
		void InitialMethods();
		std::string getContainerType();
		void getCapability();
		void setRandom(int type);
		void setEncryptMethod(int type);
		bool findEncryptMethod(std::string key);
		void setSignMethod(int type);
		std::string getUID();
		std::string getName();
		void spiltEntries();
	private:
		std::string _cname;
		std::string _cid;
		std::vector<std::string> _encrypt_methods;
		std::string entries;//user cert entry list
		bool bOpened;
		static const int success = 0;
		bool initial;
		int random_size;
		LogStream ls;

		friend class EncryptStrategy;
		friend class SignedStrategy;
	};
}

#endif // RS_UDevice_INCLUDE
