#include "stdafx.h"
#include "DBMgr.h"

#pragma comment(lib, "DBMgr/DBAccesser.lib")

CDBMgr::CDBMgr()
{
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

	//初始化用户数据库
	CDBMgr dbMgr;
	if (dbMgr.GetUserCnt() == 0)
	{
		USER_T user;
		user.eRole = role_admin;
		_stprintf_s(user.szAccount, sizeof(user.szAccount) / sizeof(user.szAccount[0]), _T("%s"), _T("admin"));
		_stprintf_s(user.szAlias, sizeof(user.szAlias) / sizeof(user.szAlias[0]), _T("%s"), _T("管理员"));
		_stprintf_s(user.szPasswd, sizeof(user.szPasswd) / sizeof(user.szPasswd[0]), _T("%s"), _T("admin"));
		dbMgr.AddUser(user);
	}

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


	//初始化章节数据库
	CDBMgr dbMgr;
	if (dbMgr.GetChapterCnt() == 0)
	{
		dbMgr.AddChapter(_T("第一章"), _T("Chapter 1"));
		dbMgr.AddChapter(_T("第二章"), _T("Chapter 2"));
		dbMgr.AddChapter(_T("第三章"), _T("Chapter 3"));
		dbMgr.AddChapter(_T("第四章"), _T("Chapter 4"));
		dbMgr.AddChapter(_T("第五章"), _T("Chapter 5"));
		dbMgr.AddChapter(_T("第六章"), _T("Chapter 6"));
		dbMgr.AddChapter(_T("第七章"), _T("Chapter 7"));
		dbMgr.AddChapter(_T("第八章"), _T("Chapter 8"));
	}

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
		  `chapter_id` int(2) NOT NULL DEFAULT 1,\
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

	if (nRet <= 0)
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
		_T("INSERT into chapter(name, alias) VALUES('%s', '%s');"), szChapterName, szChapterAlias);

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

int CDBMgr::GetChapterByID(int nID, TCHAR *szChapterName, TCHAR *szChapterAlias)
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
		_T("select * from chapter where id=%d ;"), nID);

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

int CDBMgr::GetPaperByID(int nID, TCHAR * szPaperName, int *pnSubjectCnt, TCHAR * szSubjectIDList)
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
		_T("select * from paper where id=%d ;"), nID);

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

int CDBMgr::AddUser(USER_T &stUser)
{
	CComnDBAMgr mgr;
	int nRet = mgr.OpenDBA();
	if (nRet != 0)
	{
		printf("AddUser(): open db failed\n");
		return nRet;
	}

	TCHAR szSql[1024] = { 0 };

	_stprintf_s(szSql, sizeof(szSql) / sizeof(szSql[0]),
		_T("INSERT into user(account, pswd, alias, role) VALUES('%s', '%s', '%s', %d);"), stUser.szAccount, stUser.szPasswd, stUser.szAlias, (int)stUser.eRole);

	nRet = mgr.ExcuteSQL(szSql);
	if (nRet != 0)
	{
		printf("ExcuteSQL(): exec add user sql failed\n");
	}

	mgr.CloseDBA();

	return nRet;
}

int CDBMgr::DeleteUserByAccount(TCHAR* szAccount)
{
	CComnDBAMgr mgr;
	int nRet = mgr.OpenDBA();
	if (nRet != 0)
	{
		printf("DeleteUserByAccount(): open db failed\n");
		return nRet;
	}

	TCHAR szSql[256] = { 0 };
	_stprintf_s(szSql, sizeof(szSql) / sizeof(szSql[0]),
		_T("delete  from user where account='%s' ;"), szAccount);

	nRet = mgr.ExcuteSQL(szSql);
	if (nRet != 0)
	{
		printf("ExcuteSQL(): delete user sql failed\n");
	}

	mgr.CloseDBA();

	return nRet;
}

int CDBMgr::CheckUser(USER_T &stUser)
{
	CComnDBAMgr mgr;
	TCHAR szPswdInDB[MAX_USER_ACCOUNT_LEN] = { 0 };
	int nRet = mgr.OpenDBA();
	if (nRet != 0)
	{
		printf("CheckUser(): open db failed\n");
		return nRet;
	}

	TCHAR szSql[128] = { 0 };
	_stprintf_s(szSql, sizeof(szSql) / sizeof(szSql[0]),
		_T("select * from user where account='%s' ;"), stUser.szAccount);

	mgr.InitSelectTask();
	nRet = mgr.SelectSQL(szSql);
	mgr.MoveToFirst();

	if (nRet == 1)
	{
		int nSizeInWords = sizeof(stUser.szAlias) / sizeof(stUser.szAlias[0]);
		stUser.eRole = (E_USER_ROLE)mgr.GetFieldAsInt32(_T("role"));
		mgr.GetFieldAsString(_T("alias"), stUser.szAlias, nSizeInWords);
		mgr.GetFieldAsString(_T("pswd"), szPswdInDB, nSizeInWords);
	}
	else
	{
		//用户名不存在，返回0
		mgr.CloseDBA();
		return nRet;
	}

	//校验密码，失败，返回-1
	if (StrCmp(szPswdInDB, stUser.szPasswd) != 0)
	{
		nRet = -1;
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

int CDBMgr::GetUserCnt()
{
	CComnDBAMgr mgr;
	int nRet = mgr.OpenDBA();
	if (nRet != 0)
	{
		printf("GetUserCnt(): open db failed\n");
		return nRet;
	}

	TCHAR szSql[] = _T("select * from user");

	mgr.InitSelectTask();
	nRet = mgr.SelectSQL(szSql);
	mgr.CloseDBA();

	return nRet;
}

int CDBMgr::GetUserByIdx(int nIdx, USER_T &stUser)
{
	CComnDBAMgr mgr;
	int nRet = mgr.OpenDBA();
	if (nRet != 0)
	{
		printf("GetUserByIdx(): open db failed\n");
		return nRet;
	}

	TCHAR szSql[] = _T("select * from user");
	mgr.InitSelectTask();
	nRet = mgr.SelectSQL(szSql);

	mgr.MoveToFirst();
	for (int i = 0; i < nRet; i++)
	{
		if (i < nIdx)
		{
			mgr.MoveToNext();
		}
		else
		{
			//account, pswd, alias, role
			tstring str;
			mgr.GetFieldAsString(_T("account"), str);
			StrCpy(stUser.szAccount, str.c_str());

			mgr.GetFieldAsString(_T("pswd"), str);
			StrCpy(stUser.szPasswd, str.c_str());

			mgr.GetFieldAsString(_T("alias"), str);
			StrCpy(stUser.szAlias, str.c_str());

			stUser.eRole = (E_USER_ROLE)mgr.GetFieldAsInt32(_T("role"));
			break;
		}
	}

	mgr.CloseDBA();
	return nRet;
}

int CDBMgr::ModifyUserByAccount(USER_T &stUser)
{
	CComnDBAMgr mgr;
	int nRet = mgr.OpenDBA();
	if (nRet != 0)
	{
		printf("ModifyUserByAccount(): open db failed\n");
		return nRet;
	}
	//account, pswd, alias, role
	TCHAR szSql[256] = { 0 };
	_stprintf_s(szSql, sizeof(szSql) / sizeof(szSql[0]),
		_T("update user set pswd='%s', alias='%s', role=%d where account='%s' ;"), stUser.szPasswd, stUser.szAlias, (int)stUser.eRole, stUser.szAccount);

	nRet = mgr.ExcuteSQL(szSql);
	if (nRet != 0)
	{
		printf("ExcuteSQL(): modify user sql failed\n");
	}

	mgr.CloseDBA();

	return nRet;
}

int CDBMgr::InitializeAllTable()
{
	CreateTable_Subject();
	CreateTable_User();
	CreateTable_Chapter();
	CreateTable_Paper();
	//AddTestQuestion();

	return 0;
}


