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
	_containerString("fjca_Container")
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
			rc = FJCA_IsUsbKeyConnected();
			if (rc) break;
			if (sw.elapsedSeconds() >= tout)
			{
				close();
				throw FJCAException(rc);
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
	return "fjca||fjca_Container";
}


std::string SessionImpl::getCertBase64String(short ctype)
{
	//enum certType { sign = 1, crypto };
	assert(sign <= ctype && ctype <= crypto);

	char content[4096] = { 0 };
	bool ret = FJCA_ExportUserCert(ctype, content, 4096);

	if (!ret) throw Reach::Data::DataException();

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
	std::string content = getCertBase64String(sign);

	char num[40] = { 0 };

	bool ret = FJCA_GetCertOID(const_cast<char*>(content.c_str()), num, 40);
	//serialNumber = SOF_GetDeviceInfo(_containerString, SGD_DEVICE_SERIAL_NUMBER);
	//@000@0012bit
	if (!ret) throw Poco::DataException(Utility::lastError(_containerString));

	std::string tmp(num);
	std::size_t n = tmp.find_last_of('@');
	assert(n != std::string::npos);
	return tmp.substr(n+1, 12);
}

std::string SessionImpl::encryptData(const std::string& paintText, const std::string& base64)
{
	///只允许加密证书加密
	char encryptData[4096] = { 0 };

	bool ret = FJCA_EncryptByPubkey(const_cast<char*>(base64.c_str()), const_cast<char*>(paintText.c_str()), encryptData, 4096);

	if (!ret) throw Poco::DataException(Utility::lastError(_containerString));

	return encryptData;
}

std::string SessionImpl::decryptData(const std::string& encrypt)
{
	char decryptBuffer[4096] = { 0 }; 

	bool ret = FJCA_DecryptDataByPrivateKey(const_cast<char*>(encrypt.c_str()), decryptBuffer, 4096);

	if (!ret) throw  Poco::DataException(Utility::lastError(_containerString));

	return decryptBuffer;
}

std::string SessionImpl::signByP1(const std::string& message)
{
	char signature[4096] = { 0 };

	if (!FJCA_SignData(const_cast<char*>(message.c_str()), signature, 4096)) {
		throw Poco::DataException(Utility::lastError(_containerString));
	}

	return signature;
}

bool SessionImpl::verifySignByP1(const std::string& base64, const std::string& msg, const std::string& signature)
{
	return FJCA_VerifySign(msg.c_str(),	signature.c_str(), base64.c_str());
}

std::string SessionImpl::signByP7(const std::string& textual, int mode)
{
	throw Poco::NotImplementedException("FJCA signByP7");
	return "";
}

bool SessionImpl::verifySignByP7(const std::string& textual, const std::string& signature)
{
	throw Poco::NotImplementedException("FJCA verifySignByP7");
	return false;
}

} } } // namespace Reach::Data::FJCA
