#include<iostream>
#include<WinSock2.h>
#include<WS2tcpip.h>
#pragma comment(lib, "WS2_32")
#pragma warning(disable:4996)
#define _WINSOCK_DEPRECATED_NO_WARNINGS	
#define SIO_RCVALL _WSAIOW(IOC_VENDOR,1)
// NOTE：使用了原始套接字，需要以管理员的身份运行程序，不然原始套接字创建不成功
// TODO: 创建一个能接收发往本地主机所有的ip包的套接字
// 能区分是客户端是ping请求命令来的，还是UDP请求来的

char rbuf[500];

typedef struct _IP_HEADER {		// IP头定义
	char m_cVersionAndHeaderLen;		// 版本信息
	char m_cTypeOfService;				// 服务类型
	short m_sTotalLenOfPacket;			// 数据包长度
	short m_sPacketID;		// 数据包标识
	short m_sSliceinfo;					// 分片使用
	char m_cTTL;						// 存活时间
	char m_cTypeOfProtocol;				// 协议类型
	short m_sCheckSum;					// 检验和
	unsigned int m_uiSourIp;			// 来源ip地址
	unsigned int m_uiDestIp;			// 目的ip地址
}IP_HEADER, *PIP_HEADER;

typedef struct _UDP_HEADER {	// UDP首部定义
	unsigned short m_usSourPort;		// 源端口号
	unsigned short m_usDestPort;		// 目的端口号
	unsigned short m_usLength;			// 数据包长度
	unsigned short m_usCheckSum;

}UDP_HEADER, *PUDP_HEADER;



int main() {

	int sockfd;
	int size;
	int ret;
	char on = 1;

	struct sockaddr_in saddr;
	struct sockaddr_in raddr;

	IP_HEADER iph;
	UDP_HEADER udph;

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
	saddr.sin_port = htons(9999);		// 这里的端口号无实际用途
	saddr.sin_addr.s_addr = inet_addr("127.0.0.200");		// 绑定本机中能用的ip地址

	// 创建能接收所有发往主机的ip包
	sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_IP);
	std::cout << sockfd << std::endl;
	if (sockfd < 0) {
		std::cout << "socket failed" << std::endl;
		return -1;
	}

	// 设置端口复用
	// setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));

	ret = bind(sockfd, (struct sockaddr*)&saddr, sizeof(struct sockaddr));
	if (ret < 0) {
		std::cout << "sbind faild" << std::endl;
		return -1;
	}

	DWORD dwlen[10], dwlenRtend = 0, Optval = 1;

	//WSAIoctl(sockfd, SIO_RCVALL, &Optval, sizeof(Optval), &dwlen, sizeof(dwlen), &dwlenRtend, NULL, NULL);
	WSAIoctl(sockfd, SIO_RESERVED_1, &Optval, sizeof(Optval), &dwlen, sizeof(dwlen), &dwlenRtend, NULL, NULL);

	int val = sizeof(struct sockaddr);

	while (1) {
		std::cout << "waiting data" << std::endl;
		ret = recvfrom(sockfd, rbuf, 500, 0, (struct sockaddr*)&raddr, &val);
		if (ret < 0) {
			std::cout << "recvfrom failed！" << std::endl;
			return -1;
		}

		// 获取IP头部后能够输出客户端ip地址和客户端请求的ip地址
		memcpy(&iph, rbuf, 20);		// 将缓冲区前20字节复制到iph中

		struct in_addr ias, iad;
		ias.s_addr = iph.m_uiSourIp;
		iad.s_addr = iph.m_uiDestIp;
		char dip[100];
		strcpy_s(dip, inet_ntoa(iad));

		//std::cout << "m_cTypeOfProtocol=" << iph.m_cTypeOfProtocol << std::endl;		// 输出不正确需要用%d指定类型
		printf("iph.m_cTypeOfProtocol=%d\n", iph.m_cTypeOfProtocol);
		switch (iph.m_cTypeOfProtocol)
		{
		case IPPROTO_ICMP:
			std::cout << "收到ICMP包" << std::endl;
			break;

		case IPPROTO_UDP:
			std::cout << "收到UDP包" << std::endl;
			// 获取UDP头部后，能够输出客户端的port号和请求的服务端的port号
			memcpy(&udph, rbuf + 20, 8);	// 将IP包头后的8字节复制到udph中
			std::cout << "recv data:" << rbuf + 28 << std::endl;
			break;
		default:
			std::cout << "解析出错" << std::endl;
			break;
		}

		std::cout << std::endl;
		std::cout << "------客户端发起请求的ip地址和port号信息如下：--------" << std::endl;
		std::cout << "sIP=" << inet_ntoa(ias)<<"  sPort="<< ntohs(udph.m_usSourPort) << std::endl;
		std::cout << "dIp=" << dip << "  sPort=" << ntohs(udph.m_usDestPort) << std::endl;
		
		std::cout << std::endl;
	}


	closesocket(sockfd);
	WSACleanup();
	system("pause");
	return 0;
}
