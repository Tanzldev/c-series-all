#include<iostream>
#include<WinSock2.h>
#include<WS2tcpip.h>
#pragma comment(lib,"ws2_32.lib")
#pragma warning(disable:4996)
#define _WINSOCK_DEPRECATED_NO_WARNINGS	

// TODO �ж��׽����Ƿ��ڼ���״̬

int main() {

	WORD wVersionRequseted;
	WSADATA wsaData;
	int err;
	sockaddr_in service;
	char ip[] = "127.0.0.200";

	wVersionRequseted = MAKEWORD(2, 2);
	err = WSAStartup(wVersionRequseted, &wsaData);
	if (err != 0) return 0;

	SOCKET s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);		// ������ʽ�׽���
	if (s == INVALID_SOCKET) {
		std::cout << "Error ar socket" << std::endl;
		WSACleanup();
		return -1;
	}

	service.sin_family = AF_INET;
	service.sin_addr.s_addr = inet_addr(ip);
	service.sin_port = htons(9900);

	// ���׽���
	if (bind(s, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR) {
		std::cout << "bind failed" << std::endl;
		WSACleanup();
		return -1;
	}


	DWORD optVal = true;
	int optLen = sizeof(BOOL);

	// ��ȡѡ��SO_ACCEPTCONN��ֵ
	if (getsockopt(s, SOL_SOCKET, SO_KEEPALIVE, (char*)&optVal, &optLen) == SOCKET_ERROR) {
		std::cout << "getsockopt failed" << WSAGetLastError() << std::endl;
		WSACleanup();
		return -1;
	}
	else {
		std::cout << "����ǰ SO_KEEPALIVE = " << optVal << std::endl;
	}

	optVal = false;

	if (getsockopt(s, SOL_SOCKET, SO_KEEPALIVE, (char*)&optVal, &optLen) != SOCKET_ERROR) {
		std::cout << "���ñ�����Ƴɹ���" << std::endl;

	}

	if (getsockopt(s, SOL_SOCKET, SO_KEEPALIVE, (char*)&optVal, &optLen) == SOCKET_ERROR) {
		std::cout << "getsocketopt failed" << WSAGetLastError() << std::endl;
		WSACleanup();
		return -1;
	}
	else {
		std::cout << "���ú�ѡ��SO_KEEPALIVE = " << optVal << std::endl;
	}
	
	WSACleanup();
	system("pause");
	return 0;
}
