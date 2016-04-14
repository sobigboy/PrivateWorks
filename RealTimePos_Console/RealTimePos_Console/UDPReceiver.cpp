#include "UDPReceiver.h"
#include <string>

#define DEST_PORT 	(1500)
#define LOCAL_PORT 	(1500)
#define MAX_BUFFER_LEN	(512)
#define RECV_MSG_LEN	(100)

CUDPReceiver::CUDPReceiver()
{
	m_hExit = NULL;
	m_hStart = NULL;
	m_hThread = NULL;
	m_nLocalPort = LOCAL_PORT;
	memset(m_szFlag, 0, sizeof(m_szFlag));
	memset(&m_stPosition, 0, sizeof(m_stPosition));

}


CUDPReceiver::~CUDPReceiver()
{
}

long CUDPReceiver::Init(unsigned short nLocalPort)
{
	m_nLocalPort = nLocalPort;

	if (m_hThread)
		UnInit();

	DWORD dwThreadID = 0;
	m_hExit = CreateEvent(NULL, TRUE, FALSE, NULL);
	m_hStart = CreateEvent(NULL, TRUE, FALSE, NULL);
	m_hThread = ::CreateThread(NULL, 0, RecvThreadProc,
		(void *)this, 0, &dwThreadID);

	SetEvent(m_hStart);

	return 0;
}

long CUDPReceiver::UnInit()
{

	if (m_hThread)
	{
		SetEvent(m_hExit);

		if (WAIT_OBJECT_0 != WaitForSingleObject(m_hThread, 1000))
			TerminateThread(m_hThread, 0);
	}

	CloseHandle(m_hThread);
	m_hThread = NULL;
	CloseHandle(m_hExit);
	m_hExit = NULL;
	CloseHandle(m_hStart);
	m_hStart;
	return 0;
}

long CUDPReceiver::SetFlag(const char * psz)
{
	strcpy_s(m_szFlag, psz);
	return 0;
}

long CUDPReceiver::GetLastPostion(POSITION_INFO_T * pstPos)
{
	*pstPos = &m_stPosition;

	return 0;
}

DWORD WINAPI CUDPReceiver::RecvThreadProc(LPVOID lpParameter)
{
	CUDPReceiver *p =  reinterpret_cast<CUDPReceiver*>(lpParameter);
	assert(p);

	return p->RecvThreadProcPrivate();
}

DWORD CUDPReceiver::RecvThreadProcPrivate()
{

	ProcessRecv();

	return 0;
}

void CUDPReceiver::ProcessRecv()
{
	unsigned char reply_buf[MAX_BUFFER_LEN] = { 0 };
	struct sockaddr_in addr_dest;
	ZeroMemory(&addr_dest, sizeof(struct sockaddr_in));
	addr_dest.sin_family = AF_INET;
	addr_dest.sin_addr.s_addr = htonl(INADDR_BROADCAST);
	addr_dest.sin_port = htons(DEST_PORT);

	int sock = create_udp_socket(m_nLocalPort);

	if (sock == INVALID_SOCKET)
	{
		printf("create udp socket failed : %d!\n", sock);
		return;
	}

	HANDLE h1[] = { m_hStart, m_hExit };
	DWORD dwRet = 0;
	dwRet = WaitForMultipleObjects(sizeof(h1) / sizeof(h1[0]), h1, FALSE, INFINITE);

	if (dwRet == WAIT_OBJECT_0)
	{
		ResetEvent(m_hStart);

		while (1)
		{
			if (WAIT_OBJECT_0 == WaitForSingleObject(m_hExit, 1))
			{
				ResetEvent(m_hExit);
				goto done;
			}

			int recv_len = 0;
			recv_len = recv_msg(sock, (struct sockaddr*)&addr_dest, reply_buf);
			if (recv_len <= 0)
			{
				printf("recv error....\n");
				break;
			}
			else/* if (recv_len % SEARCH_REPLY_LEN == 0)*/
			{
				ParsePositionFromBuf(reply_buf, recv_len, &m_stPosition);
			}
		}

	}
	else if (dwRet == WAIT_OBJECT_0 + 1)
	{
		ResetEvent(m_hExit);
		goto done;
	}

done:
	close_udp_socket(sock);

}

long CUDPReceiver::ParsePositionFromBuf(const unsigned char *buf, int buf_len, POSITION_INFO_T *presult)
{
	int ret = 0;
// 	char szTemp[MAX_BUFFER_LEN] = { 0 };
// 	strcpy_s(szTemp, buf_len, (const char*)buf);
// 	szTemp[buf_len] = 0;


	std::string str =(char*) buf;
	printf("recv: %s\n", str.c_str());
	
	return ret;
}
