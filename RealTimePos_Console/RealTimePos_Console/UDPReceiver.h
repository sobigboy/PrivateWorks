#pragma once
#include "RSocketCom.h"

#define MAX_FLAG_LENGTH	32

typedef struct _position_info_t
{
	/*char szFlag[MAX_FLAG_LENGTH];*/
	unsigned long long	 ullFlag;
	float fX;
	float fY;
	float fZ;

	_position_info_t* operator = (_position_info_t* p)
	{
		ullFlag = 0;
		fX = p->fX;
		fY = p->fY;
		fZ = p->fZ;
// 		strcpy_s(szFlag, p->szFlag);

		return this;
	}
}POSITION_INFO_T;

class CUDPReceiver
{
public:
	CUDPReceiver();
	virtual ~CUDPReceiver();
	
protected:
	static CUDPReceiver* m_pReceiver;

public:
	static CUDPReceiver* GetInstance();
	static void DestoryInstance();

public:
	long Init(unsigned short nLocalPort);
	long UnInit();

// 	long SetFlag(const char * psz);
	long SetFlag(unsigned long long ullFlag);

	long GetLastPostion(POSITION_INFO_T * pstPos);

protected:
	static DWORD WINAPI RecvThreadProc(LPVOID lpParameter);
	DWORD RecvThreadProcPrivate();
	void ProcessRecv();
	long ParsePositionFromBuf(const unsigned char *buf, int buf_len, POSITION_INFO_T *presult);

private:
	void* m_hStart;
	void* m_hExit;
	void* m_hThread;

	bool m_bIsRunning;

// 	char m_szFlag[MAX_FLAG_LENGTH];
	unsigned long long m_ullFlag;
	POSITION_INFO_T m_stPosition;
	unsigned short	m_nLocalPort;

};

