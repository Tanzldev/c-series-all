#include<iostream>
#include<WinSock2.h>
#include<WS2tcpip.h>
#include<string>
#pragma comment(lib,"ws2_32.lib")
#pragma warning(disable:4996)
#define _WINSOCK_DEPRECATED_NO_WARNINGS		
#define BUF_LEN 300

int main() {

	WORD wVersionRequested;
	WSADATA wsaData;
	int err, i, iRes;

	wVersionRequested = MAKEWORD(2, 2);		// 制定Winsock库版本
	err = WSAStartup(wVersionRequested, &wsaData);	// 初始化Winsock库
	if (err != 0)return 0;
	// 判断返回的版本号是否正确
	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {
		WSACleanup();
		return 0;
	}
	// 创建套接字
	SOCKET sockSrv = socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(8000);
	bind(sockSrv, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));	// 将套接字与地址信息绑定
	listen(sockSrv, 5);

	SOCKADDR_IN addrClient;
	int cn = 0, len = sizeof(SOCKADDR);

	while (1) {
		std::cout << "waiting for a client" << std::endl;
		SOCKET sockConn = accept(sockSrv, (SOCKADDR*)&addrClient, &len);
		char sendBuf[111] = "";		// 定长的数据

		for (cn = 0; cn < 50; cn++) {
			memset(sendBuf, 'a', 111);
			if (cn == 49) {
				sendBuf[110] = 'b';
			}
			send(sockConn, sendBuf, 111, 0);	// 将数据发送给客户端
		}

		// 接收来自客户端的信息
		char recvBuf[BUF_LEN];

		// 持续接收客户端的数据，直到对方关闭连接
		do {
			iRes = recv(sockConn, recvBuf, BUF_LEN, 0);
			if (iRes > 0) {
				std::cout << "Recv" << iRes << "bytes" << std::endl;
				for (i = 0; i < iRes; i++) {
					std::cout << recvBuf[i];
				}
				std::cout << std::endl;
			}
			else if (iRes == 0) {
				std::cout << "Client is disconnect" << std::endl;
			}
			else {
				std::cout << "recv failed with error" << WSAGetLastError() << std::endl;
				closesocket(sockConn);
				WSACleanup();
				return 1;
			}
		} while (iRes > 0);

		closesocket(sockConn);
		std::cout << "Continue listening? y/n" << std::endl;
		char ch[2];
		std::cin >> ch;
		if (ch[0] != 'y') {
			break;
		}
	}
	closesocket(sockSrv);	// 关闭监听套接字
	WSACleanup();		// 释放套接字
	  
	system("psuse");
	return 0;
}