#pragma once

#ifndef _GDM_H
#define _GDM_H

#include "Logger.h"

#import "../common/3rd/dm/dm.dll" \
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

	//先设计成单实例，后期根据业务修改
	Idmsoft* GetDm();

protected:
	long InitializeDm();
	long UnInitializeDm();

private:
	Idmsoft * m_pdm;
};

typedef enum e_rgame
{
	e_rgame_start = -1,
	e_rgame_mhxy,
	e_rgame_end
}E_RGAME;

std::string GetGlobalPath(long lGameID);

#endif
