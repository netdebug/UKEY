//
// UDevice.cpp
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#include "UDevice.h"
#include "GMCrypto.h"
#include "SoFProvider.h"
#include "Poco/Exception.h"
#include "Poco/SingletonHolder.h"
#include <map>

using namespace Reach;
using Poco::SingletonHolder;

UDevice::UDevice()
	:bOpened(false), initial(false), random_size(16),ls(Logger::get("LoggerTest"))
{
	open();
	InitialMethods();
}

UDevice::~UDevice()
{
	close();
}

int UDevice::random()
{
	return random_size;
}

#include "Poco/RegularExpression.h"

using Poco::RegularExpression;

void UDevice::InitialMethods()
{
	if (initial) return;

	ls.trace() << "UDevice::InitialMethods() enter" << std::endl;

	std::string list = SOF_GetUserList();
	std::string pattern("(\\S+)\\|\\|(\\S+)[&&&]*");
	int options = 0;

	RegularExpression re(pattern, options);
	RegularExpression::Match mtch;

	if (!re.match(list, mtch))
		throw Poco::LogicException("RS_KeyDecryptData uid Exception!", 0x40);

	std::vector<std::string> tags;
	re.split(list, tags, options);
	std::string& name = tags[1];
	std::string& uid = tags[2];

	std::string supported = SOF_GetDeviceInfo(uid, SGD_DEVICE_SUPPORT_ALG);

	if (supported.empty()) {
		int error = SOF_GetLastError();
		ls.warning() << "UDevice no supported():" << error << std::endl;
		throw Poco::LogicException("SOF_GetDeviceInfo failed!", error);
	}

	typedef std::pair<int, int> method;
	typedef std::map<std::string, method> method_table;
	method_table algtable;

	algtable["1"] = method(SGD_SM3_RSA, SGD_RSA);//RSA
	algtable["2"] = method(SGD_SM3_SM2, SGD_SM4_ECB);//SM2

	long result1 = SOF_SetSignMethod(algtable[supported].first);
	long result2 = SOF_SetEncryptMethod(algtable[supported].second);

	if (success != (result1 | result2))
	{
		int error = SOF_GetLastError();
		ls.warning() << "UDevice::InitialMethods() failed!" << error << std::endl;
		throw Poco::LogicException("SOF_SetSignMethod or SOF_SetEncryptMethod failed!", error);
	}

	initial = true;

	ls.trace() << "UDevice::InitialMethods() exit" << std::endl
		<< "Sign :" << SOF_GetSignMethod() << std::endl
		<< "Encrypt :" << SOF_GetEncryptMethod() << std::endl;
}

void UDevice::open()
{
	if (bOpened) return;

	if (success != SOF_OpenDevice())
	{
		int error = SOF_GetLastError();
		ls.warning() << "UDevice::open() failed!" << error << std::endl;
		throw Poco::LogicException("UDevice open failed!", error);
	}
	bOpened = true;
}

void UDevice::close()
{
	if (!bOpened) return;

	if (success != SOF_CloseDevice())
	{
		int error = SOF_GetLastError();
		ls.warning() << "UDevice::close() failed!" << error << std::endl;
		throw Poco::LogicException("UDevice close failed!", error);
	}
	bOpened = false;
}

bool UDevice::isopen()
{
	return bOpened;
}

namespace
{
	static SingletonHolder<UDevice> ukey;
}

UDevice& UDevice::default()
{
	return *ukey.get();
}

void UDevice::defaultSignMethod()
{
	//SM2 default signed method
	if (success != SOF_SetSignMethod(SGD_SM3_SM2))
	{
		int error = SOF_GetLastError();
		throw Poco::LogicException("SOF_SetSignMethod failed", error);
	}
}

void UDevice::defaultEncryptMethod()
{
	//SM2 default encrypt method
	if (success != SOF_SetEncryptMethod(SGD_SM4_ECB))
	{
		int error = SOF_GetLastError();
		throw Poco::LogicException("SOF_SetEncryptMethod failed", error);
	}
}