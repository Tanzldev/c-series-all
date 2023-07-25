#include<iostream>
#include<WinSock2.h>
#include<WS2tcpip.h>
#include<Windows.h>
#include<process.h>
#include<string>
#pragma comment(lib,"ws2_32.lib")
#pragma warning(disable:4996)
#define _WINSOCK_DEPRECATED_NO_WARNINGS		
#define BUF_SIZE 64

int main() {
	WSADATA wsd;
	SOCKET sHost;
	SOCKADDR_IN servAddr;		// 服务器的地址
	int retVal;		// 调用Socket函数的返回值
	char buf[BUF_SIZE];

	// 初始化socket环境
	if (WSAStartup(MAKEWORD(2, 2), &wsd) != 0) {
		std::cout << "WSAStartup failed!" << std::endl;
		return -1;
	}
	sHost = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	// 设置服务器socket地址
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	servAddr.sin_port = htons(6000);
	int sServerAddlen = sizeof(servAddr);

	// 调用ioctlsocket()函数将其设置为非阻塞模式
	int iMode = 1;
	retVal = ioctlsocket(sHost, FIONBIO, (u_long FAR*)&iMode);

	if (retVal == SOCKET_ERROR) {
		std::cout << "icotlsocket failed" << std::endl;
		WSACleanup();
		return -1;
	}
	std::cout << "client is running..." << std::endl;
	
	while (true) {
		// 连接到服务器
		retVal = connect(sHost, (LPSOCKADDR)&servAddr, sizeof(servAddr));
		if (SOCKET_ERROR == retVal) {
			int err = WSAGetLastError();
			// 无法立即完成的非阻塞Socket上的操作
			if (err == WSAEWOULDBLOCK || err == WSAEINVAL) {
				Sleep(1);
				std::cout << "check connect" << std::endl;
				continue;
			}
			else if (err== WSAEISCONN) {
				break;
			}
			else {
				std::cout << "connection failed" << std::endl;
				closesocket(sHost);
				WSACleanup();
				return -1;
			}
		}
	}
	
	while (true) {
		// 向服务器发送字符串，并显示反馈信息
		std::cout << "input s string to send:" << std::endl;
		std::string str;
		// 接收输入的数据
		std::cin >> str;
		// 将输入的数据复制到buf中
		ZeroMemory(buf, BUF_SIZE);
		strcpy(buf, str.c_str());
		if (strcmp(buf, "quite") == 0) {
			std::cout << "quite" << std::endl;
			break;
		}
		while (true) {
			retVal = send(sHost, buf, strlen(buf), 0);
			if (SOCKET_ERROR == retVal) {
				int err = WSAGetLastError();
				if (err == WSAEWOULDBLOCK) {
					// 无法立即完成非阻塞套接字上的操作
					Sleep(5);
					continue;
				}
				else {
					std::cout << "send data!" << std::endl;
					closesocket(sHost);
					WSACleanup();
					return -1;
				}

			}
			break;
		}
	}


	system("pause");
	return 0;
}