#include "RSocketCom.h"

#ifndef LINUX
#pragma comment(lib, "Ws2_32.lib")
#endif

int create_udp_socket(u_short local_port)
{
	int sock = -1;
	const int opt = 1;
	int ret = 0;

	struct sockaddr_in addr_local;
	ZeroMemory(&addr_local, sizeof(struct sockaddr_in));
	addr_local.sin_family = AF_INET;
	addr_local.sin_addr.s_addr = htonl(INADDR_ANY);
	addr_local.sin_port = htons(local_port);

#ifndef LINUX
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
#endif // !LINUX

	if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		printf("create socket failed with error %d\n", sock);
		return -1;
	}

	//设置该套接字为广播类型，
	ret = setsockopt(sock, SOL_SOCKET, SO_BROADCAST, (char *)&opt, sizeof(opt));
	if (ret == -1)
	{
		printf("set socket opt error \n");
		return -1;
	}

	if (bind(sock, (struct sockaddr *)&(addr_local), sizeof(addr_local)) == -1)
	{
		printf("bind error...\n");
		return -1;
	}

	return sock;
}

int close_udp_socket(int sock_fd)
{
	int ret = 0;
	ret = closesocket(sock_fd);

#ifndef LINUX
	WSACleanup();
#endif // !LINUX

	return ret;
}

int recv_msg(int sock_fd, struct sockaddr* paddr_dest, unsigned char * recv_buf)
{
	int ret = 0;
	int fromlen = sizeof(struct sockaddr);
	ret = recvfrom(sock_fd, (char*)recv_buf, MAX_BUFFER_LEN, 0, paddr_dest, &fromlen);

	if (ret < 0)
	{
		ret = WSAGetLastError();
		printf("recvfrom error :%d\n", ret);
	}
	return ret;
}
