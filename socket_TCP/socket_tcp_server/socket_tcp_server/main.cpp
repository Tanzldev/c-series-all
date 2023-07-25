#include<iostream>
#include<WinSock2.h>
#include<WS2tcpip.h>
#include<string>
#pragma comment(lib,"ws2_32.lib")
#pragma warning(disable:4996)
#define _WINSOCK_DEPRECATED_NO_WARNINGS		
#define BUF_LEN 300

/*
	1.�����--�ͻ��˼��໥ͨ��
	2.�������ݣ�ͨ��forѭ������send()������Է��������ݣ�����������ɺ����shutdowun()�����������ٷ�������
	3.�������ݣ���֪���ж������Է���˵����ݣ�ͨ��whileѭ����recv()�����ķ���ֵ���ж��Ƿ������Ƿ�������
*/
int main() 
{
	WORD wVersionRequested;
	WSADATA wsaData;
	int err, i, iRes;

	wVersionRequested = MAKEWORD(2, 2);

	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0) {
		return 0;
	}
	// �жϷ��صİ汾���Ƿ���ȷ
	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {
		WSACleanup();
		return 0;
	}
	SOCKET sockSrv = socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);	// ʹ�õ�ǰ�����������IP
	addrSrv.sin_family = AF_INET;		// �׽���ʹ�õ�Э����
	addrSrv.sin_port = htons(8000);		// ʹ�õĶ˿�
	
	bind(sockSrv, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));	// �����ص�ַ���ӵ��׽�������
	listen(sockSrv, 5);		// ��������
	
	SOCKADDR_IN addrClient;
	int len = sizeof(SOCKADDR);
	
	while (1) {
		std::cout << "----------Server is Listening------------" << std::endl;
		// ���������������ȡ����ǰ���һ���ͻ��������������б�Ϊ��������
		SOCKET sockConn = accept(sockSrv, (SOCKADDR*)&addrClient, &len);
		//std::string sendBuf;
		char sendBuf[100] = "";
		for (i = 0; i < 10; i++) {
			//sendBuf = i + 1 + ":��ӭ��¼������������1+1=?" + (std::string)inet_ntoa(addrClient.sin_addr);		// ǿ������ת��
			sprintf_s(sendBuf, "No. %dwelcome to serve��please answer1+1=�� Client's ip:%s\n", i + 1, inet_ntoa(addrClient.sin_addr));
			send(sockConn, sendBuf, strlen(sendBuf),0);		// �����ַ������ͻ���
			memset(sendBuf, 0, sizeof(sendBuf));
		}

		// ���ݷ��ͽ���������shutdown�����������ٷ������ݣ���ʱ�ͻ�����Ȼ���Խ�������
		iRes = shutdown(sockConn, SD_SEND);
		if (iRes == SOCKET_ERROR) {
			std::cout << "shutdown failed with error:" << WSAGetLastError() << std::endl;
			closesocket(sockConn);
			WSACleanup();
			return 1;
		}

		// ���ͽ�������ʼ���տͻ��˷��͵���Ϣ
		char recvBuf[BUF_LEN];
		do {
			iRes = recv(sockConn, recvBuf, BUF_LEN, 0);		// ��������
			if (iRes > 0) {
				std::cout << "Recv bytes" << iRes << std::endl;
				for (i = 0; i < iRes; i++) {
					std::cout << recvBuf[i];
				}
				std::cout << std::endl;
			}
			else if (iRes == 0) {
				std::cout << "client's socket shuedown" << std::endl;
			}
			else {
				std::cout << "recv failed with error:" << WSAGetLastError() << std::endl;
				closesocket(sockConn);
				WSACleanup();
				return 1;
			}
		} while (iRes > 0);

		closesocket(sockConn);
		std::cout << "go on listening ��y/n" << std::endl;
		char ch[2];
		std::cin >> ch;
		if (ch[0] != 'y') {
			break;
		}
	}
	closesocket(sockSrv);
	WSACleanup();
	   	  
	system("pause");
	return 0;
}