#pragma once
#include "Poco/TaskManager.h"
#include "MQTTNotification.h"
// RSyncControlCtrl.h : CRSyncControlCtrl ActiveX 控件类的声明。


// CRSyncControlCtrl : 请参阅 RSyncControlCtrl.cpp 了解实现。
#include <string>
class MQTTNotification;
class CRSyncControlCtrl : public COleControl
{
	DECLARE_DYNCREATE(CRSyncControlCtrl)

private:
	Poco::TaskManager tm;
	BOOL   m_bLoginState;
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
	BSTR ShowRSyncLoginView(BSTR containerId);
	BSTR onRsyncLogin(std::string nameStr, std::string passwordStr);
	BSTR IsLoginState(BSTR containerId);

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
	/// Cloud API
	BSTR RS_CloudLoginAuth(BSTR transid);
	BSTR RS_CloudSealAuth(BSTR transid);
	BSTR RS_CloudGetAuth(BSTR transid);
	BSTR RS_CloudGetSealList(BSTR token);
	BSTR RS_CloudSignByP7(BSTR msg, BSTR keySn, BSTR transid, BSTR token);
	BSTR RS_CloudGetSignResult(BSTR transid);
	BSTR RS_CloudLogoutAuth(BSTR token);
	BSTR RS_CloudEncryptAuth(BSTR transid);
	BSTR RS_CloudEncryptData(BSTR reachKey, BSTR transid, BSTR token);
	BSTR RS_CloudEncryptFile(BSTR souceFilePath, BSTR encFilePath, BSTR transid, BSTR token);
	BSTR RS_CloudDevryptAuth(BSTR transid);
	BSTR RS_CloudDevryptData(BSTR encReachKey, BSTR url, BSTR transid, BSTR token);
	BSTR RS_CloudDevryptFile(BSTR encFilePath, BSTR dncFilePath, BSTR url, BSTR transid, BSTR token);
	BSTR RS_CloudReceiveDevryptResult(BSTR token, BSTR resultData);
	BSTR RS_CloudGetCompanyCert(BSTR transid, BSTR token);
	BSTR RS_CloudGetCertAuth(BSTR transid);
	BSTR RS_CloudGetCertBase64(BSTR transid, BSTR token);
	BSTR RS_CloudLogout(BSTR userId);
	BSTR RS_KeyStatus(BSTR containerId);
	///签章授权事件
	inline void RS_CloudSealAuthEvent(const MQTTNotification& Nf)
	{
		//LPCTSTR authResult, LPCTSTR transid, LPCTSTR token, LPCTSTR msg
		FireEvent(eventid_1, EVENT_PARAM(VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR), _bstr_t(Nf.authResult.data()), _bstr_t(Nf.transid.data()), _bstr_t(Nf.token.data()), _bstr_t(Nf.message.data()));
	}

	///获取签名结果事件
	inline void RS_CloudGetSignResultEvent(const MQTTNotification& Nf)
	{
		//LPCTSTR signResult, LPCTSTR signdMsg, LPCTSTR transid, LPCTSTR signdCert, LPCTSTR msg
		std::string signdMsg, signdCert;
		FireEvent(eventid_2, EVENT_PARAM(VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR),
			_bstr_t(Nf.authResult.data()), _bstr_t(signdMsg.data()), _bstr_t(Nf.transid.data()), _bstr_t(signdCert.data()), _bstr_t(Nf.message.data()));
	}

	///登入授权事件
	inline void RS_CloudLoginAuthEvent(const MQTTNotification& Nf)
	{
		//LPCTSTR authResult, LPCTSTR transid, LPCTSTR token, LPCTSTR mobile, LPCTSTR userName, LPCTSTR userID, LPCTSTR msg
		std::string mobile, userName, userID;
		FireEvent(eventid_3, EVENT_PARAM(VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR),
			_bstr_t(Nf.authResult.data()), _bstr_t(Nf.transid.data()), _bstr_t(Nf.token.data())
			, _bstr_t(mobile.data()), _bstr_t(userName.data()), _bstr_t(userID.data()), _bstr_t(Nf.message.data()));
	}

	///加密授权事件
	inline void RS_CloudEncAuthEvent(const MQTTNotification& Nf)
	{
		//LPCTSTR authResult, LPCTSTR transid, LPCTSTR token, LPCTSTR msg
		FireEvent(eventid_4, EVENT_PARAM(VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR), _bstr_t(Nf.authResult.data()), _bstr_t(Nf.transid.data()), _bstr_t(Nf.token.data()), _bstr_t(Nf.message.data()));
	}

	///解密授权事件
	inline void RS_CloudDevAuthEvent(const MQTTNotification& Nf)
	{
		//LPCTSTR authResult, LPCTSTR transid, LPCTSTR token, LPCTSTR msg
		FireEvent(eventid_5, EVENT_PARAM(VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR), _bstr_t(Nf.authResult.data()), _bstr_t(Nf.transid.data()), _bstr_t(Nf.token.data()), _bstr_t(Nf.message.data()));
	}

	///获取证书授权事件
	inline void RS_CloudGetCertAuthEvent(const MQTTNotification& Nf)
	{
		//LPCTSTR authResult, LPCTSTR transid, LPCTSTR token, LPCTSTR msg
		FireEvent(eventid_6, EVENT_PARAM(VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR), _bstr_t(Nf.authResult.data()), _bstr_t(Nf.transid.data()), _bstr_t(Nf.token.data()), _bstr_t(Nf.message.data()));
	}

// 事件映射
	DECLARE_EVENT_MAP()
	protected:
		void handle1(MQTTNotification* pNf);
// 调度和事件 ID
private:
	enum {
		eventid_1 = 1,
		eventid_2,
		eventid_3,
		eventid_4,
		eventid_5,
		eventid_6,

		dispid_20 = 20,
		dispid_21,
		dispid_22,
		dispid_23,
		dispid_24,
		dispid_25,
		dispid_26,
		dispid_27,
		dispid_28,
		dispid_29,
		dispid_30,
		dispid_31,
		dispid_32,
		dispid_33,
		dispid_34,
		dispid_35,
		dispid_36,
		dispid_37,
		dispid_38,
		dispid_39,
		dispid_40,
		dispid_41,
		dispid_42,
		dispid_43,
		dispid_44,
		dispid_45,
		dispid_46,
		dispid_47,
		dispid_48,
		dispid_49,
		dispid_50,
		dispid_51,
		dispid_52
	};
};

