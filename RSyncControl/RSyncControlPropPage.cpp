// RSyncControlPropPage.cpp : CRSyncControlPropPage 属性页类的实现。

#include "stdafx.h"
#include "RSyncControl.h"
#include "RSyncControlPropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CRSyncControlPropPage, COlePropertyPage)

// 消息映射

BEGIN_MESSAGE_MAP(CRSyncControlPropPage, COlePropertyPage)
END_MESSAGE_MAP()

// 初始化类工厂和 guid

IMPLEMENT_OLECREATE_EX(CRSyncControlPropPage, "MFCACTIVEXCONT.RSyncControlPropPage.1",
	0xfae5a0a2,0x066f,0x4c57,0x8e,0xb3,0x0c,0x04,0x85,0xf8,0xb7,0x77)

// CRSyncControlPropPage::CRSyncControlPropPageFactory::UpdateRegistry -
// 添加或移除 CRSyncControlPropPage 的系统注册表项

BOOL CRSyncControlPropPage::CRSyncControlPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_RSYNCCONTROL_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, nullptr);
}

// CRSyncControlPropPage::CRSyncControlPropPage - 构造函数

CRSyncControlPropPage::CRSyncControlPropPage() :
	COlePropertyPage(IDD, IDS_RSYNCCONTROL_PPG_CAPTION)
{
}

// CRSyncControlPropPage::DoDataExchange - 在页和属性间移动数据

void CRSyncControlPropPage::DoDataExchange(CDataExchange* pDX)
{
	DDP_PostProcessing(pDX);
}

// CRSyncControlPropPage 消息处理程序
