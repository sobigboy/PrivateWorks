// AddUserUI.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "AIPaperMaker.h"
#include "AddUserUI.h"
#include "afxdialogex.h"


// CAddUserUI �Ի���

IMPLEMENT_DYNAMIC(CAddUserUI, CDialogEx)

CAddUserUI::CAddUserUI( USER_T* pstUser,CWnd* pParent /*=NULL*/)
	: CDialogEx(CAddUserUI::IDD, pParent)
{
	m_pstCurEditingUser = pstUser;
}

CAddUserUI::~CAddUserUI()
{
}

void CAddUserUI::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
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


BEGIN_MESSAGE_MAP(CAddUserUI, CDialogEx)
	ON_BN_CLICKED(IDOK, &CAddUserUI::OnBnClickedOk)
END_MESSAGE_MAP()


// CAddUserUI ��Ϣ�������
int CAddUserUI::InitCtrl()
{
	m_cbRole.Clear();
	m_cbRole.InsertString((int)role_admin, _T("����Ա"));
	m_cbRole.InsertString((int)role_teacher, _T("��ʦ"));
	m_cbRole.InsertString((int)role_student, _T("ѧ��"));

	return 0;
}

BOOL CAddUserUI::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	InitCtrl();

	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void CAddUserUI::OnBnClickedOk()
{
	UpdateData(TRUE);
	if (m_pstCurEditingUser->eRole == -1 ||
		0 == StrCmp(m_pstCurEditingUser->szAccount, _T("")) ||
		0 == StrCmp(m_pstCurEditingUser->szAlias, _T("")) ||
		0 == StrCmp(m_pstCurEditingUser->szPasswd, _T("")))

	{
		AfxMessageBox(_T("��д������Ϣ"));
		return;
	}
	CDialogEx::OnOK();
}
