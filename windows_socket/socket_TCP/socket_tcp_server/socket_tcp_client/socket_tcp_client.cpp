// socket_tcp_client.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include<iostream>
#include<WinSock2.h>
#include<WS2tcpip.h>
#include<string>
#pragma comment(lib,"ws2_32.lib")
#pragma warning(disable:4996)
#define _WINSOCK_DEPRECATED_NO_WARNINGS		
#define BUF_LEN 300
int main()
{

	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	u_long argp;
	char szMsg[] = "hello！ I have received data";

	wVersionRequested = MAKEWORD(2, 2);		// 初始化Winsock库
	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0)return 0;

	// 判断返回的版本号是否正确
	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {
		WSACleanup();
		return 0;
	}

	SOCKET sockClient = socket(AF_INET, SOCK_STREAM, 0);	// 新键一个套接字
	SOCKADDR_IN addrSrv;
	
	addrSrv.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(8000);

	//向服务器发出请求
	err = connect(sockClient, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));
	if (SOCKET_ERROR == err) {
		std::cout << "connect server happen error！" << std::endl;
		return 0;
	}
	char recvBuf[BUF_LEN];
	int i, ch = 1, iRes;
	std::cout << "----------Client------------" << std::endl;
	do {
		iRes = recv(sockClient, recvBuf, BUF_LEN, 0);
		if (iRes > 0) {
			std::cout << "Recv " << iRes << " bytes" << std::endl;
			for (i = 0; i < iRes; i++) {
				std::cout << recvBuf[i];
			}
			std::cout << std::endl;
		}
		else if (iRes == 0) {
			std::cout << "server is disconnect" << std::endl;
		}
		else {
			std::cout << "recv failed" << WSAGetLastError() << std::endl;
			closesocket(sockClient);
			WSACleanup();
			return 0;
		}
	} while (iRes > 0);

	// 开始向服务端发送信息
	//std::string sendBuf;
	char sendBuf[100];
	for (i = 0; i < 10; i++) {
		//sendBuf = i + " 我是客户端";
		sprintf_s(sendBuf, "No.%d I am Client，1+1=2\n", i + 1);
		send(sockClient, sendBuf, strlen(sendBuf) + 1, 0);
		memset(sendBuf, 0, sizeof(sendBuf));
	}

	std::cout << "Sent data to server" << std::endl;
	closesocket(sockClient);
	WSACleanup();
	system("pause");
	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
