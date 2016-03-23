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

	TCHAR szSql[] = _T("CREATE TABLE [subject] (\
		  [id] int(10), \
		  [difficulty_degree] int(2) NOT NULL DEFAULT 0,\
		  [question_type] int(2) NOT NULL DEFAULT 0,\
		  [examination_question] char(4096) NOT NULL DEFAULT '',\
		  [answerA] char(4096) NOT NULL DEFAULT '',\
		  [answerA] char(4096) NOT NULL DEFAULT '',\
		  [answerA] char(4096) NOT NULL DEFAULT '',\
		  [answerA] char(4096) NOT NULL DEFAULT '',\
		  [right_answer] int(2) NOT NULL DEFAULT 0,\
		  [timestamp] datetime DEFAULT (datetime('now', 'localtime')), \
		  CONSTRAINT [sqlite_autoindex_alarm_1] PRIMARY KEY ([id]));");

	nRet = mgr.ExcuteSQL(szSql);


	mgr.CloseDBA();

	return nRet;
}