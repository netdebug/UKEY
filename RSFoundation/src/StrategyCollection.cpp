#include "StrategyCollection.h"
#include "GMCrypto.h"
#include "SoFProvider.h"
#include <list>
#include <map>
#include <utility>

using namespace Reach;

EncryptStrategy::EncryptStrategy(UDevice& ud)
{
	//class func
	//{
	//public:
	//	func() {};
	//	bool operator ()(const std::string i1, const std::string i2)
	//	{
	//		return true;
	//	}
	//};

	typedef std::map<std::string, int> encyptTable;
	typedef encyptTable::iterator iter;
	encyptTable algorithms;
	algorithms.insert(std::make_pair("SGD_SM1_ECB", SGD_SM1_ECB));
	algorithms.insert(std::make_pair("SGD_SM1_CBC", SGD_SM1_CBC));
	algorithms.insert(std::make_pair("SGD_SM4_ECB", SGD_SM4_ECB));
	algorithms.insert(std::make_pair("SGD_SM4_CBC", SGD_SM4_CBC));

	typedef std::list<std::string> encyptIndex;
	typedef encyptIndex::iterator eIter;
	encyptIndex n;
	n.push_back("SGD_SM1_ECB");
	n.push_back("SGD_SM1_CBC");
	n.push_back("SGD_SM4_ECB");
	n.push_back("SGD_SM4_CBC");

	for (eIter it = n.begin(); it != n.end(); it++)
	{
		std::string key = *it;
		if (ud.findEncryptMethod(key)) {
			ud.setEncryptMethod(algorithms[key]);
			return;
		}
	}
	throw Poco::LogicException("Encrypt Method is out of range !");
}

void EncryptStrategy::doUpdate()
{
	
}

SignedStrategy::SignedStrategy(UDevice& ud)
{
	std::map<std::string, int> table;
	table["RSA"] = SGD_SHA1_RSA;
	table["SM2"] = SGD_SM3_SM2;

	std::string cType = ud.getContainerType();
	ud.setSignMethod(table[cType]);
}

void SignedStrategy::doUpdate()
{

}