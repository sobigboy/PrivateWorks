// GDMProject.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "GDMProject.h"
#include "Logger.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 唯一的应用程序对象

CWinApp theApp;

using namespace std;

#pragma comment(lib, "SDK/Logger.lib")

long Usage()
{
	InitializePrj();
	int nRet = m_gdm.EnableRealMouse(1, 20, 10);

	if (nRet != 0)
	{
		nRet= m_gdm.GetLastError();
	}
	m_gdm.MoveTo(100, 100);
	Sleep(1000);
	m_gdm.RightClick();
	Sleep(1000);
	m_gdm.MoveR(10, 5);
	Sleep(1000);
	m_gdm.LeftClick();

	DestoryPrj();

	system("pause");

	return 0;
}












long InitializePrj()
{
	long nRet = 0;

	nRet = InitDmDll(&m_gdm);

	CLogger::GetInstance()->Initialize("GDMPrjLog");
	CLogger::GetInstance()->AddLog(nRet, "Initialize prj. Start");
	return nRet;
}

long DestoryPrj()
{
	long nRet = 0;
	nRet = UnInitDmDll(&m_gdm);

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
		// 初始化 MFC 并在失败时显示错误
		if (!AfxWinInit(hModule, NULL, ::GetCommandLine(), 0))
		{
			// TODO:  更改错误代码以符合您的需要
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
		// TODO:  更改错误代码以符合您的需要
		_tprintf(_T("错误:  GetModuleHandle 失败\n"));
		nRetCode = 1;
	}

	return nRetCode;
}