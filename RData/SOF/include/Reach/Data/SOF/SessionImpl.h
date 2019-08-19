//
// SessionImpl.h
//
// Library: Data/SOF
// Package: SOF
// Module:  SessionImpl
//
// Definition of the SessionImpl class.
//
// Copyright (c) 2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef RData_SOF_SessionImpl_INCLUDED
#define RData_SOF_SessionImpl_INCLUDED


#include "Reach/Data/SOF/SOF.h"
#include "Reach/Data/SOF/Connector.h"
#include "Reach/Data/AbstractSessionImpl.h"
#include "Poco/SharedPtr.h"
#include "Poco/Mutex.h"
#include "UDevice.h"

namespace Reach {
namespace Data {
namespace SOF {


class SOF_API SessionImpl: public Reach::Data::AbstractSessionImpl<SessionImpl>
	/// Implements SessionImpl interface.
{
public:
	SessionImpl(const std::string& fileName,
		std::size_t loginTimeout = LOGIN_TIMEOUT_DEFAULT);
		/// Creates the SessionImpl. Opens a connection to the database.

	~SessionImpl();
		/// Destroys the SessionImpl.

	void open(const std::string& connect = "");
		/// Opens a connection to the Database.
		/// 
		/// An in-memory system database (sys), with a single table (dual) 
		/// containing single field (dummy) is attached to the database.
		/// The in-memory system database is used to force change count
		/// to be reset to zero on every new query (or batch of queries) 
		/// execution. Without this functionality, select statements
		/// executions that do not return any rows return the count of
		/// changes effected by the most recent insert, update or delete.
		/// In-memory system database can be queried and updated but can not
		/// be dropped. It may be used for other purposes 
		/// in the future.

	void close();
		/// Closes the session.

	bool isConnected();
		/// Returns true if connected, false otherwise.

	void setConnectionTimeout(std::size_t timeout);
		/// Sets the session connection timeout value.
		/// Timeout value is in seconds.

	std::size_t getConnectionTimeout();
		/// Returns the session connection timeout value.
		/// Timeout value is in seconds.

	const std::string& connectorName() const;
		/// Returns the name of the connector.

	bool login(const std::string& passwd);

	bool changePW(const std::string& oldCode, const std::string& newCode);

	std::string getUserList();

	std::string getCertBase64String(short ctype);

	int getPinRetryCount();

	std::string getCertInfo(const std::string& base64, int type);

	std::string getSerialNumber();

	std::string encryptData(const std::string& paintText, const std::string& base64);///只允许加密证书加密

	std::string decryptData(const std::string& encryptBuffer);

	std::string signByP1(const std::string& message);

	bool verifySignByP1(const std::string& base64, const std::string& msg, const std::string& signature);

protected:
	void setConnectionTimeout(const std::string& prop, const Poco::Any& value);
	Poco::Any getConnectionTimeout(const std::string& prop);

private:
	std::string _connector;
	bool        _connected;
	bool        _isTransaction;
	int         _timeout;

	std::string _ContainerString;//uid
	Poco::Mutex _mutex;

};

inline const std::string& SessionImpl::connectorName() const
{
	return _connector;
}


inline std::size_t SessionImpl::getConnectionTimeout()
{
	return static_cast<std::size_t>(_timeout/1000);
}


} } } // namespace Reach::Data::SOF


#endif // Data_SOF_SessionImpl_INCLUDED
