#include<iostream>
using namespace std;
typedef int Array[10], INT;

inline void swap(int &a, int &b) 
{
	int temp;
	temp = a;
	a = b;
	b = temp;
}
int main()
{

	int a = 1, b = 2;
	swap(a,b);
	cout << a << endl;
	cout << b << endl;
	
	system("pause");


}