
/*


class User {
	private:
		char userName[128];		// ����ֱ�Ӷ����Ա�������г�ʼ��
		char password[128];

	public:
		bool Login() {
			if (strcmp(userName, "MR") == 0 && strcmp(password, "KJ") == 0) {
				cout << "��¼�ɹ�";

			}
			else {
				cout << "��¼ʧ��";
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

	DBook()				//���캯������ʼ������
		:price(32), chapterNum(15) {		// ��ʼ����int�ͱ���
		
		strcpy_s(bookName, "��ѧӢ��");		// ��ʼ����char����

	}
	DBook()				//���캯������ʼ������
		:price(32), chapterNum(15) {		// ��ʼ����int�ͱ���

	}

	~DBook()			//��������
	{
		chapterNum = 0;
		memset(bookName, 0, 128);		//���ó�Ա�����Ĵ洢�ռ�����Ϊ0
		cout << "��������������" << endl;

	}
};



#define MAXLEN 128
class CEmployee {
public:

	int id;
	char name[128];
	char depart[128];

	CEmployee() {				// ���췽��
		memset(name, 0, 128);
		memset(depart, 0, 128);
		cout << "Ա���๹�캯��������" << endl;
			
	}

	virtual void outputName() {
		cout << "Ա��������" << name;
	}
	// ���鷽��
	virtual void output() = 0;
};
class COperator : public CEmployee {		// :������̳���
public:
	char password[MAXLEN];
	bool login() {
		if (strcmp(name, "MR") == 0 && strcmp(password, "KL") == 0) {
			cout << "��¼�ɹ���" << endl;
			return true;
		}
		else {
			cout << "��¼ʧ�ܣ�" << endl;
			return false;
		}
	}
};

// �鷽�����ڷ���ǰ����virtual�ؼ��֣�ʵ����Ķ�̬�󶨣������߶�������ʱ��������ȷ�����÷����������Ǹ��ݶ���ʱ����
// ���鷽������Ҫʵ�ַ�����

class CBird {
public:
	void FlySKY() {
		cout << "�����ڿ��з���"<< endl;
	}
	void Breath() {
		cout << "���ܹ�����" << endl;
	}
};

class CFish {
public:
	void SwiminWater() {
		cout << "���ܹ���ˮ���ζ�" << endl;
	}
	void Breath() {
		cout << "���ܹ�����" << endl;
	}
};

class CWaterBird :public CBird, public CFish {
public:
	void Breath() {
		cout << "����" << endl;
	}
	void Action() {
		cout << "ˮ����ܷ����ܹ���" << endl;
	}
};



// �ֲ��ࣺ������ں����У���Ϊ�ֲ���
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

// ģ����
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
	// ����β�ӵ�
	CNode *moveTrail() {
		CNode *tmp = p_header;
		for (int i = 1; i < sum; i++) {
			tmp = tmp->p_next;
		}
		return tmp;
	}

	// ��ӽڵ�
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

	// �����б�
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

	//������������
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
	CNode *p_next;		// ָ������͵�һ��ָ��
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
	CList() {		// ���췽��
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

// �쳣������������ʱ���ֵ��쳣��ָ���ַ��Ч���������

int add(int a, int b) {
	return a + b;
}

int sub(int a, int b) {
	return a - b;
}

// ����ָ�룺ָ������ָ�룬����ѡ����ѡ����
int(*func)(int a, int b);

// ָ�뺯��������ֵ��һ����ַ
int *add_p(int a, int b) {
	int c = a + b;
	return &c;
}


class CPerson {
public:
	CPerson();
	CPerson(int index, short age, double salary);
	CPerson(CPerson & copyPerson);		// ���ƹ��캯��������Ϊһ��CPerson����ĵ�ַ
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

CPerson::~CPerson() {				// ���������������ٵ�ʱ�����
	
}


// ��Ԫ�������������������壬����������������Ϊ��Ԫ�࣬��������ʹ�����е�˽�б���
// ��Ԫ�ࣺһ�����е�˽�б��������Խ���һ���ඨ��Ϊ�Լ�����Ԫ�࣬������һ����ܷ��ʸ����˽�б�����

class CItem;

class CList{
private:
	CItem * item;
public:
	CList();			//���캯��
	~CList();			//��������
	void Outputtern();
};

class CItem {
	friend void CList::Outputtern();			// ����Outputtern����Ϊ��Ԫ����
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
void CList::Outputtern() {				//ʵ��CList���еĺ���
	item->setname("beijing");
	item->ouputname();					// ͨ����Ԫ�����������е�˽�б���
}

CList::CList() {
	item = new CItem();			//���캯��
}

CList::~CList() {
	delete item;
	item = NULL;
}



// �����ռ䣺��һ��Ӧ�ó����ж���ļ����ܴ���ͬ����ȫ�ֶ��������ᵼ�����Ӵ���
// ʹ�������ռ��������������ͻ����ѷ�ʽ��

namespace MyName1 {
	int iValue = 10;
};

namespace MyName2 {
	int iValue = 20;
};


// �̳���������
class CEmployee {
public:
	int id;
	char name[128];
	char depart[128];

	CEmployee() {
		memset(name, 0, 128);			// Ϊ��������ڴ���г�ʼ��������ֱ�Ӳ����ڴ�ռ�
		memset(depart, 0, 128);
	}

	void outputName() {
		cout << "Ա������" << name << endl;
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
			cout << "��¼ʧ�ܣ�����" << endl;
			return false;
		}
	}
};


class CEmployee {
public:
	int id;
	char name[128];
	CEmployee() {
		cout << "CEmployee�๹�캯��������" << endl;
	}

	~CEmployee() {
		cout << "CEmployee����������������" << endl;
	}
};

class COperator :public CEmployee {
public:
	char password[128];
	COperator() {
		strcpy_s(name, "MR");
		cout << "COperator�еĹ��캯��������" << endl;
	}
	~COperator() {
		cout << "COperator�е���������������" << endl;
	}
};
	

// ���������
class CBook {
protected:
		int mpage;
public:
	CBook(int page) {			// ���ﶨ��Ĺ��캯������ʽ�����������Ա������ͬ
		mpage = page;
	}

	CBook operator+( int b) {		// ���������ʵ��������������

		return CBook(mpage + b);
	}
	void display() {
		cout << mpage << endl;
	}
};


class CBook {
public:
	CBook(double page = 0);			// ���캯��

	operator double() {				// ת�������
		return mpage;				// ����Ա��������
	}
protected:		
	int mpage;
};

CBook::CBook(double page) {			// ���캯��
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
	// �麯������
	virtual void outputName() {
		cout << "Ա��������" << name << endl;
	}
};

// �����̳�
class COperator :public CEmployee {
public:
	char password[128];
	// ������д
	void outputName() {
		cout << "����Ա������" << name << endl;
	}
};




class CFigure {
public:
	virtual double getArea() = 0;		// �����麯��
};

const double PI = 3.14;

// �̳���
class CCircle :public CFigure {

private:
	double m_dRadius;
public:
	CCircle(double dR) {		// ���캯��������һ��˫��������Ϊ�뾶
		m_dRadius = dR;
	}
	double getArea() {			// ʵ���麯��
		return m_dRadius * m_dRadius*PI;
	}
};

// �̳���
class CRectangle :public CFigure {
protected:
	double m_dHeight, m_dWidth;
public:
	CRectangle(double dHeight, double dWidth) {
		m_dHeight = dHeight;
		m_dWidth = dWidth;
	}
	double getArea() {			// ʵ���麯��
		return m_dHeight * m_dWidth;
	}
};


#include<iomanip>
#define max(a,b) ((a)>(b) ? (a):(b))	// ���к궨��,ֻ�����滻�������м���
template<class Type>
Type  max2(Type a, Type b) {			// ���庯��ģ�ͣ�����ģ�嶨��ģ�庯��
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
Type min(Type a, Type b) {		// ���庯��ģ��
	if (a < b)
		return a;
	else
		return b;
}




*/

#include<iostream>
#include "winsock2.h"
#pragma comment(lib,"ws2_32.lib")		// ����ws2_32.dll�ļ�
using namespace std;
	
int main() {
	WSADATA wsaData;			// WSADATA����
	SOCKET ServerSock;			// �������׽���
	SOCKET AccSock;				// �����洢���տͻ�����������������׽�������
	sockaddr_in sockAddr;		// �������˿ں�
	  
	//��ʼ��DLL
	WSAStartup(MAKEWORD(2, 2), &wsaData);		
	// �����׽���
	ServerSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	// ָ��������IP��ַ�Ͷ˿�
	sockAddr.sin_family = AF_INET;
	sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");		//�����IP��ַ
	sockAddr.sin_port = htons(2200);

	bind(ServerSock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));
	listen(ServerSock, 10);		// �������״̬�����10������
	
	// ���տͻ�������
	SOCKADDR clntAddr;
	int nSize = sizeof(SOCKADDR);
	AccSock = accept(ServerSock, (SOCKADDR*)&clntAddr, &nSize);
	// ��ͻ��˷�������
	char str[] = "Server sends";
	send(AccSock, str, strlen(str) + sizeof(char), NULL);
	// �ر��׽���
	closesocket(AccSock);
	closesocket(ServerSock);
	WSACleanup();					// ��ֹDLLʹ��
	return 0;


}