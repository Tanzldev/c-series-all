#include<iostream>
#include<WinSock2.h>
#include<assert.h>
#include<string.h>
#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include<fcntl.h>
#include<time.h>

#pragma comment(lib,"ws2_32.lib")		// Winsock库的引入库
#pragma warning(disable:4996)
#define _WINSOCK_DEPRECATED_NO_WARNINGS		// 为了适用inet_ntoa时不出现警告

#define BUFFER_SIZE 512

int main() {
	
	char ip[] = "127.0.0.1";		// 与本机同一一个网段，但是不存在
	int port = 13334;
	struct sockaddr_in server_address;		// 使用ipv4的专用socket地址

	WORD wVersionRequested;		// Winsock规范的版本号，即文件Ws2_32.dll的版本号

	WSADATA wsaData;	// WSADATA结构体保存了Windows套接字的相关信息
	int err;



	wVersionRequested = MAKEWORD(2, 2);		// 制作Winsock的版本号
	err = WSAStartup(wVersionRequested, &wsaData);	 // 初始化Winsock库
	if (err != 0) return 0;
	// 判断版本号是否正确
	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2 ) {
		WSACleanup();
		return 0;
	}
	
	memset(&server_address, 0, sizeof(server_address));
	server_address.sin_family = AF_INET;	// 适用的协议族
	DWORD dwIP = inet_addr(ip);		// 将点分ip地址转化为无符号长整形

	server_address.sin_addr.s_addr = dwIP;	// 网络字节序表示的ip地址
	server_address.sin_port = htons(port);	// 网络字节序表示的端口号，htons将一个主机字节序转化为网络字节序

	int sock = socket(PF_INET, SOCK_STREAM, 0);		// 定义一个流式套接字
	assert(sock >= 0);
	long t1 = GetTickCount();

	// 客户端使用connect函数与服务端套接字进行连接，这里将出现连接超时，返回-1
	int ret = connect(sock, (struct sockaddr *)&server_address, sizeof(server_address));

	std::cout << "connect ret code is:" << ret << std::endl;
	// connect连接超时，connect函数返回-1，ret=-1
	if (ret == -1) {
		long t2 = GetTickCount();
		std::cout << "tiem used:" << t2 - t1 << std::endl;
		std::cout << "connect faild!" << std::endl;
		if (errno == EINPROGRESS) {
			std::cout << "unblock mode ret code" << std::endl;
		}
	}
	else {
		std::cout << "ret code is:" << ret << std::endl;
	}
	closesocket(sock);
	WSACleanup();		// 释放套接字库

	system("pause");
	return 0;
}