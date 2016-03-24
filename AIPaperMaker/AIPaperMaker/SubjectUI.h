#pragma once

#include "DBMgr.h"
#include "afxwin.h"

// CSubjectUI 对话框

typedef enum e_status
{
	e_add_subject = 0,
	e_display_subject,
	e_answer_subject
}E_STATUS;

class CSubjectUI : public CDialogEx
{
	DECLARE_DYNAMIC(CSubjectUI)

public:
	CSubjectUI(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSubjectUI();

	CSubjectUI(SUBJECT_CST* pstSubject, E_STATUS eStatus, CWnd* pParent = NULL);
	CSubjectUI(USER_ANSWER_CST* pstUserAnswer, E_STATUS eStatus, CWnd* pParent = NULL);

// 对话框数据
	enum { IDD = IDD_ADDSUBJECT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeComboQuestionType();
	DECLARE_MESSAGE_MAP()

private:
	void InitCtrl();
	bool ProcessAddSubject();

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

};
