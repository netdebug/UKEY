//
// Session.h
//
// Library: Data
// Package: DataCore
// Module:  Session
//
// Definition of the Session class.
//
// Copyright (c) 2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef RData_Session_INCLUDED
#define RData_Session_INCLUDED


#include "Reach/Data/Data.h"
#include "Reach/Data/SessionImpl.h"
#include "Poco/AutoPtr.h"
#include "Poco/Any.h"
#include <algorithm>


namespace Reach {
namespace Data {


class Data_API Session
	/// A Session holds a connection to a Database and creates Statement objects.
	///
	/// Sessions are always created via the SessionFactory:
	///    
	///     Session ses(SessionFactory::instance().create(connectorKey, connectionString));
	///    
	/// where the first param presents the type of session one wants to create (e.g., for SQLite one would choose "SQLite",
	/// for ODBC the key is "ODBC") and the second param is the connection string that the session implementation 
	/// requires to connect to the database. The format of the connection string is specific to the actual connector.
	///
	/// A simpler form to create the session is to pass the connector key and connection string directly to
	/// the Session constructor.
	///
	/// A concrete example to open an SQLite database stored in the file "dummy.db" would be
	///    
	///     Session ses("SQLite", "dummy.db");
	///    
	/// Via a Session one can create two different types of statements. First, statements that should only be executed once and immediately, and
	/// second, statements that should be executed multiple times, using a separate execute() call.
	/// The simple one is immediate execution:
	///    
	///     ses << "CREATE TABLE Dummy (data INTEGER(10))", now;
	///
	/// The now at the end of the statement is required, otherwise the statement
	/// would not be executed.
	///    
	/// If one wants to reuse a Statement (and avoid the overhead of repeatedly parsing an SQL statement)
	/// one uses an explicit Statement object and its execute() method:
	///    
	///     int i = 0;
	///     Statement stmt = (ses << "INSERT INTO Dummy VALUES(:data)", use(i));
	///    
	///     for (i = 0; i < 100; ++i)
	///     {
	///         stmt.execute();
	///     }
	///    
	/// The above example assigns the variable i to the ":data" placeholder in the SQL query. The query is parsed and compiled exactly
	/// once, but executed 100 times. At the end the values 0 to 99 will be present in the Table "DUMMY".
	///
	/// A faster implementaton of the above code will simply create a vector of int
	/// and use the vector as parameter to the use clause (you could also use set or multiset instead):
	///    
	///     std::vector<int> data;
	///     for (int i = 0; i < 100; ++i)
	///     {
	///         data.push_back(i);
	///     }
	///     ses << "INSERT INTO Dummy VALUES(:data)", use(data);
	///
	/// NEVER try to bind to an empty collection. This will give a BindingException at run-time!
	///
	/// Retrieving data from a database works similar, you could use simple data types, vectors, sets or multiset as your targets:
	///
	///     std::set<int> retData;
	///     ses << "SELECT * FROM Dummy", into(retData));
	///
	/// Due to the blocking nature of the above call it is possible to partition the data retrieval into chunks by setting a limit to
	/// the maximum number of rows retrieved from the database:
	///
	///     std::set<int> retData;
	///     Statement stmt = (ses << "SELECT * FROM Dummy", into(retData), limit(50));
	///     while (!stmt.done())
	///     {
	///         stmt.execute();
	///     }
	///
	/// The "into" keyword is used to inform the statement where output results should be placed. The limit value ensures
	/// that during each run at most 50 rows are retrieved. Assuming Dummy contains 100 rows, retData will contain 50 
	/// elements after the first run and 100 after the second run, i.e.
	/// the collection is not cleared between consecutive runs. After the second execute stmt.done() will return true.
	///
	/// A prepared Statement will behave exactly the same but a further call to execute() will simply reset the Statement, 
	/// execute it again and append more data to the result set.
	///
	/// Note that it is possible to append several "bind" or "into" clauses to the statement. Theoretically, one could also have several
	/// limit clauses but only the last one that was added will be effective. 
	/// Also several preconditions must be met concerning binds and intos.
	/// Take the following example:
	///
	///     ses << "CREATE TABLE Person (LastName VARCHAR(30), FirstName VARCHAR, Age INTEGER(3))";
	///     std::vector<std::string> nameVec; // [...] add some elements
	///     std::vector<int> ageVec; // [...] add some elements
	///     ses << "INSERT INTO Person (LastName, Age) VALUES(:ln, :age)", use(nameVec), use(ageVec);
	///
	/// The size of all use parameters MUST be the same, otherwise an exception is thrown. Furthermore,
	/// the amount of use clauses must match the number of wildcards in the query (to be more precise: 
	/// each binding has a numberOfColumnsHandled() value which defaults to 1. The sum of all these values 
	/// must match the wildcard count in the query.
	/// However, this is only important if you have written your own TypeHandler specializations.
	/// If you plan to map complex object types to tables see the TypeHandler documentation.
	/// For now, we simply assume we have written one TypeHandler for Person objects. Instead of having n different vectors,
	/// we have one collection:
	///
	///     std::vector<Person> people; // [...] add some elements
	///     ses << "INSERT INTO Person (LastName, FirstName, Age) VALUES(:ln, :fn, :age)", use(people);
	///
	/// which will insert all Person objects from the people vector to the database (and again, you can use set, multiset too,
	/// even map and multimap if Person provides an operator() which returns the key for the map).
	/// The same works for a SELECT statement with "into" clauses:
	///
	///     std::vector<Person> people;
	///     ses << "SELECT * FROM PERSON", into(people);
	/// 
	/// Mixing constants or variables with manipulators is allowed provided there are corresponding placeholders for the constants provided in
	/// the SQL string, such as in following example:
	///
	///     std::vector<Person> people;
	///     ses << "SELECT * FROM %s", into(people), "PERSON";
	/// 
	/// Formatting only kicks in if there are values to be injected into the SQL string, otherwise it is skipped.
	/// If the formatting will occur and the percent sign is part of the query itself, it can be passed to the query by entering it twice (%%).
	/// However, if no formatting is used, one percent sign is sufficient as the string will be passed unaltered.
	/// For complete list of supported data types with their respective specifications, see the documentation for format in Foundation.
{
public:
	static const std::size_t LOGIN_TIMEOUT_DEFAULT = SessionImpl::LOGIN_TIMEOUT_DEFAULT;

	Session(Poco::AutoPtr<SessionImpl> ptrImpl);
		/// Creates the Session.

	Session(const std::string& connector,
		const std::string& connectionString,
		std::size_t timeout = LOGIN_TIMEOUT_DEFAULT);
		/// Creates a new session, using the given connector (which must have
		/// been registered), and connectionString.

	Session(const std::string& connection,
		std::size_t timeout = LOGIN_TIMEOUT_DEFAULT);
		/// Creates a new session, using the given connection (must be in
		/// "connection:///connectionString" format).

	Session(const Session&);
		/// Creates a session by copying another one.

	Session& operator = (const Session&);
		/// Assignment operator.

	~Session();
		/// Destroys the Session.

	void swap(Session& other);
		/// Swaps the session with another one.

	void open(const std::string& connect = "");
		/// Opens the session using the supplied string.
		/// Can also be used with default empty string to 
		/// reconnect a disconnected session.
		/// If the connection is not established, 
		/// a ConnectionFailedException is thrown. 
		/// Zero timout means indefinite

	void close();
		/// Closes the session.

	bool isConnected();
		/// Returns true iff session is connected, false otherwise.

	void reconnect();
		/// Closes the session and opens it.

	void setLoginTimeout(std::size_t timeout);
		/// Sets the session login timeout value.

	std::size_t getLoginTimeout() const;
		/// Returns the session login timeout value.

	void setConnectionTimeout(std::size_t timeout);
		/// Sets the session connection timeout value.

	std::size_t getConnectionTimeout();
		/// Returns the session connection timeout value.

	std::string connector() const;
		/// Returns the connector name for this session.

	std::string uri() const;
		/// Returns the URI for this session.

	static std::string uri(const std::string& connector,
		const std::string& connectionString);
		/// Utility function that teturns the URI formatted from supplied 
		/// arguments as "connector:///connectionString".

	bool login(const std::string& passwd);

	bool changePW(const std::string& oldCode, const std::string& newCode);

	std::string getUserList();

	std::string getCertBase64String(short ctype);

	int getPinRetryCount();

	std::string getCertInfo(const std::string& base64, int type);

	std::string getSerialNumber();

	std::string encryptData(const std::string& paintText, const std::string& base64);

	std::string decryptData(const std::string& encryptBuffer);

	std::string signByP1(const std::string& message);

	bool verifySignByP1(const std::string& base64, const std::string& msg, const std::string& signature);

	SessionImpl* impl();
		/// Returns a pointer to the underlying SessionImpl.

private:
	Session();

	Poco::AutoPtr<SessionImpl> _pImpl;
};

inline void Session::open(const std::string& connect)
{
	_pImpl->open(connect);
}


inline void Session::close()
{
	_pImpl->close();
}


inline bool Session::isConnected()
{
	return _pImpl->isConnected();
}


inline void Session::reconnect()
{
	_pImpl->reconnect();
}


inline void Session::setLoginTimeout(std::size_t timeout)
{
	_pImpl->setLoginTimeout(timeout);
}


inline std::size_t Session::getLoginTimeout() const
{
	return _pImpl->getLoginTimeout();
}


inline void Session::setConnectionTimeout(std::size_t timeout)
{
	_pImpl->setConnectionTimeout(timeout);
}


inline std::size_t Session::getConnectionTimeout()
{
	return _pImpl->getConnectionTimeout();
}


inline std::string Session::connector() const
{
	return _pImpl->connectorName();
}


inline std::string Session::uri(const std::string& connector,
	const std::string& connectionString)
{
	return SessionImpl::uri(connector, connectionString);
}


inline std::string Session::uri() const
{
	return _pImpl->uri();
}

inline bool Session::login(const std::string& passwd)
{
	return _pImpl->login(passwd);
}

inline bool Session::changePW(const std::string& oldCode, const std::string& newCode)
{
	return _pImpl->changePW(oldCode, newCode);
}

inline std::string Session::getUserList()
{
	return _pImpl->getUserList();
}

inline std::string Session::getCertBase64String(short ctype)
{
	return _pImpl->getCertBase64String(ctype);
}

inline int Session::getPinRetryCount()
{
	return _pImpl->getPinRetryCount();
}

inline std::string Session::getCertInfo(const std::string& base64, int type)
{
	return _pImpl->getCertInfo(base64, type);
}

inline std::string Session::getSerialNumber()
{
	return _pImpl->getSerialNumber();
}

inline std::string Session::encryptData(const std::string& paintText, const std::string& base64)
{
	return _pImpl->encryptData(paintText, base64);
}

inline std::string Session::decryptData(const std::string& encryptBuffer)
{
	return _pImpl->decryptData(encryptBuffer);
}

inline std::string Session::signByP1(const std::string& message)
{
	return _pImpl->signByP1(message);
}

inline bool Session::verifySignByP1(const std::string& base64, const std::string& msg, const std::string& signature)
{
	return _pImpl->verifySignByP1(base64, msg, signature);
}

inline SessionImpl* Session::impl()
{
	return _pImpl;
}


inline void swap(Session& s1, Session& s2)
{
	s1.swap(s2);
}


} } // namespace Reach::Data


namespace std
{
	template<>
	inline void swap<Reach::Data::Session>(Reach::Data::Session& s1,
		Reach::Data::Session& s2)
		/// Full template specalization of std:::swap for Session
	{
		s1.swap(s2);
	}
}


#endif // Data_Session_INCLUDED
