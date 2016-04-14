#pragma once
#include "RSocketCom.h"

#define MAX_FLAG_LENGTH	32

typedef struct _position_info_t
{
	char szFlag[MAX_FLAG_LENGTH];
	float fX;
	float fY;
	float fZ;

	_position_info_t* operator = (_position_info_t* p)
	{
		fX = p->fX;
		fY = p->fY;
		fZ = p->fZ;
		strcpy_s(szFlag, p->szFlag);

		return this;
	}
}POSITION_INFO_T;

class CUDPReceiver
{
public:
	CUDPReceiver();
	virtual ~CUDPReceiver();

public:
	long Init(unsigned short nLocalPort);
	long UnInit();

	long SetFlag(const char * psz);
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

	char m_szFlag[MAX_FLAG_LENGTH];
	POSITION_INFO_T m_stPosition;
	unsigned short	m_nLocalPort;
};

