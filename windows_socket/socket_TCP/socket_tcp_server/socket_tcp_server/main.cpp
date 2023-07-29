#include<iostream>
#include<WinSock2.h>
#include<WS2tcpip.h>
#include<string>
#pragma comment(lib,"ws2_32.lib")
#pragma warning(disable:4996)
#define _WINSOCK_DEPRECATED_NO_WARNINGS		
#define BUF_LEN 300

/*
	1.服务端--客户端间相互通信
	2.发送数据，通过for循环调用send()函数向对方发送数据，发送数据完成后调用shutdowun()函数声明不再发送数据
	3.接收数据，不知道有多少来自服务端的数据，通过while循环和recv()函数的返回值来判断是否数据是否接收完毕
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
	// 判断返回的版本号是否正确
	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {
		WSACleanup();
		return 0;
	}
	SOCKET sockSrv = socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);	// 使用当前主机任意可用IP
	addrSrv.sin_family = AF_INET;		// 套接字使用的协议族
	addrSrv.sin_port = htons(8000);		// 使用的端口
	
	bind(sockSrv, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));	// 将本地地址链接到套接字身上
	listen(sockSrv, 5);		// 启动监听
	
	SOCKADDR_IN addrClient;
	int len = sizeof(SOCKADDR);
	
	while (1) {
		std::cout << "----------Server is Listening------------" << std::endl;
		// 从连接请求队列中取出最前面的一个客户端请求，若请求列表为空则阻塞
		SOCKET sockConn = accept(sockSrv, (SOCKADDR*)&addrClient, &len);
		//std::string sendBuf;
		char sendBuf[100] = "";
		for (i = 0; i < 10; i++) {
			//sendBuf = i + 1 + ":欢迎登录服务器，请问1+1=?" + (std::string)inet_ntoa(addrClient.sin_addr);		// 强制类型转换
			sprintf_s(sendBuf, "No. %dwelcome to serve，please answer1+1=？ Client's ip:%s\n", i + 1, inet_ntoa(addrClient.sin_addr));
			send(sockConn, sendBuf, strlen(sendBuf),0);		// 发送字符串给客户端
			memset(sendBuf, 0, sizeof(sendBuf));
		}

		// 数据发送结束，调用shutdown函数声明不再发送数据，此时客户端仍然可以接收数据
		iRes = shutdown(sockConn, SD_SEND);
		if (iRes == SOCKET_ERROR) {
			std::cout << "shutdown failed with error:" << WSAGetLastError() << std::endl;
			closesocket(sockConn);
			WSACleanup();
			return 1;
		}

		// 发送结束，开始接收客户端发送的信息
		char recvBuf[BUF_LEN];
		do {
			iRes = recv(sockConn, recvBuf, BUF_LEN, 0);		// 接收数据
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
		std::cout << "go on listening ？y/n" << std::endl;
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