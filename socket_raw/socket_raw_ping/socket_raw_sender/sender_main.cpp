#include<iostream>
#include<WinSock2.h>
#include<WS2tcpip.h>
#pragma comment(lib,"ws2_32.lib")
#pragma warning(disable:4996)
#define _WINSOCK_DEPRECATED_NO_WARNINGS	

// TODO: 客户端，向指定的服务端发送信息
// 这里端口号不设置也可以，因为接收端是原始套接字，在网络层上抓包，端口信息对原始套接字没有什么用

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


	wVersionRequested = MAKEWORD(2, 2);		// 制作Winsock库的版本号
	err = WSAStartup(wVersionRequested, &wsaData);		// 初始化Winsock库
	if (err != 0) return 0;

	// 配置服务端的信息，包括ip地址、端口号和协议
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(9999);
	saddr.sin_addr.s_addr = inet_addr("127.0.0.200");

	sockfd = socket(AF_INET, SOCK_DGRAM, 0);		// 创建数据报套接字 
	if (sockfd < 0) {
		std::cout << "failed socket" << std::endl;
		return -1;
	}

	// 设置端口复用，就是释放后能马上再次使用
	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));

	// 发送给服务端的信息
	std::cout << "please enter data:" << std::endl;
	std::cin >> wbuf;

	// 将数据信息发送给服务端
	ret = sendto(sockfd, wbuf, sizeof(wbuf), 0, (struct sockaddr*)&saddr, sizeof(struct sockaddr));
	if (ret < 0) {
		std::cout << "sendto failed" << std::endl;
	}
	else {
		// 若发送成功会返回发送数据的字节数
		std::cout << "ret size" << ret << std::endl;
	}
	closesocket(sockfd);
	WSACleanup();

	system("pause");
	return 0;
}
