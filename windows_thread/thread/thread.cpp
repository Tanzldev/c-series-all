#include<Windows.h>
#include<iostream>
#include<strsafe.h>
#include <tchar.h>
#include<string>
#include<vector>
using namespace std;

int gticketId = 10;
HANDLE ghSemaphore;		// �ź���������

DWORD WINAPI threadfunc(LPVOID param) {
	HANDLE hStdout;
	string chWin;
	LONG cn;		// �����ͱ���

	if (param == 0) {
		chWin = "��";
	}
	else {
		chWin = "��";
	}

	while (1) {
		WaitForSingleObject(ghSemaphore, INFINITE);
		if (gticketId <= 0) {
			ReleaseSemaphore(ghSemaphore, 1, &cn);		// �ͷ��ź�������
			break;
		}

		cout << chWin << "����������" << gticketId << "��Ʊ" << endl;
		gticketId--;
		ReleaseSemaphore(ghSemaphore, 1, &cn);
	}
	return 1;
}

int main() {
	
	int i;
	HANDLE h[2];
	cout << "ʹ���ź����������߳�ͬ��" << endl;
	cout << "��ʼ��Ʊ" << endl;
	ghSemaphore = CreateSemaphore(NULL, 1, 50, "mySemaphore");
	for (i = 0; i < 2; i++) {
		h[i] = CreateThread(NULL, 0, threadfunc, (LPVOID)i, 0, 0);
	}

	for (i = 0; i < 2; i++) {
		WaitForSingleObject(h[i], INFINITE);
		CloseHandle(h[i]);
	}
	CloseHandle(ghSemaphore);
	cout << "��Ʊ����" << endl;
	
	system("pause");
	return 0;
}