#include<iostream>

struct MyData {
	int nLen;
	char data[0];
};
int main() {

	int nLen = 10;
	char str[10] = "123456789";

	std::cout << "size of MyData:" << sizeof(MyData) << std::endl;
	MyData *mydata = (MyData *)malloc(sizeof(MyData) + 10);		// 定义一个结构体指针，指向一个开辟的空间
	std::cout << "size of myData:" << sizeof(mydata) << std::endl;		// 输出结果为4
	memcpy(mydata->data, str, 10);		// 将字符串中的str赋给

	std::cout << "myData's data is:" << mydata->data << std::endl;		
	std::cout << "size of myData:" << sizeof(mydata) << std::endl;		// 输出结果为4


	system("pause");
	return 0;
}