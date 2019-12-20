// CDiWebAssist.h : 由 Microsoft Visual C++ 创建的 ActiveX 控件包装器类的声明

#pragma once

/////////////////////////////////////////////////////////////////////////////
// CDiWebAssist

class CDiWebAssist : public CWnd
{
protected:
	DECLARE_DYNCREATE(CDiWebAssist)
public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= { 0xE99768C0, 0x3DE2, 0x4C53, { 0xAA, 0x41, 0x18, 0x85, 0x50, 0xCA, 0x66, 0xAC } };
		return clsid;
	}
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle,
						const RECT& rect, CWnd* pParentWnd, UINT nID,
						CCreateContext* pContext = nullptr)
	{
		return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID);
	}

	BOOL Create(LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd,
				UINT nID, CFile* pPersist = nullptr, BOOL bStorage = FALSE,
				BSTR bstrLicKey = nullptr)
	{
		return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID,
		pPersist, bStorage, bstrLicKey);
	}

// 特性
public:

// 操作
public:

	void AboutBox()
	{
		InvokeHelper(DISPID_ABOUTBOX, DISPATCH_METHOD, VT_EMPTY, nullptr, nullptr);
	}
	CString KGGetLocalIP()
	{
		CString result;
		InvokeHelper(0x1, DISPATCH_METHOD, VT_BSTR, (void*)&result, nullptr);
		return result;
	}
	CString KGGetPublicParm(LPCTSTR FatherNode, LPCTSTR SunNode, LPCTSTR GrandsonNode)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x2, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, FatherNode, SunNode, GrandsonNode);
		return result;
	}
	CString KGReadRegiste(LPCTSTR Root, LPCTSTR ThePath, LPCTSTR Key)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x3, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, Root, ThePath, Key);
		return result;
	}
	CString KGModifyRegiste(LPCTSTR Root, LPCTSTR ThePath, LPCTSTR Key, LPCTSTR Values)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x4, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, Root, ThePath, Key, Values);
		return result;
	}
	BOOL KGDeleteRegiste(LPCTSTR Root, LPCTSTR ThePath, LPCTSTR Key, LPCTSTR KVFlag)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x5, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, Root, ThePath, Key, KVFlag);
		return result;
	}
	CString KGGetFilesAtt(LPCTSTR KGFilesPath)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x6, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, KGFilesPath);
		return result;
	}
	BOOL KGCreateFiles(LPCTSTR KGFilesPath, LPCTSTR KGFlag)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x7, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, KGFilesPath, KGFlag);
		return result;
	}
	BOOL KGDeleteFiles(LPCTSTR KGFilesPath, LPCTSTR KGFlag)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x8, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, KGFilesPath, KGFlag);
		return result;
	}
	BOOL KGCopyFiles(LPCTSTR SoursFiles, LPCTSTR DestFiles)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x9, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, SoursFiles, DestFiles);
		return result;
	}
	BOOL KGModifyFiles(LPCTSTR NewName, LPCTSTR KGFilesPath)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR ;
		InvokeHelper(0xa, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, NewName, KGFilesPath);
		return result;
	}
	BOOL KGUploadFiles(LPCTSTR LocalFile, LPCTSTR RemoteFile, LPCTSTR ServerPath)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR ;
		InvokeHelper(0xb, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, LocalFile, RemoteFile, ServerPath);
		return result;
	}
	BOOL KGDownloadFiles(LPCTSTR RemoteFile, LPCTSTR LocalFile)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR ;
		InvokeHelper(0xc, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, RemoteFile, LocalFile);
		return result;
	}
	BOOL KGOpenFiles()
	{
		BOOL result;
		InvokeHelper(0xd, DISPATCH_METHOD, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	CString KGGetComputerMsg()
	{
		CString result;
		InvokeHelper(0xe, DISPATCH_METHOD, VT_BSTR, (void*)&result, nullptr);
		return result;
	}
	CString KGGetSystmMsg()
	{
		CString result;
		InvokeHelper(0xf, DISPATCH_METHOD, VT_BSTR, (void*)&result, nullptr);
		return result;
	}
	CString KGInstallOfClient()
	{
		CString result;
		InvokeHelper(0x10, DISPATCH_METHOD, VT_BSTR, (void*)&result, nullptr);
		return result;
	}
	short KGGetError()
	{
		short result;
		InvokeHelper(0x11, DISPATCH_METHOD, VT_I2, (void*)&result, nullptr);
		return result;
	}
	CString KGFindFile(LPCTSTR KGDirPath, LPCTSTR KGFileExtName, LPCTSTR KGLikeName, LPCTSTR KGFlag)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x12, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, KGDirPath, KGFileExtName, KGLikeName, KGFlag);
		return result;
	}
	CString KGGetCertificate(LPCTSTR CardPin, LPCTSTR CSPName)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x13, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, CardPin, CSPName);
		return result;
	}
	CString KGGetKeyInfo()
	{
		CString result;
		InvokeHelper(0x14, DISPATCH_METHOD, VT_BSTR, (void*)&result, nullptr);
		return result;
	}
	CString KGCrySignMessage(LPCTSTR UserPin, LPCTSTR SignMessage, LPCTSTR SignLength)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x15, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, UserPin, SignMessage, SignLength);
		return result;
	}
	CString KGVerifySignMessage(LPCTSTR UserPin, LPCTSTR OriginalData, LPCTSTR VerifyMessage)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x16, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, UserPin, OriginalData, VerifyMessage);
		return result;
	}
	CString KGVerifyPin(LPCTSTR UserPin, LPCTSTR KeySN)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x17, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, UserPin, KeySN);
		return result;
	}
	CString KGGetCerInfo(LPCTSTR UserPin)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x18, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, UserPin);
		return result;
	}
	CString KGWriteLicensed(LPCTSTR LicInfo, LPCTSTR LicFormate, LPCTSTR LicFlag, LPCTSTR LicOther)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x19, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, LicInfo, LicFormate, LicFlag, LicOther);
		return result;
	}
	CString KGGetLicensed(LPCTSTR strDate)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x1a, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, strDate);
		return result;
	}
	CString KGDelSeal(LPWSTR KeySN, LPCTSTR SignSN, LPCTSTR UserPin, LPCTSTR OtherFlag)
	{
		CString result;
		static BYTE parms[] = VTS_UNKNOWN VTS_BSTR VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x1b, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, KeySN, SignSN, UserPin, OtherFlag);
		return result;
	}
	CString KGControlPin(LPCTSTR KeySN, LPCTSTR FirstPin, LPCTSTR SecondPin, LPCTSTR ControlType, LPCTSTR OtherFlag)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x1c, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, KeySN, FirstPin, SecondPin, ControlType, OtherFlag);
		return result;
	}
	CString KGGetKeyOtherInfo(LPCTSTR InfoType)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x1d, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, InfoType);
		return result;
	}
	CString KGAddSeal(LPCTSTR ImgStr, LPCTSTR ImgWidth, LPCTSTR ImgHeight, LPCTSTR ImgSource, LPCTSTR ImgOtherInfo)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x1e, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, ImgStr, ImgWidth, ImgHeight, ImgSource, ImgOtherInfo);
		return result;
	}
	CString KGGetCerInfo2(LPCTSTR strCes)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x1f, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, strCes);
		return result;
	}
	CString KGCrySignMessageEX(LPCTSTR UserPin, LPCTSTR SignMessage, LPCTSTR SignLength, LPCTSTR OriginalType)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x20, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, UserPin, SignMessage, SignLength, OriginalType);
		return result;
	}
	CString SetParamByName(LPCTSTR ParamName, LPCTSTR ParamValue)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x21, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, ParamName, ParamValue);
		return result;
	}
	CString KGWriterLicensed2Dog(LPCTSTR LicInfo)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x22, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, LicInfo);
		return result;
	}
	CString KGGetDogRegCount()
	{
		CString result;
		InvokeHelper(0x23, DISPATCH_METHOD, VT_BSTR, (void*)&result, nullptr);
		return result;
	}
	CString KGResetPin(LPCTSTR szOPin, LPCTSTR szUserPin)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x24, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, szOPin, szUserPin);
		return result;
	}
	CString KGAddSealEX(LPCTSTR UserPin, LPCTSTR SealInfo)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x25, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, UserPin, SealInfo);
		return result;
	}
	CString KGRunHandWritten(LPCTSTR DeviceType, LPCTSTR CopyRight, LPCTSTR Reserve1, LPCTSTR Reserve2, LPCTSTR Reserve3)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x26, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, DeviceType, CopyRight, Reserve1, Reserve2, Reserve3);
		return result;
	}
	CString KGRunFingerPrints(LPCTSTR DeviceType, LPCTSTR ImageType, LPCTSTR Reserve1, LPCTSTR Reserve2, LPCTSTR Reserve3)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x27, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, DeviceType, ImageType, Reserve1, Reserve2, Reserve3);
		return result;
	}
	CString KGValidateCertificate(LPCTSTR SignaCert, LPCTSTR Reserve1)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x28, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, SignaCert, Reserve1);
		return result;
	}
	CString KGValidate_GM(LPCTSTR SignaCert, LPCTSTR SealCert, LPCTSTR ValidStart, LPCTSTR ValidEnd, LPCTSTR CertList, LPCTSTR Reserve1)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x29, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, SignaCert, SealCert, ValidStart, ValidEnd, CertList, Reserve1);
		return result;
	}
	CString KGGetSignType(LPCTSTR Reserve1)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x2a, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, Reserve1);
		return result;
	}
	CString KGGetTSURLInfo()
	{
		CString result;
		InvokeHelper(0x2b, DISPATCH_METHOD, VT_BSTR, (void*)&result, nullptr);
		return result;
	}
	CString KGGetTSWithDigest(LPCTSTR HostUrl, LPCTSTR UserName, LPCTSTR UserPwd, LPCTSTR HashData, LPCTSTR Reserve1)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x2c, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, HostUrl, UserName, UserPwd, HashData, Reserve1);
		return result;
	}
	CString KGVerifyTSWithReq(LPCTSTR TimeStampResponse, LPCTSTR TimeStampResult, LPCTSTR CertData, LPCTSTR HashData, LPCTSTR TimeStr, LPCTSTR Reserve1)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x2d, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, TimeStampResponse, TimeStampResult, CertData, HashData, TimeStr, Reserve1);
		return result;
	}
	CString KGVerifyGBSealAction(LPCTSTR SESealInfo, LPCTSTR SignSN)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x2e, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, SESealInfo, SignSN);
		return result;
	}
	CString KGVerifyGBStampAction(LPCTSTR StampData)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x2f, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, StampData);
		return result;
	}
	CString KGPhoneShieldLic()
	{
		CString result;
		InvokeHelper(0x30, DISPATCH_METHOD, VT_BSTR, (void*)&result, nullptr);
		return result;
	}


};
