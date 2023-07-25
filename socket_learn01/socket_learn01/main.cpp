#include<iostream>
#include<WinSock2.h>
#include<WS2tcpip.h>
#pragma comment(lib,"ws2_32.lib")
#pragma warning(disable:4996)
#define _WINSOCK_DEPRECATED_NO_WARNINGS

using namespace std;

int main() {

	int sfp;
	struct sockaddr_in s_add;
	unsigned short portnum = 10051;
	struct sockaddr_in serv = { 0 };
	char on = 0;
	
	int serv_len = sizeof(serv);
	
	WORD wVersionRequested;
	WSADATA  wsaData;
	int err;

	wVersionRequested = MAKEWORD(2, 2);			// �ƶ�Winsock��İ汾��
	err = WSAStartup(wVersionRequested, &wsaData);	// �����׽���
	if (err != 0) {
		return 0;
	}
	
	sfp = socket(AF_INET, SOCK_STREAM, 0);	// �����׽���
	if (-1 == sfp) {
		cout << "socket err" << endl;
	}
	cout << "socket ok!" << endl;
	// ��ȡ�׽��ֵĵ�ַ�Ͷ˿�ֵ
	cout << inet_ntoa(serv.sin_addr) << "  " << ntohs(serv.sin_port) << endl;

	setsockopt(sfp, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
	memset(&s_add, 0, sizeof(struct sockaddr_in));
	s_add.sin_family = AF_INET;
	s_add.sin_addr.s_addr = inet_addr("0.0.0.0");
	s_add.sin_port = htons(portnum);
	        
	
	
	//��struct sockaddr *
	if (-1 == bind(sfp, (struct sockaddr *)(&s_add), sizeof(struct sockaddr))) {
		cout << "bind err!" << endl;
		return -1;
	}
	cout << "bind ok!" << endl;
	getsockname(sfp, (struct sockaddr *)&serv, &serv_len);

	// ����׽��ֵ�ַ�Ͷ˿�ֵ
	cout << inet_ntoa(serv.sin_addr) << " " << ntohs(serv.sin_port) << endl;

	WSACleanup();

	cout << "hello world" << endl;
	system("pause");
	return 0;
}
