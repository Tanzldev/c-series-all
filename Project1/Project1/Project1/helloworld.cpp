
/*


class User {
	private:
		char userName[128];		// 不能直接对类成员变量进行初始化
		char password[128];

	public:
		bool Login() {
			if (strcmp(userName, "MR") == 0 && strcmp(password, "KJ") == 0) {
				cout << "登录成功";

			}
			else {
				cout << "登录失败";
			}
	}
};

class BUser {
private:
	char userName[128];
	char password[128];
public:
	BUser() {
		strcpy_s(userName, "MR");
		strcpy_s(password, "KJ");
	}
	char* getUsername()const {
		return (char*)userName;
	}
	char* getPassword()const {
		return (char*)password;
	}
};

class DBook {
public:
	char bookName[128];
	const unsigned int price;
	int chapterNum;

	DBook()				//构造函数，初始化常量
		:price(32), chapterNum(15) {		// 初始化了int型变量
		
		strcpy_s(bookName, "大学英语");		// 初始化了char数组

	}
	DBook()				//构造函数，初始化常量
		:price(32), chapterNum(15) {		// 初始化了int型变量

	}

	~DBook()			//析构函数
	{
		chapterNum = 0;
		memset(bookName, 0, 128);		//设置成员变量的存储空间数据为0
		cout << "析构函数被调用" << endl;

	}
};



#define MAXLEN 128
class CEmployee {
public:

	int id;
	char name[128];
	char depart[128];

	CEmployee() {				// 构造方法
		memset(name, 0, 128);
		memset(depart, 0, 128);
		cout << "员工类构造函数被调用" << endl;
			
	}

	virtual void outputName() {
		cout << "员工姓名：" << name;
	}
	// 纯虚方法
	virtual void output() = 0;
};
class COperator : public CEmployee {		// :运算符继承类
public:
	char password[MAXLEN];
	bool login() {
		if (strcmp(name, "MR") == 0 && strcmp(password, "KL") == 0) {
			cout << "登录成功！" << endl;
			return true;
		}
		else {
			cout << "登录失败！" << endl;
			return false;
		}
	}
};

// 虚方法：在方法前加上virtual关键字，实现类的动态绑定，即更具对象运行时的类型来确定调用方法，而不是根据定义时方法
// 纯虚方法不需要实现方法体

class CBird {
public:
	void FlySKY() {
		cout << "鸟能在空中飞行"<< endl;
	}
	void Breath() {
		cout << "鸟能够呼吸" << endl;
	}
};

class CFish {
public:
	void SwiminWater() {
		cout << "鱼能够在水里游动" << endl;
	}
	void Breath() {
		cout << "鱼能够呼吸" << endl;
	}
};

class CWaterBird :public CBird, public CFish {
public:
	void Breath() {
		cout << "呼吸" << endl;
	}
	void Action() {
		cout << "水鸟既能飞又能够游" << endl;
	}
};



// 局部类：定义放在函数中，称为局部类
void LocalClass() {
	class CBook {
	private:
		int pages;
	public:
		void setPages(int page) {
			if (pages != page) {
				pages = page;
			}
		}
		int getPages() {
			return pages;
		}
	};

	CBook book;
	book.setPages(300);
	cout << book.getPages << endl;
}

// 模板类
class CNode {
public:
	CNode *p_next;
	int data;
	CNode() {
		p_next = NULL;
	}
};

class CList {
private:
	CNode *p_header;
	int sum;
public:
	CList() {
		p_header = NULL;
		sum = 0;
	}
	// 返回尾接点
	CNode *moveTrail() {
		CNode *tmp = p_header;
		for (int i = 1; i < sum; i++) {
			tmp = tmp->p_next;
		}
		return tmp;
	}

	// 添加节点
	void AddNode(CNode *pNode) {
		if (sum == 0) {
			p_header = pNode;
		}
		else {
			CNode *pTrail = moveTrail();
			pTrail->p_next = pNode;
		}
		sum++;
	}

	// 便利列表
	void passList() {
		if (sum > 0) {
			CNode *tmp = p_header;
			cout << tmp->data << " ";
			for (int i = 1; i < sum; i++) {
				tmp = tmp->p_next;
				cout << tmp->data << " ";
			}
		}
	}

	//链表析构函数
	~CList() {
		if (sum > 0) {
			CNode *pDelete = p_header;
			CNode *tmp = NULL;
			for (int i = 0; i < sum; i++) {
				tmp = pDelete->p_next;
				delete pDelete;
				pDelete = tmp;
			}
			sum = 0;
			pDelete = NULL;
			tmp = NULL;
		}
		p_header = NULL;
	}
};

class CNode {
public:
	CNode *p_next;		// 指向该类型的一个指针
	int data;
	CNode() {
		p_next = NULL;
	}
};

template <class Type>

class CList {

private:
	Type *p_header;
	int sum;
public:
	CList() {		// 构造方法
		p_header = NULL;
		sum = 0;
	}

	Type *moveTrail() {
		Type *tmp = p_header;
		for (int i = 0; i < sum-1; i++) {
			tmp = tmp->p_next;
		}
		return tmp;
	}

	void addNode(Type *pNode) {
		if (sum == 0) {
			p_header = pNode;
		}
		else {
			Type *pTrail = moveTrail();
			pTrail->p_next = pNode;
		}
		sum++;
	}

	void passlist() {
		if (sum > 0) {
			Type *tmp = p_header;
			cout << tmp->data;
			for (int i = 0; i < sum-1; i++) {
				tmp = tmp->p_next;
				cout << tmp->data <<" ";

			}
		}
	}
	~CList() {
		if (sum > 0) {
			Type *pDelete = p_header;
			Type *tmp = NULL;
			for (int i = 0; i < sum; i++) {
				tmp = pDelete->p_next;
				delete pDelete;
				pDelete = tmp;
			}
			sum = 0;
			pDelete = NULL;
			tmp = NULL;
		}
		p_header = NULL;
	}
};
class CNet {
public:
	CNet *p_next;
	char data;
	CNet() {
		p_next = NULL;
	}
};

// 异常处理，程序运行时出现的异常，指针地址无效，除零操作

int add(int a, int b) {
	return a + b;
}

int sub(int a, int b) {
	return a - b;
}

// 函数指针：指向函数的指针，可以选择性选择函数
int(*func)(int a, int b);

// 指针函数：返回值是一个地址
int *add_p(int a, int b) {
	int c = a + b;
	return &c;
}


class CPerson {
public:
	CPerson();
	CPerson(int index, short age, double salary);
	CPerson(CPerson & copyPerson);		// 复制构造函数，参数为一个CPerson对象的地址
	int this_index;
	short this_age;
	double this_salary;

	int getIndex();
	short getAge();
	double getSalary();
};
CPerson::CPerson() {
	this_index = 0;
	this_age = 0;
	this_salary = 0.0;

}

CPerson::CPerson(int index, short age, double salary) {
	this_index = index;
	this_age = age;
	this_salary = salary;
}
int CPerson::getIndex() {
	return this_index;
}

CPerson::~CPerson() {				// 析构函数，类销毁的时候调用
	
}


// 友元函数：函数在正常定义，但是若在类中声明为友元类，则函数可以使用类中的私有变量
// 友元类：一个类中的私有变量，可以将另一个类定义为自己的友元类，这样另一类就能访问该类的私有变量了

class CItem;

class CList{
private:
	CItem * item;
public:
	CList();			//构造函数
	~CList();			//析构函数
	void Outputtern();
};

class CItem {
	friend void CList::Outputtern();			// 声明Outputtern函数为友元函数
	private:
		char name[128];
		void ouputname() {
			cout << name << endl;
		}	
	public:
		void setname(const char* data) {
			if (data != NULL) {
				strcpy_s(name, data);
			}
		}
		CItem() {
			memset(name, 0, 128);
		}

};
void CList::Outputtern() {				//实现CList类中的函数
	item->setname("beijing");
	item->ouputname();					// 通过友元函数调用类中的私有变量
}

CList::CList() {
	item = new CItem();			//构造函数
}

CList::~CList() {
	delete item;
	item = NULL;
}



// 命名空间：在一个应用程序中多个文件可能存在同名的全局对象，这样会导致链接错误
// 使用命名空间可以消除命名冲突的最佳方式。

namespace MyName1 {
	int iValue = 10;
};

namespace MyName2 {
	int iValue = 20;
};


// 继承与派生类
class CEmployee {
public:
	int id;
	char name[128];
	char depart[128];

	CEmployee() {
		memset(name, 0, 128);			// 为新申请的内存进行初始化工作，直接操作内存空间
		memset(depart, 0, 128);
	}

	void outputName() {
		cout << "员工姓名" << name << endl;
	}


};

class COperator :public CEmployee {
public:
	char password[128];
	bool login() {
		if (strcmp(name, "MR") == 0 && strcmp(password, "KJ") == 0) {
			return true;
		}
		else {
			cout << "登录失败！！！" << endl;
			return false;
		}
	}
};


class CEmployee {
public:
	int id;
	char name[128];
	CEmployee() {
		cout << "CEmployee类构造函数被调用" << endl;
	}

	~CEmployee() {
		cout << "CEmployee类析构函数被调用" << endl;
	}
};

class COperator :public CEmployee {
public:
	char password[128];
	COperator() {
		strcpy_s(name, "MR");
		cout << "COperator中的构造函数被调用" << endl;
	}
	~COperator() {
		cout << "COperator中的析构函数被调用" << endl;
	}
};
	

// 重载运算符
class CBook {
protected:
		int mpage;
public:
	CBook(int page) {			// 这里定义的构造函数，形式参数不能与成员变量相同
		mpage = page;
	}

	CBook operator+( int b) {		// 重载运算符实现了两个类的相加

		return CBook(mpage + b);
	}
	void display() {
		cout << mpage << endl;
	}
};


class CBook {
public:
	CBook(double page = 0);			// 构造函数

	operator double() {				// 转化运算符
		return mpage;				// 将成员变量返回
	}
protected:		
	int mpage;
};

CBook::CBook(double page) {			// 构造函数
	mpage = page;
}



class CEmployee {
public:
	int id;
	char name[128];
	char depart[128];
	CEmployee() {
		memset(name, 0, 128);
		memset(depart, 0, 128);
	}
	// 虚函数定义
	virtual void outputName() {
		cout << "员工姓名：" << name << endl;
	}
};

// 函数继承
class COperator :public CEmployee {
public:
	char password[128];
	// 函数重写
	void outputName() {
		cout << "操作员姓名：" << name << endl;
	}
};




class CFigure {
public:
	virtual double getArea() = 0;		// 定义虚函数
};

const double PI = 3.14;

// 继承类
class CCircle :public CFigure {

private:
	double m_dRadius;
public:
	CCircle(double dR) {		// 构造函数，接收一个双浮点数作为半径
		m_dRadius = dR;
	}
	double getArea() {			// 实现虚函数
		return m_dRadius * m_dRadius*PI;
	}
};

// 继承类
class CRectangle :public CFigure {
protected:
	double m_dHeight, m_dWidth;
public:
	CRectangle(double dHeight, double dWidth) {
		m_dHeight = dHeight;
		m_dWidth = dWidth;
	}
	double getArea() {			// 实现虚函数
		return m_dHeight * m_dWidth;
	}
};


#include<iomanip>
#define max(a,b) ((a)>(b) ? (a):(b))	// 进行宏定义,只进行替换，不进行计算
template<class Type>
Type  max2(Type a, Type b) {			// 定义函数模型，函数模板定义模板函数
	if (a > b)
		return a;
	else
		return b;
}


template <class type,int len>
type Max(type array[len]) {
	type ret = array[0];
	for (int i = 1; i < len; i++) {
		ret = (ret > array[i]) ? ret : array[i];
	}
	return ret;
}


template<class Type>
Type min(Type a, Type b) {		// 定义函数模板
	if (a < b)
		return a;
	else
		return b;
}




*/

#include<iostream>
#include "winsock2.h"
#pragma comment(lib,"ws2_32.lib")		// 加载ws2_32.dll文件
using namespace std;
	
int main() {
	WSADATA wsaData;			// WSADATA对象
	SOCKET ServerSock;			// 服务器套接字
	SOCKET AccSock;				// 用来存储接收客户端连接请求产生的套接字数据
	sockaddr_in sockAddr;		// 服务器端口号
	  
	//初始化DLL
	WSAStartup(MAKEWORD(2, 2), &wsaData);		
	// 创建套接字
	ServerSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	// 指定服务器IP地址和端口
	sockAddr.sin_family = AF_INET;
	sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");		//具体的IP地址
	sockAddr.sin_port = htons(2200);

	bind(ServerSock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));
	listen(ServerSock, 10);		// 进入监听状态，最多10个连接
	
	// 接收客户端请求
	SOCKADDR clntAddr;
	int nSize = sizeof(SOCKADDR);
	AccSock = accept(ServerSock, (SOCKADDR*)&clntAddr, &nSize);
	// 向客户端发送数据
	char str[] = "Server sends";
	send(AccSock, str, strlen(str) + sizeof(char), NULL);
	// 关闭套接字
	closesocket(AccSock);
	closesocket(ServerSock);
	WSACleanup();					// 终止DLL使用
	return 0;


}