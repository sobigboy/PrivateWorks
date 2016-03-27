
// AIPaperMakerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "AIPaperMaker.h"
#include "AIPaperMakerDlg.h"
#include "afxdialogex.h"
#include "SubjectUI.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CAIPaperMakerDlg �Ի���



CAIPaperMakerDlg::CAIPaperMakerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAIPaperMakerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pSubjectUI = NULL;
	m_eMode = e_add_subject;
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
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CAIPaperMakerDlg ��Ϣ�������

BOOL CAIPaperMakerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	if (m_pSubjectUI)
	{
		delete(m_pSubjectUI);
		m_pSubjectUI = NULL;
	}
	m_pSubjectUI = new CSubjectUI;
	m_pSubjectUI->Create(IDD_ADDSUBJECT_DLG, this);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}


void CAIPaperMakerDlg::OnDestroy()
{
	CDialogEx::OnDestroy();
	ClearLists();
	if (m_pSubjectUI)
	{
// 		m_pSubjectUI->DestroyWindow();
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CAIPaperMakerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CAIPaperMakerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CAIPaperMakerDlg::OnBnClickedBtnAnswer()
{
	SelectMode(e_answer_subject);
}

void CAIPaperMakerDlg::OnBnClickedBtnAdd()
{
	ClearLists();
	SelectMode(e_add_subject);
}

void CAIPaperMakerDlg::OnBnClickedBtnDisplay()
{
	ClearLists();
	SelectMode(e_display_subject);
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
	m_pSubjectUI->SetMode(m_eMode, m_stSubjectList[0], m_stUserAnswerList[0]);
	m_pSubjectUI->ShowWindow(SW_SHOW);

}

BOOL CAIPaperMakerDlg::ProcessChildPre()
{

}

BOOL CAIPaperMakerDlg::ProcessChildNext()
{

}


