#pragma once
#include "BasedataDefine.h"
#include "afxwin.h"

// CAddUserUI �Ի���

class CAddUserUI : public CDialogEx
{
	DECLARE_DYNAMIC(CAddUserUI)

public:
	CAddUserUI( USER_T* pstUser, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAddUserUI();

// �Ի�������
	enum { IDD = IDD_DLG_ADDUSER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

	int InitCtrl();

protected:
	USER_T* m_pstCurEditingUser;

	CComboBox m_cbRole;
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};
