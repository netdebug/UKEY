#pragma once
#include "Poco/Notification.h"
#include <map>
#include "Poco/Dynamic/Struct.h"

using namespace std;
class MQTTNotification :
	public Poco::Notification
{
public:
	MQTTNotification(const std::string& message);
	virtual ~MQTTNotification();

	inline std::string msg() const
	{
		return _msg;
	}

	inline std::string code() const
	{
		return _code;
	}

	inline std::string context() const
	{
		return _context;
	}
	inline std::string getdata(const std::string name) const
	{
		map<string, string >::const_iterator it;
		it = _data.find(name);
		if (it != _data.end())
		{
			return it->second;
		}
		return "";
	}

	Poco::DynamicStruct paraseString(const std::string& str);
private:
	std::string _code;
	std::string _context;
	std::string _msg;
	std::map<std::string, std::string> _data;
};