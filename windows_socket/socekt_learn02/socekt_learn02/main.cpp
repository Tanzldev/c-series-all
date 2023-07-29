#include<iostream>
#include<WinSock2.h>
#include<WS2tcpip.h>
#include<string>
#pragma comment(lib,"ws2_32.lib")
#pragma warning(disable:4996)
#define _WINSOCK_DEPRECATED_NO_WARNINGS		// 为适用inet_ntoa时不出现警告
using namespace std;

int main()
{
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;

	wVersionRequested = MAKEWORD(2, 2);		// 制作Winsock库的版本号
	err = WSAStartup(wVersionRequested, &wsaData);	// 初始化winsock库
	if (err != 0) return 0;
	
	// 判断返回的版本号时候正确
	if(LOBYTE(wsaData.wVersion)!=2 || HIBYTE(wsaData.wVersion)!=2){
		WSACleanup();
		return 0;
	}
	// 创建套接字，用于监听客户端的连接
	SOCKET sockSrv = socket(AF_INET, SOCK_STREAM, 0);

	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);	// 适用主机任何可用的ip
	// 适用ipv4的协议簇
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(8000);		// 服务端的端口

	bind(sockSrv, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));	// 绑定
	listen(sockSrv, 5);		// 开启监听状态

	SOCKADDR_IN addrClient;
	int len = sizeof(SOCKADDR);
	
	while (1) {
		cout << "等待客户端" << endl;
		// 从连接队列中取出最靠前的一个客户端请求，如果队列为空则阻塞
		SOCKET sockConn = accept(sockSrv, (SOCKADDR*)&addrClient, &len);
		char sendBuf[1001];
		sprintf_s(sendBuf, "欢迎登录服务端（%s）", inet_ntoa(addrClient.sin_addr));		// 组成字符串
		send(sockConn, sendBuf, strlen(sendBuf) + 1, 0);
		char recvBuf[100];
		recv(sockConn, recvBuf, 100, 0);		// 接收客户端信息
		cout << "接收到客户端信息:" << recvBuf << endl;		// 打印客户端信息
		puts("是否监听:y/n");
		char ch[2];
		cin >> ch;
		if (tolower(ch[0]) == 'n') {
			break;
		}
		closesocket(sockSrv);
		WSACleanup();
	}
	system("pause");
	return 0;
}