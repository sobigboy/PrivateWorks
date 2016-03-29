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
	* @ subject ��Ŀ
	�� ������Ŀ��������ݿ����
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


	/*
	* chapter : �½�
	*/
	int AddChapter(TCHAR * szChapterName, TCHAR * szChapterAlias);
	int DeleteChapter(int nID);
	int GetChapterCnt();
	int GetChapterByID(int nIdx, TCHAR *szChapterName, TCHAR *szChapterAlias);

	/*
	* paper : �Ծ�
	*/
	int AddPaper(TCHAR * szPaperName, int nSubjectCnt, TCHAR * szSubjectIDList);
	int DeletePaper(int nID);
	int GetPaperCnt();
	int GetPaperByID(int nIdx, TCHAR * szPaperName, int *pnSubjectCnt, TCHAR * szSubjectIDList);

private:
	int CreateTable_Subject();
	int CreateTable_User();
	int CreateTable_Chapter();

	//just for test
	int AddTestQuestion();
};

// check answer

/**
 * database design
 * 
 * table : subject
 *
 * �ֶΣ�id, difficulty_degree, question_type, examination_question, answerA, answerB, answerC, answerD, right_answer
 * ���ͣ�int		int				int					varchar			varchar	 varchar  varchar  varchar   varchar
 *	
**/

