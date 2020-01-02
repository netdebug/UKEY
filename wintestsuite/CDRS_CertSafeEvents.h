// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装器类

#import "F:\\Work\\UKEY\\bin\\RS_CertSafe.ocx" no_namespace
// CDRS_CertSafeEvents 包装器类

class CDRS_CertSafeEvents : public COleDispatchDriver
{
public:
	CDRS_CertSafeEvents() {} // 调用 COleDispatchDriver 默认构造函数
	CDRS_CertSafeEvents(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CDRS_CertSafeEvents(const CDRS_CertSafeEvents& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// 特性
public:

	// 操作
public:


	// _DRS_CertSafeEvents 方法
public:
	void RS_CloudSealAuthEvent(LPCTSTR authResult, LPCTSTR transid, LPCTSTR token, LPCTSTR msg)
	{
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR;
		InvokeHelper(0x1, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, authResult, transid, token, msg);
	}
	void RS_CloudGetSignResultEvent(LPCTSTR signResult, LPCTSTR signdMsg, LPCTSTR transid, LPCTSTR signdCert, LPCTSTR msg)
	{
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR;
		InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, signResult, signdMsg, transid, signdCert, msg);
	}
	void RS_CloudLoginAuthEvent(LPCTSTR authResult, LPCTSTR transid, LPCTSTR token, LPCTSTR mobile, LPCTSTR userName, LPCTSTR userId, LPCTSTR msg)
	{
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR;
		InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, authResult, transid, token, mobile, userName, userId, msg);
	}
	void RS_CloudEncAuthEvent(LPCTSTR authResult, LPCTSTR transid, LPCTSTR token, LPCTSTR msg)
	{
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR;
		InvokeHelper(0x4, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, authResult, transid, token, msg);
	}
	void RS_CloudDevAuthEvent(LPCTSTR authResult, LPCTSTR transid, LPCTSTR token, LPCTSTR msg)
	{
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR;
		InvokeHelper(0x5, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, authResult, transid, token, msg);
	}
	void RS_CloudGetCertAuthEvent(LPCTSTR authResult, LPCTSTR transid, LPCTSTR token, LPCTSTR msg)
	{
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR;
		InvokeHelper(0x6, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, authResult, transid, token, msg);
	}

	// _DRS_CertSafeEvents 属性
public:

};
