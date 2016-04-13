#include "stdafx.h"
#include "Gdm.h"

CGdmApp *CGdmApp::m_pGdmApp = NULL;


CGdmApp::CGdmApp()
{
	m_pdm = NULL;
}

CGdmApp::~CGdmApp()
{
}

CGdmApp * CGdmApp::GetInstance()
{
	if (NULL == m_pGdmApp)
	{
		m_pGdmApp = new CGdmApp;
		m_pGdmApp->InitializeDm();
	}

	return m_pGdmApp;
}

void CGdmApp::DestroyInstance()
{
	if (m_pGdmApp)
	{
		m_pGdmApp->UnInitializeDm();
		delete(m_pGdmApp);
		m_pGdmApp = NULL;
	}
}

long CGdmApp::InitializeDm()
{
	if (m_pdm)
		return 1;

	CoInitialize(NULL);
	CLSID clsid;
	HRESULT hr = CLSIDFromProgID(OLESTR("dm.dmsoft"), &clsid);
	if (FAILED(hr))
	{
		printf("调用方法 [CLSIDFromProgID] 失败!\n");
		CoUninitialize();
		return 0;
	}
	hr = CoCreateInstance(clsid, NULL, CLSCTX_INPROC_SERVER, __uuidof(Idmsoft), (LPVOID*)&m_pdm);
	if (FAILED(hr))
	{
		printf("调用方法 [CoCreateInstance] 失败!\n");
		CoUninitialize();
		return 0;
	}

	// 获取大漠插件版本
	std::string strVersion = m_pdm->Ver();
	printf("当前大漠插件版本为: %s\n", strVersion.c_str());


	// 设置全局目录
	int nRet = 0;
	nRet = m_pdm->SetPath(GetGlobalPath((long)e_rgame_mhxy).c_str());
	if (nRet != 1)
	{
		printf("设置全局路径失败。\n");
		CoUninitialize();
		return 0;
	}

	// 获取注册码
	std::string strRegCode = m_pdm->ReadIni("大漠注册码", "RegCode", "config.ini");

	// 注册大漠插件
	nRet = dm->Reg(strRegCode.c_str(), "");
	if (nRet != 1)
	{
		printf("注册失败，错误码: %d。\n", nRet);
		CoUninitialize();
		return 0;
	}

	// 设置字库
	nRet = dm->SetDict(IDF_HAN_SMALL, TXF_HAN_SMALL);
	nRet = dm->SetDict(IDF_HAN_LARGE, TXF_HAN_LARGE);
	nRet = dm->SetDict(IDF_ABC_SMALL, TXF_ABC_SMALL);
	nRet = dm->SetDict(IDF_OTHER, TXF_OTHER);
	if (nRet != 1)
	{
		printf("设置字库失败。\n");
		CoUninitialize();
		return 0;
	}


	return 0;
}

long CGdmApp::UnInitializeDm()
{
	CoUninitialize();

	return 0;
}

Idmsoft* CGdmApp::GetDm()
{
	return m_pdm;
}

std::string GetGlobalPath(long lGameID)
{
	char szPath[MAX_PATH] = { 0 };
	::GetModuleFileNameA(NULL, szPath, MAX_PATH);
	std::string strSubDir;
	switch ((E_RGAME)lGameID)
	{
	case e_rgame_mhxy:
		strSubDir = "\\file\\MHXY";
		break;
	default:
		assert(0);
		break;
	}

	::PathAppendA(szPath, strSubDir.c_str());
	return szPath;
}