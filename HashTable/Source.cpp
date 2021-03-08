#include "HashTable.h"
#define SIZE 7
#define MENUSUM 6
//#include <fstream>
//
void PhoneInit(phoneBook &in, string name, string lname, string phone, string email)
{
	in.name = name;
	in.last_name = lname;
	in.email = email;
	in.phone = phone;
}

TEMPL
void FuncHistory(HashTable<Tvalue> &hashT)
{
	char ch;
	cout << "Отменить последние изменения? (y/n) ";
	cin >> ch;
	if (ch == 'y')
	{
		int col;
		cout << "Укажите количество удаляемых изменений ";
		cin >> col;
		UndoHist(hashT, col);
	}

}

TEMPL
void FuncLIstHash(HashTable<Tvalue> &hashT)
{
	cout << "Текущая хеш-таблица:" << endl;
	cout << hashT;
	cout << endl;
}

TEMPL
void FuncChangeHash(HashTable<Tvalue> &hashT)
{
	char ch;
	cout << endl << "Хотите изменить какую-либо запись? (y/n) ";
	cin >> ch;
	if (ch == 'y')
	{
		string val;
		cout << "Введите запись, которую необходимо изменить ";
		cin >> val;
		hashT.Change(Hash(val));
	}
}

void FuncChangeHash(HashTable<phoneBook> &hashT)
{
	char ch;
	cout <<endl<< "Хотите изменить какую-либо запись? (y/n) ";
	cin >> ch;
	if (ch == 'y')
	{
		string val;
		cout << "Введите email для записи, которую необходимо изменить ";
		cin >> val;
		hashT.Change( Hash(val));
	}
}

TEMPL
void FuncInsertHash(HashTable<Tvalue> &hashT)
{
	char ch;
	cout << endl << "Хотите добавить запись? (y/n) ";
	cin >> ch;
	if (ch == 'y')
	{
		Tvalue a;
		cin >> a;
		hashT.Insert(Hash(a), a);
		cout << "Добавлено!" << endl;
	}

}

TEMPL
void FuncFindHash(HashTable<Tvalue> &hashT)
{
	char ch;
	cout << endl << "Хотите найти какую-либо запись? (y/n) ";
	cin >> ch;
	if (ch == 'y')
	{
		string str;
		cout << "Введите искомую строку: ";
		cin >> str;
		SearchArg(hashT, str);

	}
}

void FuncFindHash(HashTable<phoneBook> &hashT)
{
	char ch;
	cout << endl << "Хотите найти какую-либо запись? (y/n) ";
	cin >> ch;
	if (ch == 'y')
	{

		cout << "[1] name" << endl;
		cout << "[2] lastname" << endl;
		cout << "[3] phone" << endl;
		cout << "[4] email" << endl;
		cout << "[5] company" << endl;
		cout << "[6] position" << endl;
		cin >> ch;
		if (isdigit(ch))
		{
			int num = ch - '0';
			if (num < SIZE)
			{
				string str;
				cout << "Введите искомую строку: ";
				cin >> str;
				SearchArg(hashT, str, num);
			}
		}
	}
}



template<typename Tvalue>
void(*MasFunc[SIZE])(HashTable<Tvalue> &hashT) {
	FuncInsertHash,
	FuncChangeHash,
	FuncFindHash,
	FuncHistory,
	FuncLIstHash
};

TEMPL
void Menu(HashTable<Tvalue> &hashT)
{
	cout << "[1] Вставить новую запись" << endl;
	cout << "[2] Изменить запись" << endl;
	cout << "[3] Найти запись" << endl;
	cout << "[4] Отменить последние изменения" << endl;
	cout << "[5] Вывести хеш-таблицу" << endl;
	cout << "[6] Выйти" << endl;
	char ch;
	cin >> ch;
	if (isdigit(ch))
	{
		int num = ch - '0';
		if (num < MENUSUM)
		{
			(*MasFunc<Tvalue>[num - 1])(hashT);
			system("pause");
		}
		if (num == MENUSUM)
		{
			return;
		}
	}
	ch = 0;
	try {
		system("cls");
	}
	catch (const std::exception &)
	{

	}

	Menu(hashT);
}

int main()
{
	int i = 0;
	string s;
	setlocale(0, "Rus");
	char ch;
	
	cout << "Открыть телефонную книгу? (y/n) ";
	cin >> ch;
	if (ch == 'y')
	{
		cout << "Открыта телефонная книга" << endl;
		HashTable<phoneBook> hashT;
		OpenFile(hashT);
		Menu(hashT);
		hashT.SaveFile();
	}
	else
	{
		cout << "Открыта обычная хеш-таблица" << endl;
		HashTable<string> hashT;
		OpenFile(hashT);
		Menu(hashT);
		hashT.SaveFile();
	}

	
	system("pause");
	return 0;
}