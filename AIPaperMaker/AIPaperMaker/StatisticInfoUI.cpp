// StatisticInfoUI.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "AIPaperMaker.h"
#include "StatisticInfoUI.h"
#include "afxdialogex.h"


// CStatisticInfoUI �Ի���

IMPLEMENT_DYNAMIC(CStatisticInfoUI, CDialogEx)

CStatisticInfoUI::CStatisticInfoUI(CWnd* pParent /*=NULL*/)
	: CDialogEx(CStatisticInfoUI::IDD, pParent)
{

}

CStatisticInfoUI::CStatisticInfoUI(STATISTIC_INFO* pstStatsticInfo, CWnd* pParent /*=NULL*/)
: CDialogEx(CStatisticInfoUI::IDD, pParent)
{
	assert(pstStatsticInfo);
	m_pStaitsticInfo = pstStatsticInfo;
}

CStatisticInfoUI::~CStatisticInfoUI()
{
}

void CStatisticInfoUI::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	if (!m_pStaitsticInfo)
		return;
	DDX_Text(pDX, IDC_STATIC_DURATION, m_pStaitsticInfo->strDuration);
	DDX_Text(pDX, IDC_STATIC_TOTAL_CNT, m_pStaitsticInfo->nTotalCnt);
	DDX_Text(pDX, IDC_STATIC_ANSWERED_CNT, m_pStaitsticInfo->nAnsweredCnt);
	DDX_Text(pDX, IDC_STATIC_UNANSWERED_CNT, m_pStaitsticInfo->nUnansweredCnt);
	DDX_Text(pDX, IDC_STATIC_TOTAL_SCORE, m_pStaitsticInfo->nTotalScore);
}


BEGIN_MESSAGE_MAP(CStatisticInfoUI, CDialogEx)
END_MESSAGE_MAP()


// CStatisticInfoUI ��Ϣ�������


BOOL CStatisticInfoUI::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}
