#pragma once

#ifndef _GDM_H
#define _GDM_H

#include <windows.h>
#include <shlwapi.h>
#include <string>
#include <limits>
#include <vector>
#include <map>
#include <random>
#include <stdarg.h>


#include "GLogger.h"

#import "../common/3rd/dm/dm.dll" \
	rename("SetWindowText", "DmSetWindowText") \
	rename("FindWindow", "DmFindWindow") \
	rename("FindWindowEx", "DmFindWindowEx") \
	rename("CopyFile", "DmCopyFile") \
	rename("DeleteFile", "DmDeleteFile") \
	rename("MoveFile", "DmMoveFile") \
	rename("GetCommandLine", "DmGetCommandLine") \
	rename("StrStr", "DmStrStr") \
	no_namespace


#define XP

#define within(num) ((int) ((float) (num) * rand () / (RAND_MAX + 1.0)))
#define IDH_EXIT 4001
#define IDH_F10 4010
#define IDH_F11 4011

#define IDF_HAN_SMALL	0
#define IDF_HAN_LARGE	1
#define IDF_ABC_SMALL	10
#define IDF_OTHER		19

#ifdef XP
#define TXF_HAN_SMALL "XP_常用汉字_简体_宋体_9.txt"
#define TXF_HAN_LARGE "XP_常用汉字_简体_宋体PUA_13.txt"
#define TXF_ABC_SMALL "XP_英文+数字_宋体_9.txt"
#define TXF_OTHER "其他字库.txt"
#endif

#ifdef WIN7
#define TXF_HAN_SMALL "WIN7_常用汉字_简体_宋体_9.txt"
#define TXF_HAN_LARGE "WIN7_常用汉字_简体_宋体_11.txt"
#define TXF_ABC_SMALL "WIN7_英文+数字_宋体_9.txt"
#define TXF_OTHER "其他字库.txt"
#endif

#define VK_0 0x30
#define VK_1 0x31
#define VK_2 0x32
#define VK_3 0x33
#define VK_4 0x34
#define VK_5 0x35
#define VK_6 0x36
#define VK_7 0x37
#define VK_8 0x38
#define VK_9 0x39
#define VK_A 0x41
#define VK_B 0x42
#define VK_C 0x43
#define VK_D 0x44
#define VK_E 0x45
#define VK_F 0x46
#define VK_G 0x47
#define VK_H 0x48
#define VK_I 0x49
#define VK_J 0x4A
#define VK_K 0x4B
#define VK_L 0x4C
#define VK_M 0x4D
#define VK_N 0x4E
#define VK_O 0x4F
#define VK_P 0x50
#define VK_Q 0x51
#define VK_R 0x52
#define VK_S 0x53
#define VK_T 0x54
#define VK_U 0x55
#define VK_V 0x56
#define VK_W 0x57
#define VK_X 0x58
#define VK_Y 0x59
#define VK_Z 0x5A


#define LY_EXIT -1
#define LY_SUCCESS -2
#define LY_FAIL -3

enum AppStatus
{
	NotRunning,
	Running,
	Paused
};

typedef struct tagYAOPRICEITEM
{
	long nPinMin;
	long nPinMax;
	long nPrice;
}YAOPRICEITEM;

typedef struct tagYAOPRICE
{
	std::string strName;
	std::vector<YAOPRICEITEM> vecItems;
	bool bAdjust;
}YAOPRICE;

typedef struct tagADJUSTPRICE
{
	long nMin;
	long nMax;
	long nPrice;
}ADJUSTPRICE;

typedef struct tagRESULTITEM
{
	long index;
	long xPos;
	long yPos;
}RESULTITEM;

typedef struct tagYAOINFO
{
	long nIndex;
	long xPos;
	long yPos;
	long nPin;
	bool bAdjust;
	long nOriginalPrice;
	std::string strPrice;
	std::string strName;
}YAOINFO;

static std::string g_strShopName;
static std::string g_strMouseX;
static std::string g_strMouseY;
static std::map<std::string, YAOPRICE> g_mapYaoPrice;
static std::vector<ADJUSTPRICE> g_vecAdjustPrice;
static std::vector<long> g_vecHwnd;
static AppStatus g_appStatus = NotRunning;
static HANDLE g_hEvent;
static long g_nHwnd;
static long g_nWidth;
static long g_nHeight;
static Idmsoft * g_pdm;


std::string GetGlobalPath(long lGameID);
void LeftClick(void);
void RightClick(void);
void DockMouse(void);

void Alert(void);
void StringSplit(std::string& s, std::string delim, std::vector<std::string>& ret);
void WaitEvent(void);
BOOL IsTerminates(void);
std::string GetGamePosition();
bool GetGameCoordinate(long& x, long& y);
long GetPersonProperty();
void MoveMouse(long x, long y);
long FindString(long dict, long x, long y, long width, long height, std::string text, std::string color, double sim, long& xPos, long& yPos);
long FindStringEx(long dict, long x, long y, long width, long height, std::string text, std::string color, double sim, std::vector<RESULTITEM>& vecResult);
long CloseAllWindow(void);
long CloseWindow(std::string title);
void WaitForPersonStop(long seconds);
long GetYaoInfo(std::map<std::string, std::vector<YAOINFO>>& mapYao, long index);

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

	void MonitorHotKey();


	//先设计成单实例，后期根据业务修改
	Idmsoft* GetDm();
 	void SetTaskCallBack(long(*pfnTaskCallBack)(void));


	long InitializeDm();
	long UnInitializeDm();

public:
	long (*m_pfnTaskCallBack)(void);
};

typedef enum e_rgame
{
	e_rgame_start = -1,
	e_rgame_mhxy,
	e_rgame_dnf,
	e_rgame_end
}E_RGAME;


#endif
