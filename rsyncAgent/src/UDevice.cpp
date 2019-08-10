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
#include "ErrorCode.h"
#include "Poco/Exception.h"
#include "Poco/SingletonHolder.h"
#include "Poco/RegularExpression.h"
#include "RequestHandleException.h"
#include "StrategyCollection.h"
#include <map>

using namespace Reach;
using Poco::SingletonHolder;
using Poco::RegularExpression;

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


void UDevice::InitialMethods()
{
	ls.trace() << "UDevice::InitialMethods() enter" << std::endl;

	if (initial) return;

	EncryptStrategy encrypt(*this);
	SignedStrategy sign(*this);

	initial = true;

	ls.trace() << "UDevice::InitialMethods() exit" << std::endl
		<< "Sign :" << SOF_GetSignMethod() << std::endl
		<< "Encrypt :" << SOF_GetEncryptMethod() << std::endl;
}

bool UDevice::findEncryptMethod(std::string key)
{
	return (std::find(_encrypt_methods.begin(), _encrypt_methods.end(), key) != _encrypt_methods.end());
}

void UDevice::getCapability()
{
	_encrypt_methods = SOF_GetDeviceCapability(getUID(), 0);

	for (int i = 0; i < _encrypt_methods.size(); i++) {
		ls.trace() << i << ":" << _encrypt_methods[i] << std::endl;
	}
}

void UDevice::setRandom(int type)
{
	std::map<int, int> algorithms;
	algorithms[SGD_SM1_ECB] = 16;
	algorithms[SGD_SM1_CBC] = 32;

	/*algorithms[SGD_SSF33_ECB]	= 16;
	algorithms[SGD_SSF33_CBC]	= 32;*/

	algorithms[SGD_SM4_ECB] = 16;
	algorithms[SGD_SM4_CBC] = 32;

	/// current ecb cbc have limited! So make random_size right
	random_size = algorithms[type];
}

void UDevice::setEncryptMethod(int type)
{
	setRandom(type);

	if (success != SOF_SetEncryptMethod(type)) {
		int error = SOF_GetLastError();
		ls.warning() << "UDevice::SOF_SetEncryptMethod() failed!" << error << std::endl;
		throw Poco::LogicException("SOF_SetEncryptMethod failed!", error);
	}
}

std::string UDevice::getContainerType()
{
	/// offset is betweent SOF_GetDeviceInfo and containerTypes vector
	std::size_t offset = 1;
	std::size_t supported = std::stoi(SOF_GetDeviceInfo(getUID(), SGD_DEVICE_SUPPORT_ALG)) - offset;
	std::vector<std::string> containerTypes;
	containerTypes.push_back("RSA"); // 1 - RSA Container Type
	containerTypes.push_back("SM2"); // 2 - SM Container Type
	/// index from zero
	/// (0 =>1)
	return containerTypes[supported];
}

void UDevice::setSignMethod(int type)
{
	if (SGD_SHA1_RSA != type && SGD_SM3_SM2 != type)
		throw Poco::LogicException("Out of range value for SOF_SetSignMethod!");

	if(success != SOF_SetSignMethod(type)) {
		int error = SOF_GetLastError();
		ls.warning() << "UDevice::setSignMethod() failed!" << error << std::endl;
		throw Poco::LogicException("setSignMethod failed!", error);
	}
}

std::string UDevice::getUID()
{
	return _cid;
}

std::string UDevice::getName()
{
	return _cname;
}

void UDevice::spiltEntries()
{
	std::string pattern("(\\S+)\\|\\|(\\S+)[&&&]*");
	int options = 0;

	RegularExpression re(pattern, options);
	RegularExpression::Match mtch;

	if (!re.match(entries, mtch)) {
		throw Poco::LogicException(RAR_UNIQUEIDUNCORRECT);
	}

	std::vector<std::string> tags;
	re.split(entries, tags, options);
	_cname = tags[1];
	_cid = tags[2];
}

void UDevice::open()
{
	if (bOpened) return;

	if (success != SOF_OpenDevice()) {
		throw Poco::LogicException(RAR_OPENDEVICEFAILED);
	}
	/// Do not change the call order.
	entries = SOF_GetUserList();
	spiltEntries();
	getCapability();

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