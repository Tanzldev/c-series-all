#include<iostream>
#include<WinSock2.h>
#include<WS2tcpip.h>
#include<string>
#pragma comment(lib,"ws2_32.lib")
#pragma warning(disable:4996)
#define _WINSOCK_DEPRECATED_NO_WARNINGS		
#define BUF_LEN 250

int main() {

	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	u_long argp;

	char szMsg[] = "hello server, I have received message";


	wVersionRequested = MAKEWORD(2, 2);		// 制定Winsock库版本
	err = WSAStartup(wVersionRequested, &wsaData);	// 初始化Winsock库
	if (err != 0)return 0;
	// 判断返回的版本号是否正确
	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {
		WSACleanup();
		return 0;
	}
	// 创建套接字
	SOCKET sockClient = socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(8000);

	err = connect(sockClient, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));
	if (SOCKET_ERROR == err) {
		std::cout << "connect is errorous, please restart" << std::endl;
		return 0;
	}

	char recvBuf[BUF_LEN];
	int i, cn = 1, iRes;

	double leftlen;
	unsigned char *pdata;

	iRes = recv(sockClient, (char*)&leftlen, sizeof(double), 0);		// 为了得到服务端发送数据的大小
	std::cout << "iRes=" << iRes << std::endl;
	std::cout << "leftlen=" << leftlen << std::endl;
	leftlen = ntohl(leftlen);
	std::cout << "leftlen=" << leftlen << std::endl;

	while (leftlen > 0) {
		// 接收来自服务器的信息
		iRes = recv(sockClient, recvBuf, BUF_LEN, 0);
		if (iRes > 0) {
			std::cout << "Recv" << cn++ << "  " << iRes << "  bytes" << std::endl;
			for (i = 0; i < iRes; i++) {
				std::cout << recvBuf[i];
			}
			std::cout << std::endl;

		}
		else if (iRes == 0) {
			std::cout << "Server is disconnnct!" << std::endl;
		}
		else {
			std::cout << "recv failed" << WSAGetLastError() << std::endl;
			closesocket(sockClient);
			WSACleanup();
			return 1;
		}

		leftlen = leftlen - iRes;
	}

	// 开始向服务器发送信息
	char sendBuf[100];
	sprintf_s(sendBuf, "I am a client, I have received message form you!");
	send(sockClient, sendBuf, strlen(sendBuf) + 1, 0);
	memset(sendBuf, 0, sizeof(sendBuf));

	puts("message had sent!");
	closesocket(sockClient);
	closesocket(sockClient);
	WSACleanup();

	system("pause");
	return 0;
}