// RSY.cpp: 实现文件
//

#include "stdafx.h"
#include "RSyncControl.h"
#include "RSyncMsgTip.h"
#include "afxdialogex.h"
#include <atlconv.h>


// RSY 对话框

IMPLEMENT_DYNAMIC(RSyncMsgTip, CDialogEx)

RSyncMsgTip::RSyncMsgTip(CString msgTip, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG2, pParent)
{
	m_showMsgTip = msgTip;
}

RSyncMsgTip::~RSyncMsgTip()
{
}

BOOL RSyncMsgTip::OnInitDialog()
{
	SetDlgItemText(IDC_STATIC, m_showMsgTip);
	return 0;
}

void RSyncMsgTip::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(RSyncMsgTip, CDialogEx)
END_MESSAGE_MAP()


// RSY 消息处理程序
