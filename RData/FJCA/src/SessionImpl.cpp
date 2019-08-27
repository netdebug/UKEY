//
// SessionImpl.cpp
//
// Library: Data/FJCA
// Package: FJCA
// Module:  SessionImpl
//
// Copyright (c) 2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#include "Reach/Data/DataException.h"
#include "Reach/Data/FJCA/SessionImpl.h"
#include "Reach/Data/FJCA/FJCAException.h"
#include "Reach/Data/FJCA/Utility.h"
#include "Reach/Data/FJCA/FJCA_FUN_GT_DLL.h"
#include "Reach/Data/Session.h"
#include "Poco/Stopwatch.h"
#include "Poco/String.h"
#include "Poco/Mutex.h"
#include "Poco/Thread.h"
#include "Poco/StreamCopier.h"
#include "Poco/Base64Decoder.h"
#include "Poco/Buffer.h"
#include "GMCrypto.h"
#include <cassert>
#include <cstdlib>
#include <sstream>
#include <string>


#ifndef FJCA_OPEN_URI
#define FJCA_OPEN_URI 0
#endif

extern std::string SOF_GetCertInfo(std::string Base64EncodeCert, short Type);

namespace Reach {
namespace Data {
namespace FJCA {


SessionImpl::SessionImpl(const std::string& connectionString, std::size_t loginTimeout):
	Reach::Data::AbstractSessionImpl<SessionImpl>(connectionString, loginTimeout),
	_connector(Connector::KEY),
	_connected(false),
	_random_size(0),
	_connectionString(connectionString),
	_containerString("fjca||fjca_Container")
{
	open();
	setConnectionTimeout(loginTimeout);

	addProperty("connectionTimeout", &SessionImpl::setConnectionTimeout, &SessionImpl::getConnectionTimeout);
}


SessionImpl::~SessionImpl()
{
	try
	{
		close();
	}
	catch (...)
	{
		poco_unexpected();
	}
}

void SessionImpl::open(const std::string& connect)
{
	if (connect != connectionString())
	{
		if (isConnected())
			throw Poco::InvalidAccessException("Session already connected");

		if (!connect.empty())
			setConnectionString(connect);
	}

	poco_assert_dbg (!connectionString().empty());

	try
	{
		int rc = 0;
		size_t tout = getLoginTimeout();
		Poco::Stopwatch sw; sw.start();
		while (true)
		{
			std::string wrong;
			rc = FJCA_OpenKeyWithPin(wrong.c_str());
			if (rc == 0) break;
			if (sw.elapsedSeconds() >= tout)
			{
				close();
				//Utility::throwException(_pDB, rc);
			}
			else Poco::Thread::sleep(10);
		}
	} 
	catch (FJCAException& ex)
	{
		throw ConnectionFailedException(ex.displayText());
	}

	_connected = true;
}


void SessionImpl::close()
{
	FJCA_CloseKey();

	_connected = false;
}


bool SessionImpl::isConnected()
{
	return _connected;
}


void SessionImpl::setConnectionTimeout(std::size_t timeout)
{
	int tout = static_cast<int>(1000 * timeout);
	_timeout = tout;
}

void SessionImpl::setConnectionTimeout(const std::string& prop, const Poco::Any& value)
{
	setConnectionTimeout(Poco::RefAnyCast<std::size_t>(value));
}


Poco::Any SessionImpl::getConnectionTimeout(const std::string& prop)
{
	return Poco::Any(_timeout/1000);
}

bool SessionImpl::login(const std::string& passwd)
{
	return FJCA_OpenKeyWithPin(passwd.c_str());
}

bool SessionImpl::changePW(const std::string& oldCode, const std::string& newCode)
{
	throw Poco::NotImplementedException("FJCA changePW");
	return false;
}

std::string SessionImpl::getUserList()
{
	return _containerString;
}


std::string SessionImpl::getCertBase64String(short ctype)
{
	//enum certType { sign = 1, crypto };
	assert(sign <= ctype && ctype <= crypto);
	std::string content;
	Poco::Buffer<char> c(4096);
	c.clear();
	bool ret = FJCA_ExportUserCert(ctype, c.begin(), c.capacity());

	if (!ret || c.empty())
		throw Reach::Data::DataException();

	content.append(c.begin(), c.size());
	return content;
}

int SessionImpl::getPinRetryCount()
{
	return 1;
}

std::string SessionImpl::getCertInfo(const std::string& base64, int type)
{
	std::string item;
	
	if (SGD_CERT_VERSION == type) {
		item = Utility::GetCertVersion(base64);
	}
	else if (SGD_CERT_VALID_TIME == type) {
		item = Utility::GetCertVaildTime(base64);
	}
	else if (SGD_OID_IDENTIFY_NUMBER == type) {
		/// only support user id card
		item = Utility::GetCertOwnerID(base64);
	}
	else
	{
		item = SOF_GetCertInfo(base64, type);
	}

	return item;
}

std::string SessionImpl::getSerialNumber()
{
	std::string serialNumber;
	
	std::string content = getCertBase64String(sign);

	Poco::Buffer<char> num(40);
	num.clear();
	bool ret = FJCA_GetKeySerial(const_cast<char*>(content.c_str()), num.begin(), num.capacity());
	//serialNumber = SOF_GetDeviceInfo(_containerString, SGD_DEVICE_SERIAL_NUMBER);
	//@000@0012bit
	std::string tmp(num.begin(), num.size());
	if (!ret || tmp.empty()) {
		Poco::DataException(Utility::lastError(_containerString));
	}

	std::size_t n = tmp.find_last_of('@');
	serialNumber = tmp.substr(n, 12);
	return serialNumber;
}

std::string SessionImpl::encryptData(const std::string& paintText, const std::string& base64)
{
	///只允许加密证书加密
	std::string encryptData;
	Poco::Buffer<char> buffer(4096); buffer.clear();

	bool ret = FJCA_EncryptByPubkey(const_cast<char*>(base64.c_str()), const_cast<char*>(paintText.c_str()), buffer.begin(), buffer.capacity());

	if (!ret || buffer.empty()) {
		throw Poco::DataException(Utility::lastError(_containerString));
	}

	encryptData.append(buffer.begin(), buffer.size());
	return encryptData;
}

std::string SessionImpl::decryptData(const std::string& encrypt)
{
	std::string decryptBuffer;
	Poco::Buffer<char> buffer(4096); buffer.clear();

	bool ret = FJCA_DecryptDataByPrivateKey(const_cast<char*>(encrypt.c_str()), buffer.begin(), buffer.capacity());
	if (!ret || buffer.empty())
		throw  Poco::DataException(Utility::lastError(_containerString));

	std::string text, tmp;
	tmp.append(buffer.begin(), buffer.size());

	std::istringstream istr(tmp);
	Poco::Base64Decoder decoder(istr);
	Poco::StreamCopier::copyToString(decoder, text);

	return text;
}

std::string SessionImpl::signByP1(const std::string& message)
{
	std::string signature;
	Poco::Buffer<char> val(4096); val.clear();
	if (FJCA_SignData(const_cast<char*>(message.c_str()), val.begin(), val.capacity())) {
		throw Poco::DataException(Utility::lastError(_containerString));
	}

	signature.append(val.begin(), val.size());
	return signature;
}

bool SessionImpl::verifySignByP1(const std::string& base64, const std::string& msg, const std::string& signature)
{
	return FJCA_VerifySign(msg.c_str(),	signature.c_str(), base64.c_str());
}

} } } // namespace Reach::Data::FJCA
