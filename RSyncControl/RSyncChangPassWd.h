#pragma once
#include <string>


// RSyncChangPassWd 对话框

class RSyncChangPassWd : public CDialogEx
{
	DECLARE_DYNAMIC(RSyncChangPassWd)

public:
	RSyncChangPassWd(CString& name, CString& theold, CString& thenew);   // 标准构造函数
	virtual ~RSyncChangPassWd();
	BOOL OnInitDialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:

	afx_msg void OnBnClickedOk();

	std::string name();
	std::string theOld();
	std::string theNew();

private:
	friend std::string toString(CString& );
private:
	CString _newPassWd;
	CString _oldPassWd;
	CString _name;
};
