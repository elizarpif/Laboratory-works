#include "Polynom.h"



void Menu()
{
	cout << "[1] Дроби" << endl;
	cout << "[2] Матрицы" << endl;
	cout << "[3] Полином" << endl;
	cout << "[4] Выход" << endl<<">>";
	char ch;
	cin >> ch;
	switch (ch)
	{
	case '1':
	{ 
		menuFrac();
		break;
	}
	case '2':
	{
		MatrixMenu();
		break;
	}
	case '3':
	{
		MenuPoli();
		break;
	}
	case '4':
	{
		return;
	}

	}
	Menu();
}


int main()
{
	setlocale(0, "Rus");
	Menu();
	system("pause");
	return 0;
}