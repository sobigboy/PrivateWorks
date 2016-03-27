#pragma once

#include "DBMgr.h"
#include "afxwin.h"

// CSubjectUI 对话框

class CSubjectUI : public CDialogEx
{
	DECLARE_DYNAMIC(CSubjectUI)

public:
	CSubjectUI(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSubjectUI();

// 对话框数据
	enum { IDD = IDD_ADDSUBJECT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeComboQuestionType();
	DECLARE_MESSAGE_MAP()

public:
	void SetMode(E_STATUS eMode, SUBJECT_CST* pstSubjectCS, USER_ANSWER_CST* pstUserAnser = NULL);

private:
	void InitCtrl();
	void UpdateCheckBtn(BOOL bSaved);
	bool CommitAddSubject();
	bool CommitAnswerSubject();

protected:
	SUBJECT_CST* m_pstSubjectCS;
	USER_ANSWER_CST* m_pstUserAnswerCS;
	E_STATUS m_enumStatus;
	CComboBox m_cbQustionType;
	CComboBox m_cbDifDegree;
	CButton m_btnAnsA;
	CButton m_btnAnsB;
	CButton m_btnAnsC;
	CButton m_btnAnsD;

public:
	afx_msg void OnBnClickedNextsub();
	afx_msg void OnBnClickedPresub();
};
