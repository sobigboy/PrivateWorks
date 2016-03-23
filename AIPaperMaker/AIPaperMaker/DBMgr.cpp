#include "stdafx.h"
#include "DBMgr.h"

#pragma comment(lib, "DBMgr/DBAccesser.lib")

CDBMgr::CDBMgr()
{
	CComnDBAMgr mgr;
	mgr.OpenDBA();

	mgr.CloseDBA();
}


CDBMgr::~CDBMgr()
{
}
