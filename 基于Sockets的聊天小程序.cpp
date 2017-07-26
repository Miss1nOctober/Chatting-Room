// ����Sockets������С����.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include<iostream>
#include<stdio.h>
#include<WinSock2.h>
using namespace std;


#pragma comment(lib,"ws2_32.lib")


const char *WELCOMTOCHATROOM = "You have connected to the Chatting Room";
const char *MESSAGECOMED = "Meaasge Received��";
const char *ANSWER = "Answer Back:";
const char *WAIFORCLIENT = "Connecting.......";
#define MAXBYTE 0xff

int main()
{


	BOOL bSuccess = FALSE;//�Ƿ�ִ�гɹ�
	int nError = ERROR;
	SOCKET socketServ = INVALID_SOCKET;
	SOCKET socketClient = INVALID_SOCKET;
	do
	{
		WSADATA wsaData;
		nError = WSAStartup(MAKEWORD(2, 2), &wsaData);//��ʼ��
		if (0 != nError)
			break;


		//����Socket
		socketServ = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (INVALID_SOCKET == socketServ)
			break;
		//������ַ
		sockaddr_in addrServ = { 0 };
		addrServ.sin_addr.S_un.S_addr = INADDR_ANY;//����ip��ַ
		addrServ.sin_family = AF_INET;//ipv4
		addrServ.sin_port = htons(10800);//�˿�


										 //��
		if (SOCKET_ERROR == bind(socketServ, (SOCKADDR*)&addrServ, sizeof(addrServ)))
			break;
		if (SOCKET_ERROR == listen(socketServ, SOMAXCONN))
			break;


		sockaddr_in addrClient = { 0 };


		int nAddrSize = sizeof(addrClient);


		//�ȴ��ͻ�����
		cout << WAIFORCLIENT << endl;
		socketClient = accept(socketServ, (SOCKADDR*)&addrClient, &nAddrSize);
		if (INVALID_SOCKET == socketClient)
			break;
		if (SOCKET_ERROR == send(socketClient, WELCOMTOCHATROOM, strlen(WELCOMTOCHATROOM) + 1, 0))
			break;


		char szRecvMessage[MAXBYTE] = { 0 };
		char szSendMessage[MAXBYTE] = { 0 };
		while (true)
		{
			int nResult = recv(socketClient, szRecvMessage, MAXBYTE, 0);
			if (nResult > 0)
			{
				cout << MESSAGECOMED << szRecvMessage << endl;
				cout << ANSWER;
				cin >> szSendMessage;
				if (SOCKET_ERROR == send(socketClient, szSendMessage, strlen(szSendMessage) + 1, 0))
					break;//����while
			}
			else if (nResult == 0)
			{
				cout << "connection closed!" << endl;
				break;
			}
			else
			{
				cout << "recv wrong��" << endl;
				break;
			}
		}
		bSuccess = TRUE;
	} while (false);


	if (!bSuccess)
	{
		nError = WSAGetLastError();
		cout << "Wrong Messages" << nError << endl;
		if (INVALID_SOCKET != socketServ)
			closesocket(socketServ);
		if (INVALID_SOCKET != socketClient)
			closesocket(socketClient);
	}
	WSACleanup();
	system("pause");
	return 0;
}


