#include "UDPReceiver.h"

int main()
{
	CUDPReceiver udp;

	int nRet = 0;
	int nPort = 0;

	printf("������UDP�˿ں�: ");
	scanf_s("%d", &nPort);

	nRet = udp.Init((unsigned short)nPort);
	if (nRet == 0)
	{
		printf("��ʼ���ɹ�����ʼ��������\n");
		Sleep(1000000);
		udp.UnInit();
	}
	else
		printf("��ʼ��ʧ��\n");

	system("pause");
}