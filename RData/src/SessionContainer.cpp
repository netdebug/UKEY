#include "Reach/Data/SessionContainer.h"
#include "Reach/Data/SessionHolder.h"
#include "Reach/Data/DataException.h"
#include "Poco/Exception.h"
#include "Poco/URI.h"

using Poco::FastMutex;

namespace Reach {
namespace Data {

SessionContainer::SessionContainer()
{

}

SessionContainer::~SessionContainer()
{

}

void SessionContainer::add(SessionHolder* pSH)
{
	poco_check_ptr(pSH);

	FastMutex::ScopedLock lock(_mutex);

	if (_sessions.find(pSH->name()) != _sessions.end())
		throw SessionExitsException("Session already exists: " + pSH->name());

	pSH->duplicate();
	_sessions.insert(SessionMap::value_type(pSH->name(), pSH));
}

Session SessionContainer::add(const std::string& sessionKey,
	const std::string& connectionString,
	std::size_t timeout)
{
	std::string name = Session::uri(sessionKey, connectionString);

	FastMutex::ScopedLock lock(_mutex);
	SessionMap::iterator it = _sessions.find(name);

	// session already exists, silently return a session from it
	if (it != _sessions.end()) return it->second->get();
		
	Session s(sessionKey, connectionString);
	SessionHolder* pSH = new SessionHolder(s.impl());

	std::pair<SessionMap::iterator, bool> ins =
		_sessions.insert(SessionMap::value_type(name, pSH));

	return ins.first->second->get();
}

bool SessionContainer::isActive(const std::string& sessionKey,
	const std::string& connectionString) const
{
	std::string name = connectionString.empty() ?
		sessionKey : Session::uri(sessionKey, connectionString);

	SessionMap::const_iterator it = _sessions.find(name);
	if (it != _sessions.end() && it->second->isActive())
	{
		return true;
	}

	return false;
}

Session SessionContainer::get(const std::string& name)
{
	Poco::URI uri(name);
	std::string path = uri.getPath();
	poco_assert(!path.empty());
	std::string n = Session::uri(uri.getScheme(), path.substr(1));

	FastMutex::ScopedLock lock(_mutex);
	SessionMap::iterator it = _sessions.find(n);
	if (_sessions.end() == it) throw Poco::NotFoundException(n, 0x9001);/// no key device
	return it->second->get();
}

void SessionContainer::shutdown()
{
	SessionMap::iterator it = _sessions.begin();
	SessionMap::iterator end = _sessions.end();
	for (; it != end; ++it) it->second->shutdown();
}

} } /// namespace Reach::Data