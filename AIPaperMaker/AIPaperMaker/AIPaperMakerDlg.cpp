
// AIPaperMakerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "AIPaperMaker.h"
#include "AIPaperMakerDlg.h"
#include "afxdialogex.h"
#include "StatisticInfoUI.h"
#include "LoginUI.h"
#include "UserMgrUI.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CAIPaperMakerDlg 对话框



CAIPaperMakerDlg::CAIPaperMakerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAIPaperMakerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pSubjectUI = NULL;
	m_eMode = e_add_subject;
	m_nCurSubjectIdx = 0;
	m_nExaminationQuestionCnt = MIN_ANSWERQUESTION_CNT;
	m_nDurationTimeInSec = 0;
	memset(m_stSubjectList, 0, sizeof(m_stSubjectList));
	memset(m_stUserAnswerList, 0, sizeof(m_stUserAnswerList));
}

void CAIPaperMakerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAIPaperMakerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_ANSWER, &CAIPaperMakerDlg::OnBnClickedBtnAnswer)
	ON_BN_CLICKED(IDC_BTN_ADD, &CAIPaperMakerDlg::OnBnClickedBtnAdd)
	ON_BN_CLICKED(IDC_BTN_DISPLAY, &CAIPaperMakerDlg::OnBnClickedBtnDisplay)
	ON_MESSAGE(WM_MESSAGE_COMMIT_PAPER, OnCommitPaper)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BTN_USERMGR, &CAIPaperMakerDlg::OnBnClickedBtnUsermgr)
END_MESSAGE_MAP()


// CAIPaperMakerDlg 消息处理程序

BOOL CAIPaperMakerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	CDBMgr dbMgr;
	dbMgr.InitializeAllTable();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}


void CAIPaperMakerDlg::OnDestroy()
{
	CDialogEx::OnDestroy();
	ClearLists();
	if (m_pSubjectUI)
	{
		delete(m_pSubjectUI);
		m_pSubjectUI = NULL;
	}
}

void CAIPaperMakerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CAIPaperMakerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CAIPaperMakerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CAIPaperMakerDlg::OnBnClickedBtnAnswer()
{
	// 填空题题数
	int nFillSubjectNum = 5;

	// 选择题题数
	int nSelectionSubjectNum = 5;
	m_nExaminationQuestionCnt = nFillSubjectNum + nSelectionSubjectNum;


	// 验证数据库中题库数目
	CDBMgr mgr;
	int nRet = mgr.GetSubjectsCnt();
	if (nRet < m_nExaminationQuestionCnt)
	{
		AfxMessageBox(_T("题库中题目偏少，无法完成智能组卷！"));
		return;
	}

	// 开始智能生成试卷
	nRet = AutoMakePapers(nFillSubjectNum, nSelectionSubjectNum);

	if (nRet > 0)
		SelectMode(e_answer_subject);
	else
		AfxMessageBox(_T("智能组卷失败"));
}

void CAIPaperMakerDlg::OnBnClickedBtnAdd()
{
	// 首先验证身份，管理员/老师 才能添加题库
	USER_T user ;
	ZeroMemory(&user, sizeof(USER_T));
	CLoginUI ui(&user);

	if (IDOK == ui.DoModal())
	{
		CDBMgr mgr;
		if(mgr.CheckUser(user))
		{
			ClearLists();
			SelectMode(e_add_subject);
		}
		else
		{
			AfxMessageBox(_T("身份验证失败"));
		}
	}

}

void CAIPaperMakerDlg::OnBnClickedBtnDisplay()
{
	ClearLists();
	int nRet = AutoMakeDisplay();

	if (nRet > 0)
		SelectMode(e_display_subject);
	else
		AfxMessageBox(_T("题库暂无题目，请先添加"));

}

void CAIPaperMakerDlg::ClearLists()
{
	for (int i = 0; i < MAX_ADD_SUBJECT_CNT; i++)
	{
		if (m_stSubjectList[i])
		{
			delete(m_stSubjectList[i]);
			m_stSubjectList[i] = NULL;
		}
	}
	for (int i = 0; i < MAX_ANSWERQUESTION_CNT; i++)
	{
		if (m_stUserAnswerList[i])
		{
			delete(m_stUserAnswerList[i]);
			m_stUserAnswerList[i] = NULL;
		}
	}
}

void CAIPaperMakerDlg::SelectMode(E_STATUS eStatus)
{
	m_eMode = eStatus;
	if (m_pSubjectUI)
	{
		m_pSubjectUI->DestroyWindow();
		delete(m_pSubjectUI);
		m_pSubjectUI = NULL;
	}
	m_pSubjectUI = new CSubjectUI(this);

	if (m_eMode == e_add_subject)
	{
		m_stSubjectList[m_nCurSubjectIdx] = new SUBJECT_CST;
	}
	m_pSubjectUI->SetMode(m_eMode, m_stSubjectList[m_nCurSubjectIdx], m_stUserAnswerList[m_nCurSubjectIdx]);
	m_nDurationTimeInSec = 0;
	m_pSubjectUI->SetDurationTime(&m_nDurationTimeInSec);
	m_pSubjectUI->Create(IDD_ADDSUBJECT_DLG, this);
	m_pSubjectUI->ShowWindow(SW_SHOW);
}

BOOL CAIPaperMakerDlg::ProcessChildPre()
{
	if (m_nCurSubjectIdx > 0 && m_nCurSubjectIdx < ((m_eMode == e_answer_subject || m_eMode == e_display_subject) ? m_nExaminationQuestionCnt : MAX_ADD_SUBJECT_CNT))
	{
		m_nCurSubjectIdx--;
		if (m_eMode == e_answer_subject || m_eMode == e_display_subject)
		{
			CString str;
			str.Format(_T("共%d题，当前是第%d题"), m_nExaminationQuestionCnt, m_nCurSubjectIdx + 1);
			m_pSubjectUI->SetWindowText(str);
		}
		m_pSubjectUI->SetMode(m_eMode, m_stSubjectList[m_nCurSubjectIdx], m_stUserAnswerList[m_nCurSubjectIdx]);
	}
	else
	{
		AfxMessageBox(_T("已到头,无法继续往前翻!"));
	}
	return 0;
}

BOOL CAIPaperMakerDlg::ProcessChildNext()
{
	if (m_nCurSubjectIdx >= 0 && m_nCurSubjectIdx < ((m_eMode == e_answer_subject || m_eMode == e_display_subject) ? m_nExaminationQuestionCnt : MAX_ADD_SUBJECT_CNT) - 1)
	{
		m_nCurSubjectIdx++;
		if (m_eMode == e_add_subject)
		{
			m_stSubjectList[m_nCurSubjectIdx] = new SUBJECT_CST;
		}
		else
		{
			CString str;
			str.Format(_T("共%d题，当前是第%d题"), m_nExaminationQuestionCnt, m_nCurSubjectIdx + 1);
			m_pSubjectUI->SetWindowText(str);
		}
		m_pSubjectUI->SetMode(m_eMode, m_stSubjectList[m_nCurSubjectIdx], m_stUserAnswerList[m_nCurSubjectIdx]);
	}
	else
	{
		AfxMessageBox(_T("已到尾,无法继续往后翻!"));
	}
	return 0;
}

int CAIPaperMakerDlg::AutoMakePapers(int nSelectionSubCnt, int nFillSubCnt)
{
	int nTotalCnt = 0;
	int nMakeCnt = 0;

	CDBMgr mgr;
	nTotalCnt = mgr.GetSubjectsCnt();

	if (nTotalCnt < nSelectionSubCnt + nFillSubCnt)
		return 0;

	int nOffset = nTotalCnt / (nFillSubCnt + nSelectionSubCnt);

	for (int i = 1; i < nTotalCnt + 1; i += nOffset)
	{
		if (nMakeCnt >= nSelectionSubCnt + nFillSubCnt)
		{
			break;
		}

		SUBJECT_CST temp;
		if (mgr.GetSubjectByID(i, temp))
		{
			m_stSubjectList[nMakeCnt] = new SUBJECT_CST;
			m_stUserAnswerList[nMakeCnt] = new USER_ANSWER_CST;
			*m_stSubjectList[nMakeCnt] = &temp;
			nMakeCnt++;
		}
		else
			nTotalCnt++;
	}

	return nMakeCnt;
}

LRESULT CAIPaperMakerDlg::OnCommitPaper(WPARAM w, LPARAM l)
{
	//统计答题情况，并显示

	if (m_eMode == e_answer_subject)
	{
		STATISTIC_INFO info;
		info.strDuration.Format(_T("%02d:%02d:%02d"), m_nDurationTimeInSec / 3600, m_nDurationTimeInSec / 60, m_nDurationTimeInSec % 60);

		for (int i = 0; i < m_nExaminationQuestionCnt; i++)
		{
			info.nTotalScore += m_stUserAnswerList[i]->nScore;

			if (m_stUserAnswerList[i]->nUserSelection == 0 && m_stUserAnswerList[i]->szUserAnswerA.IsEmpty())
				info.nUnansweredCnt++;
		}

		info.nTotalCnt = m_nExaminationQuestionCnt;
		info.nAnsweredCnt = info.nTotalCnt - info.nUnansweredCnt;

		CStatisticInfoUI ui(&info);
		ui.DoModal();
	}

	m_pSubjectUI->DestroyWindow();
	m_nCurSubjectIdx = 0;
	m_nExaminationQuestionCnt = 0;
	ClearLists();
	return 0;
}

int CAIPaperMakerDlg::AutoMakeDisplay()
{
	int nTotalCnt = 0;
	int nMakeCnt = 0;

	CDBMgr mgr;
	nTotalCnt = mgr.GetSubjectsCnt();

	m_nExaminationQuestionCnt = nTotalCnt;
	for (int i = 1; i < nTotalCnt + 1; i ++)
	{
		SUBJECT_CST temp;
		if (mgr.GetSubjectByID(i, temp))
		{
			m_stSubjectList[nMakeCnt] = new SUBJECT_CST;
			// 			m_stUserAnswerList[nMakeCnt] = new USER_ANSWER_CST;
			*m_stSubjectList[nMakeCnt] = &temp;
			nMakeCnt++;
		}
		else
			nTotalCnt++;
	}
	return nMakeCnt;
}


void CAIPaperMakerDlg::OnBnClickedBtnUsermgr()
{
	CUserMgrUI ui;
	ui.DoModal();
}
