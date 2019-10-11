#include "SealProvider.h"
#include "Poco/Exception.h"

using namespace Reach;

SealProvider::SealProvider()
{

}


SealProvider::~SealProvider()
{

}

void SealProvider::setProperty(const std::string& name, const std::string& value)
{
	throw Poco::PropertyNotSupportedException(name);
}

std::string SealProvider::getProperty(const std::string& name) const
{
	throw Poco::PropertyNotSupportedException(name);
}