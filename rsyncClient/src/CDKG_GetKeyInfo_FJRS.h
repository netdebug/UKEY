// CDKG_GetKeyInfo_FJRS.h : �� Microsoft Visual C++ ������ ActiveX �ؼ���װ�������

#pragma once

/////////////////////////////////////////////////////////////////////////////
// CDKG_GetKeyInfo_FJRS
#include <Windows.h>
#include <afxwin.h>

class CDKG_GetKeyInfo_FJRS
{
public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= { 0xCE70417E, 0xB247, 0x43B3, { 0xA0, 0x89, 0x82, 0x73, 0xFA, 0xD9, 0x9F, 0x1B } };
		return clsid;
	}

// ����
public:

// ����
public:

	void AboutBox()
	{
		InvokeHelper(DISPID_ABOUTBOX, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	CString KGGetKeyInfo()
	{
		CString result;
		InvokeHelper(0x1, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}


};
