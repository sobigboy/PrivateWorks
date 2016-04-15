// GDMProject_VS2010.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Gdm.h"

void usage_test();

int _tmain(int argc, _TCHAR* argv[])
{
	usage_test();

	system("pause");
	return 0;
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