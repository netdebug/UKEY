#pragma once
#include "Poco/Notification.h"

class MQTTNotification :
	public Poco::Notification
{
public:
	MQTTNotification(const std::string& message);
	virtual ~MQTTNotification();

	inline size_t action() const 
	{
		return _action;
	}

	inline std::string token() const
	{
		return _token;
	}

	inline std::string transid() const
	{
		return _transid;
	}

	inline std::string authResult() const
	{
		return _authResult;
	}

	inline std::string message() const
	{
		return _message;
	}

	inline std::string context() const
	{
		return _context;
	}
private:
	std::size_t _action;
	std::string _token;
	std::string _context;
	std::string _transid;
	std::string _authResult;
	std::string _message;
};

//ÔÆµÇÂ¼
class MQTTNotificationEvent :
	public MQTTNotification {
public:
	MQTTNotificationEvent(const std::string& message);
	~MQTTNotificationEvent();
public:
	std::string _mobile;
	std::string _userName;
	std::string _userID;
};