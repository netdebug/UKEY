#pragma once

// RSyncControlCtrl.h : CRSyncControlCtrl ActiveX 控件类的声明。


// CRSyncControlCtrl : 请参阅 RSyncControlCtrl.cpp 了解实现。
#include <string>

class CRSyncControlCtrl : public COleControl
{
	DECLARE_DYNCREATE(CRSyncControlCtrl)

// 构造函数
public:
	CRSyncControlCtrl();

// 重写
public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();

// 实现
protected:
	~CRSyncControlCtrl();

	DECLARE_OLECREATE_EX(CRSyncControlCtrl)    // 类工厂和 guid
	DECLARE_OLETYPELIB(CRSyncControlCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CRSyncControlCtrl)     // 属性页 ID
	DECLARE_OLECTLTYPE(CRSyncControlCtrl)		// 类型名称和杂项状态

// 消息映射
	DECLARE_MESSAGE_MAP()

// 调度映射
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

	BSTR RS_GetUserList();
	BSTR RS_GetCertBase64String(BSTR containerId, SHORT certType);
	BSTR RS_CertLogin(BSTR containerId, BSTR password);
	BSTR RS_GetPinRetryCount(BSTR containerId);
	BSTR RS_ChangePassWd(BSTR containerId, BSTR oldCode, BSTR newCode);
	BSTR RS_KeyGetKeySnExt(BSTR containerId);
	BSTR RS_KeyGetKeySn();
	BSTR RS_KeySignByP1(BSTR msg, BSTR containerId);
	BSTR RS_VerifySignByP1(BSTR certBase64, BSTR msg, BSTR signdMsg);
	BSTR RS_KeySignByP7(BSTR msg, BSTR flag, BSTR containerId);
	BSTR RS_VerifySignByP7(BSTR msg, BSTR signdMsg, BSTR flag);
	BSTR RS_KeyEncryptData(BSTR rsKey, BSTR certBase64);
	BSTR RS_KeyDecryptData(BSTR encRsKey, BSTR containerId);
	BSTR RS_GetCertInfo(BSTR certBase64, BSTR type);

	//签章授权事件
	void RS_CloudSealAuthEvent(LPCTSTR authResult, LPCTSTR transid, LPCTSTR token, LPCTSTR msg)
	{
		FireEvent(eventidRS_CloudSealAuthEvent, EVENT_PARAM(VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR), authResult, transid, token, msg);
	}

	//获取签名结果事件
	void RS_CloudGetSignResultEvent(LPCTSTR signResult, LPCTSTR signdMsg, LPCTSTR transid, LPCTSTR signdCert, LPCTSTR msg)
	{
		FireEvent(eventidRS_CloudGetSignResultEvent, EVENT_PARAM(VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR), signResult, signdMsg, transid, signdCert, msg);
	}

	//登入授权事件
	void RS_CloudLoginAuthEvent(LPCTSTR authResult, LPCTSTR transid, LPCTSTR token, LPCTSTR mobile, LPCTSTR userName, LPCTSTR userID, LPCTSTR msg)
	{
		FireEvent(eventidRS_CloudLoginAuthEvent, EVENT_PARAM(VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR), authResult, transid, token, mobile, userName, userID, msg);
	}

	//加密授权事件
	void RS_CloudEncAuthEvent(LPCTSTR authResult, LPCTSTR transid, LPCTSTR token, LPCTSTR msg)
	{
		FireEvent(eventidRS_CloudEncAuthEvent, EVENT_PARAM(VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR), authResult, transid, token, msg);
	}

	//解密授权事件
	void RS_CloudDevAuthEvent(LPCTSTR authResult, LPCTSTR transid, LPCTSTR token, LPCTSTR msg)
	{
		FireEvent(eventidRS_CloudDevAuthEvent, EVENT_PARAM(VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR), authResult, transid, token, msg);
	}
	//获取证书授权事件
	void RS_CloudGetCertAuthEvent(LPCTSTR authResult, LPCTSTR transid, LPCTSTR token, LPCTSTR msg)
	{
		FireEvent(eventidRS_CloudGetCertAuthEvent, EVENT_PARAM(VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR), authResult, transid, token, msg);
	}
// 事件映射
	DECLARE_EVENT_MAP()

// 调度和事件 ID
public:
	enum {
		dispid_GetUserList = 21,
		dispid_GetCertBase64String,
		dispid_CertLogin,
		dispid_GetPinRetryCount,
		dispid_ChangePassWd,
		dispid_KeyGetKeySn,
		dispid_KeyGetKeySnExt,
		dispid_KeySignByP1,
		dispid_VerifySignByP1,
		dispid_KeyEncryptData,
		dispid_KeyDecryptData,
		dispid_GetCertInfo,
		dispid_KeySignByP7,
		dispid_VerifySignByP7,

		eventidRS_CloudSealAuthEvent,
		eventidRS_CloudGetSignResultEvent,
		eventidRS_CloudLoginAuthEvent,
		eventidRS_CloudEncAuthEvent,
		eventidRS_CloudDevAuthEvent,
		eventidRS_CloudGetCertAuthEvent
	};
};

