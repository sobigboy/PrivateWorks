#pragma once

#include "CommonDBA.h"

class CDBMgr
{
public:
	CDBMgr();
	virtual ~CDBMgr();

public:
	/*
	* @nDifficultyDegree : �Ѷ�ϵ��
	*/
	int AddSubject(/*int nID, */int nDifficultyDegree, int nQuestionType,
		TCHAR * szExaminationQuestion, 
		TCHAR* szAnswerA, TCHAR* szAnswerB, TCHAR* szAnswerC, TCHAR* szAnswerD,
		int nRightAnswer);

	int DeleteSubjectByID(int nID);

	int GetSubjectByID(int nID, int &nDifficultyDegree, int &nQuestionType,
		TCHAR * szExaminationQuestion,
		TCHAR* szAnswerA, TCHAR* szAnswerB, TCHAR* szAnswerC, TCHAR* szAnswerD,
		int &nRightAnswer);

private:
	int CreateTable_Subject();
};


/**
 * database design
 * 
 * table : subject
 *
 * �ֶΣ�id, difficulty_degree, question_type, examination_question, answerA, answerB, answerC, answerD, right_answer
 * ���ͣ�int		int				int					nchar
 *	
**/

