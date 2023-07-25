// socket_learn02_client.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include<WinSock2.h>
#include<WS2tcpip.h>
#pragma comment(lib,"ws2_32.lib")
#pragma warning(disable:4996)
#define _WINSOCK_DEPRECATED_NO_WARNINGS		// 为适用inet_ntoa时不出现警告

int main()
{
    std::cout << "Hello World!\n"; 
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;

	wVersionRequested = MAKEWORD(2, 2);		// 初始化Winsock库
	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0) {
		return 0;
	}
	// 判断返回的版本号是否正确
	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {
		WSACleanup();
		return 0;
	}

	SOCKET sockClient = socket(AF_INET, SOCK_STREAM, 0);	// 创建一个套接字
	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");	// 服务器的ip
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(8000);		// 服务端的端口

	err = connect(sockClient, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));
	if (SOCKET_ERROR == err) {
		std::cout << "服务器连接错误，请检查服务器是否启动！" << std::endl;
		return 0;
	}

	char recvBuf[100];
	recv(sockClient, recvBuf, 100, 0);		// 接收来自服务端的信息
	std::cout << "收到来自服务端的信息：" << recvBuf << std::endl;
	send(sockClient, "你好，我是客户端发送的信息", strlen("你好，我是客户端发送的信息") + 1,0);
	
	closesocket(sockClient);
	WSACleanup();		// 释放套接字

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
