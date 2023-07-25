#include<iostream>
#include<WinSock2.h>
#include<WS2tcpip.h>
#include<string>
#pragma comment(lib,"ws2_32.lib")
#pragma warning(disable:4996)
#define _WINSOCK_DEPRECATED_NO_WARNINGS		
#define BUF_LEN 300

struct MyData {
	double nLen;
	char data[0];
};

int main() {

	WORD wVersionRequseted;
	WSADATA wsaData;
	int err, i, iRes;
	wVersionRequseted = MAKEWORD(2, 2);
	err = WSAStartup(wVersionRequseted, &wsaData);
	if (err != 0) return 0;

	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {
		WSACleanup();
		return 0;
	}
	SOCKET socketSrv = socket(AF_INET, SOCK_STREAM, 0);
	SOCKET sockSrv = socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);	// ʹ�õ�ǰ�����������IP
	addrSrv.sin_family = AF_INET;		// �׽���ʹ�õ�Э����
	addrSrv.sin_port = htons(8000);		// ʹ�õĶ˿�

	bind(sockSrv, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));	// �����ص�ַ���ӵ��׽�������
	listen(sockSrv, 5);		// ��������

	SOCKADDR_IN addrClient;
	int cn = 0, len = sizeof(SOCKADDR);
	struct MyData *mydata;

	while (1)
	{
		std::cout << "-----------------waiting for a client----------------" << std::endl;
		SOCKET sockConn = accept(sockSrv, (SOCKADDR*)&addrClient, &len);
		cn = 5500;
		{
			mydata = (MyData*)malloc(sizeof(MyData) + cn);
			mydata->nLen = htonl(cn);	// ��������ת��Ϊ�����ֽ���
			memset(mydata->data, 'a', cn);
			mydata->data[cn - 1] = 'b';

			// ��ͻ��˷�������
			std::cout << "sizeof(mydata)" << sizeof(MyData) + cn << std::endl;
			send(sockConn, (char *)mydata, sizeof(MyData) + cn, 0);
			free(mydata);
		}

		char recvBuf[BUF_LEN];
		do {
			iRes = recv(sockConn, recvBuf, BUF_LEN, 0);
			if (iRes > 0) {
				std::cout << "Recv " << iRes << " bytes" << std::endl;
				for (i = 0; i < iRes; i++) {
					std::cout << recvBuf[i];
				}
				std::cout << std::endl;

			}
			else if (iRes == 0) {
				std::cout << "client is disconnect" << std::endl;
			}
			else {
				std::cout << "recv failed with error" << WSAGetLastError() << std::endl;
				closesocket(sockConn);
				WSACleanup();
				return 1;
			}

		} while (iRes > 0);

		closesocket(sockConn);
		puts("continue listening ? y/n");
		char ch[2];
		std::cin >> ch;
		if (ch[0] != 'y') {
			break;
		}
	}

	closesocket(socketSrv);
	WSACleanup();
	   
	system("pause");
	return 0;
}