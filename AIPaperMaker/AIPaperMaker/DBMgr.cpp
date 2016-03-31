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

int CDBMgr::CreateTable_User()
{
	CComnDBAMgr mgr;
	int nRet = mgr.OpenDBA();
	if(nRet != 0)
	{
		printf("CreateTable_User(): open db failed\n");
		return nRet;
	}

	TCHAR szSql[] = _T("CREATE TABLE `user` (\
		  `id` INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, \
		  `account` varchar(128) NOT NULL DEFAULT '',\
		  `pswd` varchar(128) NOT NULL DEFAULT '',\
		  `alias` varchar(128) NOT NULL DEFAULT '',\
		  `role` int(2) NOT NULL DEFAULT 0,\
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

int CDBMgr::CreateTable_Chapter()
{
	CComnDBAMgr mgr;
	int nRet = mgr.OpenDBA();
	if(nRet != 0)
	{
		printf("CreateTable_Chapter(): open db failed\n");
		return nRet;
	}

	TCHAR szSql[] = _T("CREATE TABLE `chapter` (\
		  `id` INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, \
		  `name` varchar(128) NOT NULL DEFAULT '',\
		  `alias` varchar(128) NOT NULL DEFAULT '',\
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
		  `chapter_id` int(2) NOT NULL DEFAULT 0,\
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

int CDBMgr::CreateTable_Paper()
{
	CComnDBAMgr mgr;
	int nRet = mgr.OpenDBA();
	if(nRet != 0)
	{
		printf("CreateTable_Paper(): open db failed\n");
		return nRet;
	}

	TCHAR szSql[] = _T("CREATE TABLE `paper` (\
		  `id` INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, \
		  `paper_name` varchar(128) NOT NULL DEFAULT '',\
		  `subject_cnt` int(3) NOT NULL DEFAULT 0,\
		  `subject_id_list` varchar(1024) NOT NULL DEFAULT '',\
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
		_T("INSERT into subject(difficulty_degree, question_type, examination_question,answerA, answerB, answerC, answerD, right_answer, chapter_id) VALUES(%d, %d, '%s', '%s', '%s', '%s', '%s', %d, %d);"),
		stSubject.nDifficultyDegree, stSubject.nQuestionType, stSubject.szExaminationQuestion, 
		stSubject.szAnswerA, stSubject.szAnswerB, stSubject.szAnswerC, stSubject.szAnswerD, stSubject.nRightAnswer, stSubject.nChapterID);

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
		int nRightAnswer, int nChapterID)
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
		_T("INSERT into subject(difficulty_degree, question_type, examination_question,answerA, answerB, answerC, answerD, right_answer, chapter_id) VALUES(%d, %d, '%s', '%s', '%s', '%s', '%s', %d, %d);"),
		nDifficultyDegree, nQuestionType, szExaminationQuestion, szAnswerA, szAnswerB, szAnswerC, szAnswerD, nRightAnswer, nChapterID);

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
		stSubject.nChapterID = mgr.GetFieldAsInt32(_T("chapter_id"));

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
	stSubjectCS.nChapterID = stSubject.nChapterID;
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

int CDBMgr::AddChapter(TCHAR * szChapterName, TCHAR * szChapterAlias)
{
	CComnDBAMgr mgr;
	int nRet = mgr.OpenDBA();
	if (nRet != 0)
	{
		printf("AddChapter(): open db failed\n");
		return nRet;
	}

	TCHAR szSql[1024] = { 0 };

	_stprintf_s(szSql, sizeof(szSql) / sizeof(szSql[0]),
		_T("INSERT into chapter(name, alias) VALUES(%d, %d, '%s', '%s');"), szChapterName, szChapterAlias);

	nRet = mgr.ExcuteSQL(szSql);
	if (nRet != 0)
	{
		printf("ExcuteSQL(): exec add subject sql failed\n");
	}

	mgr.CloseDBA();

	return nRet;
}

int CDBMgr::DeleteChapterByID(int nID)
{
	CComnDBAMgr mgr;
	int nRet = mgr.OpenDBA();
	if (nRet != 0)
	{
		printf("DeleteChapter(): open db failed\n");
		return nRet;
	}

	TCHAR szSql[256] = { 0 };
	_stprintf_s(szSql, sizeof(szSql) / sizeof(szSql[0]),
		_T("delete  from chapter where id=%d ;"), nID);

	nRet = mgr.ExcuteSQL(szSql);
	if (nRet != 0)
	{
		printf("ExcuteSQL(): delete chapter sql failed\n");
	}

	mgr.CloseDBA();

	return nRet;
}

int CDBMgr::GetChapterCnt()
{
	CComnDBAMgr mgr;
	int nRet = mgr.OpenDBA();
	if (nRet != 0)
	{
		printf("GetChapterCnt(): open db failed\n");
		return nRet;
	}

	TCHAR szSql[] = _T("select * from chapter");

	mgr.InitSelectTask();
	nRet = mgr.SelectSQL(szSql);
	mgr.CloseDBA();

	return nRet;
}

int CDBMgr::GetChapterByID(int nIdx, TCHAR *szChapterName, TCHAR *szChapterAlias)
{
	CComnDBAMgr mgr;
	int nRet = mgr.OpenDBA();
	if (nRet != 0)
	{
		printf("GetSubjectByID(): open db failed\n");
		return nRet;
	}

	TCHAR szSql[256] = { 0 };
	_stprintf_s(szSql, sizeof(szSql) / sizeof(szSql[0]),
		_T("select * from subject where id=%d ;"), nIdx);

	mgr.InitSelectTask();
	nRet = mgr.SelectSQL(szSql);
	mgr.MoveToFirst();

	assert(nRet <= 1);

	if (nRet == 1)
	{
		int nSizeInWords = 128;
		mgr.GetFieldAsString(_T("name"), szChapterName, nSizeInWords);
		mgr.GetFieldAsString(_T("alias"), szChapterAlias, nSizeInWords);
	}

	mgr.CloseDBA();

	return nRet;
}


int CDBMgr::AddPaper(TCHAR * szPaperName, int nSubjectCnt, TCHAR * szSubjectIDList)
{
	CComnDBAMgr mgr;
	int nRet = mgr.OpenDBA();
	if (nRet != 0)
	{
		printf("AddPaper(): open db failed\n");
		return nRet;
	}

	TCHAR szSql[1024] = { 0 };
	_stprintf_s(szSql, sizeof(szSql) / sizeof(szSql[0]),
		_T("INSERT into paper(paper_name, subject_cnt, subject_id_list) VALUES('%s', %d, '%s');"), szPaperName, nSubjectCnt, szSubjectIDList);

	nRet = mgr.ExcuteSQL(szSql);
	if (nRet != 0)
	{
		printf("ExcuteSQL(): exec add paper sql failed\n");
	}

	mgr.CloseDBA();

	return nRet;
}

int CDBMgr::DeletePaperByID(int nID)
{
	CComnDBAMgr mgr;
	int nRet = mgr.OpenDBA();
	if (nRet != 0)
	{
		printf("DeleteChapter(): open db failed\n");
		return nRet;
	}

	TCHAR szSql[256] = { 0 };
	_stprintf_s(szSql, sizeof(szSql) / sizeof(szSql[0]),
		_T("delete  from paper where id=%d ;"), nID);

	nRet = mgr.ExcuteSQL(szSql);
	if (nRet != 0)
	{
		printf("ExcuteSQL(): delete paper sql failed\n");
	}

	mgr.CloseDBA();

	return nRet;
}

int CDBMgr::GetPaperCnt()
{
	CComnDBAMgr mgr;
	int nRet = mgr.OpenDBA();
	if (nRet != 0)
	{
		printf("GetPaperCnt(): open db failed\n");
		return nRet;
	}

	TCHAR szSql[] = _T("select * from paper");

	mgr.InitSelectTask();
	nRet = mgr.SelectSQL(szSql);
	mgr.CloseDBA();

	return nRet;
}

int CDBMgr::GetPaperByID(int nIdx, TCHAR * szPaperName, int *pnSubjectCnt, TCHAR * szSubjectIDList)
{
	CComnDBAMgr mgr;
	int nRet = mgr.OpenDBA();
	if (nRet != 0)
	{
		printf("GetPaperByID(): open db failed\n");
		return nRet;
	}

	TCHAR szSql[256] = { 0 };
	_stprintf_s(szSql, sizeof(szSql) / sizeof(szSql[0]),
		_T("select * from paper where id=%d ;"), nIdx);

	mgr.InitSelectTask();
	nRet = mgr.SelectSQL(szSql);
	mgr.MoveToFirst();

	assert(nRet <= 1);

	if (nRet == 1)
	{
		int nSizeInWords = 128;
		*pnSubjectCnt = mgr.GetFieldAsInt32(_T("subject_cnt"));
		mgr.GetFieldAsString(_T("paper_name"), szPaperName, nSizeInWords);
		mgr.GetFieldAsString(_T("subject_id_list"), szSubjectIDList, nSizeInWords);
	}

	mgr.CloseDBA();

	return nRet;
}




////
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
