// LoginUI.cpp : 实现文件
//

#include "stdafx.h"
#include "AIPaperMaker.h"
#include "LoginUI.h"
#include "afxdialogex.h"


// CLoginUI 对话框

IMPLEMENT_DYNAMIC(CLoginUI, CDialogEx)

CLoginUI::CLoginUI(USER_T *pstUser, CWnd* pParent /*=NULL*/)
	: CDialogEx(CLoginUI::IDD, pParent)
{
	m_pstUser = pstUser;
}

CLoginUI::~CLoginUI()
{
}

void CLoginUI::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	CString strPasswd;
	CString strAccount;

	if (!pDX->m_bSaveAndValidate)
	{
		strPasswd = m_pstUser->szPasswd;
		strAccount = m_pstUser->szAccount;
	}

	DDX_Text(pDX, IDC_EDIT_PSWD, strPasswd);
	DDX_Text(pDX, IDC_EDIT_ACCOUNT, strAccount);
	if (pDX->m_bSaveAndValidate)
	{
		_stprintf_s(m_pstUser->szAccount, sizeof(m_pstUser->szAccount) / sizeof(m_pstUser->szAccount[0]), _T("%s"), strAccount.GetString());
		_stprintf_s(m_pstUser->szPasswd, sizeof(m_pstUser->szPasswd) / sizeof(m_pstUser->szPasswd[0]), _T("%s"), strPasswd.GetString());
	}

}


BEGIN_MESSAGE_MAP(CLoginUI, CDialogEx)
END_MESSAGE_MAP()


// CLoginUI 消息处理程序
