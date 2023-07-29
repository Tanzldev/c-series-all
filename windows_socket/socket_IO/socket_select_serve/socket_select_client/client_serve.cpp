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
	SOCKADDR_IN servAddr;		// �������ĵ�ַ
	int retVal;		// ����Socket�����ķ���ֵ
	char buf[BUF_SIZE];

	// ��ʼ��socket����
	if (WSAStartup(MAKEWORD(2, 2), &wsd) != 0) {
		std::cout << "WSAStartup failed!" << std::endl;
		return -1;
	}
	sHost = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	// ���÷�����socket��ַ
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	servAddr.sin_port = htons(6000);
	int sServerAddlen = sizeof(servAddr);

	// ����ioctlsocket()������������Ϊ������ģʽ
	int iMode = 1;
	retVal = ioctlsocket(sHost, FIONBIO, (u_long FAR*)&iMode);

	if (retVal == SOCKET_ERROR) {
		std::cout << "icotlsocket failed" << std::endl;
		WSACleanup();
		return -1;
	}
	std::cout << "client is running..." << std::endl;
	
	while (true) {
		// ���ӵ�������
		retVal = connect(sHost, (LPSOCKADDR)&servAddr, sizeof(servAddr));
		if (SOCKET_ERROR == retVal) {
			int err = WSAGetLastError();
			// �޷�������ɵķ�����Socket�ϵĲ���
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
		// ������������ַ���������ʾ������Ϣ
		std::cout << "input s string to send:" << std::endl;
		std::string str;
		// �������������
		std::cin >> str;
		// ����������ݸ��Ƶ�buf��
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
					// �޷�������ɷ������׽����ϵĲ���
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