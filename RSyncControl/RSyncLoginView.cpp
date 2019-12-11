// RSyncLoginView.cpp: 实现文件
//

#include "stdafx.h"
#include "RSyncControl.h"
#include "RSyncLoginView.h"
#include "afxdialogex.h"
#include <comutil.h>
#include <cassert>

// RSyncLoginView 对话框

IMPLEMENT_DYNAMIC(RSyncLoginView, CDialog)

RSyncLoginView::RSyncLoginView(CString& cid, CString& cpassword)
	: CDialog(IDD_DIALOG1, NULL)
	, m_nameStr(cid)
	, m_passwordStr(cpassword)
{
	
}

RSyncLoginView::~RSyncLoginView()
{
}

BOOL RSyncLoginView::OnInitDialog()
{
	SetDlgItemTextW(IDC_EDIT1, m_nameStr);
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

std::string toString(CString& str)
{
	DWORD dBufSize = WideCharToMultiByte(CP_OEMCP, 0, str, -1, NULL, 0, NULL, FALSE);
	char *dBuf = new char[dBufSize];
	memset(dBuf, 0, dBufSize);
	int nRet = WideCharToMultiByte(CP_OEMCP, 0, str, -1, dBuf, dBufSize, NULL, FALSE);
	assert(nRet > 0);
	return std::string(dBuf);
}

std::string RSyncLoginView::name()
{
	return toString(m_nameStr);
}

std::string RSyncLoginView::password()
{
	return toString(m_passwordStr);
}
