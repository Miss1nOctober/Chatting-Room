// ����Sockets������С���򣨿ͻ��ˣ�.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include<iostream>
//#include<stdio.h>
#include<WinSock2.h>
using namespace std;
#define MAXBYTE 0xff
#pragma comment(lib,"ws2_32.lib")

const char *SERVERIPADDRESS = "127.0.0.1";

int main()
{
	bool bSuccess = FALSE;
	SOCKET socketClient = INVALID_SOCKET;//�ͻ��˵��׽���
	do
	{
		WSADATA wsaData;
		if (0 != WSAStartup(MAKEWORD(2, 2), &wsaData))//����
			break;
		//�ж�
		if (2 != LOBYTE(wsaData.wVersion) ||
			2 != HIBYTE(wsaData.wVersion))
			break;


		//���ֻ�
		socketClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (INVALID_SOCKET == socketClient)
			break;


		//�õ��绰����
		sockaddr_in addrServ = { 0 };
		addrServ.sin_family = AF_INET;
		addrServ.sin_port = htons(10800);
		addrServ.sin_addr.S_un.S_addr = inet_addr(SERVERIPADDRESS);


		//�������
		if (SOCKET_ERROR == connect(socketClient, (SOCKADDR*)&addrServ, sizeof(addrServ)))
			break;


		char szRecvMessage[MAXBYTE] = { 0 };
		char szSendMessage[MAXBYTE] = { 0 };
		while (true)
		{
			int nResult = recv(socketClient, szRecvMessage, MAXBYTE, 0);
			if (nResult > 0)//���յ���Ϣ
			{
				cout << "Messages from Server:" << szRecvMessage << endl;
				cout << "Client Answer Back:";
				cin >> szSendMessage;
				if (SOCKET_ERROR == send(socketClient, szSendMessage, MAXBYTE, 0))
					break;//����ѭ��
			}
			else if (nResult == 0)//���ӱ��ر�
			{
				cout << "connection closed:" << endl;
				break;
			}
			else
			{
				cout << "unknown reason ��" << endl;
				break;
			}
		}
		bSuccess = TRUE;
	} while (FALSE);


	if (!bSuccess)
	{
		int nError = WSAGetLastError();
		cout << "Wrong Message" << nError << endl;
		if (INVALID_SOCKET != socketClient)
			closesocket(socketClient);


	}
	WSACleanup();
	system("pause");
	return 0;
}

