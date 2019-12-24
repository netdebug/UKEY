// RSyncControlCtrl.cpp : CRSyncControlCtrl ActiveX 控件类的实现。

#include "stdafx.h"
#include "RSyncControl.h"
#include "RSyncControlCtrl.h"
#include "RSyncControlPropPage.h"
#include "afxdialogex.h"
#include <comutil.h>
#include "Utility.h"
#include "Poco/String.h"
#include "Poco/Net/HTMLForm.h"
#include "Poco/Dynamic/Var.h"
#include "Poco/JSON/Parser.h"
#include "Poco/JSON/Object.h"
#include "Poco/DynamicStruct.h"
#include "CloudEventRecevier.h"
#include "Poco/Debugger.h"
#include <cassert>
#include <sstream>
#include "EncodingTransfer.h"
#include "RSyncLoginView.h"
#include "RSyncMsgTip.h"
#include <atlconv.h>
#include "RSyncChangPassWd.h"

using Poco::Dynamic::Var;
using Poco::Net::HTMLForm;
using Poco::Net::HTTPRequest;
using Poco::Net::HTTPResponse;
using Poco::Net::HTTPClientSession;
using Poco::JSON::Parser;
using Poco::JSON::Object;
using Poco::DynamicStruct;
using Poco::Debugger;
using Poco::JSONOptions;

using Reach::ActiveX::Utility;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#define UM_EVENT (WM_USER + 666)

IMPLEMENT_DYNCREATE(CRSyncControlCtrl, COleControl)

// 消息映射

BEGIN_MESSAGE_MAP(CRSyncControlCtrl, COleControl)
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()

// 调度映射

BEGIN_DISPATCH_MAP(CRSyncControlCtrl, COleControl)
	DISP_FUNCTION_ID(CRSyncControlCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION_ID(CRSyncControlCtrl, "RS_KeyGetKeySn",						dispid_20,			RS_KeyGetKeySn,				VT_BSTR, VTS_NONE)
	DISP_FUNCTION_ID(CRSyncControlCtrl, "RS_KeyGetKeySnExt",					dispid_21,			RS_KeyGetKeySnExt,			VT_BSTR, VTS_BSTR)
	DISP_FUNCTION_ID(CRSyncControlCtrl, "RS_GetUserList",						dispid_22,			RS_GetUserList,				VT_BSTR, VTS_NONE)
	DISP_FUNCTION_ID(CRSyncControlCtrl, "RS_GetCertBase64String",				dispid_23,			RS_GetCertBase64String,		VT_BSTR, VTS_BSTR VTS_I2)
	DISP_FUNCTION_ID(CRSyncControlCtrl, "RS_CertLogin",							dispid_24,			RS_CertLogin,				VT_BSTR, VTS_BSTR VTS_BSTR)
	DISP_FUNCTION_ID(CRSyncControlCtrl, "RS_GetPinRetryCount",					dispid_25,			RS_GetPinRetryCount,		VT_BSTR, VTS_BSTR)
	DISP_FUNCTION_ID(CRSyncControlCtrl, "RS_ChangePassWd",						dispid_26,			RS_ChangePassWd,			VT_BSTR, VTS_BSTR VTS_BSTR VTS_BSTR)
	DISP_FUNCTION_ID(CRSyncControlCtrl, "RS_KeySignByP1",						dispid_27,			RS_KeySignByP1,				VT_BSTR, VTS_BSTR VTS_BSTR)
	DISP_FUNCTION_ID(CRSyncControlCtrl, "RS_VerifySignByP1",					dispid_28,			RS_VerifySignByP1,			VT_BSTR, VTS_BSTR VTS_BSTR VTS_BSTR)
	DISP_FUNCTION_ID(CRSyncControlCtrl, "RS_KeyEncryptData",					dispid_29,			RS_KeyEncryptData,			VT_BSTR, VTS_BSTR VTS_BSTR)
	DISP_FUNCTION_ID(CRSyncControlCtrl, "RS_KeyDecryptData",					dispid_30,			RS_KeyDecryptData,			VT_BSTR, VTS_BSTR VTS_BSTR)
	DISP_FUNCTION_ID(CRSyncControlCtrl, "RS_GetCertInfo",						dispid_31,			RS_GetCertInfo,				VT_BSTR, VTS_BSTR VTS_BSTR)
	DISP_FUNCTION_ID(CRSyncControlCtrl, "RS_KeySignByP7",						dispid_32,			RS_KeySignByP7,				VT_BSTR, VTS_BSTR VTS_BSTR VTS_BSTR)
	DISP_FUNCTION_ID(CRSyncControlCtrl, "RS_VerifySignByP7",					dispid_33,			RS_VerifySignByP7,			VT_BSTR, VTS_BSTR VTS_BSTR VTS_BSTR)
	DISP_FUNCTION_ID(CRSyncControlCtrl, "RS_CloudLoginAuth",					dispid_34,			RS_CloudLoginAuth,			VT_BSTR, VTS_BSTR)
	DISP_FUNCTION_ID(CRSyncControlCtrl, "RS_CloudSealAuth",						dispid_35,			RS_CloudSealAuth,					VT_BSTR,VTS_BSTR)
	DISP_FUNCTION_ID(CRSyncControlCtrl, "RS_CloudGetAuth",						dispid_36,			RS_CloudGetAuth,					VT_BSTR,VTS_BSTR)
	DISP_FUNCTION_ID(CRSyncControlCtrl, "RS_CloudGetSealList",					dispid_37,			RS_CloudGetSealList,				VT_BSTR,VTS_BSTR)
	DISP_FUNCTION_ID(CRSyncControlCtrl, "RS_CloudSignByP7",						dispid_38,			RS_CloudSignByP7,					VT_BSTR,VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR)
	DISP_FUNCTION_ID(CRSyncControlCtrl, "RS_CloudGetSignResult",				dispid_39,			RS_CloudGetSignResult,				VT_BSTR,VTS_BSTR)
	DISP_FUNCTION_ID(CRSyncControlCtrl, "RS_CloudLogoutAuth",					dispid_40,			RS_CloudLogoutAuth,					VT_BSTR,VTS_BSTR)
	DISP_FUNCTION_ID(CRSyncControlCtrl, "RS_CloudEncryptAuth",					dispid_41,			RS_CloudEncryptAuth,				VT_BSTR,VTS_BSTR)
	DISP_FUNCTION_ID(CRSyncControlCtrl, "RS_CloudEncryptData",					dispid_42,			RS_CloudEncryptData,				VT_BSTR,VTS_BSTR VTS_BSTR VTS_BSTR)
	DISP_FUNCTION_ID(CRSyncControlCtrl, "RS_CloudEncryptFile",					dispid_43,			RS_CloudEncryptFile,				VT_BSTR,VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR)
	DISP_FUNCTION_ID(CRSyncControlCtrl, "RS_CloudDevryptAuth",					dispid_44,			RS_CloudDevryptAuth,				VT_BSTR,VTS_BSTR)
	DISP_FUNCTION_ID(CRSyncControlCtrl, "RS_CloudDevryptData",					dispid_45,			RS_CloudDevryptData,				VT_BSTR,VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR)
	DISP_FUNCTION_ID(CRSyncControlCtrl, "RS_CloudDevryptFile",					dispid_46,			RS_CloudDevryptFile,				VT_BSTR,VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR)
	DISP_FUNCTION_ID(CRSyncControlCtrl, "RS_CloudReceiveDevryptResult",			dispid_47,			RS_CloudReceiveDevryptResult,		VT_BSTR, VTS_BSTR VTS_BSTR)
	DISP_FUNCTION_ID(CRSyncControlCtrl, "RS_CloudGetCompanyCert",				dispid_48,			RS_CloudGetCompanyCert,				VT_BSTR,VTS_BSTR VTS_BSTR)
	DISP_FUNCTION_ID(CRSyncControlCtrl, "RS_CloudGetCertAuth",					dispid_49,			RS_CloudGetCertAuth,				VT_BSTR,VTS_BSTR)
	DISP_FUNCTION_ID(CRSyncControlCtrl, "RS_CloudGetCertBase64",				dispid_50,			RS_CloudGetCertBase64,				VT_BSTR,VTS_BSTR VTS_BSTR)
	DISP_FUNCTION_ID(CRSyncControlCtrl, "RS_CloudLogout",						dispid_51,			RS_CloudLogout,						VT_BSTR,VTS_BSTR)
	DISP_FUNCTION_ID(CRSyncControlCtrl, "RS_KeyStatus",							dispid_52,			RS_KeyStatus,						VT_BSTR, VTS_BSTR)
	DISP_FUNCTION_ID(CRSyncControlCtrl, "RS_ConfigParameters",					dispid_53,			RS_ConfigParameters,				VTS_NONE, VTS_BSTR VTS_BSTR)
	DISP_FUNCTION_ID(CRSyncControlCtrl, "RS_GetParameters",						dispid_54,			RS_GetParameters,					VT_BSTR, VTS_BSTR)
	DISP_FUNCTION_ID(CRSyncControlCtrl, "RS_GreateQRCode",						dispid_55,			RS_CreateQRCode,					VT_BSTR, VTS_BSTR VTS_BSTR)
	DISP_FUNCTION_ID(CRSyncControlCtrl, "RS_GetTransid",						dispid_56,			RS_GetTransid,						VT_BSTR, VTS_BSTR)
	DISP_FUNCTION_ID(CRSyncControlCtrl, "RS_EncryptFile",						dispid_57,			RS_EncryptFile,						VT_BSTR, VTS_BSTR VTS_BSTR)
	DISP_FUNCTION_ID(CRSyncControlCtrl, "RS_DevryptFile",						dispid_58,			RS_DevryptFile,						VT_BSTR, VTS_BSTR VTS_BSTR VTS_BSTR)
	DISP_FUNCTION_ID(CRSyncControlCtrl, "RS_VerifyIdentity",					dispid_59,			RS_VerifyIdentity,					VT_BSTR, VTS_BSTR VTS_BSTR)
	DISP_FUNCTION_ID(CRSyncControlCtrl, "RS_KeyEncryptFile",					dispid_60,			RS_KeyEncryptFile,					VT_BSTR, VTS_BSTR VTS_BSTR VTS_BSTR)
	DISP_FUNCTION_ID(CRSyncControlCtrl, "RS_KeyDecryptFile",					dispid_61,			RS_KeyDecryptFile,					VT_BSTR, VTS_BSTR VTS_BSTR VTS_BSTR)
END_DISPATCH_MAP()

// 事件映射

BEGIN_EVENT_MAP(CRSyncControlCtrl, COleControl)
	EVENT_CUSTOM_ID("RS_CloudSealAuthEvent",			eventid_1, RS_CloudSealAuthEvent, VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR)
	EVENT_CUSTOM_ID("RS_CloudGetSignResultEvent",		eventid_2, RS_CloudGetSignResultEvent, VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR)
	EVENT_CUSTOM_ID("RS_CloudLoginAuthEvent",			eventid_3, RS_CloudLoginAuthEvent, VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR)
	EVENT_CUSTOM_ID("RS_CloudEncAuthEvent",				eventid_4, RS_CloudEncAuthEvent, VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR)
	EVENT_CUSTOM_ID("RS_CloudDevAuthEvent",				eventid_5, RS_CloudDevAuthEvent, VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR)
	EVENT_CUSTOM_ID("RS_CloudGetCertAuthEvent",			eventid_6, RS_CloudGetCertAuthEvent, VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR)
END_EVENT_MAP()

// 属性页

// TODO: 根据需要添加更多属性页。请记住增加计数!
BEGIN_PROPPAGEIDS(CRSyncControlCtrl, 1)
	PROPPAGEID(CRSyncControlPropPage::guid)
END_PROPPAGEIDS(CRSyncControlCtrl)

// 初始化类工厂和 guid

//IMPLEMENT_OLECREATE_EX(CRSyncControlCtrl, "RSyncControl.RSyncControlCtrl.1",
//	0xa0b23721,0x9350,0x4b4d,0xb5,0x81,0x65,0xad,0xd1,0xa7,0x7a,0x5e)
IMPLEMENT_OLECREATE_EX(CRSyncControlCtrl, "RS_CERTSAFE.RS_CertSafeCtrl.1",
	0xF84C8F57,0x5A05,0x4D8C,0x82,0x6D,0x29,0x58,0x9C,0x7A,0x12,0x1C)

// 键入库 ID 和版本

IMPLEMENT_OLETYPELIB(CRSyncControlCtrl, _tlid, _wVerMajor, _wVerMinor)

// 接口 ID

//onst IID IID_DRSyncControl = { 0xdb403885,0xf81d,0x41d2,{0x80,0xd7,0x40,0x36,0x50,0x97,0xd6,0x0c} };
const IID IID_DRSyncControl = { 0x7A58AA86,0xD40D,0x4611,{0x9D,0xA1,0xDF,0xCE,0xAE,0x95,0x31,0x5A} };
//const IID IID_DRSyncControlEvents = { 0xb1c93fb3,0x0485,0x4837,{0x9a,0xaf,0xaf,0x8f,0x96,0xa2,0xc0,0xd2} };
const IID IID_DRSyncControlEvents = { 0xEECD3FF1,0xDED8,0x44B3,{0x87,0x7C,0x99,0xD0,0x56,0xD5,0x44,0x9D} };

// 控件类型信息

static const DWORD _dwRSyncControlOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CRSyncControlCtrl, IDS_RSYNCCONTROL, _dwRSyncControlOleMisc)

// CRSyncControlCtrl::CRSyncControlCtrlFactory::UpdateRegistry -
// 添加或移除 CRSyncControlCtrl 的系统注册表项

BOOL CRSyncControlCtrl::CRSyncControlCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO:  验证您的控件是否符合单元模型线程处理规则。
	// 有关更多信息，请参考 MFC 技术说明 64。
	// 如果您的控件不符合单元模型规则，则
	// 必须修改如下代码，将第六个参数从
	// afxRegApartmentThreading 改为 0。

	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_RSYNCCONTROL,
			IDB_RSYNCCONTROL,
			afxRegApartmentThreading,
			_dwRSyncControlOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


// CRSyncControlCtrl::CRSyncControlCtrl - 构造函数
#include "Poco/Observer.h"
#include "MQTTNotification.h"
#include "Poco/String.h"
using namespace Poco;

CRSyncControlCtrl::CRSyncControlCtrl()
:tm(ThreadPool::defaultPool())
{
	InitializeIIDs(&IID_DRSyncControl, &IID_DRSyncControlEvents);
	// TODO:  在此初始化控件的实例数据。
	NotificationCenter& nc = NotificationCenter::defaultCenter();
	Observer<CRSyncControlCtrl, MQTTNotification> o1(*this, &CRSyncControlCtrl::handle1);
	nc.addObserver(o1);
	tm.start(new Reach::CloudEventRecevier);
	m_bLoginState = FALSE;
}

// CRSyncControlCtrl::~CRSyncControlCtrl - 析构函数

CRSyncControlCtrl::~CRSyncControlCtrl()
{
	NotificationCenter& nc = NotificationCenter::defaultCenter();
	nc.removeObserver(Observer<CRSyncControlCtrl, MQTTNotification>(*this, &CRSyncControlCtrl::handle1));
	// TODO:  在此清理控件的实例数据。
	OutputDebugStringA(Poco::format("threadPool count : %d", tm.count()).c_str());
	tm.cancelAll();
	tm.joinAll();
}

bool IsLogined(const std::string& id)
{
	HTMLForm params;
	params.set("containerId", id);
	std::ostringstream body;
	params.write(body);
	std::string result = Utility::SuperRequest("/RS_KeyStatus", body.str());

	Parser ps;
	Var res = ps.parse(result);
	Object::Ptr object = res.extract<Object::Ptr>();
	assert(object);
	DynamicStruct ds = *object;

	return ds["code"] == "0000";
}

void CRSyncControlCtrl::handle1(MQTTNotification* pNf)
{
	Debugger::message(format("MQTTNotification action = %s", pNf->context()));
	HWND hwnd = GetSafeHwnd();
	if (NULL == hwnd)
	{
		hwnd = AfxGetMainWnd() == NULL ? NULL : AfxGetMainWnd()->m_hWnd;
		::PostMessage(HWND_BROADCAST, UM_EVENT, (WPARAM)pNf, NULL);

	}
	else {
		::PostMessage(hwnd, UM_EVENT, (WPARAM)pNf, NULL);
	}

}

enum action
{
	LoginAuth = 1,
	EncryptAuth,
	DecryptAuth,
	SignedSealAuth,
	UnSignedSealAuth,
	GetCertAuth,
	GetSignResult = 44
};

void CRSyncControlCtrl::process_event(MQTTNotification * pNf)
{
	if (pNf) {
		std::string act = pNf->getdata("action");
		switch (atoi(act.data()))
		{
		case LoginAuth:
			RS_CloudLoginAuthEvent(*pNf);
			break;
		case EncryptAuth:
			RS_CloudEncAuthEvent(*pNf);
			break;
		case DecryptAuth:
			RS_CloudDevAuthEvent(*pNf);
			break;
		case SignedSealAuth:
		case UnSignedSealAuth:
			RS_CloudSealAuthEvent(*pNf);
			break;
		case GetCertAuth:
			RS_CloudGetCertAuthEvent(*pNf);
			break;
		case GetSignResult:
			RS_CloudGetSignResultEvent(*pNf);
			break;
		default:
			break;
		}
	}
}

void CRSyncControlCtrl::OnSetClientSite()
{
	HWND hwnd = GetSafeHwnd();
	if (NULL == hwnd)
	{
		VERIFY(CreateControlWindow(::GetDesktopWindow(), CRect(0, 0, 0, 0), CRect(0, 0, 0, 0)));
	}

	COleControl::OnSetClientSite();
}

LRESULT CRSyncControlCtrl::WindowProc(UINT message, WPARAM wParam, LPARAM Lparam)
{
	if (message == UM_EVENT)
	{
		MQTTNotification *pNf = (MQTTNotification*)wParam;
		process_event(pNf);
	}
	return COleControl::WindowProc(message, wParam, Lparam);
}

// CRSyncControlCtrl::OnDraw - 绘图函数

void CRSyncControlCtrl::OnDraw(
	CDC* pdc, const CRect& rcBounds, const CRect& /* rcInvalid */)
{
	if (!pdc)
		return;

	// TODO:  用您自己的绘图代码替换下面的代码。
	pdc->FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(WHITE_BRUSH)));
	pdc->Ellipse(rcBounds);
}

// CRSyncControlCtrl::DoPropExchange - 持久性支持

void CRSyncControlCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: 为每个持久的自定义属性调用 PX_ 函数。
}


// CRSyncControlCtrl::OnResetState - 将控件重置为默认状态

void CRSyncControlCtrl::OnResetState()
{
	COleControl::OnResetState();  // 重置 DoPropExchange 中找到的默认值

	// TODO:  在此重置任意其他控件状态。
}


// CRSyncControlCtrl::AboutBox - 向用户显示“关于”框

void CRSyncControlCtrl::AboutBox()
{
	CDialogEx dlgAbout(IDD_ABOUTBOX_RSYNCCONTROL);
	dlgAbout.DoModal();
}

void CRSyncControlCtrl::RS_ConfigParameters(BSTR cmd, BSTR val)
{
	std::string cmdid = _com_util::ConvertBSTRToString(cmd);
	std::string valadress = _com_util::ConvertBSTRToString(val);

	HTMLForm params;
	params.set("cmd", cmdid);
	params.set("val", valadress);

	std::ostringstream body;
	params.write(body);
	std::string result = Utility::SuperRequest("/RS_ConfigParameters", body.str());
	return;
}

BSTR CRSyncControlCtrl::RS_GetParameters(BSTR cmd)
{
	std::string cmdid = _com_util::ConvertBSTRToString(cmd);

	HTMLForm params;
	params.set("cmd", cmdid);
	std::ostringstream body;
	params.write(body);
	std::string result = Utility::SuperRequest("/RS_GetParameters", body.str());

	//std::string encoding = Utility::UTF8EncodingGBK(result);
	return _bstr_t(result.data());
}

BSTR CRSyncControlCtrl::RS_CreateQRCode(BSTR qrcode, BSTR path)
{
	std::string qrcodestr = _com_util::ConvertBSTRToString(qrcode);
	std::string pathstr = _com_util::ConvertBSTRToString(path);

	HTMLForm params;
	params.set("qrcode", qrcodestr);
	params.set("path", Utility::GBKEncodingUTF8(pathstr));

	std::ostringstream body;
	params.write(body);
	std::string result = Utility::SuperRequest("/RS_GreateQRCode", body.str());

	//std::string encoding = Utility::UTF8EncodingGBK(result);
	return _bstr_t(result.data());
}

BSTR CRSyncControlCtrl::RS_GetTransid(BSTR joinCode)
{
	std::string joinCodestr = _com_util::ConvertBSTRToString(joinCode);

	HTMLForm params;
	params.set("joinCode", joinCodestr);

	std::ostringstream body;
	params.write(body);
	std::string result = Utility::SuperRequest("/RS_GetTransid", body.str());

	//std::string encoding = Utility::UTF8EncodingGBK(result);
	return _bstr_t(result.data());
}

BSTR CRSyncControlCtrl::RS_EncryptFile(BSTR souceFilePath, BSTR encFilePath)
{
	std::string soucestr = _com_util::ConvertBSTRToString(souceFilePath);
	std::string encstr = _com_util::ConvertBSTRToString(encFilePath);

	HTMLForm params;
	params.set("souceFilePath", Utility::GBKEncodingUTF8(soucestr));
	params.set("encFilePath", Utility::GBKEncodingUTF8(encstr));

	std::ostringstream body;
	params.write(body);
	std::string result = Utility::SuperRequest("/RS_EncryptFile", body.str());

	//std::string encoding = Utility::UTF8EncodingGBK(result);
	return _bstr_t(result.data());
}

BSTR CRSyncControlCtrl::RS_DevryptFile(BSTR symKey, BSTR encFilePath, BSTR dncDirectoryPath)
{
	std::string symkeyid = _com_util::ConvertBSTRToString(symKey);
	std::string encstr = _com_util::ConvertBSTRToString(encFilePath);
	std::string dncpathstr = _com_util::ConvertBSTRToString(dncDirectoryPath);

	HTMLForm params;
	params.set("symKey", symkeyid);
	params.set("encFilePath", Utility::GBKEncodingUTF8(encstr));
	params.set("dncDirectoryPath", Utility::GBKEncodingUTF8(dncpathstr));

	std::ostringstream body;
	params.write(body);
	std::string result = Utility::SuperRequest("/RS_DecryptFile", body.str());

	//std::string encoding = Utility::UTF8EncodingGBK(result);
	return _bstr_t(result.data());
}

BSTR CRSyncControlCtrl::RS_VerifyIdentity(BSTR certBase64, BSTR authNo)
{
	std::string CERTBASE64 = _com_util::ConvertBSTRToString(certBase64);
	std::string AUTHNO = _com_util::ConvertBSTRToString(authNo);

	HTMLForm params;
	params.set("certBase64", CERTBASE64);
	params.set("authNo", AUTHNO);

	std::ostringstream body;
	params.write(body);
	std::string result = Utility::SuperRequest("/RS_VerifyIdentity", body.str());

	//std::string encoding = Utility::UTF8EncodingGBK(result);
	return _bstr_t(result.data());
}

BSTR CRSyncControlCtrl::RS_KeyEncryptFile(BSTR souceFilePath, BSTR encFilePath, BSTR certBase64)
{
	std::string souceFile = _com_util::ConvertBSTRToString(souceFilePath);
	std::string encFile = _com_util::ConvertBSTRToString(encFilePath);
	std::string cert = _com_util::ConvertBSTRToString(certBase64);

	HTMLForm params;
	params.set("souceFilePath", Utility::GBKEncodingUTF8(souceFile));
	params.set("encFilePath", Utility::GBKEncodingUTF8(encFile));
	params.set("certBase64", cert);

	std::ostringstream body;
	params.write(body);
	std::string result = Utility::SuperRequest("/RS_KeyEncryptFile", body.str());
	//std::string encoding = Utility::UTF8EncodingGBK(result);
	return _bstr_t(result.data());
}
//需要登录状态下才能调用接口
BSTR CRSyncControlCtrl::RS_KeyDecryptFile(BSTR encFilePath, BSTR dncFilePath, BSTR containerId)
{
	std::string encFile = _com_util::ConvertBSTRToString(encFilePath);
	std::string dncFile = _com_util::ConvertBSTRToString(dncFilePath);
	std::string id = _com_util::ConvertBSTRToString(containerId);

	if (!IsLogined(id))
	{
		RSyncLoginView loginView(CString(id.c_str()), CString(""));
		if (loginView.DoModal() != IDOK) return _bstr_t();

		std::string result = Login(loginView.name(), loginView.password());

		if (!OK(result)) return _bstr_t(result.data());
	}

	HTMLForm params;
	params.set("encFilePath", Utility::GBKEncodingUTF8(encFile));
	params.set("dncFilePath", Utility::GBKEncodingUTF8(dncFile));
	params.set("containerId", id);

	std::ostringstream body;
	params.write(body);
	std::string result = Utility::SuperRequest("/RS_KeyDecryptFile", body.str());
  
	return _bstr_t(result.data());
}


BSTR CRSyncControlCtrl::RS_GetUserList()
{
	std::string result = Utility::SuperRequest("/RS_GetUserList", "");

	return _bstr_t(result.data());
}

BSTR CRSyncControlCtrl::RS_GetCertBase64String(BSTR containerId, SHORT certType)
{
	std::string id = _com_util::ConvertBSTRToString(containerId);

	HTMLForm params;
	params.set("containerId", id);
	params.set("certType", Var(certType));

	std::ostringstream body;
	params.write(body);
	std::string result = Utility::SuperRequest("/RS_GetCertBase64String", body.str());

	return _bstr_t(result.data());
}

BSTR CRSyncControlCtrl::RS_CertLogin(BSTR containerId, BSTR password)
{
	/// containerId=91B0A65F-FBA9-4B7E-9627-F74475C53B9C&password=222222

	std::string id = _com_util::ConvertBSTRToString(containerId);
	std::string word = _com_util::ConvertBSTRToString(password);

	if (word.empty())
	{
		RSyncLoginView loginView(CString(id.data()), CString(word.data()));
		if (loginView.DoModal() == IDOK)
		{
			id = loginView.name();
			word = loginView.password();
		}
		else
			return onCancelRespone();
	}

	std::string result = Login(id, word);
	return _bstr_t(result.data());
}

std::string Login(const std::string& id, const std::string& word)
{
	HTMLForm params;
	params.set("containerId", id);
	params.set("password", word);

	std::ostringstream body;
	params.write(body);
	return Utility::SuperRequest("/RS_CertLogin", body.str());
}

BSTR onCancelRespone() {
	Poco::JSON::Object result;
	result.set("code", "9999");
	result.set("msg", "user cancel");
	std::ostringstream out;
	result.stringify(out);
	return _bstr_t(out.str().data());
}


bool OK(const std::string& result)
{
	Parser T;
	Var R = T.parse(result);
	assert(R.type() == typeid(Object::Ptr));
	DynamicStruct ds = *R.extract<Object::Ptr>();
	return ds["code"] == "0000";
}

BSTR CRSyncControlCtrl::RS_GetPinRetryCount(BSTR containerId)
{
	std::string id = _com_util::ConvertBSTRToString(containerId);
	//std::string body(Poco::format("containerId=%s", id));
	HTMLForm params;
	params.set("containerId", id);

	std::ostringstream body;
	params.write(body);
	std::string result = Utility::SuperRequest("/RS_GetPinRetryCount", body.str());

	//std::string encoding = Utility::UTF8EncodingGBK(result);
	return _bstr_t(result.data());
}

BSTR CRSyncControlCtrl::RS_ChangePassWd(BSTR containerId, BSTR oldCode, BSTR newCode)
{
	std::string id = _com_util::ConvertBSTRToString(containerId);
	std::string theold = _com_util::ConvertBSTRToString(oldCode);
	std::string thenew = _com_util::ConvertBSTRToString(newCode);

	if (theold.empty() || thenew.empty())
	{
		RSyncChangPassWd passwd(CString(id.data()), CString(theold.data()), CString(thenew.data()));
		INT_PTR modal = passwd.DoModal();
		if (modal != IDOK) return onCancelRespone();
		{
			id = passwd.name();
			theold = passwd.theOld();
			thenew = passwd.theNew();
		}
	}
	//std::string body(Poco::format("containerId=%s&oldCode=%s&newCode=%s", id, theold, thenew));
	std::string result = changpasswd(id, theold, thenew);
	return _bstr_t(result.data());
}

std::string changpasswd(const std::string& id, const std::string& theold, const std::string& thenew) {
	HTMLForm params;
	params.set("containerId", id);
	params.set("oldCode", theold);
	params.set("newCode", thenew);

	std::ostringstream body;
	params.write(body);
	std::string result = Utility::SuperRequest("/RS_ChangePassWd", body.str());

	return result;
}

BSTR CRSyncControlCtrl::RS_KeyGetKeySnExt(BSTR containerId)
{
	std::string id = _com_util::ConvertBSTRToString(containerId);
	//std::string body(Poco::format("containerId=%s", id));
	HTMLForm params;
	params.set("containerId", id);

	std::ostringstream body;
	params.write(body);
	std::string result = Utility::SuperRequest("/RS_KeyGetKeySn", body.str());

	//std::string encoding = Utility::UTF8EncodingGBK(result);
	return _bstr_t(result.data());
}

BSTR CRSyncControlCtrl::RS_KeyGetKeySn()
{
	std::string result;
	result = Utility::SuperRequest("/RS_GetUserList", "");

	std::string id = Utility::formatUid(result);

	if (!IsLogined(id))
	{
		RSyncLoginView loginView(CString(id.c_str()), CString(""));
		if (loginView.DoModal() != IDOK) return onCancelRespone();

		std::string result = Login(loginView.name(), loginView.password());

		if (!OK(result)) return _bstr_t(result.data());
	}

	HTMLForm params;
	params.set("containerId", id);
	std::ostringstream body;
	params.write(body);
	result = Utility::SuperRequest("/RS_KeyGetKeySn", body.str());

	//std::string encoding = Utility::UTF8EncodingGBK(result);
	Parser ps;
	Var res = ps.parse(result);
	assert(res.type() == typeid(Object::Ptr));

	Object::Ptr object = res.extract<Object::Ptr>();
	assert(object);
	Object::Ptr data = object->getObject("data");
	if (data && data->has("containerId"))
		data->remove("containerId");
	object->set("data", data);
	DynamicStruct ds = *object;

	return _bstr_t(ds.toString().data());
}

BSTR CRSyncControlCtrl::RS_KeySignByP1(BSTR msg, BSTR containerId)
{
	/// containerId=806000119631708&asn1Msg=Today+is+nice+day
	std::string id = _com_util::ConvertBSTRToString(containerId);
	std::string text = _com_util::ConvertBSTRToString(msg);
	//std::string body(Poco::format("containerId=%s&asn1Msg=%s", id, text));
	HTMLForm params;
	params.set("containerId", id);
	params.set("asn1Msg", Utility::GBKEncodingUTF8(text));

	std::ostringstream body;
	params.write(body);
	std::string result = Utility::SuperRequest("/RS_KeySignByP1", body.str());

	//std::string encoding = Utility::UTF8EncodingGBK(result);
	return _bstr_t(result.data());
}

BSTR CRSyncControlCtrl::RS_VerifySignByP1(BSTR certBase64, BSTR msg, BSTR signdMsg)
{
	std::string cert = _com_util::ConvertBSTRToString(certBase64);
	std::string text = _com_util::ConvertBSTRToString(msg);
	std::string signature = _com_util::ConvertBSTRToString(signdMsg);
	//std::string body(Poco::format("certBase64=%s&msg=%s&signdMsg=%s", cert, text, signature));
	HTMLForm params;
	params.set("certBase64", cert);
	params.set("msg", Utility::GBKEncodingUTF8(text));
	params.set("signdMsg", signature);
	std::ostringstream body;
	params.write(body);
	std::string result = Utility::SuperRequest("/RS_VerifySignByP1", body.str());

	//std::string encoding = Utility::UTF8EncodingGBK(result);
	return _bstr_t(result.data());
}

BSTR CRSyncControlCtrl::RS_KeySignByP7(BSTR msg, BSTR flag, BSTR containerId)
{
	std::string id = _com_util::ConvertBSTRToString(containerId);
	std::string message = _com_util::ConvertBSTRToString(msg);
	std::string mode = _com_util::ConvertBSTRToString(flag);
	//std::string body(Poco::format("containerId=%s&msg=%s&flag=%s", id, message, mode));
	HTMLForm params;
	params.set("containerId", id);
	params.set("msg", Utility::GBKEncodingUTF8(message));
	params.set("flag", mode);
	std::ostringstream body;
	params.write(body);
	std::string result = Utility::SuperRequest("/RS_KeySignByP7", body.str());

	//std::string encoding = Utility::UTF8EncodingGBK(result);
	return _bstr_t(result.data());
}

BSTR CRSyncControlCtrl::RS_VerifySignByP7(BSTR msg, BSTR signdMsg, BSTR flag)
{
	std::string message = _com_util::ConvertBSTRToString(msg);
	std::string signedMessage = _com_util::ConvertBSTRToString(signdMsg);
	std::string mode = _com_util::ConvertBSTRToString(flag);

	//std::string body(Poco::format("msg=%s&signdMsg=%s&flag=%s", message, signedMessage, mode));
	HTMLForm params;
	params.set("msg", Utility::GBKEncodingUTF8(message));
	params.set("signdMsg", signedMessage);
	params.set("flag", mode);
	std::ostringstream body;
	params.write(body);
	std::string result = Utility::SuperRequest("/RS_VerifySignByP7", body.str());

	//std::string encoding = Utility::UTF8EncodingGBK(result);
	return _bstr_t(result.data());
}

BSTR CRSyncControlCtrl::RS_KeyEncryptData(BSTR rsKey, BSTR certBase64)
{
	std::string cert = _com_util::ConvertBSTRToString(certBase64);
	std::string rskey = _com_util::ConvertBSTRToString(rsKey);
	//std::string body(Poco::format("certBase64=%s&rsKey=%s", cert, rskey));
	HTMLForm params;
	params.set("certBase64", cert);
	params.set("rsKey", Utility::GBKEncodingUTF8(rskey));
	std::ostringstream body;
	params.write(body);
	std::string result = Utility::SuperRequest("/RS_KeyEncryptData", body.str());

	//std::string encoding = Utility::UTF8EncodingGBK(result);
	return _bstr_t(result.data());
}

BSTR CRSyncControlCtrl::RS_KeyDecryptData(BSTR encRsKey, BSTR containerId)
{
	std::string id = _com_util::ConvertBSTRToString(containerId);
	std::string rskey = _com_util::ConvertBSTRToString(encRsKey);
	//std::string body(Poco::format("containerId=%s&encRsKey=%s", id, rskey));
	if (!IsLogined(id))
	{
		RSyncLoginView loginView(CString(id.c_str()), CString(""));
		if (loginView.DoModal() != IDOK) return onCancelRespone();

		std::string result = Login(loginView.name(), loginView.password());

		if (!OK(result)) return _bstr_t(result.data());
	}
	HTMLForm params;
	params.set("containerId", id);
	params.set("encRsKey", rskey);
	std::ostringstream body;
	params.write(body);
	std::string result = Utility::SuperRequest("/RS_KeyDecryptData", body.str());

	//std::string encoding = Utility::UTF8EncodingGBK(result);
	return _bstr_t(result.data());
}

BSTR CRSyncControlCtrl::RS_GetCertInfo(BSTR certBase64, BSTR type)
{
	std::string cert = _com_util::ConvertBSTRToString(certBase64);
	std::string ctype = _com_util::ConvertBSTRToString(type);
	//std::string body(Poco::format("certBase64=%s&type=%s", cert, ctype));
	HTMLForm params;
	params.set("certBase64", cert);
	params.set("type", ctype);
	std::ostringstream body;
	params.write(body);
	std::string result = Utility::SuperRequest("/RS_GetCertInfo", body.str());

	//std::wstring bstr = Utility::convert(result);
	//std::string encoding = Utility::UTF8EncodingGBK(result);
	return _bstr_t(result.data());
}

BSTR CRSyncControlCtrl::RS_CloudLoginAuth(BSTR transid)
{
	std::string id = _com_util::ConvertBSTRToString(transid);

	HTMLForm params;
	params.set("transid", id);
	std::ostringstream body;
	params.write(body);
	std::string result = Utility::SuperRequest("/RS_CloudLoginAuth", body.str());

	//std::string encoding = Utility::UTF8EncodingGBK(result);
	return _bstr_t(result.data());
}

BSTR CRSyncControlCtrl::RS_CloudSealAuth(BSTR transid)
{
	std::string id = _com_util::ConvertBSTRToString(transid);

	HTMLForm params;
	params.set("transid", id);
	std::ostringstream body;
	params.write(body);
	std::string result = Utility::SuperRequest("/RS_CloudSealAuth", body.str());

	//std::string encoding = Utility::UTF8EncodingGBK(result);
	return _bstr_t(result.data());
}

BSTR CRSyncControlCtrl::RS_CloudGetAuth(BSTR transid)
{
	std::string TRANSID = _com_util::ConvertBSTRToString(transid);
	std::string result;
	if (m_authResult.find(TRANSID) != m_authResult.end())
	{
		result = m_authResult[TRANSID];
	}
	else {
		Poco::JSON::Object obj;
		obj.set("code", "0000");
		obj.set("msg", "执行成功");
		Object data = onCloudAuthData("0", "", "", "");
		obj.set("data", data);
		std::ostringstream out;
		obj.stringify(out);
		obj.setEscapeUnicode();
		result = out.str();
	}
	return _bstr_t(result.data());
}

BSTR CRSyncControlCtrl::RS_CloudGetSealList(BSTR token)
{
	std::string TOKEN = _com_util::ConvertBSTRToString(token);

	HTMLForm params;
	params.set("token", TOKEN);
	std::ostringstream body;
	params.write(body);
	std::string result = Utility::SuperRequest("/RS_CloudGetSealList", body.str());
	return _bstr_t(result.data());
}
BSTR CRSyncControlCtrl::RS_CloudSignByP7(BSTR msg, BSTR keySn, BSTR transid, BSTR token)
{
	std::string MSG = _com_util::ConvertBSTRToString(msg);
	std::string KEYSN = _com_util::ConvertBSTRToString(keySn);
	std::string TRANSID = _com_util::ConvertBSTRToString(transid);
	std::string TOKEN = _com_util::ConvertBSTRToString(token);

	HTMLForm params;
	params.set("msg", Utility::GBKEncodingUTF8(MSG));
	params.set("keySn", Utility::GBKEncodingUTF8(KEYSN));
	params.set("transid", TRANSID);
	params.set("token", TOKEN);
	std::ostringstream body;
	params.write(body);
	std::string result = Utility::SuperRequest("/RS_CloudSignByP7", body.str());

	//std::string encoding = Utility::UTF8EncodingGBK(result);
	return _bstr_t(result.data());
}

BSTR CRSyncControlCtrl::RS_CloudGetSignResult(BSTR transid)
{
	std::string TRANSID = _com_util::ConvertBSTRToString(transid);
	std::string result;
	if (m_authResult.find(TRANSID) != m_authResult.end())
	{
		result = m_authResult[TRANSID];
	}
	else {
		Poco::JSON::Object obj;
		obj.set("code","0000");
		obj.set("msg", "执行成功");
		Object data = onCloudSignData("0", "", "");
		obj.set("data", data);
		std::ostringstream out;
		obj.stringify(out);
		obj.setEscapeUnicode();
		result = out.str();
	}

	return _bstr_t(result.data());
}

BSTR CRSyncControlCtrl::RS_CloudLogoutAuth(BSTR token)
{
	std::string TOKEN = _com_util::ConvertBSTRToString(token);

	HTMLForm params;
	params.set("token", TOKEN);
	std::ostringstream body;
	params.write(body);
	std::string result = Utility::SuperRequest("/RS_CloudLogoutAuth", body.str());

	//std::string encoding = Utility::UTF8EncodingGBK(result);
	return _bstr_t(result.data());
}
BSTR CRSyncControlCtrl::RS_CloudEncryptAuth(BSTR transid)
{
	std::string TRANSID = _com_util::ConvertBSTRToString(transid);

	HTMLForm params;
	params.set("transid", TRANSID);
	std::ostringstream body;
	params.write(body);
	std::string result = Utility::SuperRequest("/RS_CloudEncryptAuth", body.str());

	//std::string encoding = Utility::UTF8EncodingGBK(result);
	return _bstr_t(result.data());
}
BSTR CRSyncControlCtrl::RS_CloudEncryptData(BSTR reachKey, BSTR transid, BSTR token)
{
	std::string REACHKEY = _com_util::ConvertBSTRToString(reachKey);
	std::string TOKEN = _com_util::ConvertBSTRToString(token);
	std::string TRANSID = _com_util::ConvertBSTRToString(transid);

	HTMLForm params;
	params.set("symKey", REACHKEY);
	params.set("token", TOKEN);
	params.set("transid", TRANSID);
	std::ostringstream body;
	params.write(body);
	std::string result = Utility::SuperRequest("/RS_CloudEncryptData", body.str());

	//std::string encoding = Utility::UTF8EncodingGBK(result);
	return _bstr_t(result.data());
}

BSTR CRSyncControlCtrl::RS_CloudEncryptFile(BSTR souceFilePath, BSTR encFilePath, BSTR transid, BSTR token)
{
	std::string SOUCEFILEPATH = _com_util::ConvertBSTRToString(souceFilePath);
	std::string ENCFILEPATH = _com_util::ConvertBSTRToString(encFilePath);
	std::string TOKEN = _com_util::ConvertBSTRToString(token);
	std::string TRANSID = _com_util::ConvertBSTRToString(transid);

	HTMLForm params;
	params.set("souceFilePath", Utility::GBKEncodingUTF8(SOUCEFILEPATH));
	params.set("encFilePath", Utility::GBKEncodingUTF8(ENCFILEPATH));
	params.set("token", TOKEN);
	params.set("transid", TRANSID);
	std::ostringstream body;
	params.write(body);
	std::string result = Utility::SuperRequest("/RS_CloudEncryptFile", body.str());

	//std::string encoding = Utility::UTF8EncodingGBK(result);
	return _bstr_t(result.data());
}
BSTR CRSyncControlCtrl::RS_CloudDevryptAuth(BSTR transid)
{
	std::string TRANSID = _com_util::ConvertBSTRToString(transid);

	HTMLForm params;
	params.set("transid", TRANSID);
	std::ostringstream body;
	params.write(body);
	std::string result = Utility::SuperRequest("/RS_CloudDevryptAuth", body.str());

	//std::string encoding = Utility::UTF8EncodingGBK(result);
	return _bstr_t(result.data());
}
BSTR CRSyncControlCtrl::RS_CloudDevryptData(BSTR encReachKey, BSTR url, BSTR transid, BSTR token)
{
	std::string ENCREACHKEY = _com_util::ConvertBSTRToString(encReachKey);
	std::string URL = _com_util::ConvertBSTRToString(url);
	std::string TRANSID = _com_util::ConvertBSTRToString(transid);
	std::string TOKEN = _com_util::ConvertBSTRToString(token);

	HTMLForm params;
	params.set("encSymKey", ENCREACHKEY);
	params.set("url", URL);
	params.set("transid", TRANSID);
	params.set("token", TOKEN);
	std::ostringstream body;
	params.write(body);
	std::string result = Utility::SuperRequest("/RS_CloudDevryptData", body.str());

	//std::string encoding = Utility::UTF8EncodingGBK(result);
	return _bstr_t(result.data());
}

BSTR CRSyncControlCtrl::RS_CloudDevryptFile(BSTR encFilePath, BSTR dncFilePath, BSTR url, BSTR transid, BSTR token)
{
	std::string ENCFILEPATH = _com_util::ConvertBSTRToString(encFilePath);
	std::string DNCFILEPATH = _com_util::ConvertBSTRToString(dncFilePath);
	std::string TRANSID = _com_util::ConvertBSTRToString(transid);
	std::string TOKEN = _com_util::ConvertBSTRToString(token);
	std::string URL = _com_util::ConvertBSTRToString(url);

	HTMLForm params;
	params.set("encFilePath", Utility::GBKEncodingUTF8(ENCFILEPATH));
	params.set("dncFilePath", Utility::GBKEncodingUTF8(DNCFILEPATH));
	params.set("url", URL);
	params.set("transid", TRANSID);
	params.set("token", TOKEN);
	std::ostringstream body;
	params.write(body);
	std::string result = Utility::SuperRequest("/RS_CloudDevryptFile", body.str());

	//std::string encoding = Utility::UTF8EncodingGBK(result);
	return _bstr_t(result.data());
}
BSTR CRSyncControlCtrl::RS_CloudReceiveDevryptResult(BSTR token, BSTR resultData)
{
	std::string RESULTDATA = _com_util::ConvertBSTRToString(resultData);
	std::string TOKEN = _com_util::ConvertBSTRToString(token);

	HTMLForm params;
	params.set("transid", RESULTDATA);
	params.set("token", TOKEN);
	std::ostringstream body;
	params.write(body);
	std::string result = Utility::SuperRequest("/RS_CloudReceiveDevryptResult", body.str());

	//std::string encoding = Utility::UTF8EncodingGBK(result);
	return _bstr_t(result.data());

}

BSTR CRSyncControlCtrl::RS_CloudGetCompanyCert(BSTR transid, BSTR token)
{
	std::string TRANSID = _com_util::ConvertBSTRToString(transid);
	std::string TOKEN = _com_util::ConvertBSTRToString(token);

	HTMLForm params;
	params.set("transid", TRANSID);
	params.set("token", TOKEN);
	std::ostringstream body;
	params.write(body);
	std::string result = Utility::SuperRequest("/RS_CloudGetCompanyCert", body.str());

	//std::string encoding = Utility::UTF8EncodingGBK(result);
	return _bstr_t(result.data());
}

BSTR CRSyncControlCtrl::RS_CloudGetCertAuth(BSTR transid)
{
	std::string TRANSID = _com_util::ConvertBSTRToString(transid);

	HTMLForm params;
	params.set("transid", TRANSID);
	std::ostringstream body;
	params.write(body);
	std::string result = Utility::SuperRequest("/RS_CloudGetCertAuth", body.str());

	//std::string encoding = Utility::UTF8EncodingGBK(result);
	return _bstr_t(result.data());
}

BSTR CRSyncControlCtrl::RS_CloudGetCertBase64(BSTR transid, BSTR token)
{
	std::string TRANSID = _com_util::ConvertBSTRToString(transid);
	std::string TOKEN = _com_util::ConvertBSTRToString(token);

	HTMLForm params;
	params.set("transid", TRANSID);
	params.set("token", TOKEN);
	std::ostringstream body;
	params.write(body);
	std::string result = Utility::SuperRequest("/RS_CloudGetCertBase64", body.str());

	//std::string encoding = Utility::UTF8EncodingGBK(result);
	return _bstr_t(result.data());
}

BSTR CRSyncControlCtrl::RS_CloudLogout(BSTR userId)
{
	std::string USERID = _com_util::ConvertBSTRToString(userId);

	HTMLForm params;
	params.set("userId", USERID);
	std::ostringstream body;
	params.write(body);
	std::string result = Utility::SuperRequest("/RS_CloudLogout", body.str());

	//std::string encoding = Utility::UTF8EncodingGBK(result);
	return _bstr_t(result.data());
}

BSTR CRSyncControlCtrl::RS_KeyStatus(BSTR containerId)
{
	std::string id = _com_util::ConvertBSTRToString(containerId);
	HTMLForm params;
	params.set("containerId", id);
	std::ostringstream body;
	params.write(body);
	std::string result = Utility::SuperRequest("/RS_KeyStatus", body.str());

	//std::string encoding = Utility::UTF8EncodingGBK(result);
	return _bstr_t(result.data());
}

inline void CRSyncControlCtrl::RS_CloudLoginAuthEvent(const MQTTNotification& Nf)
{
	CString _authResult, _transid, _token, _mobile, _userName, _userID, _message;
	_authResult = Nf.getdata("authResult").data();
	_transid = Nf.getdata("transid").data();
	_token = Nf.getdata("token").data();
	_message = Nf.getdata("authMsg").data();

	_mobile = Nf.getdata("mobile").data();
	_userName = Nf.getdata("userName").data();
	_userID = Nf.getdata("userId").data();
	FireEvent(eventid_3, EVENT_PARAM(VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR), _authResult, _transid, _token
		, _mobile, _userName, _userID, _message);
}

void CRSyncControlCtrl::onSaveCloudEvent(const MQTTNotification & Nf)
{
	std::string transid = Nf.getdata("transid");
	Poco::JSON::Object result(JSONOptions::JSON_ESCAPE_UNICODE);
	result.set("code", Nf.code());
	result.set("msg", Utility::GBKEncodingUTF8(Nf.msg()));
	std::string act = Nf.getdata("action");
	Object data;
	switch (atoi(act.data()))
	{
	case SignedSealAuth:
	case UnSignedSealAuth :
		data = onCloudAuthData(Nf.getdata("authResult"), Nf.getdata("authMsg"), Nf.getdata("token"), Nf.getdata("keySn"));
		break;
	case GetSignResult:
		data = onCloudSignData(Nf.getdata("authResult"), Nf.getdata("signdMsg"), Nf.getdata("certBase64"));
		break;
	default:
		break;
	}
	result.set("data", data);
	std::ostringstream out;
	result.stringify(out);
	m_authResult[transid] = out.str();
}

Poco::JSON::Object CRSyncControlCtrl::onCloudAuthData(std::string authResult, std::string authMsg, std::string token, std::string keysn)
{
	Object data(JSONOptions::JSON_ESCAPE_UNICODE);
	data.set("authResult", authResult);
	data.set("authMsg", authMsg);
	data.set("token", token);
	data.set("keySn", keysn);
	return data;
}

Poco::JSON::Object CRSyncControlCtrl::onCloudSignData(std::string signResult, std::string signdMsg, std::string signdCert)
{
	Object data(JSONOptions::JSON_ESCAPE_UNICODE);
	data.set("signResult", signResult);
	data.set("signdMsg", signdMsg);
	data.set("certBase64", signdCert);
	return data;
}

// CRSyncControlCtrl 消息处理程序
