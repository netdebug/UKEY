#pragma once
#include "Poco/JSON/Parser.h"
#include "Poco/Dynamic/Var.h"

namespace Reach {

	class CloudCommand :
		public Poco::JSON::Parser
	{
	public:
		CloudCommand(const std::string& url);
		virtual ~CloudCommand();
		
		void sendRequest();
		virtual void mixValue() = 0;
		bool success();
		void prepare(const std::string& data);
		std::string extract(const std::string& name);
		std::string extract(const std::string& body, const std::string& name);
	private:
		Poco::Dynamic::Var _in;
		Poco::Dynamic::Var _out;
		std::string _url;
	};
}