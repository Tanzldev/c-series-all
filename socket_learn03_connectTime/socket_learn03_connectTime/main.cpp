#include<iostream>
#include<WinSock2.h>
#include<assert.h>
#include<string.h>
#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include<fcntl.h>
#include<time.h>

#pragma comment(lib,"ws2_32.lib")		// Winsock��������
#pragma warning(disable:4996)
#define _WINSOCK_DEPRECATED_NO_WARNINGS		// Ϊ������inet_ntoaʱ�����־���

#define BUFFER_SIZE 512

int main() {
	
	char ip[] = "127.0.0.1";		// �뱾��ͬһһ�����Σ����ǲ�����
	int port = 13334;
	struct sockaddr_in server_address;		// ʹ��ipv4��ר��socket��ַ

	WORD wVersionRequested;		// Winsock�淶�İ汾�ţ����ļ�Ws2_32.dll�İ汾��

	WSADATA wsaData;	// WSADATA�ṹ�屣����Windows�׽��ֵ������Ϣ
	int err;



	wVersionRequested = MAKEWORD(2, 2);		// ����Winsock�İ汾��
	err = WSAStartup(wVersionRequested, &wsaData);	 // ��ʼ��Winsock��
	if (err != 0) return 0;
	// �жϰ汾���Ƿ���ȷ
	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2 ) {
		WSACleanup();
		return 0;
	}
	
	memset(&server_address, 0, sizeof(server_address));
	server_address.sin_family = AF_INET;	// ���õ�Э����
	DWORD dwIP = inet_addr(ip);		// �����ip��ַת��Ϊ�޷��ų�����

	server_address.sin_addr.s_addr = dwIP;	// �����ֽ����ʾ��ip��ַ
	server_address.sin_port = htons(port);	// �����ֽ����ʾ�Ķ˿ںţ�htons��һ�������ֽ���ת��Ϊ�����ֽ���

	int sock = socket(PF_INET, SOCK_STREAM, 0);		// ����һ����ʽ�׽���
	assert(sock >= 0);
	long t1 = GetTickCount();

	// �ͻ���ʹ��connect�����������׽��ֽ������ӣ����ｫ�������ӳ�ʱ������-1
	int ret = connect(sock, (struct sockaddr *)&server_address, sizeof(server_address));

	std::cout << "connect ret code is:" << ret << std::endl;
	// connect���ӳ�ʱ��connect��������-1��ret=-1
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
	WSACleanup();		// �ͷ��׽��ֿ�

	system("pause");
	return 0;
}