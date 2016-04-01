// SubjectUI.cpp : 实现文件
//

#include "stdafx.h"
#include "AIPaperMaker.h"
#include "SubjectUI.h"
#include "afxdialogex.h"
#include "AIPaperMakerDlg.h"

// CSubjectUI 对话框

IMPLEMENT_DYNAMIC(CSubjectUI, CDialogEx)

#define ID_TIMER_DURATION	(20001)

CSubjectUI::CSubjectUI(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSubjectUI::IDD, pParent)
{
	m_pstSubjectCS = NULL;
	m_pstUserAnswerCS = NULL;
	m_enumStatus = e_add_subject;
}

CSubjectUI::~CSubjectUI()
{
}

void CSubjectUI::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_QUESTION_TYPE, m_cbQustionType);
	DDX_Control(pDX, IDC_COMBO_DIF_DEGREE, m_cbDifDegree);
	DDX_Control(pDX, IDC_CHECK1, m_btnAnsA);
	DDX_Control(pDX, IDC_CHECK2, m_btnAnsB);
	DDX_Control(pDX, IDC_CHECK3, m_btnAnsC);
	DDX_Control(pDX, IDC_CHECK4, m_btnAnsD);
	DDX_Control(pDX, IDC_STATIC_DURATION, m_staticDuration);
	DDX_Control(pDX, IDC_STATIC_DUR_FLAG, m_staticDurFlag);
	DDX_Control(pDX, IDC_COMBO_CHAPTER, m_cbChapter);

	if (!m_pstSubjectCS)
		return;
	DDX_CBIndex(pDX, IDC_COMBO_DIF_DEGREE, m_pstSubjectCS->nDifficultyDegree);
	DDX_CBIndex(pDX, IDC_COMBO_QUESTION_TYPE, m_pstSubjectCS->nQuestionType);
// 	DDX_CBIndex(pDX, IDC_COMBO_CHAPTER, m_pstSubjectCS->nChapterID);

	DDX_Text(pDX, IDC_EDIT_TITLE, m_pstSubjectCS->szExaminationQuestion);

	if (m_enumStatus == e_answer_subject && m_pstSubjectCS->nQuestionType == QUESTION_TYPE_FILL)
	{
		DDX_Text(pDX, IDC_EDIT_ANS_A, m_pstUserAnswerCS->szUserAnswerA);
		DDX_Text(pDX, IDC_EDIT_ANS_B, m_pstUserAnswerCS->szUserAnswerB);
		DDX_Text(pDX, IDC_EDIT_ANS_C, m_pstUserAnswerCS->szUserAnswerC);
		DDX_Text(pDX, IDC_EDIT_ANS_D, m_pstUserAnswerCS->szUserAnswerD);
	}
	else
	{
		DDX_Text(pDX, IDC_EDIT_ANS_A, m_pstSubjectCS->szAnswerA);
		DDX_Text(pDX, IDC_EDIT_ANS_B, m_pstSubjectCS->szAnswerB);
		DDX_Text(pDX, IDC_EDIT_ANS_C, m_pstSubjectCS->szAnswerC);
		DDX_Text(pDX, IDC_EDIT_ANS_D, m_pstSubjectCS->szAnswerD);
	}

}


BEGIN_MESSAGE_MAP(CSubjectUI, CDialogEx)
	ON_BN_CLICKED(IDOK, &CSubjectUI::OnBnClickedOk)
	ON_CBN_SELCHANGE(IDC_COMBO_QUESTION_TYPE, &CSubjectUI::OnCbnSelchangeComboQuestionType)
	ON_BN_CLICKED(ID_NEXTSUB, &CSubjectUI::OnBnClickedNextsub)
	ON_BN_CLICKED(ID_PRESUB, &CSubjectUI::OnBnClickedPresub)
	ON_WM_TIMER()
	ON_WM_DESTROY()
END_MESSAGE_MAP()

void CSubjectUI::OnBnClickedOk()
{
	bool bRet = true;
	bRet = Commit();
	if (!bRet)
		return;

	::PostMessage(m_pParentWnd->GetSafeHwnd(), WM_MESSAGE_COMMIT_PAPER, 0, 0);

	CDialogEx::OnOK();
}

BOOL CSubjectUI::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	SetTimer(ID_TIMER_DURATION, 1000, NULL);
	InitCtrl();

	return TRUE; 
}

void CSubjectUI::SetMode(E_STATUS eMode, SUBJECT_CST* pstSubjectCS, USER_ANSWER_CST* pstUserAnser/* = NULL*/)
{
	m_enumStatus = eMode;

	if (m_enumStatus == e_display_subject ||
		m_enumStatus == e_add_subject)
	{
		m_pstSubjectCS = pstSubjectCS;

		assert(m_pstSubjectCS);
	}
	else if (m_enumStatus == e_answer_subject)
	{
		m_pstUserAnswerCS = pstUserAnser;
		m_pstSubjectCS = pstSubjectCS;

		assert(m_pstSubjectCS && m_pstUserAnswerCS);
		m_pstUserAnswerCS->nSubjectID = m_pstSubjectCS->nSubjectID;
	}
}

void CSubjectUI::InitCtrl()
{
	//initialize chapter comboBox
	CDBMgr dbMgr;
	int nCnt = dbMgr.GetChapterCnt();

	m_cbChapter.Clear();
	for (int i = 0; i < nCnt; i++)
	{
		TCHAR szName[MAX_USER_ACCOUNT_LEN] = { 0 };
		TCHAR szAlias[MAX_USER_ACCOUNT_LEN] = { 0 };
		if (dbMgr.GetChapterByID(i + 1, szName, szAlias) > 0)
			m_cbChapter.InsertString(i, szName);
		else
			nCnt++;
	}

	if (!m_cbQustionType.GetSafeHwnd())
		return;
	m_cbQustionType.InsertString(QUESTION_TYPE_SELECTION, _T("选择题"));
	m_cbQustionType.InsertString(QUESTION_TYPE_FILL, _T("填空题"));

	m_cbDifDegree.InsertString(0, _T("1"));
	m_cbDifDegree.InsertString(1, _T("2"));
	m_cbDifDegree.InsertString(2, _T("3"));
	m_cbDifDegree.InsertString(3, _T("4"));
	m_cbDifDegree.InsertString(4, _T("5"));
	m_cbDifDegree.InsertString(5, _T("6"));
	m_cbDifDegree.InsertString(6, _T("7"));
	m_cbDifDegree.InsertString(7, _T("8"));
	m_cbDifDegree.InsertString(8, _T("9"));
	m_cbDifDegree.InsertString(9, _T("10"));

	UpdateData(FALSE);
	UpdateCtrl(FALSE);
	if (m_enumStatus == e_add_subject)
	{
		SetWindowText(_T("添加题库"));
		m_cbQustionType.SetCurSel(0);
		m_cbDifDegree.SetCurSel(0);
		m_cbQustionType.EnableWindow(TRUE);
		m_cbDifDegree.EnableWindow(TRUE);
		m_cbChapter.SetCurSel(0);
		m_cbChapter.EnableWindow(TRUE);
		GetDlgItem(ID_BTN_PRESUB)->ShowWindow(SW_HIDE);
		m_staticDuration.ShowWindow(SW_HIDE);
		m_staticDurFlag.ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_TITLE)->EnableWindow(TRUE);
	}
	else if (m_enumStatus == e_display_subject)
	{
		SetWindowText(_T("展示题库"));
		m_cbQustionType.EnableWindow(FALSE);
		m_cbDifDegree.EnableWindow(FALSE);
		m_cbChapter.EnableWindow(FALSE);
		GetDlgItem(ID_BTN_PRESUB)->ShowWindow(SW_SHOW);
		m_staticDuration.ShowWindow(SW_HIDE);
		m_staticDurFlag.ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_TITLE)->EnableWindow(FALSE);
	}
	else if (m_enumStatus == e_answer_subject)
	{
		SetWindowText(_T("答题"));
		m_cbQustionType.EnableWindow(FALSE);
		m_cbDifDegree.EnableWindow(FALSE);
		m_cbChapter.EnableWindow(FALSE);
		GetDlgItem(ID_BTN_PRESUB)->ShowWindow(SW_SHOW);
		m_staticDuration.ShowWindow(SW_SHOW);
		m_staticDurFlag.ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_TITLE)->EnableWindow(FALSE);
	}

	m_staticDuration.SetWindowText(_T(""));
}

void CSubjectUI::OnCbnSelchangeComboQuestionType()
{
	UpdateCtrl(FALSE);
}

bool CSubjectUI::CommitAddSubject()
{
	assert(m_pstSubjectCS);
	if (m_pstSubjectCS->nQuestionType == QUESTION_TYPE_SELECTION && m_pstSubjectCS->nRightAnswer == 0)
	{
		AfxMessageBox(_T("添加失败，必须设置一项或多项为正确答案，并勾选上"));
		return false;
	}
	if (m_pstSubjectCS->nQuestionType == QUESTION_TYPE_FILL && m_pstSubjectCS->szAnswerA.IsEmpty())
	{
		AfxMessageBox(_T("必须填写答案"));
		return false;
	}

	CDBMgr dbMgr;
	if (0 == dbMgr.AddSubject(*m_pstSubjectCS))
	{
		AfxMessageBox(_T("添加成功"));
	}
	else
	{
		AfxMessageBox(_T("添加失败，请重试"));
		return false;
	}

	return true;
}

bool CSubjectUI::CommitAnswerSubject()
{
	assert(m_pstSubjectCS && m_pstUserAnswerCS);

// 	if (m_pstSubjectCS->nQuestionType == QUESTION_TYPE_SELECTION && m_pstUserAnswerCS->nUserSelection == 0)
// 	{
// 		AfxMessageBox(_T("必须选择一个答案"));
// 		return false;
// 	}
// 
// 	if (m_pstSubjectCS->nQuestionType == QUESTION_TYPE_FILL && m_pstUserAnswerCS->szUserAnswerA.IsEmpty())
// 	{
// 		AfxMessageBox(_T("必须填写答案"));
// 		return false;
// 	}

	CDBMgr mgr;
	int nScore = mgr.CheckAnswer(*m_pstUserAnswerCS, *m_pstSubjectCS);
	m_pstUserAnswerCS->nScore = nScore / 4;
	return true;
}

void CSubjectUI::UpdateCtrl(BOOL bSaved)
{
	if (bSaved)
		m_pstSubjectCS->nChapterID = m_cbChapter.GetCurSel() + 1;
	else
		m_cbChapter.SetCurSel(m_pstSubjectCS->nChapterID - 1);

	if (m_enumStatus == e_add_subject || m_enumStatus == e_display_subject)
	{
		if (bSaved)
		{
			m_pstSubjectCS->nRightAnswer = (m_btnAnsD.GetCheck() << 3) + (m_btnAnsC.GetCheck() << 2) + (m_btnAnsB.GetCheck() << 1) + m_btnAnsA.GetCheck();
		}
		else
		{
			m_btnAnsD.SetCheck(m_pstSubjectCS->nRightAnswer >> 3 & 1);
			m_btnAnsC.SetCheck(m_pstSubjectCS->nRightAnswer >> 2 & 1);
			m_btnAnsB.SetCheck(m_pstSubjectCS->nRightAnswer >> 1 & 1);
			m_btnAnsA.SetCheck(m_pstSubjectCS->nRightAnswer >> 0 & 1);
		}
	}
	else
	{
		//answer question mode
		if (bSaved)
		{
			m_pstUserAnswerCS->nUserSelection = (m_btnAnsD.GetCheck() << 3) + (m_btnAnsC.GetCheck() << 2) + (m_btnAnsB.GetCheck() << 1) + m_btnAnsA.GetCheck();
		}
		else
		{
			m_btnAnsD.SetCheck(m_pstUserAnswerCS->nUserSelection >> 3 & 1);
			m_btnAnsC.SetCheck(m_pstUserAnswerCS->nUserSelection >> 2 & 1);
			m_btnAnsB.SetCheck(m_pstUserAnswerCS->nUserSelection >> 1 & 1);
			m_btnAnsA.SetCheck(m_pstUserAnswerCS->nUserSelection >> 0 & 1);
		}
	}

	//填空题
	GetDlgItem(IDC_EDIT_ANS_B)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_EDIT_ANS_C)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_EDIT_ANS_D)->ShowWindow(SW_SHOW);

	GetDlgItem(IDC_EDIT_ANS_A)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_ANS_B)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_ANS_C)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_ANS_D)->EnableWindow(TRUE);
	if (m_cbQustionType.GetCurSel() == QUESTION_TYPE_FILL)
	{
		m_btnAnsA.ShowWindow(SW_HIDE);
		m_btnAnsB.ShowWindow(SW_HIDE);
		m_btnAnsC.ShowWindow(SW_HIDE);
		m_btnAnsD.ShowWindow(SW_HIDE);

		if (m_pstSubjectCS->szAnswerB.IsEmpty())
			GetDlgItem(IDC_EDIT_ANS_B)->ShowWindow(SW_HIDE);
		if (m_pstSubjectCS->szAnswerC.IsEmpty())
			GetDlgItem(IDC_EDIT_ANS_C)->ShowWindow(SW_HIDE);
		if (m_pstSubjectCS->szAnswerD.IsEmpty())
			GetDlgItem(IDC_EDIT_ANS_D)->ShowWindow(SW_HIDE);
	}
	else if (m_cbQustionType.GetCurSel() == QUESTION_TYPE_SELECTION)
	{
		m_btnAnsA.ShowWindow(SW_SHOW);
		m_btnAnsB.ShowWindow(SW_SHOW);
		m_btnAnsC.ShowWindow(SW_SHOW);
		m_btnAnsD.ShowWindow(SW_SHOW);

		if (m_enumStatus != e_add_subject)
		{
			GetDlgItem(IDC_EDIT_ANS_A)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_ANS_B)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_ANS_C)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_ANS_D)->EnableWindow(FALSE);
		}
	}
}

void CSubjectUI::OnBnClickedNextsub()
{
	bool bRet = true;
	bRet = Commit();
	if (!bRet)
		return;

	((CAIPaperMakerDlg*)m_pParentWnd)->ProcessChildNext();
	UpdateData(FALSE);
	UpdateCtrl(FALSE);
}


void CSubjectUI::OnBnClickedPresub()
{
	bool bRet = true;
	bRet = Commit();
	if (!bRet)
		return;

	((CAIPaperMakerDlg*)m_pParentWnd)->ProcessChildPre();
	UpdateData(FALSE);
	UpdateCtrl(FALSE);

}

bool CSubjectUI::Commit()
{
	bool bRet = true;
	UpdateData(TRUE);
	UpdateCtrl(TRUE);

	switch (m_enumStatus)
	{
	case e_display_subject:
		break;
	case e_add_subject:
		bRet = CommitAddSubject();
		break;
	case e_answer_subject:
		bRet = CommitAnswerSubject();
		break;
	default:
		break;
	}
	return bRet;
}


void CSubjectUI::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	(*m_pnDurationTime)++;

	CString str;
	str.Format(_T("%02d:%02d:%02d"), *m_pnDurationTime / 3600, *m_pnDurationTime / 60, *m_pnDurationTime % 60);

	m_staticDuration.SetWindowText(str);
	CDialogEx::OnTimer(nIDEvent);
}

void CSubjectUI::OnDestroy()
{
	CDialogEx::OnDestroy();

	KillTimer(ID_TIMER_DURATION);
}
