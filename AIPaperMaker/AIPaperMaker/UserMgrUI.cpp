// UserMgrUI.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "AIPaperMaker.h"
#include "UserMgrUI.h"
#include "afxdialogex.h"
#include "AddUserUI.h"
#include "DBMgr.h"
// CUserMgrUI �Ի���

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


// CUserMgrUI ��Ϣ�������


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
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
	m_cbRole.InsertString((int)role_admin, _T("����Ա"));
	m_cbRole.InsertString((int)role_teacher, _T("��ʦ"));
	m_cbRole.InsertString((int)role_student, _T("ѧ��"));

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
		AfxMessageBox(_T("��ӳɹ�"));
	}
	else
	{
		AfxMessageBox(_T("���ʧ��"));
	}


}


void CUserMgrUI::OnBnClickedBtnDeluser()
{
	if (!m_pstCurEditingUser)
	{
		AfxMessageBox(L"����ѡ��һ���û�");
		return;
	}
	
	if (m_pstCurEditingUser->eRole == role_admin)
	{
		AfxMessageBox(L"�㲻��ɾ��һ������Ա");
		return;
	}

	if (IDCANCEL == AfxMessageBox(L"�Ƿ�ȷ��ɾ����", MB_OKCANCEL | MB_ICONWARNING))
		return;

	CDBMgr dbMgr;
	dbMgr.DeleteUserByAccount(m_pstCurEditingUser->szAccount);
	RefreshUserInfoList();
	m_pstCurEditingUser = NULL;
}
