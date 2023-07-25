#include<iostream>
#include<WinSock2.h>
#include<WS2tcpip.h>
#include<string>
#include<assert.h>
#include<stdio.h>
#pragma comment(lib,"ws2_32.lib")
#pragma warning(disable:4996)
#define _WINSOCK_DEPRECATED_NO_WARNINGS		

/*
	����˵����ͨ��ioctlsocket()�����������׽��ֵĹ���ģʽ
	SOCKET sock = socket(PF_INET, SOCK_STREAM, 0);	sock����Ĭ��ʹ������ģʽ���׽��֣�����������ʱ���ȴ�����ʱ��
	�������ȴ�ʱ���ڣ���Ȼû�����ӳɹ����򷵻ش���������retΪ-1

	res = ioctlsocket(sock, FIONBIO, (u_long FAR*)&argp);	ioctlsocket()�������׽�������Ϊ������ģʽ������������ʱ
	��δ���ӳɹ��������Ϸ��ش�����

*/

int main() {

	u_long argp;
	int res;
	char ip[] = "127.0.0.1";		// �����в����ڵ�ip��ַ
	int port = 13334;
	struct sockaddr_in server_address;

	WSADATA wsaData;
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);

	if (iResult != NO_ERROR) {
		std::cout << "error at WSAStartup" << std::endl;
	}

	memset(&server_address, 0, sizeof(server_address));

	server_address.sin_family = AF_INET;
	DWORD dwIP = inet_addr(ip);
	server_address.sin_addr.s_addr = dwIP;
	server_address.sin_port = htons(port);

	SOCKET sock = socket(PF_INET, SOCK_STREAM, 0);
	assert(sock >= 0);

	long t1 = GetTickCount();
	int ret = connect(sock, (struct sockaddr*)&server_address, sizeof(server_address));

	std::cout << "connect ret code is:" << ret << std::endl;
	if (ret == -1) {
		long t2 = GetTickCount();
		std::cout << "time used:" << t2 - t1 << std::endl;
		std::cout << "connect failed...." << std::endl;
		if (errno == EINPROGRESS) {
			std::cout << "unblock mode ret code..." << std::endl;
		}
	}
	else {
		std::cout << "ret code is:" << ret << std::endl;
	}

	argp = 1;

	// ���׽���ģʽ����Ϊ������ģʽ
	res = ioctlsocket(sock, FIONBIO, (u_long FAR*)&argp);		
	
	if (SOCKET_ERROR == res) {
		std::cout << "Error ar ioctlsocket" << WSAGetLastError() << std::endl;
		WSACleanup();
		return -1;
	}
	std::cout << "-----set the mode asyn-----" << std::endl;
	memset(&server_address, 0, sizeof(server_address));
	server_address.sin_family = AF_INET;
	dwIP = inet_addr(ip);
	server_address.sin_addr.s_addr = dwIP;
	server_address.sin_port = htons(port);

	t1 = GetTickCount();

	ret = connect(sock, (struct sockaddr*)&server_address, sizeof(server_address));
	std::cout << "connect ret code is:" << ret << std::endl;
	if (ret == -1) {
		long t2 = GetTickCount();
		std::cout << "time used:" << t2 - t1 << std::endl;
		std::cout << "connnect failed..." << std::endl;
		if (errno == EINPROGRESS) {
			std::cout << "unblock mode ret code..." << std::endl;
		}
	}
	else {
		std::cout << "ret code is:" << ret << std::endl;
	}
	closesocket(sock);
	WSACleanup();
	system("pause");
	return 0;
}