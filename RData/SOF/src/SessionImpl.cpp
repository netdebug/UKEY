//
// SessionImpl.cpp
//
// Library: Data/SOF
// Package: SOF
// Module:  SessionImpl
//
// Copyright (c) 2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#include "Reach/Data/SOF/SessionImpl.h"
#include "Reach/Data/SOF/SOFException.h"
#include "Reach/Data/Session.h"
#include "Poco/Stopwatch.h"
#include "Poco/String.h"
#include "Poco/Mutex.h"
#include "Poco/Thread.h"
#include "Reach/Data/DataException.h"
#include "SoFProvider.h"
#include "SOFErrorCode.h"

#include <cstdlib>


#ifndef SOF_OPEN_URI
#define SOF_OPEN_URI 0
#endif


namespace Reach {
namespace Data {
namespace SOF {


SessionImpl::SessionImpl(const std::string& fileName, std::size_t loginTimeout):
	Reach::Data::AbstractSessionImpl<SessionImpl>(fileName, loginTimeout),
	_connector(Connector::KEY),
	_connected(false),
	_isTransaction(false)
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
			rc = SOF_OpenDevice();
			if (rc == SAR_OK) break;
			if (sw.elapsedSeconds() >= tout)
			{
				close();
				//Utility::throwException(_pDB, rc);
			}
			else Poco::Thread::sleep(10);
		}
	} 
	catch (SOFException& ex)
	{
		throw ConnectionFailedException(ex.displayText());
	}

	_connected = true;
}


void SessionImpl::close()
{
	SOF_CloseDevice();

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
	return false;
}

bool SessionImpl::changePW(const std::string& oldCode, const std::string& newCode)
{
	return false;
}

std::string SessionImpl::getUserList()
{
	return "";
}

std::string SessionImpl::getCertBase64String(short ctype)
{
	return "";
}

int SessionImpl::getPinRetryCount()
{
	return 0;
}

std::string SessionImpl::getCertInfo(const std::string& base64, int type)
{
	return "";
}

std::string SessionImpl::getSerialNumber()
{
	return "";
}

std::string SessionImpl::encryptData(const std::string& paintText, const std::string& base64)
{
	///只允许加密证书加密
	return "";
}

std::string SessionImpl::decryptData(const std::string& encryptBuffer)
{
	return "";
}

std::string SessionImpl::signByP1(const std::string& message)
{
	return "";
}

bool SessionImpl::verifySignByP1(const std::string& base64, const std::string& msg, const std::string& signature)
{
	return false;
}

} } } // namespace Reach::Data::SOF
