#pragma once
#include "BasedataDefine.h"

// CLoginUI �Ի���

class CLoginUI : public CDialogEx
{
	DECLARE_DYNAMIC(CLoginUI)

public:
	CLoginUI(USER_T *pstUser, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CLoginUI();

// �Ի�������
	enum { IDD = IDD_DLG_LOGIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()


private:
	USER_T * m_pstUser;
};
