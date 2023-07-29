#include<iostream>
#include<WinSock2.h>
#include<WS2tcpip.h>
#pragma comment(lib, "WS2_32")
#pragma warning(disable:4996)
#define _WINSOCK_DEPRECATED_NO_WARNINGS	

// NOTE��ʹ����ԭʼ�׽��֣���Ҫ�Թ���Ա��������г��򣬲�Ȼԭʼ�׽��ִ������ɹ�
// TODO:����ԭʼ�׽��֣�ʹ�����ݱ�Э�飬����UDP���ģ�����ͻ���ip��ַ��port��
// �Լ�����ͻ�������ķ����ip��ַ��port��

char rbuf[500];

typedef struct _IP_HEADER {		// IPͷ����
	char m_cVersionAndHeaderLen;		// �汾��Ϣ
	char m_cTypeOfService;				// ��������
	short m_sTotalLenOfPacket;			// ���ݰ�����
	short m_sSliceinfo;					// ���ݰ���ʶ
	char m_cTTL;						// ��Ƭʹ��
	char m_cTypeOfProtocol;				// ���ʱ��
	short m_sCheckSum;					// Э������
	unsigned int m_uiSourIp;			// У���
	unsigned int m_uiDestIp;			// Ŀ��ip��ַ
}IP_HEADER,*PIP_HEADER;

typedef struct _UDP_HEADER {	// UDP�ײ�����
	unsigned short m_usSourPort;		// Դ�˿ں�
	unsigned short m_usDestPort;		// Ŀ�Ķ˿ں�
	unsigned short m_usLength;			// ���ݰ�����
	unsigned short m_usCheckSum;		
	
}UDP_HEADER,*PUDP_HEADER;



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
	saddr.sin_port = htons(8888);		// ����Ķ˿ں���ʵ����;
	saddr.sin_addr.s_addr = htonl(INADDR_ANY);		// �󶨱��������õ�ip��ַ

	// ����UDP���׽���,IPPROTO_UDP��ʾ�׽�����ʹ�õ�Э��
	sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);
	std::cout << sockfd << std::endl;
	if (sockfd < 0) {
		std::cout << "socket failed" << std::endl;
		return -1;
	}

	// ���ö˿ڸ���
	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));

	ret = bind(sockfd, (struct sockaddr*)&saddr, sizeof(struct sockaddr));
	if (ret < 0) {
		std::cout << "sbind faild" << std::endl;
		return -1;
	}

	int val = sizeof(struct sockaddr);
	while (1) {
		std::cout << "waiting data" << std::endl;
		ret = recvfrom(sockfd, rbuf, 500, 0, (struct sockaddr*)&raddr, &val);
		if (ret < 0) {
			std::cout << "recvfrom failed��" << std::endl;
			return -1;
		}
		
		// ��ȡIPͷ�����ܹ�����ͻ���ip��ַ�Ϳͻ��������ip��ַ
		memcpy(&iph, rbuf, 20);		// ��������ǰ20�ֽڸ��Ƶ�iph��

		// ��ȡUDPͷ�����ܹ�����ͻ��˵�port�ź�����ķ���˵�port��
		memcpy(&udph, rbuf + 20, 8);	// ��IP��ͷ���8�ֽڸ��Ƶ�udph��

		int srcp = ntohs(udph.m_usSourPort);
		struct in_addr ias, iad;
		ias.s_addr = iph.m_uiSourIp;
		iad.s_addr = iph.m_uiDestIp;

		char dip[100];
		strcpy_s(dip, inet_ntoa(iad));
		std::cout << "------�����пͻ��ˣ�ip��ַ��port����Ϣ���£�--------" << std::endl;
		std::cout << "sIP=" << inet_ntoa(ias) << std::endl;
		std::cout << "sPort=" << ntohs(udph.m_usSourPort) << std::endl;
		std::cout << "------�ͻ��˷��������ip��ַ��port����Ϣ���£�--------" << std::endl;
		std::cout << "dIp=" << dip << std::endl;
		std::cout << "dPort=" << ntohs(udph.m_usDestPort) << std::endl;
		std::cout << "------�ͻ���Я�����������£�--------" << std::endl;
		std::cout << "recv data:" << rbuf + 28 << std::endl;
		std::cout << std::endl;
	}


	closesocket(sockfd);
	WSACleanup();
	system("pause");
	return 0;
}
