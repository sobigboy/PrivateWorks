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
	}

	if(1 !=	m_pGdmApp->InitializeDm())
	{
		DestroyInstance();
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
	int nRet = 0;
	if (m_pdm)
		return 1;

	WinExec("regsvr32 dm.dll /s", SW_HIDE);
	CoInitialize(NULL);
	CLSID clsid;
	HRESULT hr = CLSIDFromProgID(OLESTR("dm.dmsoft"), &clsid);
	if (FAILED(hr))
	{
		printf("���÷��� [CLSIDFromProgID] ʧ��!\n");
		CoUninitialize();
		return 0;
	}
	hr = CoCreateInstance(clsid, NULL, CLSCTX_INPROC_SERVER, __uuidof(Idmsoft), (LPVOID*)&m_pdm);
	if (FAILED(hr))
	{
		printf("���÷��� [CoCreateInstance] ʧ��!\n");
		CoUninitialize();
		return 0;
	}

	// ��ȡ��Į����汾
	std::string strVersion = m_pdm->Ver();
	printf("��ǰ��Į����汾Ϊ: %s\n", strVersion.c_str());


	// ����ȫ��Ŀ¼
	nRet = m_pdm->SetPath(GetGlobalPath((long)e_rgame_mhxy).c_str());
	if (nRet != 1)
	{
		printf("����ȫ��·��ʧ�ܡ�\n");
		CoUninitialize();
		return 0;
	}

	// ��ȡע����
	std::string strRegCode = m_pdm->ReadIni("��Įע����", "RegCode", "config.ini");

	// ע���Į���
	nRet = m_pdm->Reg(strRegCode.c_str(), "");
	if (nRet != 1)
	{
		printf("ע��ʧ�ܣ�������: %d��\n", nRet);
		CoUninitialize();
		return 0;
	}

	// �����ֿ�
	nRet = m_pdm->SetDict(IDF_HAN_SMALL, TXF_HAN_SMALL);
	nRet = m_pdm->SetDict(IDF_HAN_LARGE, TXF_HAN_LARGE);
	nRet = m_pdm->SetDict(IDF_ABC_SMALL, TXF_ABC_SMALL);
	nRet = m_pdm->SetDict(IDF_OTHER, TXF_OTHER);
	if (nRet != 1)
	{
		printf("�����ֿ�ʧ�ܡ�\n");
		CoUninitialize();
		return 0;
	}

	return 1;
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
	::GetModuleFileName(NULL, szPath, MAX_PATH);
	std::string strSubDir;
	switch ((E_RGAME)lGameID)
	{
	case e_rgame_mhxy:
		strSubDir = "..\\file\\MHXY";
		break;
	default:
		assert(0);
		break;
	}

	::PathAppendA(szPath, strSubDir.c_str());
	return szPath;
}