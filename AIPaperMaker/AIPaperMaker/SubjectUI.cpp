// SubjectUI.cpp : 实现文件
//

#include "stdafx.h"
#include "AIPaperMaker.h"
#include "SubjectUI.h"
#include "afxdialogex.h"


// CSubjectUI 对话框

IMPLEMENT_DYNAMIC(CSubjectUI, CDialogEx)

CSubjectUI::CSubjectUI(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSubjectUI::IDD, pParent)
{
	m_pstSubjectCS = NULL;
	m_pstUserAnswerCS = NULL;
	m_enumStatus = e_add_subject;
}

CSubjectUI::CSubjectUI(SUBJECT_CST* pstSubject, E_STATUS eStatus, CWnd* pParent /*=NULL*/)
: CDialogEx(CSubjectUI::IDD, pParent)
{
	m_pstSubjectCS = pstSubject;
	m_pstUserAnswerCS = NULL;
	m_enumStatus = eStatus;
}

CSubjectUI::CSubjectUI(USER_ANSWER_CST* pstUserAnswerCS,  E_STATUS eStatus, CWnd* pParent /*=NULL*/)
: CDialogEx(CSubjectUI::IDD, pParent)
{
	m_pstUserAnswerCS = pstUserAnswerCS;
	m_pstSubjectCS = NULL;
	m_enumStatus = eStatus;
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

	//添加题库 || 展示题库
	if (m_enumStatus == e_add_subject || m_enumStatus == e_display_subject)
	{
		DDX_Text(pDX, IDC_EDIT_TITLE, m_pstSubjectCS->szExaminationQuestion);
		DDX_CBIndex(pDX, IDC_COMBO_DIF_DEGREE, m_pstSubjectCS->nDifficultyDegree);
		DDX_CBIndex(pDX, IDC_COMBO_QUESTION_TYPE, m_pstSubjectCS->nQuestionType);

		DDX_Text(pDX, IDC_EDIT_ANS_A, m_pstSubjectCS->szAnswerA);
		DDX_Text(pDX, IDC_EDIT_ANS_B, m_pstSubjectCS->szAnswerB);
		DDX_Text(pDX, IDC_EDIT_ANS_C, m_pstSubjectCS->szAnswerC);
		DDX_Text(pDX, IDC_EDIT_ANS_D, m_pstSubjectCS->szAnswerD);
	}
	//考试中
	if (m_enumStatus == e_answer_subject)
	{
		DDX_Text(pDX, IDC_EDIT_TITLE, m_pstSubjectCS->szExaminationQuestion);
		DDX_CBIndex(pDX, IDC_COMBO_DIF_DEGREE, m_pstSubjectCS->nDifficultyDegree);
		DDX_CBIndex(pDX, IDC_COMBO_QUESTION_TYPE, m_pstSubjectCS->nQuestionType);

		DDX_Text(pDX, IDC_EDIT_ANS_A, m_pstUserAnswerCS->szUserAnswerA);
		DDX_Text(pDX, IDC_EDIT_ANS_B, m_pstUserAnswerCS->szUserAnswerB);
		DDX_Text(pDX, IDC_EDIT_ANS_C, m_pstUserAnswerCS->szUserAnswerC);
		DDX_Text(pDX, IDC_EDIT_ANS_D, m_pstUserAnswerCS->szUserAnswerD);
	}

}


BEGIN_MESSAGE_MAP(CSubjectUI, CDialogEx)
	ON_BN_CLICKED(IDOK, &CSubjectUI::OnBnClickedOk)
	ON_CBN_SELCHANGE(IDC_COMBO_QUESTION_TYPE, &CSubjectUI::OnCbnSelchangeComboQuestionType)
END_MESSAGE_MAP()


void CSubjectUI::OnBnClickedOk()
{

	bool bRet = true;
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

	if (!bRet)
		return;

	CDialogEx::OnOK();
}

BOOL CSubjectUI::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	InitCtrl();

	return TRUE; 
}

void CSubjectUI::InitCtrl()
{
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

	if (m_enumStatus == e_add_subject)
	{
		m_cbQustionType.SetCurSel(0);
		m_cbDifDegree.SetCurSel(0);
		m_cbQustionType.EnableWindow(TRUE);
		m_cbDifDegree.EnableWindow(TRUE);
	}
	else if (m_enumStatus == e_display_subject)
	{
		UpdateData(FALSE);
		UpdateCheckBtn(FALSE);
		m_cbQustionType.EnableWindow(FALSE);
		m_cbDifDegree.EnableWindow(FALSE);
	}
	else if (m_enumStatus == e_answer_subject)
	{
		UpdateData(TRUE);
		m_cbQustionType.EnableWindow(FALSE);
		m_cbDifDegree.EnableWindow(FALSE);
	}
}


void CSubjectUI::OnCbnSelchangeComboQuestionType()
{
	//填空题
	if (m_cbQustionType.GetCurSel() == QUESTION_TYPE_FILL)
	{
		m_btnAnsA.ShowWindow(SW_HIDE);
		m_btnAnsB.ShowWindow(SW_HIDE);
		m_btnAnsC.ShowWindow(SW_HIDE);
		m_btnAnsD.ShowWindow(SW_HIDE);
	}
	else if (m_cbQustionType.GetCurSel() == QUESTION_TYPE_SELECTION)
	{
		m_btnAnsA.ShowWindow(SW_SHOW);
		m_btnAnsB.ShowWindow(SW_SHOW);
		m_btnAnsC.ShowWindow(SW_SHOW);
		m_btnAnsD.ShowWindow(SW_SHOW);
	}

}

bool CSubjectUI::CommitAddSubject()
{
	UpdateData(TRUE);
	UpdateCheckBtn(TRUE);

	assert(m_pstSubjectCS);
	if (m_pstSubjectCS->nQuestionType == QUESTION_TYPE_SELECTION && m_pstSubjectCS->nRightAnswer == 0)
	{
		AfxMessageBox(_T("添加失败，必须设置一项或多项为正确答案，并勾选上"));
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
	UpdateData(TRUE);
	UpdateCheckBtn(TRUE);

	assert(m_pstSubjectCS && m_pstUserAnswerCS);

	if (m_pstSubjectCS->nQuestionType == QUESTION_TYPE_SELECTION && m_pstUserAnswerCS->nUserSelection == 0)
	{
		AfxMessageBox(_T("必须选择一个答案"));
		return false;
	}

	if (m_pstSubjectCS->nQuestionType == QUESTION_TYPE_FILL && m_pstUserAnswerCS->szUserAnswerA.IsEmpty())
	{
		AfxMessageBox(_T("必须填写答案"));
		return false;
	}

	return true;
}

void CSubjectUI::UpdateCheckBtn(BOOL bSaved)
{
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


}
