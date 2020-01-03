#pragma once
#include "Command.h"
#include "Poco/Net/NameValueCollection.h"
#include "Poco/Util/Application.h"
#include "Poco/Debugger.h"
#include "Poco/String.h"
#include "JSONStringify.h"
#include "../Utility.h"
#include "RequestHandleException.h"
#include "Reach/Data/DataException.h"
#include "translater.h"
#include <string>

using namespace Reach;

using Poco::Debugger;
using Poco::format;
using Poco::Net::NameValueCollection;
using Poco::Util::Application;

Command::Command()
{
}

Command::~Command()
{
}

Command& Command::execute()
{
	try {
		this->run();
		toJSON();
		/// 业务逻辑不允许 response 为空
		if (response.empty()) {
			int error = Utility::SOF_GetLastError();
			throw RequestHandleException(RAR_UNKNOWNERR);
		}
	}
	catch (RequestHandleException& e) {
		///统一错误解析处理
		sendErrorResponse(e.className(), e.code());
	}
	catch (Reach::Data::ConnectionFailedException& e) {
		sendErrorResponse(e.className(), RAR_OPENDEVICEFAILED);
	}
	catch (Reach::CloudCommandException& e) {
		sendErrorResponseEx(e.message(), e.code());
	}
	catch (Poco::NotFoundException& e){
		sendErrorResponse(e.message(), e.code());
	}
	catch (Poco::Exception& e) {
		sendErrorResponseEx(e.message(), e.code());
	}

	return *this;
}

std::string  Command::getEngine()
{
	Application& app = Application::instance();
	return app.config().getString("engine.mode", "");
}

void  Command::add(const std::string& name, const std::string& value)
{
	colletion.add(name, value);
}

void  Command::add(const std::string& name, int value)
{
	colletion.add(name, std::to_string(value));
}

void Command::sendErrorResponseEx(const std::string& msg, int code)
{
	response = JSONStringify(msg, code);
}

void  Command::sendErrorResponse(const std::string& msg, int code)
{
	Debugger::message(format("%s : <%s>:<%d>", msg, msg, code));
	translater& trans = translater::default();
	std::string message, detail;

	try
	{
		message = trans.tr("error", code);
		detail = trans.tr("SOFError", Utility::SOF_GetLastError());
	}
	catch (Poco::NotFoundException&)
	{
		message = trans.tr("error", RAR_UNKNOWNERR);
	}

	response = JSONStringify(message, code);
	response.addObject("info", detail);
}

std::string  Command::operator ()()
{
	return response.toString();
}

void  Command::toJSON()
{
	typedef NameValueCollection::ConstIterator Iter;
	for (Iter it = colletion.begin(); it != colletion.end(); it++) {
		Debugger::message(format("object item <%s>:<%s> ", it->first, it->second));
		response.addDataItem(it->first, it->second);
	}
}