#pragma once
#include "BasedataDefine.h"
#include "afxwin.h"

// CAddUserUI 对话框

class CAddUserUI : public CDialogEx
{
	DECLARE_DYNAMIC(CAddUserUI)

public:
	CAddUserUI( USER_T* pstUser, CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAddUserUI();

// 对话框数据
	enum { IDD = IDD_DLG_ADDUSER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

	int InitCtrl();

protected:
	USER_T* m_pstCurEditingUser;

	CComboBox m_cbRole;
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};
