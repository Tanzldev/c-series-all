#include<iostream>
#include<WinSock2.h>
#include<WS2tcpip.h>
#pragma comment(lib,"ws2_32.lib")
#pragma warning(disable:4996)
#define _WINSOCK_DEPRECATED_NO_WARNINGS	

// TODO ��ȡ�׽��ֵ�����

int main() {

	WORD wVersionRequseted;
	WSADATA wsaData;
	int err;
	wVersionRequseted = MAKEWORD(2, 2);
	err = WSAStartup(wVersionRequseted, &wsaData);
	if (err != 0) return 0;

	SOCKET s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);		// ������ʽ�׽���
	if (s == INVALID_SOCKET) {
		std::cout << "Error ar socket" << std::endl;
		WSACleanup();
		return -1;
	}

	SOCKET su = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);		// �������ݱ��׽���
	if (su == INVALID_SOCKET) {
		std::cout << "Error ar socket" << std::endl;
		WSACleanup();
		return -1;
	}

	DWORD optVal;
	int optLen = sizeof(optVal);

	// ��ȡ��ʽ�׽��ֽ��ջ�������С
	if (getsockopt(s, SOL_SOCKET, SO_TYPE, (char*)&optVal, &optLen) == SOCKET_ERROR) {
		std::cout << "getsockopt failed" << WSAGetLastError() << std::endl;
	}
	else {

		if (SOCK_STREAM == optVal) {	// SOCK_STREAM�궨��ָΪ1
			std::cout << "��ǰ�׽�������ʽ�׽���" << std::endl;
		}
		else if(SOCK_DGRAM == optVal){
			std::cout << "��ǰ�׽��������ݱ��׽���" << std::endl;
		}

	}


	// ��ȡ���ݱ��׽��ַ��ͻ�������С
	if (getsockopt(su, SOL_SOCKET, SO_TYPE, (char *)&optVal, &optLen) == SOCKET_ERROR) {
		std::cout << "getsockopt failed" << WSAGetLastError() << std::endl;
	}
	else {
		
		if (SOCK_STREAM == optVal) {	// SOCK_STREAM�궨��ָΪ1
			std::cout << "��ǰ�׽�������ʽ�׽���" << std::endl;
		}
		else if (SOCK_DGRAM == optVal) {
			std::cout << "��ǰ�׽��������ݱ��׽���" << std::endl;
		}
	}
	system("pause");
	return 0;
}
