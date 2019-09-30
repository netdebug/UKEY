#pragma once

#include "Reach/Data/Data.h"
#include "Reach/Data/Session.h"
#include "Reach/Data/SessionHolder.h"
#include "Poco/String.h"
#include "Poco/Mutex.h"
#include "Poco/AutoPtr.h"
#include <map>

namespace Reach {
namespace Data {

	class Data_API SessionContainer
	{
	public:
		static const std::size_t LOGIN_TIMEOUT_DEFAULT = Session::LOGIN_TIMEOUT_DEFAULT;

		SessionContainer();
		/// Create the SessionContainer for session with the given session parameters.

		~SessionContainer();
		/// Destroys the SessionPoolContainer.

		void add(SessionHolder* pS);
		/// Adds existing session to the container.
		/// Throws SessionExitsException if session already exists.

		Session add(const std::string& sessionKey,
			const std::string& connectionString,
			std::size_t timeout = LOGIN_TIMEOUT_DEFAULT);
		/// Add a new session to the container and returns a Session from
		/// newly created session. If session exists, request to add is silently
		/// ignored and session is returned from the existing session.

		bool has(const std::string& name) const;
		/// Returns true if the requested name exists, false otherwise.

		bool isActive(const std::string& sessionKey,
			const std::string& connectionString = "") const;
		/// Returns true if the session is active (i.e. not shut down).
		/// If connectionString is empty string, sessionKey must be a 
		/// fully qualified session name as registered with the session
		/// container.

		Session get(const std::string& name);
		/// Returns the requested Session.
		/// Throws NotFoundException if session is not found.

		void remove(const std::string& name);
		/// Removes a Session.

		void clear();
		/// Removes all sessiones;

		int count() const;
		/// Returns the number of session in the container.

		void shutdown();
		/// Shuts down all the sessions.

	private:
		typedef Poco::AutoPtr<SessionHolder> SessionHolderPtr;
		typedef std::map<std::string, SessionHolderPtr, Poco::CILess> SessionMap;

		SessionContainer(const SessionContainer&);
		SessionContainer& operator = (const SessionContainer&);

		SessionMap _sessions;
		Poco::FastMutex _mutex;
	};

	inline bool SessionContainer::has(const std::string& name) const
	{
		return _sessions.find(name) != _sessions.end();
	}

	inline void SessionContainer::remove(const std::string& name)
	{
		_sessions.erase(name);
	}

	inline void SessionContainer::clear()
	{
		_sessions.clear();
	}

	inline int SessionContainer::count() const
	{
		return static_cast<int>(_sessions.size());
	}
} } /// namespace Reach::Data
