#pragma once
#include <string>
#include "Poco/AccessExpireCache.h"

namespace Reach {

	class TokenManager
	{
	public:
		TokenManager();
		~TokenManager();

		void add(const std::string& key, const std::string& val);
		void update(const std::string& key, const std::string& val);
		void remove(const std::string& key);
		std::string get(const std::string& key);
		void clear();

		static TokenManager& default();
	private:
		typedef Poco::AccessExpireCache<std::string, std::string> TokenList;
		
		TokenList _cache;
	};
}