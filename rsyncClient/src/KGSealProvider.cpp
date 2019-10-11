#include <cassert>
#include <Windows.h>
#include <comdef.h>
#include "KG_GetKeyInfo_FJRS_i.c"
#include "KG_GetKeyInfo_FJRS.h"
#include "KGSealProvider.h"
#include "Poco/SharedLibrary.h"


using namespace Reach;

using Poco::SharedLibrary;

// MIDL Compiler
/// MIDL KG_GetKeyInfo_FJRS.IDL /tlb KG_GetKeyInfo_FJRS.tlb /h KG_GetKeyInfo_FJRS.h /iid KG_GetKeyInfo_FJRS_i.c /Oicf

KGSealProvider::KGSealProvider()
{
	/// Com interface
	HRESULT	hr;
	hr = CoInitialize(0);
	assert(SUCCEEDED(hr));

	hr = CoCreateInstance(CLSID_KG_GetKeyInfo_FJRS,
		NULL,
		CLSCTX_INPROC_SERVER,
		DIID__DKG_GetKeyInfo_FJRS,
		(void**)&_ext);

	assert(SUCCEEDED(hr));

}

KGSealProvider::~KGSealProvider()
{
	HRESULT	hr;
	hr = _ext->Release();
	assert(SUCCEEDED(hr));

	::CoUninitialize();
}

void KGSealProvider::AboutBox()
{
	HRESULT	hr;

	//hr = _ext->AboutBox();

	assert(SUCCEEDED(hr));
}

void KGSealProvider::KGGetKeyInfo()
{
	HRESULT	hr;
	_bstr_t keyinfo;

	//hr = _ext->KGGetKeyInfo(keyinfo.GetAddress());

	//_keyinfo.assign(keyinfo, keyinfo.length());

	assert(SUCCEEDED(hr));
}

void KGSealProvider::read(Object::Ptr JSONin, Object::Ptr JSONout)
{

}

void KGSealProvider::setProperty(const std::string& name, const std::string& value)
{
	if (name == "name")
	{
		_name = value;
	}
	else if (name == "code")
	{
		_code = value;
	}
	else if (name == "validStart")
	{
		_validStart = value;
	}
	else if (name == "validEnd")
	{
		_validEnd = value;
	}
	else
	{
		SealProvider::setProperty(name, value);
	}
}

std::string KGSealProvider::getProperty(const std::string& name) const
{
	if (name == "name")
	{
		return _name;
	}
	else if (name == "code")
	{
		return _code;
	}
	else if (name == "validStart")
	{
		return _validStart;
	}
	else if(name == "validEnd")
	{
		return _validEnd;
	}
	else
	{
	return SealProvider::getProperty(name);
	}
}