#include<iostream>
#include<WinSock2.h>
#include<WS2tcpip.h>
#pragma comment(lib,"ws2_32.lib")
#pragma warning(disable:4996)
#define _WINSOCK_DEPRECATED_NO_WARNINGS	


char wbuf[50];
int main() {

	int sockfd;
	int size;
	char on = 1;
	struct sockaddr_in saddr;
	int ret;

	size = sizeof(struct sockaddr_in);
	memset(&saddr, 0, size);

	WORD wVersionRequested;
	WSADATA wsaData;
	int err;


	wVersionRequested = MAKEWORD(2, 2);
	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0) return 0;

	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(8888);
	saddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	sockfd = socket(AF_INET, SOCK_DGRAM, 0);		// 创建数据报套接字 
	if (sockfd < 0) {
		std::cout << "failed socket" << std::endl;
		return -1;
	}
	// 设置端口复用
	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));

	while (1) {
		std::cout << "please enter data:" << std::endl;
		std::cin >> wbuf;

		ret = sendto(sockfd, wbuf, sizeof(wbuf), 0, (struct sockaddr*)&saddr, sizeof(struct sockaddr));
		
		if (ret < 0) {
			std::cout << "sendto failed" << std::endl;
		}
		else {
			std::cout << "ret size" << ret << std::endl;
		}
		memset(wbuf, 0, sizeof(wbuf));
	}

	closesocket(sockfd);
	WSACleanup();

	system("pause");
	return 0;
}
