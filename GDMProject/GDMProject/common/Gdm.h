#pragma once

#include "Logger.h"

#import "3rd/dm/dm.dll" \
	rename("SetWindowText", "DmSetWindowText") \
	rename("FindWindow", "DmFindWindow") \
	rename("FindWindowEx", "DmFindWindowEx") \
	rename("CopyFile", "DmCopyFile") \
	rename("DeleteFile", "DmDeleteFile") \
	rename("MoveFile", "DmMoveFile") \
	rename("GetCommandLine", "DmGetCommandLine") \
	no_namespace

class CGdmApp
{
public:
	CGdmApp();
	virtual ~CGdmApp();

protected:
	static CGdmApp *m_pGdmApp;

public:	
	static CGdmApp *GetInstance();
	static void DestroyInstance();

	//����Ƴɵ�ʵ�������ڸ���ҵ���޸�
	Idmsoft* GetDm();

protected:
	long InitializeDm();
	long UnInitializeDm();

private:
	Idmsoft * m_pdm;
};

