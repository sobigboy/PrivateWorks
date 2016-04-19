#include "stdafx.h"
#include "Gdm.h"

CGdmApp *CGdmApp::m_pGdmApp = NULL;

CGdmApp::CGdmApp()
{
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

// 	if(1 !=	m_pGdmApp->InitializeDm())
// 	{
// 		DestroyInstance();
// 	}

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
DWORD WINAPI ThreadProc(LPVOID lpParam);
long CGdmApp::InitializeDm()
{
	int nRet = 0;
	if (g_pdm)
		return 1;

	WinExec("regsvr32 dm.dll /s", SW_HIDE);
	CoInitialize(NULL);
	CLSID clsid;
	HRESULT hr = CLSIDFromProgID(OLESTR("dm.dmsoft"), &clsid);
	if (FAILED(hr))
	{
		printf("调用方法 [CLSIDFromProgID] 失败!\n");
		CoUninitialize();
		return 0;
	}
	hr = CoCreateInstance(clsid, NULL, CLSCTX_INPROC_SERVER, __uuidof(Idmsoft), (LPVOID*)&g_pdm);
	if (FAILED(hr))
	{
		printf("调用方法 [CoCreateInstance] 失败!\n");
		CoUninitialize();
		return 0;
	}

	// 获取大漠插件版本
	std::string strVersion = g_pdm->Ver();
	printf("当前大漠插件版本为: %s\n", strVersion.c_str());


	// 设置全局目录
	nRet = g_pdm->SetPath(GetGlobalPath((long)e_rgame_mhxy).c_str());
	if (nRet != 1)
	{
		printf("设置全局路径失败。\n");
		CoUninitialize();
		return 0;
	}

	// 获取注册码
	std::string strRegCode = g_pdm->ReadIni("大漠注册码", "RegCode", "config.ini");

	// 注册大漠插件
	nRet = g_pdm->Reg(strRegCode.c_str(), "");
	if (nRet != 1)
	{
		printf("注册失败，错误码: %d。\n", nRet);
		CoUninitialize();
		return 0;
	}

	// 设置字库
	nRet = g_pdm->SetDict(IDF_HAN_SMALL, TXF_HAN_SMALL);
	nRet = g_pdm->SetDict(IDF_HAN_LARGE, TXF_HAN_LARGE);
	nRet = g_pdm->SetDict(IDF_ABC_SMALL, TXF_ABC_SMALL);
	nRet = g_pdm->SetDict(IDF_OTHER, TXF_OTHER);
	if (nRet != 1)
	{
		printf("设置字库失败。\n");
		CoUninitialize();
		return 0;
	}


	// 查找主窗口
	long parent_hwnd = g_pdm->DmFindWindow("MHXYMainFrame", "梦幻西游");
	if (parent_hwnd == 0)
	{
		printf("未找到梦幻西游主窗口。\n");
		CoUninitialize();
		return 0;
	}

	// 激活主窗口
	g_pdm->SetWindowState(parent_hwnd, 1);

	// 查找游戏窗口
	std::string hwnds = g_pdm->EnumWindow(parent_hwnd, "", "WSGAME", 2);
	std::vector<std::string> vecHwnd;
	StringSplit(hwnds, ",", vecHwnd);
	for (size_t i = 0; i < vecHwnd.size(); ++i)
	{
		long hwnd = atol(vecHwnd.at(i).c_str());
		g_vecHwnd.push_back(hwnd);
	}

	g_pdm->SetKeypadDelay("normal", 100);
	g_pdm->SetMouseDelay("normal", 100);

	// 注册热键
	if (RegisterHotKey(NULL, IDH_F10, MOD_CONTROL, VK_S))
	{
		printf("启动/停止:\tCtrl+S\n");
	}
	if (RegisterHotKey(NULL, IDH_F11, MOD_CONTROL, VK_P))
	{
		printf("暂停/继续:\tCtrl+P\n");
	}
	if (RegisterHotKey(NULL, IDH_EXIT, MOD_CONTROL, VK_E))
	{
		printf("关闭程序:\tCtrl+E\n");
	}

	// 创建事件
	g_hEvent = CreateEvent(NULL, TRUE, TRUE, NULL/*_T("{D5695329-7DEB-488E-AC65-5709A907A091}")*/);

	return 0;
}

long CGdmApp::UnInitializeDm()
{
	// 关闭事件句柄
	CloseHandle(g_hEvent);
	CoUninitialize();

	return 0;
}

Idmsoft* CGdmApp::GetDm()
{
	return g_pdm;
}

void CGdmApp::SetTaskCallBack( long(*pfnTaskCallBack)(void) )
{
	m_pfnTaskCallBack = pfnTaskCallBack;
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
	case e_rgame_dnf:
		strSubDir = "..\\file\\DNF";
		break;
	default:
		assert(0);
		break;
	}

	::PathAppendA(szPath, strSubDir.c_str());
	return szPath;
}


void Alert(void)
{
	long id = g_pdm->Play("1.wav");
	if(id != 0)
	{
		g_pdm->delay(2000);
		g_pdm->Stop(id);
	}

}


void StringSplit(std::string& s, std::string delim, std::vector<std::string>& ret)
{
	if (s.empty()) return;

	size_t last = 0;
	size_t index = s.find_first_of(delim, last);
	while (index != std::string::npos)
	{
		ret.push_back(s.substr(last, index - last));
		last = index + 1;
		index = s.find_first_of(delim, last);
	}
	if (index - last > 0)
	{
		ret.push_back(s.substr(last, index - last));
	}
}

void WaitEvent(void)
{
	WaitForSingleObject(g_hEvent, INFINITE);
}

BOOL IsTerminates(void)
{
	return !(g_appStatus != NotRunning);
}

std::string GetGamePosition()
{
	g_pdm->UseDict(IDF_HAN_SMALL);
	return g_pdm->Ocr(15, 22, 130, 40, "ffffff-000000", 1);
}

bool GetGameCoordinate(long& x, long& y)
{
	g_pdm->UseDict(IDF_ABC_SMALL);
	std::string strRet = g_pdm->Ocr(15, 22, 130, 40, "ffffff-000000", 1);
	size_t begin = strRet.find_first_of("[");
	size_t end = strRet.find_last_of("]");
	strRet = strRet.substr(begin + 1, end - begin - 1);
	std::vector<std::string> vecPosition;
	StringSplit(strRet, ",", vecPosition);
	if (vecPosition.size() == 2)
	{
		x = atol(vecPosition.at(0).c_str());
		y = atol(vecPosition.at(1).c_str());
		return true;
	}

	return false;
}

long GetPersonProperty()
{
	// 打开人物属性
	long xPos, yPos;
	long nRet = LY_FAIL;
	long nLoop = 5;
	for (int i = 0; i < nLoop; ++i)
	{
		MoveMouse(g_nWidth - 96, 29);
		LeftClick();

		for (int j = 0; j < nLoop; ++j)
		{
			nRet = FindString(IDF_HAN_LARGE, 0, 0, g_nWidth, g_nHeight, "人物属性", "ffffff-", 1.0, xPos, yPos);
			if(nRet == LY_SUCCESS)
			{
				break;
			}
			g_pdm->delay(500);
		}

		if(nRet == LY_SUCCESS) break;
	}

	return nRet;
}

void GetMouseCoordinate(long& x, long& y)
{
	x = g_pdm->ReadInt(g_nHwnd, "[118A45F0]+50", 0);
	y = g_pdm->ReadInt(g_nHwnd, "[118A45F0]+54", 0);
}

void MoveMouse(long x, long y)
{
	long mx, my;
	long cx, cy;
	while (true)
	{
		GetMouseCoordinate(mx, my);
		if (mx < 0 || mx > g_nWidth || my < 0 || my > g_nHeight)
		{
			g_pdm->MoveTo(g_nWidth / 2, g_nHeight / 2);
			g_pdm->delay(20);
		}
		else
		{
			cx = x - mx;
			cy = y - my;
			if (abs(cx) <= 2 && abs(cy) <= 2) break;

			cx = cx / 2;
			cy = cy / 2;

			g_pdm->MoveR(cx, cy);
			g_pdm->delay(20);
		}
	}
}

void LeftClick(void)
{
	g_pdm->LeftClick();
}

void RightClick(void)
{
	g_pdm->RightClick();
}

void DockMouse(void)
{
	g_pdm->MoveTo(1, 1);
}

long FindString(long dict, long x, long y, long width, long height, std::string text, std::string color, double sim, long& xPos, long& yPos)
{
	VARIANT intX, intY;
	long nRet;

	g_pdm->delay(1000);
	g_pdm->UseDict(dict);
	nRet = g_pdm->FindStrFast(x, y, x + width, y + height, text.c_str(), color.c_str(), sim, &intX, &intY);
	if (nRet == -1)
	{
		DockMouse();
		nRet = g_pdm->FindStrFast(x, y, x + width, y + height, text.c_str(), color.c_str(), sim, &intX, &intY);
	}

	if (nRet == -1)
	{
		return LY_FAIL;
	}
	else
	{
		xPos = intX.lVal;
		yPos = intY.lVal;
		return LY_SUCCESS;
	}
}

long FindStringEx(long dict, long x, long y, long width, long height, std::string text, std::string color, double sim, std::vector<RESULTITEM>& vecResult)
{
	std::string strRet;

	DockMouse();
	g_pdm->UseDict(dict);
	strRet = g_pdm->FindStrFastEx(x, y, x + width, y + height, text.c_str(), color.c_str(), sim);
	std::vector<std::string> vecTemp;
	StringSplit(strRet, "|", vecTemp);
	for (std::vector<std::string>::iterator iter = vecTemp.begin(); iter != vecTemp.end(); ++iter)
	{
		std::vector<std::string> vecItem;
		StringSplit(*iter, ",", vecItem);

		RESULTITEM item;
		item.index = atol(vecItem.at(0).c_str());
		item.xPos = atol(vecItem.at(1).c_str());
		item.yPos = atol(vecItem.at(2).c_str());

		vecResult.push_back(item);
	}

	return LY_SUCCESS;
}

long CloseAllWindow(void)
{
	std::vector<std::string> vecTemp;

	while (true)
	{
		WaitEvent();
		if (IsTerminates()) return LY_EXIT;

		g_pdm->delay(500);
		std::string strRet = g_pdm->FindPicEx(0, 0, g_nWidth, g_nHeight, "关闭.bmp", "000000", 1.0, 0);
		vecTemp.clear();
		StringSplit(strRet, "|", vecTemp);
		if (vecTemp.size() == 0) return LY_SUCCESS;

		std::map<std::string, int> mapWindow;
		for (std::vector<std::string>::iterator iterTemp = vecTemp.begin(); iterTemp != vecTemp.end(); ++iterTemp)
		{
			std::string strItem = *iterTemp;
			mapWindow.insert(std::make_pair(strItem, 0));
		}

		while (true)
		{
			std::string strTarget;
			for (std::map<std::string, int>::reverse_iterator iter = mapWindow.rbegin(); iter != mapWindow.rend(); ++iter)
			{
				if (iter->second == 0)
				{
					strTarget = iter->first;
				}
			}

			if (strTarget.empty()) break;

			vecTemp.clear();
			StringSplit(strTarget, ",", vecTemp);

			long x = atol(vecTemp.at(1).c_str()) + 2;
			long y = atol(vecTemp.at(2).c_str()) + 2;

			MoveMouse(x, y);
			LeftClick();

			g_pdm->delay(500);
			std::string strRet = g_pdm->FindPicEx(0, 0, g_nWidth, g_nHeight, "关闭.bmp", "000000", 1.0, 0);
			vecTemp.clear();
			StringSplit(strRet, "|", vecTemp);
			if (vecTemp.size() == 0) return LY_SUCCESS;

			bool bFlag = false;
			for (std::vector<std::string>::iterator iterTemp = vecTemp.begin(); iterTemp != vecTemp.end(); ++iterTemp)
			{
				std::string strItem = *iterTemp;
				if (strItem == strTarget)
				{
					mapWindow[strTarget] = 1;
					bFlag = true;
					break;
				}
			}

			if (!bFlag)
			{
				mapWindow.erase(strTarget);
			}
		}
	}

	return LY_SUCCESS;
}

long CloseWindow(std::string title)
{
	VARIANT intX, intY;
	long xPos, yPos;
	long nRet;
	g_pdm->delay(1000);
	nRet = FindString(IDF_HAN_LARGE, 0, 0, g_nWidth, g_nHeight, title.c_str(), "ffffff-", 1.0, xPos, yPos);
	if (nRet == LY_SUCCESS)
	{
		nRet = g_pdm->FindPic(xPos, yPos - 5, g_nWidth, yPos - 5 +20, "关闭.bmp", "000000", 1.0, 0, &intX, &intY);
		if (nRet == 0)
		{
			MoveMouse(intX.lVal + 2, intY.lVal + 2);
			LeftClick();

			return LY_SUCCESS;
		}
	}

	return LY_FAIL;
}

void WaitForPersonStop(long seconds)
{
	long xPos1 = 0, yPos1 = 0;
	long xPos2 = 0, yPos2 = 0;
	long count = 0;
	while (true)
	{
		if (GetGameCoordinate(xPos1, yPos1))
		{
			if (xPos1 == xPos2 && yPos1 == yPos2)
			{
				count++;
			}
			else
			{
				count = 0;
			}

			xPos2 = xPos1;
			yPos2 = yPos1;
		}
		else
		{
			printf("找不到游戏坐标\n");
		}
		if (count >= seconds) return;
		g_pdm->delay(1000);
	}
}

long GetYaoInfo(std::map<std::string, std::vector<YAOINFO>>& mapYao, long index)
{
	VARIANT intX, intY;
	long xPos, yPos;
	long nRet;

	WaitEvent();
	if (IsTerminates()) return LY_EXIT;

	do 
	{
		g_pdm->delay(1000);
		nRet = g_pdm->FindPic(0, 0, g_nWidth, g_nHeight, "消息.bmp", "000000", 1.0, 1, &intX, &intY);
	} while (nRet == 0);

	DockMouse();

	g_pdm->delay(1000);

	std::string strRet = g_pdm->FindPicEx(0, 0, g_nWidth, g_nHeight, "千年保心丹.bmp|蛇蝎美人.bmp|十香返生丸.bmp|金香玉.bmp|风水混元丹.bmp|九转回魂丹.bmp|红雪散.bmp|小还丹.bmp|定神香.bmp|佛光舍利子.bmp|五龙丹.bmp|金创药.bmp", "000000", 1.0, 0);
	std::vector<std::string> vecSplit1;
	StringSplit(strRet, "|", vecSplit1);
	for (size_t i = 0; i < vecSplit1.size(); ++i)
	{
		WaitEvent();
		if (IsTerminates()) return LY_EXIT;

		std::string strItem = vecSplit1.at(i);
		std::vector<std::string> vecSplit2;
		StringSplit(strItem, ",", vecSplit2);

		std::string strName;
		long x = atol(vecSplit2.at(1).c_str());
		long y = atol(vecSplit2.at(2).c_str());
		switch (atol(vecSplit2.at(0).c_str()))
		{
		case 0:
			strName = "千年保心丹";
			x += 7;
			y += 7;
			break;
		case 1:
			strName = "蛇蝎美人";
			x += 3;
			y += 4;
			break;
		case 2:
			strName = "十香返生丸";
			x += 8;
			y += 8;
			break;
		case 3:
			strName = "金香玉";
			x += 8;
			y += 8;
			break;
		case 4:
			strName = "风水混元丹";
			x += 8;
			y += 8;
			break;
		case 5:
			strName = "九转回魂丹";
			x += 5;
			y += 4;
			break;
		case 6:
			strName = "红雪散";
			x += 6;
			y -= 6;
			break;
		case 7:
			strName = "小还丹";
			x += 8;
			y += 8;
			break;
		case 8:
			strName = "定神香";
			x += 7;
			y += 7;
			break;
		case 9:
			strName = "佛光舍利子";
			x += 9;
			y += 8;
			break;
		case 10:
			strName = "五龙丹";
			x += 8;
			y += 7;
			break;
		case 11:
			strName = "金创药";
			x += 7;
			y += 7;
			break;
		}

		MoveMouse(x, y);
		g_pdm->delay(1000);
		long nPin = 0;
		nRet = FindString(IDF_HAN_LARGE, 0, 0, g_nWidth, g_nHeight, "品质", "ffff00-", 1.0, xPos, yPos);
		if(nRet == LY_SUCCESS)
		{
			g_pdm->UseDict(IDF_OTHER);
			strRet = g_pdm->Ocr(xPos + 29, yPos, xPos + 58, yPos + 14, "ffff00-", 1.0);
			if(strRet.empty()) 
			{
				continue;
			}

			nPin = atol(strRet.c_str());
		}

		long nOriginalPrice = 0;
		bool bAdjust = false;
		std::map<std::string, YAOPRICE >::iterator iter1 = g_mapYaoPrice.find(strName);
		if (iter1 != g_mapYaoPrice.end())
		{
			YAOPRICE& yaoPrice = iter1->second;
			std::vector<YAOPRICEITEM>& vecItems = yaoPrice.vecItems;
			for (std::vector<YAOPRICEITEM>::iterator iter2 = vecItems.begin(); iter2 != vecItems.end(); ++iter2)
			{
				YAOPRICEITEM& item = *iter2;
				if(nPin >= item.nPinMin && nPin < item.nPinMax)
				{
					nOriginalPrice = item.nPrice;
					break;
				}
			}
			bAdjust = yaoPrice.bAdjust;
		}
		else
		{
			printf("未配置%s的售价\n", strName.c_str());
			continue;
		}

		YAOINFO t;
		t.nIndex = index;
		t.strName = strName;
		t.xPos = x;
		t.yPos = y;
		t.nPin = nPin;
		t.nOriginalPrice = nOriginalPrice;
		t.bAdjust = bAdjust;

		mapYao[strName].push_back(t);
	}

	return LY_SUCCESS;
}

void MainControl(void);
void ExecuteTask(long hwnd)
{
	g_nHwnd = hwnd;

	VARIANT intX, intY;
	long nRet;

	// 绑定窗口
	nRet = g_pdm->BindWindow(hwnd, "normal", "normal", "normal", 0);
	if (nRet != 1)
	{
		printf("绑定窗口失败。\n");
		return;
	}

	// 延时3秒，等待绑定窗口成功
	g_pdm->delay(3000);

	// 获取游戏区宽度和高度
	nRet = g_pdm->GetClientSize(hwnd, &intX, &intY);
	if (nRet != 1)
	{
		printf("获取游戏区宽度和高度失败。\n");
		g_pdm->UnBindWindow();
		return;
	}
	else
	{
		g_nWidth = intX.lVal;
		g_nHeight = intY.lVal;
		printf("游戏客户区宽高： %d , %d\n", g_nWidth, g_nHeight);
	}

	g_pdm->EnableKeypadSync(1, 5000);
	g_pdm->EnableMouseSync(1, 5000);
	g_pdm->EnableRealMouse(2, 20, 30);
	g_pdm->EnableRealKeypad(1);

	MainControl();

	g_pdm->UnBindWindow();
}

DWORD WINAPI ThreadProc(LPVOID lpParam)
{
	long nRet;


	printf("\n启动任务...\n");


	while (true)
	{
		WaitEvent();
		if (IsTerminates()) break;

		for (size_t i = 0; i < g_vecHwnd.size(); ++i)
		{
			WaitEvent();
			if (IsTerminates()) break;

			long hwnd = g_vecHwnd.at(i);
			std::string strTitle = g_pdm->GetWindowTitle(hwnd);
			printf("%s\n", strTitle.c_str());

			// 激活当前窗口
			while (true)
			{
				nRet = g_pdm->GetWindowState(hwnd, 2);
				if (nRet == 1)
					break;
				else
				{
					g_pdm->KeyDown(VK_CONTROL);
					g_pdm->KeyPress(VK_TAB);
					g_pdm->KeyUp(VK_CONTROL);
					g_pdm->delay(500);
				}
			}

			// 执行任务
			ExecuteTask(hwnd);

			// 切换窗口
			g_pdm->KeyDown(VK_CONTROL);
			g_pdm->KeyPress(VK_TAB);
			g_pdm->KeyUp(VK_CONTROL);
		}

		for (int i = 360*60; i > 0; --i)
		{
			WaitEvent();
			if (IsTerminates()) break;

			int hour = i / 3600;
			int minute = (i % 3600) / 60;
			int second = ((i % 3600) % 60) % 60;
			printf("\r%d小时%2d分%2d秒后将开始新一轮任务...", hour, minute, second);
			g_pdm->delay(1000);
		}
	}

	printf("\n停止任务...\n");

	return 0;
}

void MainControl(void)
{
	long nRet = LY_SUCCESS;
	CloseAllWindow();

	//回调
	nRet = CGdmApp::GetInstance()->m_pfnTaskCallBack();

	if(nRet == LY_FAIL)
	{
		Alert();
	}

	CloseAllWindow();
}

void CGdmApp::MonitorHotKey()
{
	// 接收热键消息
	DWORD dwThreadID;
	HANDLE hThread = INVALID_HANDLE_VALUE;
	MSG msg = { 0 };
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (msg.message == WM_HOTKEY)
		{
			if (msg.wParam == IDH_EXIT)
			{
				g_pdm->UnBindWindow();
				break;
			}
			else if (msg.wParam == IDH_F10)
			{
				if (g_appStatus == NotRunning)
				{
					g_appStatus = Running;
					hThread = CreateThread(NULL, 0, ThreadProc, NULL, 0, &dwThreadID);
				}
				else
				{
					// 等待线程结束
					if (g_appStatus == Paused)
					{
						g_appStatus = NotRunning;
						SetEvent(g_hEvent);
					}
					else
					{
						g_appStatus = NotRunning;
					}
					WaitForSingleObject(hThread, INFINITE);
					CloseHandle(hThread);
				}
			}
			else if (msg.wParam == IDH_F11)
			{
				if (g_appStatus == Running)
				{
					g_appStatus = Paused;
					ResetEvent(g_hEvent);
				}
				else if (g_appStatus == Paused)
				{
					g_appStatus = Running;
					SetEvent(g_hEvent);
				}
			}
		}
	}

}