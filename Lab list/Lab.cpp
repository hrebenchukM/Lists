#include <iostream>
#include <cassert>
using namespace std;

struct Element
{
	// ������
	char data;
	// ����� ���������� �������� ������
	Element* Next;
};

// ����������� ������
class List
{
	// ����� ��������� �������� ������
	Element* Head;
	// ����� ��������� �������� ������
	Element* Tail;
	// ���������� ��������� ������
	int Count;

public:
	// �����������
	List();
	// ����������
	~List();

	// ���������� �������� � ������
	// (����� ������� ���������� ���������)
	void Add(char );

	// �������� �������� ������
	// (��������� �������� �������)
	void Del();
	// �������� ����� ������
	void DelAll();

	// ���������� ����������� ������
	// (���������� ���������� � ��������� ��������)
	void Print();

	// ��������� ���������� ���������, ����������� � ������
	int GetCount();




	void AddElemInPos(char,int );
	int SearchElem(char );

};

List::List()
{
	// ���������� ������ ����
	Head = Tail = NULL;
	Count = 0;
}

List::~List()
{
	// ����� ������� ��������
	DelAll();
}

int List::GetCount()
{
	// ���������� ���������� ���������
	return Count;
}

void List::Add(char data)
{
	// �������� ������ ��������
	Element* temp = new Element;

	// ���������� �������
	temp->data = data;
	// ��������� ������� �����������
	temp->Next = NULL;
	// ����� ������� ���������� ��������� ��������� ������
	// ���� �� �� ������ �����������
	if (Head != NULL) {
		Tail->Next = temp;
		Tail = temp;
	}
	// ����� ������� ���������� ������������
	// ���� �� ������ �����������
	else {
		Head = Tail = temp;
	}
	Count++;
}

void List::Del()
{
	// ���������� ����� ��������� ��������
	Element* temp = Head;
	// ������������� ������ �� ��������� �������
	Head = Head->Next;
	// ������� ������ �������� �������
	delete temp;
	Count--;
}

void List::AddElemInPos(char data,int pos)
{ 
	if (Count == 0 || Count == pos)
	{
		Add(data);
		return;
	}
	
	// �������� ������ ��������
	Element* temp = new Element;

	// ���������� �������
	temp->data = data;

	if (pos > 1) {
		Element* prev = Head;
		for (int i = 1; i < pos - 1; i++)
		{
			prev = prev->Next;
		}
		temp->Next = prev->Next;
		prev->Next = temp;
	}
	else {
		temp->Next = Head;
		Head = temp;
	}
	Count++;
}

 int List::SearchElem(char Udata)
{
	Element* temp = Head;

	for (int i = 0; i < Count; i++)
	{
			if (temp->data==Udata)
			{
				return i+1;
			}
			temp = temp->Next;
	}
     return 0;		
}

void List::DelAll()
{
	// ���� ��� ���� ��������
	while (Head != 0)
		// ������� �������� �� ������
		Del();
}

void List::Print()
{
	// ���������� ����� ��������� ��������
	Element* temp = Head;
	// ���� ��� ���� ��������
	while (temp != 0)
	{
		// ������� ������
		cout << '[' << temp->data << ']';
		// ��������� �� ��������� �������
		temp = temp->Next;
	}

	cout << endl;
}




//
//// �������� ������
//int main()
//{
//	// ������� ������ ������ List
//	List lst;
//
//	// �������� ������
//	char s[] = "Hello, World !!!";
//	// ������� ������
//	cout << s << "\n\n";
//	// ���������� ����� ������
//	int len = strlen(s);
//	// �������� ������ � ������
//	for (int i = 0; i < len; i++)
//		lst.Add(s[i]);
//	// ������������� ���������� ������
//	lst.Print();
//	// ������� ��� �������� ������
//	//lst.Del();
//	//lst.Del();
//	//lst.Del();
//	////������������� ���������� ������
//	//lst.Print();
//
//	lst.AddElemInPos('*', 1);
//	lst.AddElemInPos('?', 15);
//	lst.Print();
//
//	assert(15 == lst.SearchElem('?'));
//}
//


