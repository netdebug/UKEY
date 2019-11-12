#include "BridgePDFReader.h"
#include <Windows.h>
#include <comdef.h>
#include "iWebPDF.h"
#include <iostream>

using namespace Reach;

BridgePDFReader::BridgePDFReader()
	:_reader(NULL)
{
	HRESULT	hr;
	hr = CoInitialize(0);
	if (FAILED(hr))
		throw std::exception("CoInitialize Failed!", hr);

	int a = 1;
	hr = CoCreateInstance(CLSID_PDFReader,
		NULL,
		CLSCTX_ALL,
		IID_IPDFReader,
		(void**)&_reader);//这里的异常

	if (FAILED(hr))
		throw std::exception("CoCreateInstance PDFReader Failed!", hr);
}

/// set("VirtualKeyNumber","_serialNumber");
void BridgePDFReader::set(const std::string& name, const std::string& value)
{
	/// invoke KingGrid ActiveX(.ocx)
	/// call iWebPDF.COMAddins.Item("KingGrid.iWebPDF2015").Object;
	/// addin.SetPublicParam("VirtualKeyNumber", keysn, "");

	long	ReturnValue;
	_bstr_t Name(name.c_str());
	_bstr_t Value(value.c_str());
	_bstr_t HeaderValue;

	HRESULT hr = _reader->SetPublicParam(Name, Value, HeaderValue, &ReturnValue);

	if (FAILED(hr)) {
		release();
		throw std::exception("PDFReader SetPublicParam Failed!", hr);
	}
}

void BridgePDFReader::release()
{
	HRESULT	hr;
	hr = _reader->Release();

	if (FAILED(hr))
		throw std::exception("PDFReader Release Failed!", hr);

	::CoUninitialize();
}

BridgePDFReader::~BridgePDFReader()
{
	release();
}
