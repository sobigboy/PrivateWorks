// UserMgrUI.cpp : 实现文件
//

#include "stdafx.h"
#include "AIPaperMaker.h"
#include "UserMgrUI.h"
#include "afxdialogex.h"
#include "AddUserUI.h"
#include "DBMgr.h"
// CUserMgrUI 对话框

IMPLEMENT_DYNAMIC(CUserMgrUI, CDialogEx)

CUserMgrUI::CUserMgrUI(CWnd* pParent /*=NULL*/)
	: CDialogEx(CUserMgrUI::IDD, pParent)
{
	m_pstCurEditingUser = NULL;
}

CUserMgrUI::~CUserMgrUI()
{
}

void CUserMgrUI::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_USERINFO, m_lbUsersInfo);
	DDX_Control(pDX, IDC_COMBO_ROLE, m_cbRole);
	if (m_pstCurEditingUser && !pDX->m_bSaveAndValidate)
	{
		CString strTemp(m_pstCurEditingUser->szAccount);
		DDX_Text(pDX, IDC_EDIT_ACCOUNT, strTemp);
		strTemp = m_pstCurEditingUser->szPasswd;
		DDX_Text(pDX, IDC_EDIT_PSWD, strTemp);
		strTemp = m_pstCurEditingUser->szAlias;
		DDX_Text(pDX, IDC_EDIT_ALIAS, strTemp);

		DDX_CBIndex(pDX, IDC_COMBO_ROLE, (int&)m_pstCurEditingUser->eRole);

	}
	else if (m_pstCurEditingUser && pDX->m_bSaveAndValidate)
	{
		CString strTemp;
		DDX_Text(pDX, IDC_EDIT_ACCOUNT, strTemp);
		StrCpy(m_pstCurEditingUser->szAccount, strTemp.GetString());
		DDX_Text(pDX, IDC_EDIT_PSWD, strTemp);
		StrCpy(m_pstCurEditingUser->szPasswd, strTemp.GetString());
		DDX_Text(pDX, IDC_EDIT_ALIAS, strTemp);
		StrCpy(m_pstCurEditingUser->szAlias, strTemp.GetString());

		DDX_CBIndex(pDX, IDC_COMBO_ROLE, (int&)m_pstCurEditingUser->eRole);

	}
}


BEGIN_MESSAGE_MAP(CUserMgrUI, CDialogEx)
	ON_WM_DESTROY()
	ON_LBN_SELCHANGE(IDC_LIST_USERINFO, &CUserMgrUI::OnLbnSelchangeListUserinfo)
	ON_BN_CLICKED(IDC_BTN_ADDUSER, &CUserMgrUI::OnBnClickedBtnAdduser)
	ON_BN_CLICKED(IDC_BTN_DELUSER, &CUserMgrUI::OnBnClickedBtnDeluser)
END_MESSAGE_MAP()


// CUserMgrUI 消息处理程序


BOOL CUserMgrUI::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	RefreshUserInfoList();
	InitCtrl();
	return TRUE;  // return TRUE unless you set the focus to a control

}

int CUserMgrUI::RefreshUserInfoList()
{
	DestroyUserInfoList();

	CDBMgr dbMgr;
	int nCnt = dbMgr.GetUserCnt();
	for (int i = 0; i < nCnt; i++)
	{
		USER_T *pstUser = new USER_T;
		dbMgr.GetUserByIdx(i, *pstUser);

		m_lbUsersInfo.InsertString(i, pstUser->szAlias);
		m_lbUsersInfo.SetItemData(i, (DWORD_PTR)pstUser);
	}

	return 0;
}

int CUserMgrUI::DestroyUserInfoList()
{
	int nCnt = m_lbUsersInfo.GetCount();
	for (int i = 0; i < nCnt; i++)
	{
		USER_T *pUser = (USER_T *)m_lbUsersInfo.GetItemDataPtr(i);
		delete(pUser);
	}
	m_lbUsersInfo.ResetContent();
	m_pstCurEditingUser = NULL;
	return 0;
}


void CUserMgrUI::OnDestroy()
{
	CDialogEx::OnDestroy();
	DestroyUserInfoList();
}


void CUserMgrUI::OnLbnSelchangeListUserinfo()
{
	// TODO:  在此添加控件通知处理程序代码
	int nCurIdx = m_lbUsersInfo.GetCurSel();

	if (nCurIdx < 0)
		return;
	m_pstCurEditingUser = (USER_T*)m_lbUsersInfo.GetItemData(nCurIdx);
	assert(m_pstCurEditingUser);
	UpdateData(FALSE);
}

int CUserMgrUI::InitCtrl()
{
	m_cbRole.Clear();
	m_cbRole.InsertString((int)role_admin, _T("管理员"));
	m_cbRole.InsertString((int)role_teacher, _T("教师"));
	m_cbRole.InsertString((int)role_student, _T("学生"));

	return 0;
}


void CUserMgrUI::OnBnClickedBtnAdduser()
{
	USER_T stUser;
	CAddUserUI ui(&stUser);

	if (ui.DoModal() == IDCANCEL)
	{
		return;
	}



	CDBMgr dbMgr;
	if (0 == dbMgr.AddUser(stUser))
	{
		RefreshUserInfoList();
		int nCnt = m_lbUsersInfo.GetCount();
		m_lbUsersInfo.SetCurSel(nCnt - 1);
		m_pstCurEditingUser = (USER_T*)m_lbUsersInfo.GetItemData(nCnt - 1);

		UpdateData(FALSE);
		AfxMessageBox(_T("添加成功"));
	}
	else
	{
		AfxMessageBox(_T("添加失败"));
	}


}


void CUserMgrUI::OnBnClickedBtnDeluser()
{
	if (!m_pstCurEditingUser)
	{
		AfxMessageBox(L"请先选择一个用户");
		return;
	}
	
	if (m_pstCurEditingUser->eRole == role_admin)
	{
		AfxMessageBox(L"你不能删除一个管理员");
		return;
	}

	if (IDCANCEL == AfxMessageBox(L"是否确认删除？", MB_OKCANCEL | MB_ICONWARNING))
		return;

	CDBMgr dbMgr;
	dbMgr.DeleteUserByAccount(m_pstCurEditingUser->szAccount);
	RefreshUserInfoList();
	m_pstCurEditingUser = NULL;
}
