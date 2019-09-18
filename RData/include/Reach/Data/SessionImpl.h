//
// SessionImpl.h
//
// Library: Data
// Package: DataCore
// Module:  SessionImpl
//
// Definition of the SessionImpl class.
//
// Copyright (c) 2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef RData_SessionImpl_INCLUDED
#define RData_SessionImpl_INCLUDED


#include "Reach/Data/Data.h"
#include "Poco/RefCountedObject.h"
#include "Poco/String.h"
#include "Poco/Format.h"
#include "Poco/Any.h"


namespace Reach {
namespace Data {


class StatementImpl;


class Data_API SessionImpl: public Poco::RefCountedObject
	/// Interface for Session functionality that subclasses must extend. 
	/// SessionImpl objects are noncopyable.
{
public:
	static const std::size_t LOGIN_TIMEOUT_INFINITE = 0;
		/// Infinite connection/login timeout.

	static const std::size_t LOGIN_TIMEOUT_DEFAULT = 10;
		/// Default connection/login timeout in seconds.

	static const std::size_t CONNECTION_TIMEOUT_INFINITE = 0;
		/// Infinite connection/login timeout.

	static const std::size_t CONNECTION_TIMEOUT_DEFAULT = CONNECTION_TIMEOUT_INFINITE;
		/// Default connection/login timeout in seconds.

	SessionImpl(const std::string& connectionString,
		std::size_t timeout = LOGIN_TIMEOUT_DEFAULT);
		/// Creates the SessionImpl.

	virtual ~SessionImpl();
		/// Destroys the SessionImpl.

	virtual void open(const std::string& connectionString = "") = 0;
		/// Opens the session using the supplied string.
		/// Can also be used with default empty string to reconnect 
		/// a disconnected session.
		/// If the connection is not established within requested timeout 
		/// (specified in seconds), a ConnectionFailedException is thrown. 
		/// Zero timout means indefinite

	virtual void close() = 0;
		/// Closes the connection.

	virtual bool isConnected() = 0;
		/// Returns true if session is connected, false otherwise.

	void setLoginTimeout(std::size_t timeout);
		/// Sets the session login timeout value.

	std::size_t getLoginTimeout() const;
		/// Returns the session login timeout value.

	virtual void setConnectionTimeout(std::size_t timeout) = 0;
		/// Sets the session connection timeout value.

	virtual std::size_t getConnectionTimeout() = 0;
		/// Returns the session connection timeout value.

	void reconnect();
		/// Closes the connection and opens it again.

	virtual const std::string& connectorName() const = 0;
		/// Returns the name of the connector.
	virtual const std::string& contianerName() const = 0;

	virtual bool login(const std::string& passwd) = 0;

	virtual bool changePW(const std::string& oldCode, const std::string& newCode) = 0;

	virtual std::string getUserList() = 0;

	virtual std::string getCertBase64String(short ctype) = 0;

	virtual int getPinRetryCount() = 0;

	virtual std::string getCertInfo(const std::string& base64, int type) = 0;

	virtual std::string getSerialNumber() = 0;

	virtual std::string encryptData(const std::string& paintText, const std::string& base64) = 0;///只允许加密证书加密

	virtual std::string decryptData(const std::string& encryptBuffer) = 0;

	virtual std::string signByP1(const std::string& message) = 0;

	virtual bool verifySignByP1(const std::string& base64, const std::string& msg, const std::string& signature) = 0;

	virtual std::string signByP7(const std::string& textual, int mode) = 0;

	virtual bool verifySignByP7(const std::string& textual, const std::string& signature) = 0;

	const std::string& connectionString() const;
		/// Returns the connection string.

	static std::string uri(const std::string& connector, const std::string& connectionString);
		/// Returns formatted URI.

	std::string uri() const;
		/// Returns the URI for this session.

protected:
	void setConnectionString(const std::string& connectionString);
		/// Sets the connection string. Should only be called on
		/// disconnetced sessions. Throws InvalidAccessException when called on
		/// a connected session.

private:
	SessionImpl();
	SessionImpl(const SessionImpl&);
	SessionImpl& operator = (const SessionImpl&);

	std::string _connectionString;
	std::size_t _loginTimeout;
};


//
// inlines
//
inline const std::string& SessionImpl::connectionString() const
{
	return _connectionString;
}


inline void SessionImpl::setLoginTimeout(std::size_t timeout)
{
	_loginTimeout = timeout;
}


inline std::size_t SessionImpl::getLoginTimeout() const
{
	return _loginTimeout;
}


inline std::string SessionImpl::uri(const std::string& connector,
	const std::string& connectionString)
{
	return Poco::format("%s:///%s", connector, connectionString);
}


inline std::string SessionImpl::uri() const
{
	return uri(connectorName(), connectionString());
}


} } // namespace Poco::Reach


#endif // RData_SessionImpl_INCLUDED
