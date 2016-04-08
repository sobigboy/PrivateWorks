#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "BasedataDefine.h"

// CUserMgrUI 对话框

class CUserMgrUI : public CDialogEx
{
	DECLARE_DYNAMIC(CUserMgrUI)

public:
	CUserMgrUI(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CUserMgrUI();

// 对话框数据
	enum { IDD = IDD_DLG_USERMGR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnLbnSelchangeListUserinfo();
	DECLARE_MESSAGE_MAP()


protected:
	int RefreshUserInfoList();
	int DestroyUserInfoList();
	int InitCtrl();

	USER_T* m_pstCurEditingUser;
	CListBox m_lbUsersInfo;
public:
	CComboBox m_cbRole;
	afx_msg void OnBnClickedBtnAdduser();
	afx_msg void OnBnClickedBtnDeluser();
};
