#pragma once

#include "Poco/AutoPtr.h"
#include "Poco/Util/IniFileConfiguration.h"

namespace Reach {
namespace Data {
namespace SOF {

			class translater
			{
			public:
				translater();
				~translater();
				static translater& default();

				std::string tr(int key);
				std::string tr(const std::string& key);
				std::string tr(const std::string& section, int key);
				std::string tr(const std::string& section, const std::string& key);

			private:
				Poco::AutoPtr<Poco::Util::IniFileConfiguration> _pConfig;
			};
		}
	}
}
