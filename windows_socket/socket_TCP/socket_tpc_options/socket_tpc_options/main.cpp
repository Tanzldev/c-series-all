#include<iostream>
#include<WinSock2.h>
#include<WS2tcpip.h>
#pragma comment(lib,"ws2_32.lib")
#pragma warning(disable:4996)
#define _WINSOCK_DEPRECATED_NO_WARNINGS	

// TODO 获取流和数据报套接字接收和发送的缓冲区大小

int main() {

	WORD wVersionRequseted;
	WSADATA wsaData;
	int err;
	wVersionRequseted = MAKEWORD(2, 2);
	err = WSAStartup(wVersionRequseted, &wsaData);
	if (err != 0) return 0;

	SOCKET s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);		// 创建流式套接字
	if (s == INVALID_SOCKET) {
		std::cout << "Error ar socket" << std::endl;
		WSACleanup();
		return -1;
	}

	SOCKET su = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);		// 创建数据报套接字
	if (su == INVALID_SOCKET) {
		std::cout << "Error ar socket" << std::endl;
		WSACleanup();
		return -1;
	}

	DWORD optVal;
	int optLen = sizeof(optVal);
	
	// 获取流式套接字接收缓冲区大小
	if (getsockopt(s, SOL_SOCKET, SO_RCVBUF, (char*)&optVal, &optLen) == SOCKET_ERROR) {
		std::cout << "getsockopt failed" << WSAGetLastError() << std::endl;
	}
	else {
		std::cout << "stream socket size:" << optVal << "bytes" << std::endl;
	}

	// 获取流套接字发送缓冲区大小
	if (getsockopt(s, SOL_SOCKET, SO_SNDBUF, (char *)&optVal, &optLen) == SOCKET_ERROR) {
		std::cout << "getsockopt failed" << WSAGetLastError() << std::endl;
	}
	else {
		std::cout << "stream socket size:" << optVal << "bytes" << std::endl;
	}

	// 获取数据报套接字接收缓冲区大小
	if (getsockopt(su, SOL_SOCKET, SO_RCVBUF, (char*)&optVal, &optLen) == SOCKET_ERROR) {
		std::cout << "getsockopt failed" << WSAGetLastError() << std::endl;
	}
	else {
		std::cout << "udp socket size:" << optVal << "bytes" << std::endl;
	}

	// 获取数据报套接字发送缓冲区大小
	if (getsockopt(su, SOL_SOCKET, SO_SNDBUF, (char *)&optVal, &optLen) == SOCKET_ERROR) {
		std::cout << "getsockopt failed" << WSAGetLastError() << std::endl;
	}
	else {
		std::cout << "udp socket size:" << optVal << "bytes" << std::endl;
	}
	system("pause");
	return 0;
}
