
// AIPaperMakerDlg.h : ͷ�ļ�
//

#pragma once
#include "DBMgr.h"
#include "SubjectUI.h"


// CAIPaperMakerDlg �Ի���
class CAIPaperMakerDlg : public CDialogEx
{
// ����
public:
	CAIPaperMakerDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_AIPAPERMAKER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBnClickedBtnAnswer();
	afx_msg void OnBnClickedBtnAdd();
	afx_msg void OnBnClickedBtnDisplay();
	afx_msg void OnDestroy();
	DECLARE_MESSAGE_MAP()

public:
	BOOL ProcessChildPre();
	BOOL ProcessChildNext();

protected:
	void ClearLists();
	void SelectMode(E_STATUS eStatus);

private:
	E_STATUS m_eMode;
	CSubjectUI* m_pSubjectUI;
	SUBJECT_CST* m_stSubjectList[MAX_ADD_SUBJECT_CNT];
	USER_ANSWER_CST* m_stUserAnswerList[MAX_ANSWERQUESTION_CNT];
};
