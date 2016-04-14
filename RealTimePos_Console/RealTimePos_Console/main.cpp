#include "UDPReceiver.h"

int main()
{
	CUDPReceiver udp;

	int nRet = 0;
	int nPort = 0;

	printf("请输入UDP端口号: ");
	scanf_s("%d", &nPort);

	nRet = udp.Init((unsigned short)nPort);
	if (nRet == 0)
	{
		printf("初始化成功，开始接收数据\n");
		Sleep(1000000);
		udp.UnInit();
	}
	else
		printf("初始化失败\n");

	system("pause");
}