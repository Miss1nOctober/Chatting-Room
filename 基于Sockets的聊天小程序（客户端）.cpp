// 基于Sockets的聊天小程序（客户端）.cpp : 定义控制台应用程序的入口点。
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
	SOCKET socketClient = INVALID_SOCKET;//客户端的套接字
	do
	{
		WSADATA wsaData;
		if (0 != WSAStartup(MAKEWORD(2, 2), &wsaData))//叫醒
			break;
		//判断
		if (2 != LOBYTE(wsaData.wVersion) ||
			2 != HIBYTE(wsaData.wVersion))
			break;


		//拿手机
		socketClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (INVALID_SOCKET == socketClient)
			break;


		//拿到电话号码
		sockaddr_in addrServ = { 0 };
		addrServ.sin_family = AF_INET;
		addrServ.sin_port = htons(10800);
		addrServ.sin_addr.S_un.S_addr = inet_addr(SERVERIPADDRESS);


		//拨打号码
		if (SOCKET_ERROR == connect(socketClient, (SOCKADDR*)&addrServ, sizeof(addrServ)))
			break;


		char szRecvMessage[MAXBYTE] = { 0 };
		char szSendMessage[MAXBYTE] = { 0 };
		while (true)
		{
			int nResult = recv(socketClient, szRecvMessage, MAXBYTE, 0);
			if (nResult > 0)//接收到信息
			{
				cout << "Messages from Server:" << szRecvMessage << endl;
				cout << "Client Answer Back:";
				cin >> szSendMessage;
				if (SOCKET_ERROR == send(socketClient, szSendMessage, MAXBYTE, 0))
					break;//跳出循环
			}
			else if (nResult == 0)//连接被关闭
			{
				cout << "connection closed:" << endl;
				break;
			}
			else
			{
				cout << "unknown reason ：" << endl;
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

