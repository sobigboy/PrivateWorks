// GDMProject.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "GDMProject.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Ψһ��Ӧ�ó������

CWinApp theApp;

using namespace std;



long Usage()
{
	InitializePrj();

	m_gdm.MoveTo(100, 100);
	Sleep(1000);
	m_gdm.RightClick();
	Sleep(1000);
	m_gdm.MoveR(10, 5);
	Sleep(1000);
	m_gdm.LeftClick();

	DestoryPrj();

	return 0;
}


int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	HMODULE hModule = ::GetModuleHandle(NULL);

	if (hModule != NULL)
	{
		// ��ʼ�� MFC ����ʧ��ʱ��ʾ����
		if (!AfxWinInit(hModule, NULL, ::GetCommandLine(), 0))
		{
			// TODO:  ���Ĵ�������Է���������Ҫ
			_tprintf(_T("����:  MFC ��ʼ��ʧ��\n"));
			nRetCode = 1;
		}
		else
		{
			Usage();
		}
	}
	else
	{
		// TODO:  ���Ĵ�������Է���������Ҫ
		_tprintf(_T("����:  GetModuleHandle ʧ��\n"));
		nRetCode = 1;
	}

	return nRetCode;
}

long InitializePrj()
{
	long nRet = 0;
	nRet = InitDmDll(&m_gdm);

	return nRet;
}

long DestoryPrj()
{
	long nRet = 0;
	nRet = UnInitDmDll(&m_gdm);

	return nRet;
}
