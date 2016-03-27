#pragma once


// CStatisticInfoUI �Ի���
#include "BasedataDefine.h"
class CStatisticInfoUI : public CDialogEx
{
	DECLARE_DYNAMIC(CStatisticInfoUI)

public:
	CStatisticInfoUI(CWnd* pParent = NULL);   // ��׼���캯��
	CStatisticInfoUI(STATISTIC_INFO* pstStatsticInfo, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CStatisticInfoUI();

// �Ի�������
	enum { IDD = IDD_DLG_STATISTIC_INFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()


protected:
	STATISTIC_INFO* m_pStaitsticInfo;
public:
	virtual BOOL OnInitDialog();
};
