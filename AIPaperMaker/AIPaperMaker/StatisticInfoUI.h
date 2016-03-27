#pragma once


// CStatisticInfoUI 对话框
#include "BasedataDefine.h"
class CStatisticInfoUI : public CDialogEx
{
	DECLARE_DYNAMIC(CStatisticInfoUI)

public:
	CStatisticInfoUI(CWnd* pParent = NULL);   // 标准构造函数
	CStatisticInfoUI(STATISTIC_INFO* pstStatsticInfo, CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CStatisticInfoUI();

// 对话框数据
	enum { IDD = IDD_DLG_STATISTIC_INFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()


protected:
	STATISTIC_INFO* m_pStaitsticInfo;
public:
	virtual BOOL OnInitDialog();
};
