#include<iostream>
#include<WinSock2.h>
#include<WS2tcpip.h>
#pragma comment(lib,"ws2_32.lib")
#pragma warning(disable:4996)
#define _WINSOCK_DEPRECATED_NO_WARNINGS	

// TODO 判断套接字是否处于监听状态

int main() {

	WORD wVersionRequseted;
	WSADATA wsaData;
	int err;
	sockaddr_in service;
	char ip[] = "127.0.0.200";

	wVersionRequseted = MAKEWORD(2, 2);
	err = WSAStartup(wVersionRequseted, &wsaData);
	if (err != 0) return 0;

	SOCKET s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);		// 创建流式套接字
	if (s == INVALID_SOCKET) {
		std::cout << "Error ar socket" << std::endl;
		WSACleanup();
		return -1;
	}

	service.sin_family = AF_INET;
	service.sin_addr.s_addr = inet_addr(ip);
	service.sin_port = htons(9000);

	// 绑定套接字
	if (bind(s, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR) {	
		std::cout << "bind failed" << std::endl;
		WSACleanup();
		return -1;
	}


	DWORD optVal;
	int optLen = sizeof(optVal);

	// 获取选项SO_ACCEPTCONN的值
	if (getsockopt(s, SOL_SOCKET, SO_ACCEPTCONN, (char*)&optVal, &optLen) == SOCKET_ERROR) {
		std::cout << "getsockopt failed" << WSAGetLastError() << std::endl;
	}
	else {

		std::cout << "before listening SO_ACCEPTCONN = " << optVal << std::endl;

	}
	if (listen(s, 100) == SOCKET_ERROR) {
		std::cout << "listening failed" << WSAGetLastError() << std::endl;
		WSACleanup();
		return -1;
	}

	// 获取选项SO_ACCEPTCONN的值
	if (getsockopt(s, SOL_SOCKET, SO_ACCEPTCONN, (char*)&optVal, &optLen) == SOCKET_ERROR) {
		std::cout << "getsockopt failed" << WSAGetLastError() << std::endl;
		WSACleanup();
		return -1;
	}
	else {
		std::cout << "after listening, SO_ACCEPTCONN = " << optVal << std::endl;
	}

	WSACleanup();
	system("pause");
	return 0;
}
