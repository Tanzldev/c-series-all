#include<iostream>
#include<WinSock2.h>
#include<WS2tcpip.h>
#include<string>
#pragma comment(lib,"ws2_32.lib")
#pragma warning(disable:4996)
#define _WINSOCK_DEPRECATED_NO_WARNINGS		


int main() {

	WSADATA wsaData;
	WSAStartup(WINSOCK_VERSION, &wsaData);

	USHORT uPort = 6000;
	SOCKET sListen = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);	// ������ʽ�׽���
	if (INVALID_SOCKET == sListen) {
		std::cout << "socket error" << GetLastError() << std::endl;
		return 0;
	}
	SOCKADDR_IN sin;
	sin.sin_family = AF_INET;
	sin.sin_port = htons(uPort);
	sin.sin_addr.S_un.S_addr = INADDR_ANY;

	if (SOCKET_ERROR == bind(sListen,(PSOCKADDR)&sin, sizeof(sin))) {
		std::cout<<"bind error:"<<WSAGetLastError()<<std::endl;
		closesocket(sListen);
		WSACleanup();
		return 0;
	}

	if (SOCKET_ERROR == listen(sListen, 5)) {
		std::cout << "listen error:" << WSAGetLastError() << std::endl;
		closesocket(sListen);
		WSACleanup();
		return 0;
	}
	fd_set fdSocket;
	FD_ZERO(&fdSocket);
	FD_SET(sListen, &fdSocket);		// ���׽���sListen���뵽set������

	while (TRUE) {
		fd_set fdRead = fdSocket;	// ��fdRead����ָ��fdSocket
		int iRet = select(0, &fdRead, NULL, NULL, NULL);
		if (iRet > 0) {
			for (size_t i = 0; i < fdSocket.fd_count; i++) {
				// ����׽���fd_array[i]�Ƿ�Ϊ����fdError�ĳ�Ա
				if (FD_ISSET(fdSocket.fd_array[i], &fdRead)) {
					if (fdSocket.fd_array[i] == sListen) {
						if (fdSocket.fd_count < FD_SETSIZE) {
							SOCKADDR_IN addrRemote;
							int iAddrLen = sizeof(addrRemote);
							SOCKET sNew = accept(sListen, (PSOCKADDR)&addrRemote, &iAddrLen);
							FD_SET(sNew, &fdSocket);
							std::cout << "���յ����ӣ�" << inet_ntoa(addrRemote.sin_addr);
						}
						else {
							std::cout << "����̫��" << std::endl;
							continue;
						}
						std::cout << std::endl;
					}
					else {
						char szText[256];
						int iRecv = recv(fdSocket.fd_array[i], szText, strlen(szText), 0);
						if (iRecv > 0) {
							szText[iRecv] = '\0';
							std::cout << "���յ�����" << szText;
						}
						else {
							closesocket(fdSocket.fd_array[i]);
							FD_CLR(fdSocket.fd_array[i], &fdSocket);
						}
						std::cout << std::endl;
					}
				}
			}
		}
		else {
			std::cout << "select error:" << WSAGetLastError() << std::endl;
			closesocket(sListen);
			WSACleanup();
			break;
		}
	}

	shutdown(sListen, SD_RECEIVE);
	WSACleanup();
	system("psuse");
	return 0;
}