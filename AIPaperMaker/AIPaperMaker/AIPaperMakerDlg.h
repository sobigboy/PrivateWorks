
// AIPaperMakerDlg.h : 头文件
//

#pragma once
#include "DBMgr.h"
#include "SubjectUI.h"


// CAIPaperMakerDlg 对话框
class CAIPaperMakerDlg : public CDialogEx
{
// 构造
public:
	CAIPaperMakerDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_AIPAPERMAKER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBnClickedBtnAnswer();
	afx_msg void OnBnClickedBtnAdd();
	afx_msg void OnBnClickedBtnDisplay();
	afx_msg void OnDestroy();
	afx_msg LRESULT OnCommitPaper(WPARAM w, LPARAM l);
	DECLARE_MESSAGE_MAP()

public:
	BOOL ProcessChildPre();
	BOOL ProcessChildNext();

protected:

	int AutoMakePapers(int nSelectionSubCnt, int nFillSubCnt);
	int AutoMakeDisplay();
	void ClearLists();
	void SelectMode(E_STATUS eStatus);

private:
	int m_nDurationTimeInSec;
	int m_nExaminationQuestionCnt;
	E_STATUS m_eMode;
	CSubjectUI* m_pSubjectUI;
	int m_nCurSubjectIdx;
	SUBJECT_CST* m_stSubjectList[MAX_ADD_SUBJECT_CNT];
	USER_ANSWER_CST* m_stUserAnswerList[MAX_ANSWERQUESTION_CNT];
};
