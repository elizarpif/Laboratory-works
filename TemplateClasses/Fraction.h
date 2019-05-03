#pragma once
#include <iostream>
#include <locale>
#include <string>
#include <vector>
#define Z 0
#define FOSIZE 4
using namespace std;


long double check(int r);

void ClearCin()
{ 
	//функция для очистки ввода
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}


template<typename T>
class Frac
{
	T num, denom;
public:
	Frac() : num(0), denom(0) {};
	Frac(T n1, T d1) : num(n1), denom(d1) {};
	void reduction();//сокращение

	template<typename T>
	friend ostream &operator<<(ostream &s, const Frac<T> &f);

	template<typename T>
	friend istream &operator>>(istream &s, Frac<T> &f);


	Frac operator+ (Frac op2)
	{
		Frac temp;
		if (denom == op2.denom)
		{
			temp.num = num + op2.num;
			temp.denom = denom;
		}
		else
		{
			temp.num = num * op2.denom + op2.num*denom;
			temp.denom = denom * op2.denom;
		}
		if (temp.num != 0) temp.reduction();
		return temp;
	}

	Frac operator- (Frac op2)
	{
		Frac temp;
		if (denom == op2.denom)
		{
			temp.num = num - op2.num;
			temp.denom = denom;
		}
		else
		{
			temp.num = num * op2.denom - op2.num*denom;
			temp.denom = denom * op2.denom;
		}
		if (temp.num != 0) temp.reduction();
		return temp;
	}
	Frac operator* (Frac op2)
	{
		Frac t;
		t.num = num * op2.num;
		t.denom = denom * op2.denom;
		if (t.num != 0) t.reduction();
		return t;
	}
	Frac operator* (int op2)
	{
		Frac t;
		t.num = num * op2;
		t.denom = denom;
		if (t.num != 0) t.reduction();
		return t;
	}
	Frac operator/ (int op2)
	{
		Frac t;
		t.denom = denom * op2;
		if (t.denom == 0)
		{
			cout << "Error! / 0. Знаменатель будет заменен на '1'" << endl;
			t.denom = 1;
		}
		t.num = num;
		if (t.num != 0) t.reduction();
		return t;
	}
	Frac operator= (int op2)
	{
		num = op2;
		denom = 1;
		return *this;
	}

	Frac operator= (double op2)
	{
		num = op2;
		denom = 1;
		return *this;
	}
	/*double operator= (Frac op2)
	{
		return op2.num;
	}*/
	Frac operator= (Frac ob)
	{
		num = ob.num;
		denom = ob.denom;
		if (this->num != 0) this->reduction();
		return *this;
	}
	bool operator== (int op2)
	{
		if (num == op2 && denom == 1) return true;
		else return false;
	}
	bool operator!= (int op2)
	{
		if (num == op2 && denom == 1) return false;
		else return true;
	}
	bool operator== (Frac op2)
	{
		if (num == op2.num && denom == op2.denom) return true;
		else return false;
	}
	Frac operator/ (Frac op2)
	{
		Frac t;
		t.num = num * op2.denom;
		t.denom = denom * op2.num;
		if (t.denom == 0)
		{
			cout << "Error! / 0. Знаменатель будет заменен на '1'" << endl;
			t.denom = 1;
		}
		if (t.num != 0) t.reduction();
		return t;
	}
};


template<typename T>
ostream &operator<<(ostream &s, const Frac<T> &f)
{

		if (f.denom == 1)
			s << " " << f.num << " ";
		else if (f.num == 0)
			s << f.num << " ";
		else if (f.denom == 0)
			s << " null ";
		else
		s << " "<< f.num << "/" << f.denom << " ";
		

	return s;
}

template<typename T>
istream &operator>>(istream &s,  Frac<T> &f)
{
	char c;
	T tmp;
	
	s >> tmp;
	
	//если введенное число оказалось 0, то зануляем
	if (tmp == 0)
	{
		f.num = 0;
		f.denom = 1;
	}
	else
	{
		s >> c;
		f.num = tmp;
		s >> tmp;
		if (tmp == 0) f.denom = 1;
		else f.denom = tmp;
	}


	return s;
}

template<typename T>
void Frac<T>::reduction() //сокращение дробей
{
	T n= abs(num), den = abs(denom);
	while (n != den) //пока числитель не равен знаменателю
	{
		if (n > den) n = n - den;
		else den = den - n;
	}

	//нашли число, на которое можно сократить, сокращаем
	num /= n;
	denom /= n;
	
	if (num < 0 && denom<0) //если числитель и знаменатель меньше нуля
	{
		num *= -1;
		denom *= -1;
	}
	else if (denom < 0)//знаменатель меньше нуля
	{
		denom *= (-1);
	}

}

Frac <int> FracInt1;
Frac <int> FracInt2;
Frac <float> FracFloat1;
Frac <float> FracFloat2;


template<typename T>
void FracPlus(Frac<T> a, Frac<T> b)
{
	cout << a << " + " << b << " = " << a + b;
}
template<typename T>
void FracMinus(Frac<T> a, Frac<T> b)
{
	cout << a << " - " << b << " = " << a - b;
	
}
template<typename T>
void FracMultiply(Frac<T> a, Frac<T> b)
{
	cout << a << " * " << b << " = " << a * b;
}

template<typename T>
void FracDivision(Frac<T> a, Frac<T> b)
{
	cout << a << " / " << b << " = " << a / b;
}


template<typename T>
void (*masFracOperations[FOSIZE])(Frac<T> a, Frac<T> b) {
	FracPlus,
	FracMinus,
	FracMultiply,
	FracDivision
};

template<typename T>
void menuOperFrac(Frac<T> &a, Frac<T> &b)
{
	Frac<T> result;
	char c;
	ClearCin();
	cout << "\n\nТекущие дроби: " << a << ", " << b << endl<<endl;
	cout << "[1] Ввести дроби заново" << endl;
	cout << "[2] Сложение дробей" << endl;
	cout << "[3] Вычитание дробей" << endl;
	cout << "[4] Умножение дробей" << endl;
	cout << "[5] Деление дробей" << endl;
	cout << "[6] Очистить экран " << endl;
	cout << "[7] Вернуться на уровень назад " << endl;
	cout << ">> ";
	cin >> c;
	if (c - '0' > 1 && c - '0' < 6)
	{
		int index = c - '0' - 2;
		
		(*masFracOperations<T>[index])(a, b);
		//(*MasFracOperations<T>[0])(a, b);
		system("pause");
	}
	else if (c - '0' == 1)
	{
		cout << "Введите дробь: ";
		cin >> a;
		cout << "Введите дробь: ";
		cin >> b;
	}
	else if (c - '0' == 6)
	{
		system("cls");
	}
	if (c - '0' != 7)
		menuOperFrac(a, b);
}


void menuFrac()
{
	char c;
	cout << "[1] Целочисленная дробь " << endl;
	cout << "[2] Дробь из чисел с плавающей точкой " << endl;
	cout << "[3] Вернуться на уровень назад" << endl;
	cout << ">> ";
	cin >> c;
	ClearCin();
	
	if (c == '1')
	{
		cout << "Введите дробь: ";
		cin >> FracInt1;
		cout << "Введите дробь: ";
		cin >> FracInt2;
		menuOperFrac(FracInt1, FracInt2);
	}
	else if (c == '2')
	{
		cout << "Введите дробь: ";
		cin >> FracFloat1;
		cout << "Введите дробь: ";
		cin >> FracFloat2;
		menuOperFrac(FracFloat1, FracFloat2);
	}
	cout << endl;
	if (c!='3')
		menuFrac();

}





