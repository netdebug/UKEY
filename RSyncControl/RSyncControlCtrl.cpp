// RSyncControlCtrl.cpp : CRSyncControlCtrl ActiveX 控件类的实现。

#include "stdafx.h"
#include "RSyncControl.h"
#include "RSyncControlCtrl.h"
#include "RSyncControlPropPage.h"
#include "afxdialogex.h"
#include <comutil.h>
#include "Utility.h"

using Reach::ActiveX::Utility;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CRSyncControlCtrl, COleControl)

// 消息映射

BEGIN_MESSAGE_MAP(CRSyncControlCtrl, COleControl)
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()

// 调度映射

BEGIN_DISPATCH_MAP(CRSyncControlCtrl, COleControl)
	DISP_FUNCTION_ID(CRSyncControlCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION_ID(CRSyncControlCtrl, "RS_GetUserList", dispid_GetUserList, RS_GetUserList, VT_BSTR, VTS_NONE)
	DISP_FUNCTION_ID(CRSyncControlCtrl, "RS_GetCertBase64String", dispid_GetCertBase64String, RS_GetCertBase64String, VT_BSTR, VTS_BSTR VTS_I2)
	DISP_FUNCTION_ID(CRSyncControlCtrl, "RS_CertLogin", dispid_CertLogin, RS_CertLogin, VT_BSTR, VTS_BSTR VTS_BSTR)
	DISP_FUNCTION_ID(CRSyncControlCtrl, "RS_GetPinRetryCount", dispid_GetPinRetryCount, RS_GetPinRetryCount, VT_BSTR, VTS_BSTR)
	DISP_FUNCTION_ID(CRSyncControlCtrl, "RS_KeyGetKeySn", dispid_KeyGetKeySn, RS_KeyGetKeySn, VT_BSTR, VTS_NONE)
	DISP_FUNCTION_ID(CRSyncControlCtrl, "RS_KeySignByP1", dispid_KeySignByP1, RS_KeySignByP1, VT_BSTR, VTS_BSTR VTS_BSTR)
	DISP_FUNCTION_ID(CRSyncControlCtrl, "RS_VerifySignByP1", dispid_VerifySignByP1, RS_VerifySignByP1, VT_BSTR, VTS_BSTR VTS_BSTR VTS_BSTR)
	DISP_FUNCTION_ID(CRSyncControlCtrl, "RS_KeyEncryptData", dispid_KeyEncryptData, RS_KeyEncryptData, VT_BSTR, VTS_BSTR VTS_BSTR)
	DISP_FUNCTION_ID(CRSyncControlCtrl, "RS_KeyDecryptData", dispid_KeyDecryptData, RS_KeyDecryptData, VT_BSTR, VTS_BSTR VTS_BSTR)
	DISP_FUNCTION_ID(CRSyncControlCtrl, "RS_GetCertInfo", dispid_GetCertInfo, RS_GetCertInfo, VT_BSTR, VTS_BSTR VTS_BSTR)
	DISP_FUNCTION_ID(CRSyncControlCtrl, "RS_KeySignByP7", dispid_KeySignByP7, RS_KeySignByP7, VT_BSTR, VTS_BSTR VTS_BSTR)
	DISP_FUNCTION_ID(CRSyncControlCtrl, "RS_VerifySignByP7", dispid_VerifySignByP7, RS_VerifySignByP7, VT_BSTR, VTS_BSTR VTS_BSTR)
END_DISPATCH_MAP()

// 事件映射

BEGIN_EVENT_MAP(CRSyncControlCtrl, COleControl)
END_EVENT_MAP()

// 属性页

// TODO: 根据需要添加更多属性页。请记住增加计数!
BEGIN_PROPPAGEIDS(CRSyncControlCtrl, 1)
	PROPPAGEID(CRSyncControlPropPage::guid)
END_PROPPAGEIDS(CRSyncControlCtrl)

// 初始化类工厂和 guid

IMPLEMENT_OLECREATE_EX(CRSyncControlCtrl, "RSyncControl.RSyncControlCtrl.1",
	0xa0b23721,0x9350,0x4b4d,0xb5,0x81,0x65,0xad,0xd1,0xa7,0x7a,0x5e)

// 键入库 ID 和版本

IMPLEMENT_OLETYPELIB(CRSyncControlCtrl, _tlid, _wVerMajor, _wVerMinor)

// 接口 ID

const IID IID_DRSyncControl = {0xdb403885,0xf81d,0x41d2,{0x80,0xd7,0x40,0x36,0x50,0x97,0xd6,0x0c}};
const IID IID_DRSyncControlEvents = {0xb1c93fb3,0x0485,0x4837,{0x9a,0xaf,0xaf,0x8f,0x96,0xa2,0xc0,0xd2}};

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

CRSyncControlCtrl::CRSyncControlCtrl()
{
	InitializeIIDs(&IID_DRSyncControl, &IID_DRSyncControlEvents);
	// TODO:  在此初始化控件的实例数据。
}

// CRSyncControlCtrl::~CRSyncControlCtrl - 析构函数

CRSyncControlCtrl::~CRSyncControlCtrl()
{
	// TODO:  在此清理控件的实例数据。
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

BSTR CRSyncControlCtrl::RS_GetUserList()
{
	std::string result;
	Utility::request("/RS_GetUserList");
	result = Utility::response();
	std::wstring bstr = Utility::convert(result);

	return _bstr_t(bstr.data());
}

BSTR CRSyncControlCtrl::RS_GetCertBase64String(BSTR containerId, SHORT certType)
{
	std::string id = _com_util::ConvertBSTRToString(containerId);
	std::string body(Poco::format("containerId=%s&certType=$d", id, certType));
	Utility::request("/RS_GetCertBase64String", body);

	std::string result = Utility::response();
	std::wstring bstr = Utility::convert(result);

	return _bstr_t(bstr.data());
}

BSTR CRSyncControlCtrl::RS_CertLogin(BSTR containerId, BSTR password)
{
	/// containerId=91B0A65F-FBA9-4B7E-9627-F74475C53B9C&password=222222

	std::string id = _com_util::ConvertBSTRToString(containerId);
	std::string word = _com_util::ConvertBSTRToString(password);
	std::string body(Poco::format("containerId=%s&password=$d", id, word));
	Utility::request("/RS_CertLogin", body);

	std::string result = Utility::response();
	std::wstring bstr = Utility::convert(result);

	return _bstr_t(bstr.data());
}

BSTR CRSyncControlCtrl::RS_GetPinRetryCount(BSTR containerId)
{
	std::string id = _com_util::ConvertBSTRToString(containerId);
	std::string body(Poco::format("containerId=%s", id));
	Utility::request("/RS_GetPinRetryCount", body);

	std::string result = Utility::response();
	std::wstring bstr = Utility::convert(result);

	return _bstr_t(bstr.data());
}

BSTR CRSyncControlCtrl::RS_ChangePassWd(BSTR containerId, BSTR oldCode, BSTR newCode)
{
	std::string id = _com_util::ConvertBSTRToString(containerId);
	std::string theold = _com_util::ConvertBSTRToString(oldCode);
	std::string thenew = _com_util::ConvertBSTRToString(newCode);

	std::string body(Poco::format("containerId=%s&oldCode=%s&newCode=%s", id, theold, thenew));
	Utility::request("/RS_ChangePassWd", body);

	std::string result = Utility::response();
	std::wstring bstr = Utility::convert(result);

	return _bstr_t(bstr.data());
}

BSTR CRSyncControlCtrl::RS_KeyGetKeySn(BSTR containerId)
{
	std::string id = _com_util::ConvertBSTRToString(containerId);
	std::string body(Poco::format("containerId=%s", id));
	Utility::request("/RS_KeyGetKeySn", body);

	std::string result = Utility::response();
	std::wstring bstr = Utility::convert(result);

	return _bstr_t(bstr.data());
}

BSTR CRSyncControlCtrl::RS_KeySignByP1(BSTR msg, BSTR containerId)
{
	/// containerId=806000119631708&asn1Msg=Today+is+nice+day
	std::string id = _com_util::ConvertBSTRToString(containerId);
	std::string text = _com_util::ConvertBSTRToString(msg);
	std::string body(Poco::format("containerId=%s&asn1Msg=%s", id, text));
	Utility::request("/RS_KeySignByP1", body);

	std::string result = Utility::response();
	std::wstring bstr = Utility::convert(result);

	return _bstr_t(bstr.data());
}

BSTR CRSyncControlCtrl::RS_VerifySignByP1(BSTR certBase64, BSTR msg, BSTR signdMsg)
{
	std::string cert = _com_util::ConvertBSTRToString(certBase64);
	std::string text = _com_util::ConvertBSTRToString(msg);
	std::string signature = _com_util::ConvertBSTRToString(signdMsg);
	std::string body(Poco::format("certBase64=%s&msg=%s&signdMsg=%s", cert, text, signature));
	Utility::request("/RS_VerifySignByP1", body);

	std::string result = Utility::response();
	std::wstring bstr = Utility::convert(result);

	return _bstr_t(bstr.data());
}

BSTR CRSyncControlCtrl::RS_KeySignByP7(BSTR msg, BSTR flag, BSTR containerId)
{
	std::string id = _com_util::ConvertBSTRToString(containerId);
	std::string message = _com_util::ConvertBSTRToString(msg);
	std::string mode = _com_util::ConvertBSTRToString(flag);
	std::string body(Poco::format("containerId=%s&msg=%s&flag=%s", id, message, mode));
	Utility::request("/RS_KeySignByP7", body);

	std::string result = Utility::response();
	std::wstring bstr = Utility::convert(result);

	return _bstr_t(bstr.data());
}

BSTR CRSyncControlCtrl::RS_VerifySignByP7(BSTR msg, BSTR signdMsg, BSTR flag)
{
	std::string message = _com_util::ConvertBSTRToString(msg);
	std::string signedMessage = _com_util::ConvertBSTRToString(signdMsg);
	std::string mode = _com_util::ConvertBSTRToString(flag);

	std::string body(Poco::format("msg=%s&signdMsg=%s&flag=%s", message, signedMessage, mode));
	Utility::request("/RS_VerifySignByP7", body);

	std::string result = Utility::response();
	std::wstring bstr = Utility::convert(result);

	return _bstr_t(bstr.data());
}

BSTR CRSyncControlCtrl::RS_KeyEncryptData(BSTR rsKey, BSTR certBase64)
{
	std::string cert = _com_util::ConvertBSTRToString(certBase64);
	std::string rskey = _com_util::ConvertBSTRToString(rsKey);
	std::string body(Poco::format("certBase64=%s&rsKey=%s", cert, rskey));
	Utility::request("/RS_KeyEncryptData", body);

	std::string result = Utility::response();
	std::wstring bstr = Utility::convert(result);

	return _bstr_t(bstr.data());
}

BSTR CRSyncControlCtrl::RS_KeyDecryptData(BSTR encRsKey, BSTR containerId)
{
	std::string id = _com_util::ConvertBSTRToString(containerId);
	std::string rskey = _com_util::ConvertBSTRToString(encRsKey);
	std::string body(Poco::format("containerId=%s&encRsKey=%s", id, rskey));
	Utility::request("/RS_KeyDecryptData", body);

	std::string result = Utility::response();
	std::wstring bstr = Utility::convert(result);

	return _bstr_t(bstr.data());
}

BSTR CRSyncControlCtrl::RS_GetCertInfo(BSTR certBase64, BSTR type)
{
	std::string cert = _com_util::ConvertBSTRToString(certBase64);
	std::string ctype = _com_util::ConvertBSTRToString(type);
	std::string body(Poco::format("certBase64=%s&type=%s", cert, ctype));
	Utility::request("/RS_GetCertInfo", body);

	std::string result = Utility::response();
	std::wstring bstr = Utility::convert(result);

	return _bstr_t(bstr.data());
}


// CRSyncControlCtrl 消息处理程序
