#pragma once
#include <string>

// RSY 对话框
class RSyncMsgTip : public CDialogEx
{
	DECLARE_DYNAMIC(RSyncMsgTip)

public:
	RSyncMsgTip(CString msgTip, CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~RSyncMsgTip();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif
	BOOL OnInitDialog();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	CString m_showMsgTip;
};
