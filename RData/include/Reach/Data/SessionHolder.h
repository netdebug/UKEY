#pragma once
#include "Reach/Data/Data.h"
#include "Reach/Data/SessionImpl.h"
#include "Poco/RefCountedObject.h"
#include "Poco/AutoPtr.h"

namespace Reach {
namespace Data {

	class Data_API SessionHolder: public Poco::RefCountedObject
		/// This class is used by SessionContainer to manage SessionImpl object
	{
	public:
		
		SessionHolder(SessionImpl* pSessionImpl);
		/// Creates the SessionHolder.

		~SessionHolder();
		/// Destroys the SessionHolder.

		Poco::AutoPtr<SessionImpl> get();
		/// Returns a pointer to the SessionImpl.

		SessionImpl* session();
		/// Returns a pointer to the SessionImpl;

		std::string name() const;
		/// Returns the name for this session.

		static std::string name(const std::string& connector,
			const std::string& connectionString);
		/// Returns the name formatted from supplied arguments as "connector:///connectionString".

		bool isActive() const;
		/// Returns true if the session is active(i.e. not shut down).

		void shutdown();
		/// Shuts down the session.
	private:
		Poco::AutoPtr<SessionImpl> _pImpl;
		bool _shutdown;
	};

	inline std::string SessionHolder::name(const std::string& connector,
		const std::string& connectionString)
	{
		return SessionImpl::uri(connector, connectionString);
	}

	inline std::string SessionHolder::name() const
	{
		return _pImpl->uri();
	}

	inline SessionImpl* SessionHolder::session()
	{
		return _pImpl;
	}

	inline Poco::AutoPtr<SessionImpl> SessionHolder::get()
	{
		return _pImpl;
	}

	inline bool SessionHolder::isActive() const
	{
		return !_shutdown;
	}

} } ///namespace Reach::Data