// GDMProject.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "GDMProject.h"
#include "Logger.h"
#include "Gdm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 唯一的应用程序对象

CWinApp theApp;

using namespace std;
// #pragma comment(lib, "3rd/logger/Logger.lib")

long Usage()
{
	CGdmApp* pApp = CGdmApp::GetInstance();
	m_gdm = pApp->GetDm();

	m_gdm->MoveTo(100, 100);
	Sleep(1000);
// 	m_gdm->RightClick();
	Sleep(1000);
	m_gdm->MoveR(10, 5);
	Sleep(1000);
	m_gdm->LeftClick();



	CGdmApp::DestroyInstance();
// 	pApp->DestroyInstance();

	system("pause");
	return 0;
}

long InitializePrj()
{
	long nRet = 0;
// 	nRet = InitDmDll(&m_gdm);

	CLogger::GetInstance()->Initialize("GDMPrjLog");
	CLogger::GetInstance()->AddLog(nRet, "Initialize prj. Start!");
	return nRet;
}

long DestoryPrj()
{
	long nRet = 0;
//  	nRet = UnInitDmDll(&m_gdm);

	CLogger::GetInstance()->AddLog(nRet, "UnInitialize prj. Exit!");
	CLogger::GetInstance()->UnInitialize();
	CLogger::GetInstance()->DestroyInstance();
	return nRet;
}

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	HMODULE hModule = ::GetModuleHandle(NULL);

	if (hModule != NULL)
	{
		if (!AfxWinInit(hModule, NULL, ::GetCommandLine(), 0))
		{
			_tprintf(_T("错误:  MFC 初始化失败\n"));
			nRetCode = 1;
		}
		else
		{
			Usage();
		}
	}
	else
	{
		_tprintf(_T("错误:  GetModuleHandle 失败\n"));
		nRetCode = 1;
	}

	return nRetCode;
}