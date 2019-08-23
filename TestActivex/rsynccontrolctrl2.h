#pragma once

// 计算机生成了由 Microsoft Visual C++ 创建的 IDispatch 包装器类

// 注意:  不要修改此文件的内容。  如果此类由
//  Microsoft Visual C++ 重新生成，您的修改将被覆盖。

/////////////////////////////////////////////////////////////////////////////
// CRsynccontrolctrl2 包装器类

class CRsynccontrolctrl2 : public CWnd
{
protected:
	DECLARE_DYNCREATE(CRsynccontrolctrl2)
public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= { 0xA0B23721, 0x9350, 0x4B4D, { 0xB5, 0x81, 0x65, 0xAD, 0xD1, 0xA7, 0x7A, 0x5E } };
		return clsid;
	}
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle,
						const RECT& rect, CWnd* pParentWnd, UINT nID, 
						CCreateContext* pContext = NULL)
	{ 
		return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID); 
	}

    BOOL Create(LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, 
				UINT nID, CFile* pPersist = NULL, BOOL bStorage = FALSE,
				BSTR bstrLicKey = NULL)
	{ 
		return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID,
		pPersist, bStorage, bstrLicKey); 
	}

// 特性
public:


// 操作
public:

// _DRSyncControl

// Functions
//

	void AboutBox()
	{
		InvokeHelper(DISPID_ABOUTBOX, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	CString RS_GetUserList()
	{
		CString result;
		InvokeHelper(0x15, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	CString RS_GetCertBase64String(LPCTSTR containerId, short certType)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_I2 ;
		InvokeHelper(0x16, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, containerId, certType);
		return result;
	}
	CString RS_CertLogin(LPCTSTR containerId, LPCTSTR password)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x17, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, containerId, password);
		return result;
	}
	CString RS_GetPinRetryCount(LPCTSTR containerId)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x18, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, containerId);
		return result;
	}
	CString RS_ChangePassWd(LPCTSTR containerId, LPCTSTR oldCdoe, LPCTSTR newCode)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x19, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, containerId, oldCdoe, newCode);
		return result;
	}
	CString RS_KeyGetKeySn(LPCTSTR containerId)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x1a, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, containerId);
		return result;
	}
	CString RS_KeySignByP1(LPCTSTR msg, LPCTSTR containerId)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x1b, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, msg, containerId);
		return result;
	}
	CString RS_VerifySignByP1(LPCTSTR certBase64, LPCTSTR msg, LPCTSTR signdMsg)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x1c, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, certBase64, msg, signdMsg);
		return result;
	}
	CString RS_KeyEncryptData(LPCTSTR rsKey, LPCTSTR certBase64)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x1d, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, rsKey, certBase64);
		return result;
	}
	CString RS_KeyDecryptData(LPCTSTR encRsKey, LPCTSTR containerId)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x1e, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, encRsKey, containerId);
		return result;
	}
	CString RS_GetCertInfo(LPCTSTR certBase64, LPCTSTR type)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x1f, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, certBase64, type);
		return result;
	}

// Properties
//



};
