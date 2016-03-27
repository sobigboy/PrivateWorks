#include "CommonDBA.h"

#define MAX_ANSWERQUESTION_CNT (100)
#define MAX_ADD_SUBJECT_CNT	(100)

#define MAX_SUBJECT_STRING_LEN	(4096)

#define QUESTION_TYPE_SELECTION	(0)
#define QUESTION_TYPE_FILL	(1)

typedef enum e_status
{
	e_add_subject = 0,
	e_display_subject,
	e_answer_subject
}E_STATUS;

typedef struct _subject_cst
{
	int nSubjectID;
	int nDifficultyDegree;
	int nQuestionType;
	CString szExaminationQuestion;
	CString szAnswerA;
	CString szAnswerB;
	CString szAnswerC;
	CString szAnswerD;
	int	nRightAnswer;
}SUBJECT_CST;

typedef struct _user_answer_cst
{
	int nSubjectID;
	CString szUserAnswerA;
	CString szUserAnswerB;
	CString szUserAnswerC;
	CString szUserAnswerD;
	int nUserSelection;
}USER_ANSWER_CST;

typedef struct _user_answer_t
{
	int nSubjectID;
	int nDifficultyDegree;
	int nQuestionType;
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
		_stprintf_s(szExaminationQuestion, _T("%s"), cs.szExaminationQuestion.GetString());
		_stprintf_s(szAnswerA, _T("%s"), cs.szAnswerA.GetString());
		_stprintf_s(szAnswerB, _T("%s"), cs.szAnswerB.GetString());
		_stprintf_s(szAnswerC, _T("%s"), cs.szAnswerC.GetString());
		_stprintf_s(szAnswerD, _T("%s"), cs.szAnswerD.GetString());
		nRightAnswer = cs.nRightAnswer;
		return this;
	}
}SUBJECT_T;