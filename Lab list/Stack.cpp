#include <iostream>
#include <cassert>
using namespace std;

struct Elem
{
    int data; // данные
    Elem* next, * prev;
};

class Stack
{
    // Голова, хвост
    Elem* Head, * Tail;
    // Количество элементов
    int Count;
    int maxCount;

public:

    // Конструктор
    Stack();
    Stack(int maxCount);
    // Конструктор копирования
    Stack(const Stack&);
    // Деструктор
    ~Stack();

    // Получить количество
    int GetCount();
    // Удалить весь список
    void DelAll();
    // Удаление элемента, если параметр не указывается,
    // то функция его запрашивает
    // Добавление в конец списка
    void PUSH(int n);
    int PULL();

    // Печать списка
    void Print();
    bool IsEmpty();
    bool IsFulL();


};

Stack::Stack()
{
    // Изначально список пуст
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

    // Голова списка, из которого копируем
    Elem* temp = L.Head;
    // Пока не конец списка
    while (temp != 0)
    {
        // Передираем данные
        PUSH(temp->data);
        temp = temp->next;
    }
}

Stack::~Stack()
{
    cout << "Destructor called!";
    // Удаляем все элементы
    DelAll();
}


void Stack::PUSH(int n)
{
    if (IsFulL())
    {
        cout << "Stack is full!!!";
        return;//Все что после не віполняется
    }
    // Создаем новый элемент
    Elem* temp = new Elem;
    // Следующего нет
    temp->next = 0;
    // Заполняем данные
    temp->data = n;
    // Предыдущий - бывший хвост
    temp->prev = Tail;

    // Если элементы есть?
    if (Tail != 0)
        Tail->next = temp;

    // Если элемент первый, то он одновременно и голова и хвост
    if (Count == 0)
        Head = Tail = temp;
    else
        // иначе новый элемент - хвостовой
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
    // Если в списке присутствуют элементы, то пробегаем по нему
    // и печатаем элементы, начиная с головного
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



// Тестовый пример
int main()
{
    const int n = 10;
    Stack stack(n);

    int a[n] = { 0,1,2,3,4,5,6,7,8,9 };

    assert(stack.IsEmpty());
    // Добавляем элементы, стоящие на четных индексах, в голову,
    // на нечетных - в хвост
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

