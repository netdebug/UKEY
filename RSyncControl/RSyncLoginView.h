#pragma once


// RSyncLoginView 对话框
#include <string>

class RSyncLoginView : public CDialog
{
	DECLARE_DYNAMIC(RSyncLoginView)

public:
	RSyncLoginView(CString& cid, CString& cpassword);   // 标准构造函数
	virtual ~RSyncLoginView();
	BOOL OnInitDialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	void SetInputName(CString name);

	CString GetInputName();
	CString GetInputPassword();

	std::string name();
	std::string password();
private:
	CString m_pName;
	// 用户名
	CString m_nameStr;
	// 密码
	CString m_passwordStr;
};
