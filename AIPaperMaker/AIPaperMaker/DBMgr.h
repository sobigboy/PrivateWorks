#pragma once

#include "CommonDBA.h"

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

	int DeleteSubjectByID(int nID);

	int GetSubjectByID(int nID, int &nDifficultyDegree, int &nQuestionType,
		TCHAR * szExaminationQuestion,
		TCHAR* szAnswerA, TCHAR* szAnswerB, TCHAR* szAnswerC, TCHAR* szAnswerD,
		int &nRightAnswer);
};

