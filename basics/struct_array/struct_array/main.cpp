#include<iostream>

struct MyData {
	int nLen;
	char data[0];
};
int main() {

	int nLen = 10;
	char str[10] = "123456789";

	std::cout << "size of MyData:" << sizeof(MyData) << std::endl;
	MyData *mydata = (MyData *)malloc(sizeof(MyData) + 10);		// ����һ���ṹ��ָ�룬ָ��һ�����ٵĿռ�
	std::cout << "size of myData:" << sizeof(mydata) << std::endl;		// ������Ϊ4
	memcpy(mydata->data, str, 10);		// ���ַ����е�str����

	std::cout << "myData's data is:" << mydata->data << std::endl;		
	std::cout << "size of myData:" << sizeof(mydata) << std::endl;		// ������Ϊ4


	system("pause");
	return 0;
}