#pragma once
#include <string>
#include "SealProvider.h"
#include "Poco/JSON/Object.h"

struct _DKG_GetKeyInfo_FJRS;
namespace Reach {
	using Poco::JSON::Object;
	class KGSealProvider
		: public SealProvider
	{
	public:
		KGSealProvider();
		virtual ~KGSealProvider();
		virtual void read(Object::Ptr JSONin, Object::Ptr JSONout);
		virtual void setProperty(const std::string& name, const std::string& value);
		virtual std::string getProperty(const std::string& name) const;
		void AboutBox();
		void KGGetKeyInfo();
	private:

	/*	typedef int(*OES_ReadSealData)(
			const char*signCertB64Data,
			const long certDataLen,
			const char*sealID,
			unsigned char*puchSealJson,
			long * puchSealJsonLen);

		OES_ReadSealData fnPtr;*/
		static const int all_seal = -1;
		std::string _name;
		std::string _code;
		std::string _validStart;
		std::string _validEnd;
		std::string _keyinfo;
		_DKG_GetKeyInfo_FJRS* _ext;
	};
}