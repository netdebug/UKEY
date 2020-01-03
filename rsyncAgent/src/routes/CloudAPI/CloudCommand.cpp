#include "CloudCommand.h"
#include "Poco/JSON/Object.h"
#include "Poco/Util/Application.h"
#include "Poco/DynamicStruct.h"
#include "Poco/Dynamic/Var.h"
#include <cassert>
#include "../src/Utility.h"

using namespace Reach;
using Poco::Util::Application;
using Poco::JSON::Object;
using Poco::DynamicStruct;
using Poco::Dynamic::Var;

CloudCommand::CloudCommand(const std::string& url)
:_url(url)
{

}

CloudCommand::~CloudCommand()
{

}

void CloudCommand::sendRequest()
{
	Application& app = Application::instance();

	std::string message = Utility::sendRequest(_url, _in);

	_out = parse(message);
	assert(_out.type() == typeid(Object::Ptr));


	poco_information_f1(app.logger(), "receiveResponse:\n%s", message);
}

bool CloudCommand::success()
{
	DynamicStruct ds = *_out.extract<Object::Ptr>();
	if (ds["head"]["code"] == "0000")
		return true;

	return false;
}

void CloudCommand::prepare(const std::string& data)
{
	_in = data;
}

std::string CloudCommand::extract(const std::string& name)
{
	DynamicStruct ds = *_out.extract<Object::Ptr>();
	assert(ds.contains(name));
	return ds[name];
}

std::string CloudCommand::extract(const std::string& body, const std::string& name)
{
	DynamicStruct ds = *_out.extract<Object::Ptr>();
	Var result = parse(ds[body]);
	assert(result.type() == typeid(Object::Ptr));
	ds = *result.extract<Object::Ptr>();
	assert(ds.contains(name));
	return ds[name];
}