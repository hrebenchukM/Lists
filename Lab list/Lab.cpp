#include <iostream>
#include <cassert>
using namespace std;

struct Element
{
	// Данные
	char data;
	// Адрес следующего элемента списка
	Element* Next;
};

// Односвязный список
class List
{
	// Адрес головного элемента списка
	Element* Head;
	// Адрес головного элемента списка
	Element* Tail;
	// Количество элементов списка
	int Count;

public:
	// Конструктор
	List();
	// Деструктор
	~List();

	// Добавление элемента в список
	// (Новый элемент становится последним)
	void Add(char );

	// Удаление элемента списка
	// (Удаляется головной элемент)
	void Del();
	// Удаление всего списка
	void DelAll();

	// Распечатка содержимого списка
	// (Распечатка начинается с головного элемента)
	void Print();

	// Получение количества элементов, находящихся в списке
	int GetCount();




	void AddElemInPos(char,int );
	int SearchElem(char );

};

List::List()
{
	// Изначально список пуст
	Head = Tail = NULL;
	Count = 0;
}

List::~List()
{
	// Вызов функции удаления
	DelAll();
}

int List::GetCount()
{
	// Возвращаем количество элементов
	return Count;
}

void List::Add(char data)
{
	// создание нового элемента
	Element* temp = new Element;

	// заполнение данными
	temp->data = data;
	// следующий элемент отсутствует
	temp->Next = NULL;
	// новый элемент становится последним элементом списка
	// если он не первый добавленный
	if (Head != NULL) {
		Tail->Next = temp;
		Tail = temp;
	}
	// новый элемент становится единственным
	// если он первый добавленный
	else {
		Head = Tail = temp;
	}
	Count++;
}

void List::Del()
{
	// запоминаем адрес головного элемента
	Element* temp = Head;
	// перебрасываем голову на следующий элемент
	Head = Head->Next;
	// удаляем бывший головной элемент
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
	
	// создание нового элемента
	Element* temp = new Element;

	// заполнение данными
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
	// Пока еще есть элементы
	while (Head != 0)
		// Удаляем элементы по одному
		Del();
}

void List::Print()
{
	// запоминаем адрес головного элемента
	Element* temp = Head;
	// Пока еще есть элементы
	while (temp != 0)
	{
		// Выводим данные
		cout << '[' << temp->data << ']';
		// Переходим на следующий элемент
		temp = temp->Next;
	}

	cout << endl;
}




//
//// Тестовый пример
//int main()
//{
//	// Создаем объект класса List
//	List lst;
//
//	// Тестовая строка
//	char s[] = "Hello, World !!!";
//	// Выводим строку
//	cout << s << "\n\n";
//	// Определяем длину строки
//	int len = strlen(s);
//	// Загоняем строку в список
//	for (int i = 0; i < len; i++)
//		lst.Add(s[i]);
//	// Распечатываем содержимое списка
//	lst.Print();
//	// Удаляем три элемента списка
//	//lst.Del();
//	//lst.Del();
//	//lst.Del();
//	////Распечатываем содержимое списка
//	//lst.Print();
//
//	lst.AddElemInPos('*', 1);
//	lst.AddElemInPos('?', 15);
//	lst.Print();
//
//	assert(15 == lst.SearchElem('?'));
//}
//


