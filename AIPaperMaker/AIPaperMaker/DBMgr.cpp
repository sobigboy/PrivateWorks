#include "stdafx.h"
#include "DBMgr.h"

#pragma comment(lib, "DBMgr/DBAccesser.lib")

CDBMgr::CDBMgr()
{
	CreateTable_Subject();
 	//AddTestQuestion();

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

int CDBMgr::AddSubject(SUBJECT_T &stSubject)
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
		stSubject.nDifficultyDegree, stSubject.nQuestionType, stSubject.szExaminationQuestion, 
		stSubject.szAnswerA, stSubject.szAnswerB, stSubject.szAnswerC, stSubject.szAnswerD, stSubject.nRightAnswer);

	nRet = mgr.ExcuteSQL(szSql);
	if(nRet != 0)
	{
		printf("ExcuteSQL(): exec add subject sql failed\n");
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

int CDBMgr::AddSubject(SUBJECT_CST &stSubjectCS)
{
	SUBJECT_T stSubject = { 0 };
	stSubject = stSubjectCS;

	return AddSubject(stSubject);
}

int CDBMgr::GetSubjectByID(int nID, SUBJECT_T &stSubject)
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
	
	assert(nRet <= 1);

	if (nRet == 1)
	{
		stSubject.nSubjectID = nID;
	}
	else
	{
		mgr.CloseDBA();
		return -1;
	}

	for(int i = 0; i < nRet; i++)
	{
		stSubject.nDifficultyDegree = mgr.GetFieldAsInt32(_T("difficulty_degree"));
		stSubject.nQuestionType = mgr.GetFieldAsInt32(_T("question_type"));
		stSubject.nRightAnswer = mgr.GetFieldAsInt32(_T("right_answer"));

		int nSizeInWords = sizeof(stSubject.szExaminationQuestion) / sizeof(stSubject.szExaminationQuestion[0]);

		mgr.GetFieldAsString(_T("examination_question"), stSubject.szExaminationQuestion, nSizeInWords);
		mgr.GetFieldAsString(_T("answerA"), stSubject.szAnswerA, nSizeInWords);
		mgr.GetFieldAsString(_T("answerB"), stSubject.szAnswerB, nSizeInWords);
		mgr.GetFieldAsString(_T("answerC"), stSubject.szAnswerC, nSizeInWords);
		mgr.GetFieldAsString(_T("answerD"), stSubject.szAnswerD, nSizeInWords);

	}

	mgr.CloseDBA();

	return nRet;
}

int CDBMgr::GetSubjectByID(int nID, SUBJECT_CST &stSubjectCS)
{
	int nRet = 0;
	SUBJECT_T stSubject = { 0 };
	
	nRet = GetSubjectByID(nID, stSubject);

	if (nRet < 0)
		return nRet;

	stSubjectCS.nSubjectID = stSubject.nSubjectID;
	stSubjectCS.nDifficultyDegree = stSubject.nDifficultyDegree;
	stSubjectCS.nQuestionType = stSubject.nQuestionType;
	stSubjectCS.szExaminationQuestion = stSubject.szExaminationQuestion;
	stSubjectCS.szAnswerA = stSubject.szAnswerA;
	stSubjectCS.szAnswerB = stSubject.szAnswerB;
	stSubjectCS.szAnswerC = stSubject.szAnswerC;
	stSubjectCS.szAnswerD = stSubject.szAnswerD;
	stSubjectCS.nRightAnswer = stSubject.nRightAnswer;
	return nRet;
}

int CDBMgr::CheckAnswer(USER_ANSWER_T &stUserAnswer, SUBJECT_T* pstSubject/* = NULL*/)
{
	SUBJECT_T stSubject = { 0 };
	int nScore = 0;

	if (!pstSubject)
		GetSubjectByID(stUserAnswer.nSubjectID, stSubject);
	else
		memcpy(&stSubject, pstSubject, sizeof(SUBJECT_T));

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

int CDBMgr::CheckAnswer(USER_ANSWER_CST &stUserAnswerCS)
{
	USER_ANSWER_T stUserAnswer = { 0 };
	stUserAnswer = stUserAnswerCS;

	return CheckAnswer(stUserAnswer);
}

int CDBMgr::CheckAnswer(USER_ANSWER_CST &stUserAnswerCS, SUBJECT_CST &stSubjectCS)
{
	USER_ANSWER_T stUserAnswer = { 0 };
	stUserAnswer = stUserAnswerCS;

	SUBJECT_T stSubject = { 0 };
	stSubject = stSubjectCS;

	return CheckAnswer(stUserAnswer, &stSubject);
}

int CDBMgr::DeleteSubjectByID(int nID)
{
	CComnDBAMgr mgr;
	int nRet = mgr.OpenDBA();
	if (nRet != 0)
	{
		printf("DeleteSubjectByID(): open db failed\n");
		return nRet;
	}

	TCHAR szSql[256] = { 0 };
	_stprintf_s(szSql, sizeof(szSql) / sizeof(szSql[0]),
		_T("delete  from subject where id=%d ;"), nID);

	nRet = mgr.ExcuteSQL(szSql);
	if (nRet != 0)
	{
		printf("ExcuteSQL(): delete subject sql failed\n");
	}

	mgr.CloseDBA();
	return nRet;
}

int CDBMgr::AddTestQuestion()
{
	SUBJECT_T subject = { 0 };

	subject.nDifficultyDegree = 1;
	subject.nQuestionType = 0;
	_stprintf_s(subject.szExaminationQuestion, MAX_SUBJECT_STRING_LEN, _T("%s"), _T("question : test question?"));
	_stprintf_s(subject.szAnswerA, MAX_SUBJECT_STRING_LEN, _T("%s"), _T("answer : a"));
	_stprintf_s(subject.szAnswerB, MAX_SUBJECT_STRING_LEN, _T("%s"), _T("answer : b"));
	_stprintf_s(subject.szAnswerC, MAX_SUBJECT_STRING_LEN, _T("%s"), _T("right answer : c"));
	_stprintf_s(subject.szAnswerD, MAX_SUBJECT_STRING_LEN, _T("%s"), _T("answer : d"));
	subject.nRightAnswer = 4;

	return AddSubject(subject);
}

int CDBMgr::GetSubjectsCnt()
{
	CComnDBAMgr mgr;
	int nRet = mgr.OpenDBA();
	if (nRet != 0)
	{
		printf("GetSubjectsCnt(): open db failed\n");
		return nRet;
	}

	TCHAR szSql[] = _T("select * from subject");

	mgr.InitSelectTask();
	nRet = mgr.SelectSQL(szSql);
	mgr.CloseDBA();

	return nRet;
}



