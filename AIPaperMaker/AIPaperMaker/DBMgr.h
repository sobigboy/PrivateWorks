#pragma once

#include "CommonDBA.h"
#include "BasedataDefine.h"

class CDBMgr
{
public:
	CDBMgr();
	virtual ~CDBMgr();

public:
	/*
	* @nDifficultyDegree : 难度系数
	*/
	int AddSubject(int nDifficultyDegree, int nQuestionType,
		TCHAR * szExaminationQuestion, 
		TCHAR* szAnswerA, TCHAR* szAnswerB, TCHAR* szAnswerC, TCHAR* szAnswerD,
		int nRightAnswer);

	int AddSubject(SUBJECT_T &stSubject);
	int GetSubjectByID(int nID, SUBJECT_T &stSuject);
	int CheckAnswer(USER_ANSWER_T &stUserAnswer, SUBJECT_T *pstSubject = NULL);

	int AddSubject(SUBJECT_CST &stSubjectCS);
	int GetSubjectByID(int nID, SUBJECT_CST &stSubjectCS);
	int CheckAnswer(USER_ANSWER_CST &stUserAnswerCS);
	int CheckAnswer(USER_ANSWER_CST &stUserAnswerCS, SUBJECT_CST &stSubjectCS);

	int GetSubjectsCnt();

	int DeleteSubjectByID(int nID);

private:
	int CreateTable_Subject();

	//just for test
	int AddTestQuestion();
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

