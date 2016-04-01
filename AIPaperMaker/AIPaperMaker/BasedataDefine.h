#ifndef _BASEDATADEFINE_H_
#define _BASEDATADEFINE_H_

#include "CommonDBA.h"

#define MAX_USER_ACCOUNT_LEN			(128)

#define MIN_ANSWERQUESTION_CNT	(5)
#define MAX_ANSWERQUESTION_CNT (50)
#define MAX_ADD_SUBJECT_CNT	(100)

#define MAX_SUBJECT_STRING_LEN	(4096)

#define QUESTION_TYPE_SELECTION	(0)
#define QUESTION_TYPE_FILL	(1)


#define WM_MESSAGE_COMMIT_PAPER		(10012)

typedef struct _statistic_info
{
	CString strDuration;
	int nTotalCnt;
	int nAnsweredCnt;
	int nUnansweredCnt;
	int nTotalScore;

	_statistic_info()
	{
		strDuration = _T("");
		nTotalCnt = 0;
		nAnsweredCnt = 0;
		nUnansweredCnt = 0;
		nTotalScore = 0;
	}
}STATISTIC_INFO;

typedef enum e_user_role
{
	role_admin = 0,
	role_teacher,
	role_student
}E_USER_ROLE;

typedef enum e_status
{
	e_add_subject = 0,
	e_display_subject,
	e_answer_subject
}E_STATUS;

typedef struct _user_t
{
	E_USER_ROLE eRole;
	TCHAR szAccount[MAX_USER_ACCOUNT_LEN];
	TCHAR szAlias[MAX_USER_ACCOUNT_LEN];
	TCHAR szPasswd[MAX_USER_ACCOUNT_LEN];
}USER_T;

typedef struct _subject_cst
{
	int nSubjectID;
	int nDifficultyDegree;
	int nQuestionType;
	int nChapterID;
	CString szExaminationQuestion;
	CString szAnswerA;
	CString szAnswerB;
	CString szAnswerC;
	CString szAnswerD;
	int	nRightAnswer;

	_subject_cst()
	{
		nSubjectID = 0;
		nDifficultyDegree = 0;
		nQuestionType = 0;
		nChapterID = 0;
		szExaminationQuestion = _T("");
		szAnswerA = _T("");
		szAnswerB = _T("");
		szAnswerC = _T("");
		szAnswerD = _T("");
		nRightAnswer = 0;
	}

	_subject_cst& operator = (_subject_cst*cs)
	{
		nSubjectID = cs->nSubjectID;
		nDifficultyDegree = cs->nDifficultyDegree;
		nQuestionType = cs->nQuestionType;
		nChapterID = cs->nChapterID;
		szExaminationQuestion = cs->szExaminationQuestion;
		szAnswerA = cs->szAnswerA;
		szAnswerB = cs->szAnswerB;
		szAnswerC = cs->szAnswerC;
		szAnswerD = cs->szAnswerD;
		nRightAnswer = cs->nRightAnswer;

		return *this;
	}
}SUBJECT_CST;

typedef struct _user_answer_cst
{
	int nSubjectID;
	CString szUserAnswerA;
	CString szUserAnswerB;
	CString szUserAnswerC;
	CString szUserAnswerD;
	int nUserSelection;
	int nScore;
	_user_answer_cst()
	{
		nSubjectID = 0;
		szUserAnswerA = _T("");
		szUserAnswerB = _T("");
		szUserAnswerC= _T("");
		szUserAnswerD= _T("");
		nUserSelection = 0;
		nScore = 0;
	}
}USER_ANSWER_CST;

typedef struct _user_answer_t
{
	int nSubjectID;
	int nDifficultyDegree;
	TCHAR szUserAnswerA[MAX_SUBJECT_STRING_LEN];
	TCHAR szUserAnswerB[MAX_SUBJECT_STRING_LEN];
	TCHAR szUserAnswerC[MAX_SUBJECT_STRING_LEN];
	TCHAR szUserAnswerD[MAX_SUBJECT_STRING_LEN];
	int nUserSelection;

	_user_answer_t* operator = (_user_answer_cst &cs)
	{
		nSubjectID = cs.nSubjectID;
		_stprintf_s(szUserAnswerA, _T("%s"), cs.szUserAnswerA.GetString());
		_stprintf_s(szUserAnswerB, _T("%s"), cs.szUserAnswerB.GetString());
		_stprintf_s(szUserAnswerC, _T("%s"), cs.szUserAnswerC.GetString());
		_stprintf_s(szUserAnswerD, _T("%s"), cs.szUserAnswerD.GetString());
		nUserSelection = cs.nUserSelection;
		return this;
	}

}USER_ANSWER_T;

typedef struct _subject_t
{
	int nSubjectID;
	int nDifficultyDegree;
	int nQuestionType;
	int nChapterID;
	TCHAR szExaminationQuestion[MAX_SUBJECT_STRING_LEN];
	TCHAR szAnswerA[MAX_SUBJECT_STRING_LEN];
	TCHAR szAnswerB[MAX_SUBJECT_STRING_LEN];
	TCHAR szAnswerC[MAX_SUBJECT_STRING_LEN];
	TCHAR szAnswerD[MAX_SUBJECT_STRING_LEN];
	int	nRightAnswer;

	_subject_t* operator = (_subject_cst &cs)
	{
		nSubjectID = cs.nSubjectID;
		nDifficultyDegree = cs.nDifficultyDegree;
		nQuestionType = cs.nQuestionType;
		nChapterID = cs.nChapterID;
		_stprintf_s(szExaminationQuestion, _T("%s"), cs.szExaminationQuestion.GetString());
		_stprintf_s(szAnswerA, _T("%s"), cs.szAnswerA.GetString());
		_stprintf_s(szAnswerB, _T("%s"), cs.szAnswerB.GetString());
		_stprintf_s(szAnswerC, _T("%s"), cs.szAnswerC.GetString());
		_stprintf_s(szAnswerD, _T("%s"), cs.szAnswerD.GetString());
		nRightAnswer = cs.nRightAnswer;
		return this;
	}
}SUBJECT_T;

#endif