#include<iostream>
#include<WinSock2.h>
#include<WS2tcpip.h>
#pragma comment(lib,"ws2_32.lib")
#pragma warning(disable:4996)
#define _WINSOCK_DEPRECATED_NO_WARNINGS	

char rbuf[50];
int main() {

	int sockfd;
	int size;
	int ret;
	char on = 1;

	struct sockaddr_in saddr;
	struct sockaddr_in raddr;

	WORD wVersionRequested;
	WSADATA wsaData;
	int err;

	wVersionRequested = MAKEWORD(2, 2);
	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0) {
		return 0;
	}

	size = sizeof(struct sockaddr_in);
	memset(&saddr, 0, size);
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(9999);
	saddr.sin_addr.s_addr = htonl(INADDR_ANY);		// 绑定本机中能用的ip地址

	// 创建UDP的套接字
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd < 0) {
		std::cout << "socket failed" << std::endl;
		return -1;
	}
		
	// 设置端口复用
	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));

	ret = bind(sockfd, (struct sockaddr*)&saddr, sizeof(struct sockaddr));
	if (ret < 0) {
		std::cout << "sbind faild" << std::endl;
		return -1;
	}

	int val = sizeof(struct sockaddr);
	std::cout << "waiting data" << std::endl;
	
	ret = recvfrom(sockfd, rbuf, 50, 0, (struct sockaddr*)&raddr, &val);

	if (ret < 0) {
		std::cout << "recvfrom failed！" << std::endl;
	}

	std::cout << "recv data " << rbuf << std::endl;

	closesocket(sockfd);
	WSACleanup();
	system("pause");
	return 0;
}
