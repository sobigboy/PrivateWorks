#include "UDPReceiver.h"

int main()
{
	CUDPReceiver *udp = NULL;

	int nRet = 0;
	int nPort = 0;
	unsigned long long ull = 0;

	printf("请输入UDP端口号: ");
	scanf_s("%d", &nPort);

	printf("请输入定位ID: ");
	scanf_s("%I64d", &ull);

	udp = CUDPReceiver::GetInstance();

	nRet = udp->Init((unsigned short)nPort);
	udp->SetFlag(ull);

	if (nRet == 0)
	{
		printf("初始化成功，开始接收数据\n");
		Sleep(1000000);
	}
	else
		printf("初始化失败\n");

	udp->DestoryInstance();
	system("pause");
}