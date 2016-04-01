#pragma once
#include "BasedataDefine.h"

// CLoginUI 对话框

class CLoginUI : public CDialogEx
{
	DECLARE_DYNAMIC(CLoginUI)

public:
	CLoginUI(USER_T *pstUser, CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLoginUI();

// 对话框数据
	enum { IDD = IDD_DLG_LOGIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()


private:
	USER_T * m_pstUser;
};
