#pragma once
#include "Poco/Notification.h"

class MQTTNotification :
	public Poco::Notification
{
public:
	MQTTNotification(const std::string& message);
	~MQTTNotification();

	std::size_t action;
	std::string token;
	std::string context;
};

