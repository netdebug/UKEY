#include "UKeyDevice.h"
#include "Certificate.h"
#include "Container.h"
#include "Poco/RegularExpression.h"
#include <cassert>

using namespace Reach;
using Poco::RegularExpression;

UKeyDevice::UKeyDevice(const std::string entries)
	:_entries(entries)
{
	poco_assert(!_entries.empty());
	extract();
}

UKeyDevice::~UKeyDevice()
{

}

std::string UKeyDevice::containerName() const
{
	return _container->name();
}

std::string UKeyDevice::certificateName() const
{
	return _certificate->name();
}

void UKeyDevice::extract()
{
	std::string pattern("(\\S+)\\|\\|(\\S+)[&&&]*");
	int options = 0;

	RegularExpression re(pattern, options);
	RegularExpression::Match mtch;

	if (!re.match(_entries, mtch)) {
		throw Poco::RegularExpressionException(pattern, _entries);
	}

	std::vector<std::string> tags;
	re.split(_entries, tags, options);

	_certificate = new Certificate(tags[1]);
	_container = new Container(tags[2]);
}

