#include<iostream>
#include<WinSock2.h>
#include<WS2tcpip.h>
#include<string>
#pragma comment(lib,"ws2_32.lib")
#pragma warning(disable:4996)
#define _WINSOCK_DEPRECATED_NO_WARNINGS		// Ϊ����inet_ntoaʱ�����־���
using namespace std;

int main()
{
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;

	wVersionRequested = MAKEWORD(2, 2);		// ����Winsock��İ汾��
	err = WSAStartup(wVersionRequested, &wsaData);	// ��ʼ��winsock��
	if (err != 0) return 0;
	
	// �жϷ��صİ汾��ʱ����ȷ
	if(LOBYTE(wsaData.wVersion)!=2 || HIBYTE(wsaData.wVersion)!=2){
		WSACleanup();
		return 0;
	}
	// �����׽��֣����ڼ����ͻ��˵�����
	SOCKET sockSrv = socket(AF_INET, SOCK_STREAM, 0);

	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);	// ���������κο��õ�ip
	// ����ipv4��Э���
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(8000);		// ����˵Ķ˿�

	bind(sockSrv, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));	// ��
	listen(sockSrv, 5);		// ��������״̬

	SOCKADDR_IN addrClient;
	int len = sizeof(SOCKADDR);
	
	while (1) {
		cout << "�ȴ��ͻ���" << endl;
		// �����Ӷ�����ȡ���ǰ��һ���ͻ��������������Ϊ��������
		SOCKET sockConn = accept(sockSrv, (SOCKADDR*)&addrClient, &len);
		char sendBuf[1001];
		sprintf_s(sendBuf, "��ӭ��¼����ˣ�%s��", inet_ntoa(addrClient.sin_addr));		// ����ַ���
		send(sockConn, sendBuf, strlen(sendBuf) + 1, 0);
		char recvBuf[100];
		recv(sockConn, recvBuf, 100, 0);		// ���տͻ�����Ϣ
		cout << "���յ��ͻ�����Ϣ:" << recvBuf << endl;		// ��ӡ�ͻ�����Ϣ
		puts("�Ƿ����:y/n");
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