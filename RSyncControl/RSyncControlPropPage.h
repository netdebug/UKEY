#pragma once

// RSyncControlPropPage.h: CRSyncControlPropPage 属性页类的声明。


// CRSyncControlPropPage : 请参阅 RSyncControlPropPage.cpp 了解实现。

class CRSyncControlPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CRSyncControlPropPage)
	DECLARE_OLECREATE_EX(CRSyncControlPropPage)

// 构造函数
public:
	CRSyncControlPropPage();

// 对话框数据
	enum { IDD = IDD_PROPPAGE_RSYNCCONTROL };

// 实现
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 消息映射
protected:
	DECLARE_MESSAGE_MAP()
};

