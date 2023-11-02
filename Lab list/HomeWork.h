#include <iostream>
using namespace std;

template<typename E>
struct Elem
{
    E data; // ������
    Elem* next, * prev;
};


template<typename E>
class List
{
    // ������, �����
    Elem<E>* Head, * Tail;
    // ���������� ���������
    int Count;

public:

    // �����������
    List();
    // ����������� �����������
    List(const List&);
    // ����������
    ~List();

    // �������� ����������
    int GetCount();
    // �������� ������� ������
    Elem<E>* GetElem(int);

    // ������� ���� ������
    void DelAll();
    // �������� ��������, ���� �������� �� �����������,
    // �� ������� ��� �����������
    void Del(int pos = 0);
    // ������� ��������, ���� �������� �� �����������,
    // �� ������� ��� �����������
    void Insert(int pos = 0);

    // ���������� � ����� ������
    void AddTail(E n);

    // ���������� � ������ ������
    void AddHead(E n);

    // ������ ������
    void Print();
    // ������ ������������� ��������
    void Print(int pos);

    List& operator = (const List&);
    // �������� ���� ������� (�����������)
    List operator + (const List&);

    // ��������� �� ���������
    bool operator == (const List&);
    bool operator != (const List&);
    bool operator <= (const List&);
    bool operator >= (const List&);
    bool operator < (const List&);
    bool operator > (const List&);

    // ��������������� ������
    List operator - ();
};

template<typename E>
List<E>::List()
{
    // ���������� ������ ����
    Head = Tail = NULL;
    Count = 0;
}


template<typename E>
List<E>::List(const List& L)
{
    Head = Tail = NULL;
    Count = 0;

    // ������ ������, �� �������� ��������
    Elem* temp = L.Head;
    // ���� �� ����� ������
    while (temp != 0)
    {
        // ���������� ������
        AddTail(temp->data);
        temp = temp->next;
    }
}


template<typename E>
List<E>::~List()
{
    // ������� ��� ��������
    DelAll();
}


template<typename E>
void List<E>::AddHead(E n)
{
    // ����� �������
    Elem<E>* temp = new Elem<E>;

    // ����������� ���
    temp->prev = 0;
    // ��������� ������
    temp->data = n;
    // ��������� - ������ ������
    temp->next = Head;

    // ���� �������� ����?
    if (Head != 0)
        Head->prev = temp;

    // ���� �������c ������, �� �� ������������ � ������ � �����
    if (Count == 0)
        Head = Tail = temp;
    else
        // ����� ����� ������� - ��������
        Head = temp;

    Count++;
}


template<typename E>
void List<E>::AddTail(E n)
{
    // ������� ����� �������
    Elem<E>* temp = new Elem<E>;
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


template<typename E>
void List<E>::Insert(int pos)
{
    // ���� �������� ����������� ��� ����� 0, �� ����������� ���
    if (pos == 0)
    {
        cout << "Input position: ";
        cin >> pos;
    }

    // ������� �� 1 �� Count?
    if (pos < 1 || pos > Count + 1)
    {
        // �������� �������
        cout << "Incorrect position !!!\n";
        return;
    }

    // ���� ������� � ����� ������
    if (pos == Count + 1)
    {
        // ����������� ������
        E data;
        cout << "Input new number: ";
        cin >> data;
        // ���������� � ����� ������
        AddTail(data);
        return;
    }
    else if (pos == 1)
    {
        // ����������� ������
        E data;
        cout << "Input new number: ";
        cin >> data;
        // ���������� � ������ ������
        AddHead(data);
        return;
    }

    // �������
    int i = 1;

    // ����������� �� ������ n - 1 ���������
    Elem* Ins = Head;

    while (i < pos)
    {
        // ������� �� ��������, 
        // ����� ������� �����������
        Ins = Ins->next;
        i++;
    }

    // ������� �� ��������, 
    // ������� ������������
    Elem<E>* PrevIns = Ins->prev;

    // ������� ����� �������
    Elem<E>* temp = new Elem<E>;

    // ������ ������
    cout << "Input new number: ";
    cin >> temp->data;

    // ��������� ������
    if (PrevIns != 0 && Count != 1)
        PrevIns->next = temp;

    temp->next = Ins;
    temp->prev = PrevIns;
    Ins->prev = temp;

    Count++;
}


template<typename E>
void List<E>::Del(int pos)
{
    // ���� �������� ����������� ��� ����� 0, �� ����������� ���
    if (pos == 0)
    {
        cout << "Input position: ";
        cin >> pos;
    }
    // ������� �� 1 �� Count?
    if (pos < 1 || pos > Count)
    {
        // �������� �������
        cout << "Incorrect position !!!\n";
        return;
    }

    // �������
    int i = 1;
   
    Elem<E>* Del = Head;

    while (i < pos)
    {
        // ������� �� ��������, 
        // ������� ���������
        Del = Del->next;
        i++;
    }

    // ������� �� ��������, 
    // ������� ������������ ����������
    Elem* PrevDel = Del->prev;
    // ������� �� ��������, ������� ������� �� ���������
    Elem* AfterDel = Del->next;

    // ���� ������� �� ������
    if (PrevDel != 0 && Count != 1)
        PrevDel->next = AfterDel;
    // ���� ������� �� �����
    if (AfterDel != 0 && Count != 1)
        AfterDel->prev = PrevDel;

    // ��������� �������?
    if (pos == 1)
        Head = AfterDel;
    if (pos == Count)
        Tail = PrevDel;

    // �������� ��������
    delete Del;

    Count--;
}


template<typename E>
void List<E>::Print(int pos)
{
    // ������� �� 1 �� Count?
    if (pos < 1 || pos > Count)
    {
        // �������� �������
        cout << "Incorrect position !!!\n";
        return;
    }

    Elem<E>* temp;

    // ���������� � ����� ������� 
    // ������� ���������
    if (pos <= Count / 2)
    {
        // ������ � ������
        temp = Head;
        int i = 1;

        while (i < pos)
        {
            // ��������� �� ������� ��������
            temp = temp->next;
            i++;
        }
    }
    else
    {
        // ������ � ������
        temp = Tail;
        int i = 1;

        while (i <= Count - pos)
        {
            // ��������� �� ������� ��������
            temp = temp->prev;
            i++;
        }
    }
    // ����� ��������
    cout << pos << " element: ";
    cout << temp->data << endl;
}



template<typename E>
void List<E>::Print()
{
    // ���� � ������ ������������ ��������, �� ��������� �� ����
    // � �������� ��������, ������� � ���������
    if (Count != 0)
    {
        Elem* temp = Head;//������� �������
        cout << "( ";
        while (temp->next != 0)
        {
            cout << temp->data << ", ";
            temp = temp->next;
        }

        cout << temp->data << " )\n";
    }
}


template<typename E>
void List<E>::DelAll()
{
    // ���� �������� ��������, ������� �� ������ � ������
    while (Count != 0)
        Del(1);
}

template<typename E>
int List<E>::GetCount()
{
    return Count;
}

template<typename E>
Elem<E>* List<E>::GetElem(int pos)
{
    Elem* temp = Head;

    // ������� �� 1 �� Count?
    if (pos < 1 || pos > Count)
    {
        // �������� �������
        cout << "Incorrect position !!!\n";
        return 0;
    }

    int i = 1;
    // ���� ������ ��� �������
    while (i < pos && temp != 0)
    {
        temp = temp->next;
        i++;
    }

    if (temp == 0)
        return 0;
    else
        return temp;
}

template<typename E>
List<E>& List<E>::operator = (const List& L)
{
    // �������� ������������ �������� "������ ����"
    if (this == &L)
        return *this;

    // �������� ������� ������
    this->~List(); // DelAll();

    Elem* temp = L.Head;

    // �������� ��������
    while (temp != 0)
    {
        AddTail(temp->data);
        temp = temp->next;
    }

    return *this;
}



template<typename E>
// �������� ���� �������
List<E> List<E>::operator + (const List& L)
{
    // ������� �� ��������� ������ �������� ������� ������
    List Result(*this);
    // List Result = *this;

    Elem* temp = L.Head;

    // ��������� �� ��������� ������ �������� ������� ������
    while (temp != 0)
    {
        Result.AddTail(temp->data);
        temp = temp->next;
    }

    return Result;
}
template<typename E>
bool List<E>::operator == (const List& L)
{
    // ��������� �� ����������
    if (Count != L.Count)
        return false;

    Elem* t1, * t2;

    t1 = Head;
    t2 = L.Head;

    // ��������� �� ����������
    while (t1 != 0)
    {
        // ������� ������, �������
        // ��������� �� ���������� ��������
        if (t1->data != t2->data)
            return false;

        t1 = t1->next;
        t2 = t2->next;
    }

    return true;
}
template<typename E>
bool List<E>::operator != (const List& L)
{
    // ���������� ���������� ������� ���������
    return !(*this == L);
}

template<typename E>
bool List<E>::operator >= (const List& L)
{
    // ��������� �� ����������
    if (Count > L.Count)
        return true;
    // ��������� �� ����������
    if (*this == L)
        return true;

    return false;
}
template<typename E>
bool List<E>::operator <= (const List& L)
{
    // ��������� �� ����������
    if (Count < L.Count)
        return true;
    // ��������� �� ����������
    if (*this == L)
        return true;

    return false;
}
template<typename E>
bool List<E>::operator > (const List& L)
{
    if (Count > L.Count)
        return true;

    return false;
}
template<typename E>
bool List<E>::operator < (const List& L)
{
    if (Count < L.Count)
        return true;

    return false;
}

// ���������
template<typename E>
List<E> List<E>::operator - ()
{
    List Result;

    Elem* temp = Head;
    // �������� �������� ������, ������� � ���������,
    // � ���� ����� ���������� ��������� � ������,
    // ����� ������� ��������� ������ Result ����� ���������
    // �������� � �������� �������
    while (temp != 0)
    {
        Result.AddHead(temp->data);
        temp = temp->next;
    }

    return Result;
}

// �������� ������
void main()
{
    List<int> L;

    const int n = 10;
    int a[n] = { 0,1,2,3,4,5,6,7,8,9 };

    // ��������� ��������, ������� �� ������ ��������, � ������,
    // �� �������� - � �����
    for (int i = 0; i < n; i++)
        if (i % 2 == 0)
            L.AddHead(a[i]);
        else
            L.AddTail(a[i]);

    // ���������� ������
    cout << "List L:\n";
    L.Print();

    cout << endl;

    // ������� �������� � ������
    L.Insert();
    // ���������� ������
    cout << "List L:\n";
    L.Print();

    // ���������� 2-�� � 8-�� ��������� ������
    L.Print(2);
    L.Print(8);

    List<int> T;

    // �������� ������
    T = L;
    // ���������� �����
    cout << "List T:\n";
    T.Print();

    // ���������� ��� ������ (������ � ������������ ���������)
    cout << "List Sum:\n";
    List<int> Sum = -L + T;
    // ���������� ������
    Sum.Print();
}



