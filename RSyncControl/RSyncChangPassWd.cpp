// RSyncChangPassWd.cpp: 实现文件
//

#include "stdafx.h"
#include "RSyncControl.h"
#include "RSyncChangPassWd.h"
#include "afxdialogex.h"


// RSyncChangPassWd 对话框

IMPLEMENT_DYNAMIC(RSyncChangPassWd, CDialogEx)

RSyncChangPassWd::RSyncChangPassWd(CString name, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG3, pParent)
	, _name(name)
	, _oldPassWd(_T(""))
	, _newPassWd(_T(""))
{

}

RSyncChangPassWd::~RSyncChangPassWd()
{
}

BOOL RSyncChangPassWd::OnInitDialog()
{	
	SetDlgItemTextW(IDC_EDIT1, _name);
	SetDlgItemTextW(IDC_EDIT2, _newPassWd);
	SetDlgItemTextW(IDC_EDIT3, _oldPassWd);
	return 0;
}

void RSyncChangPassWd::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT3, _oldPassWd);
	DDX_Text(pDX, IDC_EDIT2, _newPassWd);
	DDX_Text(pDX, IDC_EDIT1, _name);
}
BEGIN_MESSAGE_MAP(RSyncChangPassWd, CDialogEx)
	ON_BN_CLICKED(IDOK, &RSyncChangPassWd::OnBnClickedOk)
END_MESSAGE_MAP()


void RSyncChangPassWd::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}

CString RSyncChangPassWd::GetInputName()
{
	return _name;
}

CString RSyncChangPassWd::GetInputNewPasswd()
{
	return _oldPassWd;
}

CString RSyncChangPassWd::GetInputOldPasswd()
{
	return _newPassWd;
}

void RSyncChangPassWd::SetInputPassWd(CString oldCode, CString newCode)
{
	_oldPassWd = oldCode;
	_newPassWd = newCode;
}