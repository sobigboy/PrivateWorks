// GDMProject_VS2010.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "Gdm.h"

static Idmsoft* dm;

void usage_test();
long Do_BaiTan();

int _tmain(int argc, _TCHAR* argv[])
{
	CLogger::GetInstance()->Initialize("GDMProject_2010_log");
	CLogger::GetInstance()->AddLog(0, "Initialize...");

	CGdmApp *app = CGdmApp::GetInstance();
	app->InitializeDm();
	app->SetTaskCallBack(Do_BaiTan);
	dm = app->GetDm();

	app->MonitorHotKey();
// 	Sleep(100000);
	app->UnInitializeDm();
	app->DestroyInstance();

	CLogger::GetInstance()->AddLog(0, "UnInitialize...Exit!");
	CLogger::GetInstance()->DestroyInstance();
// 	system("pause");
	return 0;
}

long ShangJia(std::map<std::string, std::vector<YAOINFO>>& mapYao, long index)
{
	long xPut, yPut;
	long nRet;
	std::string strRet;

	WaitEvent();
	if (IsTerminates()) return LY_EXIT;

	dm->delay(1000);

	nRet = FindString(IDF_HAN_LARGE, 0, 0, g_nWidth, g_nHeight, "�ϼ�|�¼�", "ffffff-", 1.0, xPut, yPut);
	if(nRet != LY_SUCCESS)
	{
		return nRet;
	}

	for (std::map<std::string, std::vector<YAOINFO>>::iterator iter1 = mapYao.begin(); iter1 != mapYao.end(); ++iter1)
	{
		WaitEvent();
		if (IsTerminates()) return LY_EXIT;


		std::vector<YAOINFO>& vecYao = iter1->second;

		for (std::vector<YAOINFO>::iterator iter2 = vecYao.begin(); iter2 != vecYao.end(); ++iter2)
		{
			YAOINFO& t = *iter2;

			if(t.nIndex == index)
			{
				MoveMouse(t.xPos, t.yPos);
				LeftClick();

				for (int i = 0; i < 10; ++i)
				{
					dm->KeyPress(VK_BACK);
					dm->delay(100);
				}

				dm->SetClipboard(t.strPrice.c_str());
				dm->KeyDown(VK_CONTROL);
				dm->KeyPress(VK_V);
				dm->KeyUp(VK_CONTROL);

				MoveMouse(xPut + 15, yPut + 7);
				LeftClick();

				printf("�ϼܡ�%s������ Ʒ��:%d, ԭ��:%d, �ּ�:%s\n", t.strName.c_str(), t.nPin, t.nOriginalPrice, t.strPrice.c_str());

				dm->delay(1000);
			}
		}
	}

	return LY_SUCCESS;
}

long Do_BaiTan(void)
{
	VARIANT intX, intY;
	long xPage, yPage;
	long xPos, yPos;
	long nRet;

	dm->delay(1000);

	WaitEvent();
	if (IsTerminates()) return LY_EXIT;

	// ����������
	nRet = GetPersonProperty();
	if(nRet != LY_SUCCESS)
	{
		printf("�򿪡��������ԡ�ʧ��\n");
		Alert();
		return LY_FAIL;
	}
	// �����������
	nRet = FindString(IDF_HAN_SMALL, 0, 0, g_nWidth, g_nHeight, "��������", "ffffff-", 1.0, xPos, yPos);
	if (nRet == LY_SUCCESS)
	{
		MoveMouse(xPos + 8, yPos + 30);
		LeftClick();
	}
	else
	{
		printf("δ�ҵ����������ܡ�����\n");
		return LY_FAIL;
	}

	// �����̯
	nRet = FindString(IDF_HAN_LARGE, 0, 0, g_nWidth, g_nHeight, "��̯", "ffffff-", 1.0, xPos, yPos);
	if (nRet == LY_SUCCESS)
	{
		MoveMouse(xPos + 15, yPos + 7);
		LeftClick();
	}
	else
	{
		printf("δ�ҵ�����̯������\n");
		return LY_FAIL;
	}

	dm->delay(1000);

	nRet = FindString(IDF_HAN_LARGE, 0, 0, g_nWidth, g_nHeight, "���ﲻ�����̯", "ffff00-", 1.0, xPos, yPos);
	if(nRet == LY_SUCCESS)
	{
		printf("��ǰλ�ò������̯�������˹�����!\n");
		return LY_FAIL;
	}

	nRet = FindString(IDF_HAN_LARGE, 0, 0, g_nWidth, g_nHeight, "�Ҽ���������̯", "ff0000-", 1.0, xPos, yPos);
	if(nRet == LY_SUCCESS)
	{
		MoveMouse(xPos + 60, yPos + 7);
		LeftClick();
	}

	WaitEvent();
	if (IsTerminates()) return LY_EXIT;

	do 
	{
		nRet = FindString(IDF_HAN_LARGE, 0, 0, g_nWidth, g_nHeight, "�ҵ�̯λ", "ffffff-", 1.0, xPos, yPos);
		dm->delay(1000);
	} while (nRet == LY_FAIL);

	DockMouse();

	// �ص���һҳ
	nRet = dm->FindPic(0, 0, g_nWidth, g_nHeight, "��һҳ.bmp", "000000", 1.0, 0, &intX, &intY);
	if(nRet == -1)
	{
		nRet = dm->FindPic(0, 0, g_nWidth, g_nHeight, "��һҳ.bmp", "000000", 1.0, 0, &intX, &intY);
		if(nRet == 0)
		{
			MoveMouse(intX.lVal, intY.lVal);
			LeftClick();
		}
	}

	xPage = intX.lVal + 3;
	yPage = intY.lVal + 4;

	std::map<std::string, std::vector<YAOINFO>> mapYao;

	// ��ҩ
	nRet = GetYaoInfo(mapYao, 1);
	if(nRet != LY_SUCCESS) return nRet;

	// ȥ��һҳ
	MoveMouse(xPage, yPage);
	LeftClick();

	// ��ҩ
	nRet = GetYaoInfo(mapYao, 2);
	if(nRet != LY_SUCCESS) return nRet;

	// ͳ�Ƽ۸�
	for (std::map<std::string, std::vector<YAOINFO>>::iterator iter1 = mapYao.begin(); iter1 != mapYao.end(); ++iter1)
	{
		std::vector<YAOINFO>& vecYao = iter1->second;
		size_t nCount = vecYao.size();
		long nAdjustPrice = 0;
		long nPrice = 0;
		for (std::vector<ADJUSTPRICE>::iterator iter2 = g_vecAdjustPrice.begin(); iter2 != g_vecAdjustPrice.end(); ++iter2)
		{
			ADJUSTPRICE t = *iter2;
			if(nCount >= t.nMin && nCount < t.nMax)
			{
				nAdjustPrice = t.nPrice;
				break;
			}
		}

		for (std::vector<YAOINFO>::iterator iter2 = vecYao.begin(); iter2 != vecYao.end(); ++iter2)
		{
			YAOINFO& t = *iter2;
			if(t.bAdjust)
			{
				nPrice = t.nOriginalPrice - nAdjustPrice;
			}
			else
			{
				nPrice = t.nOriginalPrice;
			}

			char temp[10];
			_ltoa_s(nPrice, temp, 10, 10);
			t.strPrice = temp;
		}
	}

	// �ص���һҳ
	MoveMouse(xPage, yPage);
	LeftClick();

	//�ϼ�
	nRet = ShangJia(mapYao, 1);
	if(nRet != LY_SUCCESS) return nRet;

	WaitEvent();
	if (IsTerminates()) return LY_EXIT;

	// ȥ��һҳ
	MoveMouse(xPage, yPage);
	LeftClick();

	//�ϼ�
	nRet = ShangJia(mapYao, 2);
	if(nRet != LY_SUCCESS) return nRet;

	// �ص���һҳ
	MoveMouse(xPage, yPage);
	LeftClick();

	CloseAllWindow();

	return LY_SUCCESS;
}

void usage_test()
{
	CLogger::GetInstance()->Initialize("GDMProject_2010_log");
	CLogger::GetInstance()->AddLog(0, "Initialize...");

	CGdmApp *app = CGdmApp::GetInstance();
	Idmsoft *dm = app->GetDm();


	dm->MoveTo(50, 50);
	dm->delay(1000);
	dm->RightClick();
	dm->delay(1000);

	dm->MoveR(10, 5);
	dm->delay(1000);

	dm->LeftClick();

	dm->delay(1000);
	app->DestroyInstance();


	CLogger::GetInstance()->AddLog(0, "UnInitialize...Exit!");
	CLogger::GetInstance()->DestroyInstance();
}