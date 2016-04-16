#include "UDPReceiver.h"

int main()
{
	CUDPReceiver *udp = NULL;

	int nRet = 0;
	int nPort = 0;
	unsigned long long ull = 0;

	printf("������UDP�˿ں�: ");
	scanf_s("%d", &nPort);

	printf("�����붨λID: ");
	scanf_s("%I64d", &ull);

	udp = CUDPReceiver::GetInstance();

	nRet = udp->Init((unsigned short)nPort);
	udp->SetFlag(ull);

	if (nRet == 0)
	{
		printf("��ʼ���ɹ�����ʼ��������\n");
		Sleep(1000000);
	}
	else
		printf("��ʼ��ʧ��\n");

	udp->DestoryInstance();
	system("pause");
}