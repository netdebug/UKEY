// RSyncLoginView.cpp: 实现文件
//

#include "stdafx.h"
#include "RSyncControl.h"
#include "RSyncLoginView.h"
#include "afxdialogex.h"
#include <comutil.h>

// RSyncLoginView 对话框

IMPLEMENT_DYNAMIC(RSyncLoginView, CDialog)

RSyncLoginView::RSyncLoginView(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG1, pParent)
	, m_nameStr(_T(""))
	, m_passwordStr(_T(""))
{
	
}

RSyncLoginView::~RSyncLoginView()
{
}

BOOL RSyncLoginView::OnInitDialog()
{
	SetDlgItemTextW(IDC_EDIT1, m_pName);
	return 0;
}

void RSyncLoginView::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_nameStr);
	DDX_Text(pDX, IDC_EDIT2, m_passwordStr);
}


BEGIN_MESSAGE_MAP(RSyncLoginView, CDialog)
	ON_BN_CLICKED(IDOK, &RSyncLoginView::OnBnClickedOk)
END_MESSAGE_MAP()


// RSyncLoginView 消息处理程序


void RSyncLoginView::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnOK();
}

void RSyncLoginView::SetInputName(CString name)
{
	m_pName = name;
}

CString RSyncLoginView::GetInputName()
{
	return m_nameStr;
}

CString RSyncLoginView::GetInputPassword()
{
	return m_passwordStr;
}

