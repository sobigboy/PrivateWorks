#pragma once

#include "CommonDBA.h"

#define MAX_SUBJECT_STRING_LEN	(4096)

#define QUESTION_TYPE_SELECTION	(1)
#define QUESTION_TYPE_FILL	(2)

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
}SUBJECT_T;

class CDBMgr
{
public:
	CDBMgr();
	virtual ~CDBMgr();

public:
	/*
	* @nDifficultyDegree : 难度系数
	*/
	int AddSubject(/*int nID, */int nDifficultyDegree, int nQuestionType,
		TCHAR * szExaminationQuestion, 
		TCHAR* szAnswerA, TCHAR* szAnswerB, TCHAR* szAnswerC, TCHAR* szAnswerD,
		int nRightAnswer);

	int AddSubject(SUBJECT_T &stSubject);
	int DeleteSubjectByID(int nID);

	int GetSubjectByID(int nID, SUBJECT_T &stSuject);

	int CheckAnswer(USER_ANSWER_T &stUserAnswer);

private:
	int CreateTable_Subject();
};

// check answer

/**
 * database design
 * 
 * table : subject
 *
 * 字段：id, difficulty_degree, question_type, examination_question, answerA, answerB, answerC, answerD, right_answer
 * 类型：int		int				int					varchar			varchar	 varchar  varchar  varchar   varchar
 *	
**/

