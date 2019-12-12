// RSyncChangPassWd.cpp: 实现文件
//

#include "stdafx.h"
#include "RSyncControl.h"
#include "RSyncChangPassWd.h"
#include "afxdialogex.h"


// RSyncChangPassWd 对话框

IMPLEMENT_DYNAMIC(RSyncChangPassWd, CDialogEx)

RSyncChangPassWd::RSyncChangPassWd(CString& name, CString& theold, CString& thenew)
	: CDialogEx(IDD_DIALOG3, NULL)
	, _name(name)
	, _oldPassWd(theold)
	, _newPassWd(thenew)
{

}

RSyncChangPassWd::~RSyncChangPassWd()
{
}

BOOL RSyncChangPassWd::OnInitDialog()
{	
	SetDlgItemText(IDC_EDIT1, _name);
	SetDlgItemText(IDC_EDIT2, _newPassWd);
	SetDlgItemText(IDC_EDIT3, _oldPassWd);
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

std::string RSyncChangPassWd::name()
{
	return toString(_name);
}

std::string RSyncChangPassWd::theOld()
{
	return toString(_oldPassWd);
}

std::string RSyncChangPassWd::theNew()
{
	return toString(_newPassWd);
}
