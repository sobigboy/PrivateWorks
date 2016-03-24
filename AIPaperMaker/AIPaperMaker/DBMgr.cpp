#include "stdafx.h"
#include "DBMgr.h"

#pragma comment(lib, "DBMgr/DBAccesser.lib")

CDBMgr::CDBMgr()
{
	CreateTable_Subject();
}

CDBMgr::~CDBMgr()
{
}

int CDBMgr::CreateTable_Subject()
{
	CComnDBAMgr mgr;
	int nRet = mgr.OpenDBA();
	if(nRet != 0)
	{
		printf("CreateTable_Subject(): open db failed\n");
		return nRet;
	}

	TCHAR szSql[] = _T("CREATE TABLE `subject` (\
		  `id` INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, \
		  `difficulty_degree` int(2) NOT NULL DEFAULT 0,\
		  `question_type` int(2) NOT NULL DEFAULT 0,\
		  `examination_question` varchar(4096) NOT NULL DEFAULT '',\
		  `answerA` varchar(4096) NOT NULL DEFAULT '',\
		  `answerB` varchar(4096) NOT NULL DEFAULT '',\
		  `answerC` varchar(4096) NOT NULL DEFAULT '',\
		  `answerD` varchar(4096) NOT NULL DEFAULT '',\
		  `right_answer` int(2) NOT NULL DEFAULT 0,\
		  `timestamp` datetime DEFAULT (datetime('now', 'localtime'))\
		  );");

	nRet = mgr.ExcuteSQL(szSql);
	if(nRet != 0)
	{
		printf("ExcuteSQL(): exec create table sql failed\n");
	}

	mgr.CloseDBA();

	return nRet;
}

int CDBMgr::AddSubject(int nDifficultyDegree, int nQuestionType,
		TCHAR * szExaminationQuestion, 
		TCHAR* szAnswerA, TCHAR* szAnswerB, TCHAR* szAnswerC, TCHAR* szAnswerD,
		int nRightAnswer)
{
	CComnDBAMgr mgr;
	int nRet = mgr.OpenDBA();
	if(nRet != 0)
	{
		printf("AddSubject(): open db failed\n");
		return nRet;
	}

	TCHAR szSql[1024] = { 0 };
	
	_stprintf_s(szSql, sizeof(szSql) / sizeof(szSql[0]),
		_T("INSERT into subject(difficulty_degree, question_type, examination_question,answerA, answerB, answerC, answerD, right_answer) VALUES(%d, %d, '%s', '%s', '%s', '%s', '%s', %d);"),
		nDifficultyDegree, nQuestionType, szExaminationQuestion, szAnswerA, szAnswerB, szAnswerC, szAnswerD, nRightAnswer);

	nRet = mgr.ExcuteSQL(szSql);
	if(nRet != 0)
	{
		printf("ExcuteSQL(): exec add subject sql failed\n");
	}

	mgr.CloseDBA();

	return nRet;
}

int CDBMgr::GetSubjectByID(int nID, SUBJECT_T &stSuject)
{
	CComnDBAMgr mgr;
	int nRet = mgr.OpenDBA();
	if(nRet != 0)
	{
		printf("GetSubjectByID(): open db failed\n");
		return nRet;
	}

	TCHAR szSql[256] = { 0 };
	_stprintf_s(szSql, sizeof(szSql) / sizeof(szSql[0]),
		_T("select * from subject where id=%d ;"), nID);

	mgr.InitSelectTask();
	nRet = mgr.SelectSQL(szSql);
	mgr.MoveToFirst();

	assert(nRet == 1);

	stSuject.nSubjectID = nID;

	for(int i = 0; i < nRet; i++)
	{
		stSuject.nDifficultyDegree = mgr.GetFieldAsInt32(_T("difficulty_degree"));
		stSuject.nQuestionType = mgr.GetFieldAsInt32(_T("question_type"));
		stSuject.nRightAnswer = mgr.GetFieldAsInt32(_T("right_answer"));

		int nSizeInWords = sizeof(stSuject.szExaminationQuestion) / sizeof(stSuject.szExaminationQuestion[0]);

		mgr.GetFieldAsString(_T("examination_question"), stSuject.szExaminationQuestion, nSizeInWords);
		mgr.GetFieldAsString(_T("answerA"), stSuject.szAnswerA, nSizeInWords);
		mgr.GetFieldAsString(_T("answerB"), stSuject.szAnswerB, nSizeInWords);
		mgr.GetFieldAsString(_T("answerC"), stSuject.szAnswerC, nSizeInWords);
		mgr.GetFieldAsString(_T("answerD"), stSuject.szAnswerD, nSizeInWords);

	}

	mgr.CloseDBA();

	return nRet;
}

int CDBMgr::CheckAnswer(USER_ANSWER_T &stUserAnswer)
{
	SUBJECT_T stSubject = { 0 };
	int nScore = 0;

	GetSubjectByID(stUserAnswer.nSubjectID, stSubject);

	//assert(stUserAnswer.nQuestionType == stSubject.nQuestionType);

	if(stSubject.nQuestionType == QUESTION_TYPE_SELECTION)
	{
		if (stUserAnswer.nUserSelection == stSubject.nRightAnswer)
			nScore = 4;
		else
			nScore = 0;
	}
	else if(stSubject.nQuestionType == QUESTION_TYPE_FILL)
	{
		//字符串比较 计算得分
		if (StrCmp(stSubject.szAnswerA, stUserAnswer.szUserAnswerA) == 0)
			nScore++;
		if (StrCmp(stSubject.szAnswerB, stUserAnswer.szUserAnswerB) == 0)
			nScore++;
		if (StrCmp(stSubject.szAnswerC, stUserAnswer.szUserAnswerC) == 0)
			nScore++;
		if (StrCmp(stSubject.szAnswerD, stUserAnswer.szUserAnswerD) == 0)
			nScore++;
	}
	else
	{
		nScore = -1;
	}

	return nScore;
}



