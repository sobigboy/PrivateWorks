#pragma once

#include "tstring.h"
#include <vector>
using namespace std;

#pragma warning( disable : 4251 )

#define MAX_LOG_CNT (100)

typedef struct _log_item_t
{
	SYSTEMTIME	timeLog;
	DWORD		dwError;
	tstring		strLog;

}Log_Item;

#define	WM_LOGGER_LOGCHANGED		(WM_USER+1023)

#ifdef GLOGGER_EXPORTS
#define LOGGER_API __declspec(dllexport)
#else
#define LOGGER_API __declspec(dllimport)
#endif

class LOGGER_API CLogger
{
public:
	CLogger(void);
	virtual ~CLogger(void);

protected:
	HWND				m_hwndNotify;
	int					m_nMaxLogCnt;
	int					m_nCurLogIdx;
	vector<Log_Item>		m_arrayLog;
	CRITICAL_SECTION	m_csLogArray;


	FILE					*m_pLogFile;
	tstring				m_strFolderName;
	BOOL				m_bLog;//是否记录日志文件。用户可以配置

private:
	tstring GetModulePath();
	HRESULT OpenLogFile();
	HRESULT CloseLogFile();
	HRESULT CreateLogFile(const tstring &strLogFileFullName);

protected:
	static CLogger *m_pLogger;

public:
	static CLogger *GetInstance();
	static void DestroyInstance();

	HRESULT Initialize(tstring strFolderName);
	HRESULT UnInitialize();
	void SetNotifyWnd(HWND hwnd){m_hwndNotify = hwnd;};
	void SetLogFlag(BOOL bLog){m_bLog = bLog;};

	HRESULT AddLog(DWORD dwError, const tstring &strLog);
	BOOL GetLastestLog(Log_Item *pLogItem);
	
	//! 测试用
	HRESULT DelLogFile();

protected://reserveds
	HRESULT GetLogCnt();
	Log_Item *GetLogByIdx(int nIdx);

};
