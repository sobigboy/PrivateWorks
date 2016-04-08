#pragma once

#include "CommonDBA.h"
#include "BasedataDefine.h"

class CDBMgr
{
public:
	CDBMgr();
	virtual ~CDBMgr();

public:

	int InitializeAllTable();

	/*
	* @ user
	* 关于用户信息
	*1.用户角色 2.用户账号 3.用户姓名 4.用户密码
	*/
	int AddUser(USER_T &stUser);
	int DeleteUserByAccount(TCHAR* szAccount);
	int CheckUser(USER_T &stUser);
	int GetUserCnt();
	int GetUserByIdx(int nIdx, USER_T &stUser);
	int ModifyUserByAccount(USER_T &stUser);


	/*
	* @ subject 题目
	＊ 关于题目的相关数据库操作
	*/
	// 添加题库
	int AddSubject(int nDifficultyDegree, int nQuestionType,
		TCHAR * szExaminationQuestion, 
		TCHAR* szAnswerA, TCHAR* szAnswerB, TCHAR* szAnswerC, TCHAR* szAnswerD,
		int nRightAnswer, int nChapterID);

	int AddSubject(SUBJECT_T &stSubject);

	// 通过ID号获取题目
	int GetSubjectByID(int nID, SUBJECT_T &stSuject);

	// 检查答案得分
	int CheckAnswer(USER_ANSWER_T &stUserAnswer, SUBJECT_T *pstSubject = NULL);

	int AddSubject(SUBJECT_CST &stSubjectCS);
	int GetSubjectByID(int nID, SUBJECT_CST &stSubjectCS);
	int CheckAnswer(USER_ANSWER_CST &stUserAnswerCS);
	int CheckAnswer(USER_ANSWER_CST &stUserAnswerCS, SUBJECT_CST &stSubjectCS);

	// 获取题库的题目数量
	int GetSubjectsCnt();

	// 删除题库中题目
	int DeleteSubjectByID(int nID);


	/*
	* chapter : 章节
	*/
	int AddChapter(TCHAR * szChapterName, TCHAR * szChapterAlias);
	int DeleteChapterByID(int nID);
	int GetChapterCnt();
	int GetChapterByID(int nID, TCHAR *szChapterName, TCHAR *szChapterAlias);

	/*
	* paper : 试卷
	*/
	int AddPaper(TCHAR * szPaperName, int nSubjectCnt, TCHAR * szSubjectIDList);
	int DeletePaperByID(int nID);
	int GetPaperCnt();
	int GetPaperByID(int nID, TCHAR * szPaperName, int *pnSubjectCnt, TCHAR * szSubjectIDList);

private:
	int CreateTable_Subject();
	int CreateTable_User();
	int CreateTable_Chapter();
	int CreateTable_Paper();

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

