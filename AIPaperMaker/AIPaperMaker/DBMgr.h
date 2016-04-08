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
	* �����û���Ϣ
	*1.�û���ɫ 2.�û��˺� 3.�û����� 4.�û�����
	*/
	int AddUser(USER_T &stUser);
	int DeleteUserByAccount(TCHAR* szAccount);
	int CheckUser(USER_T &stUser);
	int GetUserCnt();
	int GetUserByIdx(int nIdx, USER_T &stUser);
	int ModifyUserByAccount(USER_T &stUser);


	/*
	* @ subject ��Ŀ
	�� ������Ŀ��������ݿ����
	*/
	// ������
	int AddSubject(int nDifficultyDegree, int nQuestionType,
		TCHAR * szExaminationQuestion, 
		TCHAR* szAnswerA, TCHAR* szAnswerB, TCHAR* szAnswerC, TCHAR* szAnswerD,
		int nRightAnswer, int nChapterID);

	int AddSubject(SUBJECT_T &stSubject);

	// ͨ��ID�Ż�ȡ��Ŀ
	int GetSubjectByID(int nID, SUBJECT_T &stSuject);

	// ���𰸵÷�
	int CheckAnswer(USER_ANSWER_T &stUserAnswer, SUBJECT_T *pstSubject = NULL);

	int AddSubject(SUBJECT_CST &stSubjectCS);
	int GetSubjectByID(int nID, SUBJECT_CST &stSubjectCS);
	int CheckAnswer(USER_ANSWER_CST &stUserAnswerCS);
	int CheckAnswer(USER_ANSWER_CST &stUserAnswerCS, SUBJECT_CST &stSubjectCS);

	// ��ȡ������Ŀ����
	int GetSubjectsCnt();

	// ɾ���������Ŀ
	int DeleteSubjectByID(int nID);


	/*
	* chapter : �½�
	*/
	int AddChapter(TCHAR * szChapterName, TCHAR * szChapterAlias);
	int DeleteChapterByID(int nID);
	int GetChapterCnt();
	int GetChapterByID(int nID, TCHAR *szChapterName, TCHAR *szChapterAlias);

	/*
	* paper : �Ծ�
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
 * �ֶΣ�id, difficulty_degree, question_type, examination_question, answerA, answerB, answerC, answerD, right_answer
 * ���ͣ�int		int				int					varchar			varchar	 varchar  varchar  varchar   varchar
 *	
**/

