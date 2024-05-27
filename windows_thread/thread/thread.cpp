#include<Windows.h>
#include<iostream>
#include<strsafe.h>
#include <tchar.h>
#include<string>
using namespace std;

int gticketId = 10;
HANDLE ghSemaphore;		// 信号量对象句柄

DWORD WINAPI threadfunc(LPVOID param) {
	HANDLE hStdout;
	string chWin;
	LONG cn;		

	if (param == 0) {
		chWin = "甲";
	}
	else {
		chWin = "乙";
	}

	while (1) {
		// 等待信号量的响应结果
		WaitForSingleObject(ghSemaphore, INFINITE);
		// 当余票数量小于等于0时，卖票结束
		if (gticketId <= 0) {
			ReleaseSemaphore(ghSemaphore, 1, &cn);		// 释放信号量对象
			break;
		}

		cout << chWin << "窗口卖出了" << gticketId << "号票" << endl;
		gticketId--;
		// 当前卖票结束，释放占用的信号量事件，是计数器+1
		ReleaseSemaphore(ghSemaphore, 1, &cn);
	}
	return 1;
}

int main() {
	
	int i;
	HANDLE h[2];
	cout << "使用信号量对象开启线程同步" << endl;
	cout << "开始卖票" << endl;
	ghSemaphore = CreateSemaphore(NULL, 1, 50, "mySemaphore");
	for (i = 0; i < 2; i++) {
		h[i] = CreateThread(NULL, 0, threadfunc, (LPVOID)i, 0, 0);
	}

	for (i = 0; i < 2; i++) {
		WaitForSingleObject(h[i], INFINITE);
		CloseHandle(h[i]);
	}
	CloseHandle(ghSemaphore);
	cout << "卖票结束" << endl;
	
	system("pause");
	return 0;
}