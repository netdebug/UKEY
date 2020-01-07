#include "TokenManager.h"
#include "Poco/SingletonHolder.h"
#include "Poco/SharedPtr.h"

using namespace Reach;
using Poco::SharedPtr;
using Poco::SingletonHolder;

TokenManager::TokenManager()
{

}

TokenManager::~TokenManager()
{

}

void TokenManager::add(const std::string& key, const std::string& val)
{
	_cache.add(key, val);
}

void TokenManager::update(const std::string& key, const std::string& val)
{
	_cache.update(key, val);
}

void TokenManager::remove(const std::string& key)
{
	_cache.remove(key);
}

std::string TokenManager::get(const std::string& key)
{
	SharedPtr<std::string> ptr = _cache.get(key);
	if (ptr) return *ptr;
	return "";
}

void TokenManager::clear()
{
	_cache.clear();
}

namespace
{
	static SingletonHolder<TokenManager> sh;
}

TokenManager& TokenManager::default()
{
	return *sh.get();
}