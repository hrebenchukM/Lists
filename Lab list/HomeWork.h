#include <iostream>
using namespace std;

template<typename E>
struct Elem
{
    E data; // данные
    Elem* next, * prev;
};


template<typename E>
class List
{
    // Голова, хвост
    Elem<E>* Head, * Tail;
    // Количество элементов
    int Count;

public:

    // Конструктор
    List();
    // Конструктор копирования
    List(const List&);
    // Деструктор
    ~List();

    // Получить количество
    int GetCount();
    // Получить элемент списка
    Elem<E>* GetElem(int);

    // Удалить весь список
    void DelAll();
    // Удаление элемента, если параметр не указывается,
    // то функция его запрашивает
    void Del(int pos = 0);
    // Вставка элемента, если параметр не указывается,
    // то функция его запрашивает
    void Insert(int pos = 0);

    // Добавление в конец списка
    void AddTail(E n);

    // Добавление в начало списка
    void AddHead(E n);

    // Печать списка
    void Print();
    // Печать определенного элемента
    void Print(int pos);

    List& operator = (const List&);
    // сложение двух списков (дописывание)
    List operator + (const List&);

    // сравнение по элементам
    bool operator == (const List&);
    bool operator != (const List&);
    bool operator <= (const List&);
    bool operator >= (const List&);
    bool operator < (const List&);
    bool operator > (const List&);

    // переворачивание списка
    List operator - ();
};

template<typename E>
List<E>::List()
{
    // Изначально список пуст
    Head = Tail = NULL;
    Count = 0;
}


template<typename E>
List<E>::List(const List& L)
{
    Head = Tail = NULL;
    Count = 0;

    // Голова списка, из которого копируем
    Elem* temp = L.Head;
    // Пока не конец списка
    while (temp != 0)
    {
        // Передираем данные
        AddTail(temp->data);
        temp = temp->next;
    }
}


template<typename E>
List<E>::~List()
{
    // Удаляем все элементы
    DelAll();
}


template<typename E>
void List<E>::AddHead(E n)
{
    // новый элемент
    Elem<E>* temp = new Elem<E>;

    // Предыдущего нет
    temp->prev = 0;
    // Заполняем данные
    temp->data = n;
    // Следующий - бывшая голова
    temp->next = Head;

    // Если элементы есть?
    if (Head != 0)
        Head->prev = temp;

    // Если элементc первый, то он одновременно и голова и хвост
    if (Count == 0)
        Head = Tail = temp;
    else
        // иначе новый элемент - головной
        Head = temp;

    Count++;
}


template<typename E>
void List<E>::AddTail(E n)
{
    // Создаем новый элемент
    Elem<E>* temp = new Elem<E>;
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


template<typename E>
void List<E>::Insert(int pos)
{
    // если параметр отсутствует или равен 0, то запрашиваем его
    if (pos == 0)
    {
        cout << "Input position: ";
        cin >> pos;
    }

    // Позиция от 1 до Count?
    if (pos < 1 || pos > Count + 1)
    {
        // Неверная позиция
        cout << "Incorrect position !!!\n";
        return;
    }

    // Если вставка в конец списка
    if (pos == Count + 1)
    {
        // Вставляемые данные
        E data;
        cout << "Input new number: ";
        cin >> data;
        // Добавление в конец списка
        AddTail(data);
        return;
    }
    else if (pos == 1)
    {
        // Вставляемые данные
        E data;
        cout << "Input new number: ";
        cin >> data;
        // Добавление в начало списка
        AddHead(data);
        return;
    }

    // Счетчик
    int i = 1;

    // Отсчитываем от головы n - 1 элементов
    Elem* Ins = Head;

    while (i < pos)
    {
        // Доходим до элемента, 
        // перед которым вставляемся
        Ins = Ins->next;
        i++;
    }

    // Доходим до элемента, 
    // который предшествует
    Elem<E>* PrevIns = Ins->prev;

    // Создаем новый элемент
    Elem<E>* temp = new Elem<E>;

    // Вводим данные
    cout << "Input new number: ";
    cin >> temp->data;

    // настройка связей
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
    // если параметр отсутствует или равен 0, то запрашиваем его
    if (pos == 0)
    {
        cout << "Input position: ";
        cin >> pos;
    }
    // Позиция от 1 до Count?
    if (pos < 1 || pos > Count)
    {
        // Неверная позиция
        cout << "Incorrect position !!!\n";
        return;
    }

    // Счетчик
    int i = 1;
   
    Elem<E>* Del = Head;

    while (i < pos)
    {
        // Доходим до элемента, 
        // который удаляется
        Del = Del->next;
        i++;
    }

    // Доходим до элемента, 
    // который предшествует удаляемому
    Elem* PrevDel = Del->prev;
    // Доходим до элемента, который следует за удаляемым
    Elem* AfterDel = Del->next;

    // Если удаляем не голову
    if (PrevDel != 0 && Count != 1)
        PrevDel->next = AfterDel;
    // Если удаляем не хвост
    if (AfterDel != 0 && Count != 1)
        AfterDel->prev = PrevDel;

    // Удаляются крайние?
    if (pos == 1)
        Head = AfterDel;
    if (pos == Count)
        Tail = PrevDel;

    // Удаление элемента
    delete Del;

    Count--;
}


template<typename E>
void List<E>::Print(int pos)
{
    // Позиция от 1 до Count?
    if (pos < 1 || pos > Count)
    {
        // Неверная позиция
        cout << "Incorrect position !!!\n";
        return;
    }

    Elem<E>* temp;

    // Определяем с какой стороны 
    // быстрее двигаться
    if (pos <= Count / 2)
    {
        // Отсчет с головы
        temp = Head;
        int i = 1;

        while (i < pos)
        {
            // Двигаемся до нужного элемента
            temp = temp->next;
            i++;
        }
    }
    else
    {
        // Отсчет с хвоста
        temp = Tail;
        int i = 1;

        while (i <= Count - pos)
        {
            // Двигаемся до нужного элемента
            temp = temp->prev;
            i++;
        }
    }
    // Вывод элемента
    cout << pos << " element: ";
    cout << temp->data << endl;
}



template<typename E>
void List<E>::Print()
{
    // Если в списке присутствуют элементы, то пробегаем по нему
    // и печатаем элементы, начиная с головного
    if (Count != 0)
    {
        Elem* temp = Head;//Текущий єлемннт
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
    // Пока остаются элементы, удаляем по одному с головы
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

    // Позиция от 1 до Count?
    if (pos < 1 || pos > Count)
    {
        // Неверная позиция
        cout << "Incorrect position !!!\n";
        return 0;
    }

    int i = 1;
    // Ищем нужный нам элемент
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
    // Проверка присваивания элемента "самому себе"
    if (this == &L)
        return *this;

    // удаление старого списка
    this->~List(); // DelAll();

    Elem* temp = L.Head;

    // Копируем элементы
    while (temp != 0)
    {
        AddTail(temp->data);
        temp = temp->next;
    }

    return *this;
}



template<typename E>
// сложение двух списков
List<E> List<E>::operator + (const List& L)
{
    // Заносим во временный список элементы первого списка
    List Result(*this);
    // List Result = *this;

    Elem* temp = L.Head;

    // Добавляем во временный список элементы второго списка
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
    // Сравнение по количеству
    if (Count != L.Count)
        return false;

    Elem* t1, * t2;

    t1 = Head;
    t2 = L.Head;

    // Сравнение по содержанию
    while (t1 != 0)
    {
        // Сверяем данные, которые
        // находятся на одинаковых позициях
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
    // Используем предыдущую функцию сравнения
    return !(*this == L);
}

template<typename E>
bool List<E>::operator >= (const List& L)
{
    // Сравнение по количеству
    if (Count > L.Count)
        return true;
    // Сравнение по содержанию
    if (*this == L)
        return true;

    return false;
}
template<typename E>
bool List<E>::operator <= (const List& L)
{
    // Сравнение по количеству
    if (Count < L.Count)
        return true;
    // Сравнение по содержанию
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

// переворот
template<typename E>
List<E> List<E>::operator - ()
{
    List Result;

    Elem* temp = Head;
    // Копируем элементы списка, начиная с головного,
    // в свой путем добавления элементов в голову,
    // таким образом временный список Result будет содержать
    // элементы в обратном порядке
    while (temp != 0)
    {
        Result.AddHead(temp->data);
        temp = temp->next;
    }

    return Result;
}

// Тестовый пример
void main()
{
    List<int> L;

    const int n = 10;
    int a[n] = { 0,1,2,3,4,5,6,7,8,9 };

    // Добавляем элементы, стоящие на четных индексах, в голову,
    // на нечетных - в хвост
    for (int i = 0; i < n; i++)
        if (i % 2 == 0)
            L.AddHead(a[i]);
        else
            L.AddTail(a[i]);

    // Распечатка списка
    cout << "List L:\n";
    L.Print();

    cout << endl;

    // Вставка элемента в список
    L.Insert();
    // Распечатка списка
    cout << "List L:\n";
    L.Print();

    // Распечатка 2-го и 8-го элементов списка
    L.Print(2);
    L.Print(8);

    List<int> T;

    // Копируем список
    T = L;
    // Распечатка копии
    cout << "List T:\n";
    T.Print();

    // Складываем два списка (первый в перевернутом состоянии)
    cout << "List Sum:\n";
    List<int> Sum = -L + T;
    // Распечатка списка
    Sum.Print();
}



