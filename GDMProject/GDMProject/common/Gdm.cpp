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

// 	// 设置全局目录
// 	nRet = m_pdm->SetPath(GetGlobalPath().c_str());
// 	if (nRet != 1)
// 	{
// 		printf("设置全局路径失败。\n");
// 		CoUninitialize();
// 		return 0;
// 	}

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
