#include<iostream>
#include<WinSock2.h>
#include<WS2tcpip.h>
#pragma comment(lib,"ws2_32.lib")
#pragma warning(disable:4996)
#define _WINSOCK_DEPRECATED_NO_WARNINGS	

// TODO: �ͻ��ˣ���ָ���ķ���˷�����Ϣ
// ����˿ںŲ�����Ҳ���ԣ���Ϊ���ն���ԭʼ�׽��֣����������ץ�����˿���Ϣ��ԭʼ�׽���û��ʲô��

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


	wVersionRequested = MAKEWORD(2, 2);		// ����Winsock��İ汾��
	err = WSAStartup(wVersionRequested, &wsaData);		// ��ʼ��Winsock��
	if (err != 0) return 0;

	// ���÷���˵���Ϣ������ip��ַ���˿ںź�Э��
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(9999);
	saddr.sin_addr.s_addr = inet_addr("127.0.0.200");

	sockfd = socket(AF_INET, SOCK_DGRAM, 0);		// �������ݱ��׽��� 
	if (sockfd < 0) {
		std::cout << "failed socket" << std::endl;
		return -1;
	}

	// ���ö˿ڸ��ã������ͷź��������ٴ�ʹ��
	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));

	// ���͸�����˵���Ϣ
	std::cout << "please enter data:" << std::endl;
	std::cin >> wbuf;

	// ��������Ϣ���͸������
	ret = sendto(sockfd, wbuf, sizeof(wbuf), 0, (struct sockaddr*)&saddr, sizeof(struct sockaddr));
	if (ret < 0) {
		std::cout << "sendto failed" << std::endl;
	}
	else {
		// �����ͳɹ��᷵�ط������ݵ��ֽ���
		std::cout << "ret size" << ret << std::endl;
	}
	closesocket(sockfd);
	WSACleanup();

	system("pause");
	return 0;
}
