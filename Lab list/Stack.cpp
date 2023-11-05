#include <iostream>
#include <cassert>
using namespace std;

struct Elem
{
    int data; // ������
    Elem* next, * prev;
};

class Stack
{
    // ������, �����
    Elem* Head, * Tail;
    // ���������� ���������
    int Count;
    int maxCount;

public:

    // �����������
    Stack();
    Stack(int maxCount);
    // ����������� �����������
    Stack(const Stack&);
    // ����������
    ~Stack();

    // �������� ����������
    int GetCount();
    // ������� ���� ������
    void DelAll();
    // �������� ��������, ���� �������� �� �����������,
    // �� ������� ��� �����������
    // ���������� � ����� ������
    void PUSH(int n);
    int PULL();

    // ������ ������
    void Print();
    bool IsEmpty();
    bool IsFulL();


};

Stack::Stack()
{
    // ���������� ������ ����
    Head = Tail = NULL;
    Count = 0;
}

Stack::Stack(int maxCount)
{
    Head = Tail = NULL;
    Count = 0;
   this-> maxCount = maxCount;
}

Stack::Stack(const Stack& L)
{
    Head = Tail = NULL;
    Count = 0;

    // ������ ������, �� �������� ��������
    Elem* temp = L.Head;
    // ���� �� ����� ������
    while (temp != 0)
    {
        // ���������� ������
        PUSH(temp->data);
        temp = temp->next;
    }
}

Stack::~Stack()
{
    cout << "Destructor called!";
    // ������� ��� ��������
    DelAll();
}


void Stack::PUSH(int n)
{
    if (IsFulL())
    {
        cout << "Stack is full!!!";
        return;//��� ��� ����� �� ����������
    }
    // ������� ����� �������
    Elem* temp = new Elem;
    // ���������� ���
    temp->next = 0;
    // ��������� ������
    temp->data = n;
    // ���������� - ������ �����
    temp->prev = Tail;

    // ���� �������� ����?
    if (Tail != 0)
        Tail->next = temp;

    // ���� ������� ������, �� �� ������������ � ������ � �����
    if (Count == 0)
        Head = Tail = temp;
    else
        // ����� ����� ������� - ���������
        Tail = temp;

    Count++;
}

int Stack::PULL()
{
    
    if (IsEmpty())
    {
        return -1;
    }
    Elem* temp = 0;
    if (Count>1) {
        temp = Tail->prev;
        temp->next = nullptr;
    }

    int result= Tail->data;  
    delete Tail;//* =0

    Tail = temp;//*= prev Tail
    Count--;
    if (Count == 0) {
        Head = 0;
    }
    return result;
}


bool Stack::IsEmpty()
{
    return  Count == 0;
}

bool Stack::IsFulL()
{
    return Count== maxCount;
}

void Stack::Print()
{
    // ���� � ������ ������������ ��������, �� ��������� �� ����
    // � �������� ��������, ������� � ���������
    if (Count != 0)
    {
        Elem* temp = Head;
        cout << "( ";
        while (temp->next != 0)
        {
            cout << temp->data << ", ";
            temp = temp->next;
        }

        cout << temp->data << " )\n";
    }
    else {
        cout << "Empty!";
    }
}

void Stack::DelAll()
{
    for (int i = 0; i < Count; i++) {
        PULL();
    }
}

int Stack::GetCount()
{
    return Count;
}



// �������� ������
int main()
{
    const int n = 10;
    Stack stack(n);

    int a[n] = { 0,1,2,3,4,5,6,7,8,9 };

    assert(stack.IsEmpty());
    // ��������� ��������, ������� �� ������ ��������, � ������,
    // �� �������� - � �����
    for (int i = 0; i < n; i++)
            stack.PUSH(a[i]);
    assert(10, stack.GetCount());
    
    assert(stack.IsFulL());
    stack.PUSH(100500); // overflow
    assert(10, stack.GetCount());

    for (int i = 0; i < n; i++) {
        int expected = a[9 - i];
        int actual = stack.PULL();
        cout <<endl<< "expected=" << expected << ", actual=" << actual << ", count=" << stack.GetCount();
        assert(expected == actual);
    }

    assert(stack.IsEmpty());

}

