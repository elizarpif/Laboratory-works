#pragma once
#include "Matrix.h"
#include <list>
#include <algorithm>
#include <iterator>
#include <string>
#define PSIZE 5

template<typename T>
struct Monom
{
	T coef;
	int degree;
	Monom(T c, int d) : coef(c), degree(d) {};
	Monom() {};
	void SetMonom(T c, int d)
	{
		coef = c;
		degree = d;
	}
	T getCoef()
	{
		return coef;
	}
	int getDegree()
	{
		return degree;
	}
	Monom operator+ (Monom op2)//одинаковые степени!!!
	{
		Monom tmp = op2;
		tmp.coef = this->coef + op2.coef;
		return tmp;
	}
	bool operator== (Monom op2)
	{
		if (this->degree == op2.degree) return true;
		else return false;
	}
	Monom operator- (Monom op2)
	{
		Monom tmp = op2;
		tmp.coef = this->coef - op2.coef;
		return tmp;
	}
	Monom operator* (Monom op2)
	{
		Monom tmp = op2;
		tmp.coef = this->coef * op2.coef;
		tmp.degree = this->degree + op2.degree;
		return tmp;
	}
	Monom operator* (int op2)
	{
		Monom tmp = *this;
		tmp.coef = this->coef * op2;
		return tmp;
	}
	Monom operator/ (Monom op2)
	{
		Monom tmp = op2;
		if (op2.coef == 0)
			throw 124;
		else
		{
			tmp.coef = this->coef / op2.coef;
			tmp.degree = this->degree - op2.degree;
		}

		return tmp;
	}
	Monom operator=(int op2)
	{
		Monom tmp = *this;
		tmp.coef = op2;
		tmp.degree = 0;
		return tmp;
	}
	bool operator< (Monom op2)
	{
		if (this->degree < op2.degree) return true;
		else return false;
	}
	bool operator<= (Monom op2)
	{
		if (this->degree <= op2.degree) return true;
		else return false;
	}
	template<typename T> 
	friend ostream &operator<< (ostream &s, const Monom<T> &m);
};

template <typename T> 
ostream & operator<<(ostream & s, const Monom<T> & m)
{
	//if (m.coef != 0)
	s << m.coef << "x^" << m.degree << " ";
	return s;
}



template<typename T>
class Polynom
{
	int degr;
	list<Monom<T>> Node;

public:
	

	Polynom()
	{
	}

	~Polynom()
	{
		Node.clear();
	}


	Monom<T> getMon(int i)
	{
		return Node[i];
	}
	void SetMon(T c, int d)
	{
		Monom<T> a(c, d);
		Node.push_back(a);
	}

	template<typename T>
	friend istream &operator>>(istream &s, Polynom<T> &ob);

	template<typename T>
	friend ostream &operator<<(ostream &s, const Polynom<T> &ob);

	template<typename T>
	friend void superpos(Polynom<T> ob1, Polynom<T> ob2);

	template<typename T>
	friend void diffenencial (Polynom<T> ob);

	template<typename T>
	friend void znach(Polynom<T> ob, int ch);

	Polynom operator+ (Polynom op2);
	Polynom operator* (Polynom op2);
	Polynom operator- (Polynom op2);
	Polynom operator/ (Polynom op2);
	Polynom operator% (Polynom op2);
	/*template<>
	Polynom<double> operator/(Polynom<int> op2);*/

	Polynom operator* (int op2) 
	{
		Polynom tmp;
		Monom<T> tmon;
		for (auto it = Node.begin(); it != Node.end(); it++)
		{
			tmon = *it;
			tmon.coef = op2 *tmon.coef;
			tmp.Node.push_back(tmon);
		}

		return tmp;
	}
	bool operator!=(int ob)
	{
		Monom<T> tmon;
		for (auto it = Node.begin(); it != Node.end(); it++)
		{
			tmon = *it;
			if (!(tmon.coef==ob && tmon.degree==0))return false;
		}
	}
	Polynom operator=(int op2)
	{
		Polynom tmp;
		Monom<T> tmon;
		for (auto it = Node.begin(); it != Node.end(); it++)
		{
			tmon.coef = op2;
			tmon.degree = 0;
			tmp.Node.push_back(tmon);
		}
		
		return tmp;
	}
};

template<typename T>
Polynom<T> Polynom<T>::operator+(Polynom<T> op2)
{
	Polynom temp;
	if (this->degr >= op2.degr) //первый больше второго!
	{
		temp = *this;
		auto longer = this->Node.begin();
		auto shorter = op2.Node.begin();
		auto k = temp.Node.begin();
		while (!((*shorter) == (*longer)))
		{
			longer++;
			k++;
		}

		for (shorter; shorter != op2.Node.end(); shorter++)
		{

			*k = *longer + *shorter;
			k++;
			longer++;
		}


	}
	else if (this->degr < op2.degr) //первый меньше второго
	{
		temp = op2;
		auto shorter = this->Node.begin();
		auto longer = op2.Node.begin();
		auto k = temp.Node.begin();
		while (!((*shorter) == (*longer)))
		{
			longer++;
			k++;
		}

		for (shorter; shorter != this->Node.end(); shorter++)
		{

			*k = *longer + *shorter;
			k++;
			longer++;
		}
	}
	temp.Node.sort([](const Monom<T> &a, const Monom<T> &b) { return a.degree > b.degree; });
	return temp;
}


template<typename T>
Polynom<T> Polynom<T>::operator*(Polynom<T> op2)
{
	Polynom temp;
	//каждый умножить с каждым
	auto first = this->Node.begin();
	for (first; first != this->Node.end(); first++)
	{
		auto second = op2.Node.begin();
		for (second; second != op2.Node.end(); second++)
		{
			temp.Node.push_back((*first)*(*second));
		}
	}
	temp.Node.sort([](const Monom<T> &a, const Monom<T> &b) { return a.degree > b.degree; });
	//теперь надо избавиться от одностепенных
	Polynom add;
	auto ik = temp.Node.begin();
	auto it = temp.Node.begin();
	while (it != temp.Node.end())
	{
		if (ik != it)
		{
			if (*ik == *it)//если степени равны
			{
				*ik = *it + *ik;
				auto il = it;
				temp.Node.erase(il);
				it = ik;
			}
		}
		if (it != temp.Node.begin() && ik!=it)
			ik++;
		it++;
	}

	return temp;
}

template<typename T>
Polynom<T> Polynom<T>::operator%(Polynom<T> op2)
{
	Polynom<T> newPolynom;
	Polynom<T> copyPol = *this;
	int res = 0;
	cout << endl;
	auto it = copyPol.Node.begin();
	while (it != copyPol.Node.end())
	{
		if (*it <= *op2.Node.begin())//!!!!
		{
			Monom<T> tmpMon = *it;
			newPolynom.Node.push_back(tmpMon);
			it++;
		}
		else
		{
			Monom<T> tmpMon;
			try {

				tmpMon = *it / *op2.Node.begin();
			}
			catch (const std::exception&)
			{
				tmpMon = *it;
				cout << "При делении что-то пошло не так" << endl;
			}
			Polynom<T> tempR = op2;
			for (auto jt = tempR.Node.begin(); jt != tempR.Node.end(); jt++)
			{
				*jt = *jt * tmpMon;
				//it++;
			}

			copyPol = copyPol - tempR;
			it++;
		}

	}
	return newPolynom;
}

template<typename T>
Polynom<T> Polynom<T>::operator/(Polynom<T> op2)
{
	Polynom<T> newPolynom;
	Polynom<T> copyPol = *this;
	cout << endl;
	auto it = copyPol.Node.begin();
		while ( it != copyPol.Node.end())
		{
			if (*it < *op2.Node.begin())//!!!!
			{
				break;
			}
			else
			{
				Monom<T> tmpMon;
				try {

					tmpMon = *it / *op2.Node.begin();
				}
				catch(int a)
				{
					tmpMon = *it;
					if (a == 123)
					{
						cout << "Деление матриц не приветствуется!" << endl;
						return newPolynom;
					}
					if (a == 124)
					{
						cout << "Деление на 0 не приветствуется!" << endl;
						return newPolynom;
					}
				}
				newPolynom.Node.push_back(tmpMon);
				Polynom<T> tempR = op2;
				for (auto jt = tempR.Node.begin(); jt != tempR.Node.end(); jt++)
				{
					*jt = *jt * tmpMon;
					//it++;
				}
				
				copyPol = copyPol - tempR;
				it++;
			}

		}
	return newPolynom;
}





template<typename T>
Polynom<T> Polynom<T>::operator-(Polynom<T> op2)
{
	Polynom temp;
	Monom<T> t1,t2;
	if (this->Node.size() >= op2.Node.size()) 
	{
		temp = *this;
		auto longer = this->Node.begin();
		auto shorter = op2.Node.begin();
		auto k = temp.Node.begin();

		while (!((*shorter) == (*longer)))
		{
			longer++;
			k++;
		}

		for (shorter; shorter != op2.Node.end(); shorter++)
		{

			*k = *longer - *shorter;
			k++;
			longer++;
		}
	}
	else if (this->Node.size() < op2.Node.size()) 
	{
		temp = op2;
		auto shorter = this->Node.begin();
		auto longer = op2.Node.begin();
		auto k = temp.Node.begin();
		while (!((*shorter) == (*longer)))
		{
			longer++;
			(*k) = (*k) * (-1);
			k++;
		}

		for (shorter; shorter != this->Node.end(); shorter++)
		{

			*k = *longer - *shorter;
			k++;
			longer++;
		}
	}
	temp.Node.sort([](const Monom<T> &a, const Monom<T> &b) { return a.degree > b.degree; });
	return temp;
}

template<typename T>
istream &operator>>(istream &s, Polynom<T> &ob)
{
	int degr;
	T a;
	try
	{
		ob.Node.clear();
		cout << " ";
		s >> degr;
		//ob.degr;
		cout << "Введите коэффииенты: ";
		ClearCin();
		for (int i = degr; i >=0; i--)
		{
			//
			s >> a;	
			//cout << a;
			ob.SetMon(a, i);
		}
		ClearCin();
		ob.degr = degr;
	}
	catch (const std::exception&)
	{
		cout << " Problem!" << endl;
	}
	return s;

}

template<typename T>
ostream &operator<<(ostream &s, const Polynom<T> &ob)
{
	if (ob.Node.size() == 0)
		return s;
	auto gr = ob.Node.end();
	gr--;
	for (auto i = ob.Node.begin(); i != ob.Node.end(); ++i)
	{
		Monom<T> tmp = *i;
			s << *i;
			if (i != gr)
				s << "+ ";
	}
	s << endl;
	return s;
}


template<typename T>
void diffenencial(Polynom<T> ob) //дифференциал
{
	Monom<T> mon;
	for (auto it = ob.Node.begin(); it != ob.Node.end(); it++)
	{
		mon = *it;
		if (mon.degree != 0)
		{
			mon.coef = mon.coef * mon.degree;
			mon.degree = mon.degree - 1;
			if (it == ob.Node.begin())
				cout << "y' = ";
			else
				cout << " + ";
		}
		else
			mon.coef = 0;
		cout << mon;
		
	}
}

template<typename T>
void superpos(Polynom<T> ob1, Polynom<T> ob2) //суперпозиция
{
	for (auto it = ob1.Node.begin(); it != ob1.Node.end(); it++)
	{
		Monom<T> temp1 = *it;
		if (it != ob1.Node.begin() && it != ob1.Node.end())
			cout << " + ";
		cout << temp1.coef << "(";
		for (auto ik = ob2.Node.begin(); ik != ob2.Node.end(); ik++)
		{
			Monom<T> temp2 = *ik;
			if (ik != ob2.Node.begin() && ik != ob2.Node.end())
				cout << " + ";
			cout << temp2.coef << "x^" << temp2.degree;
			
		}
		cout << ")x^" << temp1.degree;
	}
}


template<typename T>
void znach(Polynom<T> ob, int ch) //значение полинома в точке
{
	T tmp;
	for (auto it = ob.Node.begin(); it != ob.Node.end(); it++)
	{
		Monom<T> temp1 = *it;
		
		int t = ch;
		for (int i = 0; i < temp1.degree-1; i++)
			t = t * ch;
		if (it == ob.Node.begin())
			tmp = temp1.coef*t;
		else 
		{
			if (temp1.degree == 0)
				tmp = tmp + temp1.coef;
			else
				tmp = tmp + temp1.coef*t;
		}

	}
	cout << " y = " << tmp;
}


template<typename T>
void PoliPlus(Polynom<T> a, Polynom<T> b)
{
	cout << a << " + " << b << " = "<< a + b;
}

template<typename T>
void PoliMinus(Polynom<T> a, Polynom<T> b) //-
{
	cout << a << " - " << b << " = "<< a - b;
}

template<typename T>
void PoliMultiply(Polynom<T> a, Polynom<T> b)//*
{
	cout << a << " * " << b << " = "<< a * b;
}

template<typename T>
void PoliDivision(Polynom<T> a, Polynom<T> b)///
{
	cout << a << " / " << b << " = "<< a / b;
}

template<typename T>
void PoliRemainder(Polynom<T> a, Polynom<T> b)//%
{
	cout << a << " % " << b << " = "<< a % b;

}

template<typename T>
void(*masPoliOperations[PSIZE])(Polynom<T> a, Polynom<T> b) {
	PoliPlus,
		PoliMinus,
		PoliMultiply,
		PoliDivision,
		PoliRemainder
};

template<typename T>
void subMenuPoli(Polynom<T> &a, Polynom<T> &b)
{
	string choice;
	ClearCin();
	cout << "\n\nТекущие полиномы: " << a << "\n\nand\n\n " << b << endl << endl;
	cout << "[1] Ввести полиномы заново" << endl;
	cout << "[2] Сложение " << endl;
	cout << "[3] Вычитание " << endl;
	cout << "[4] Умножение " << endl;
	cout << "[5] Деление " << endl;
	cout << "[6] Деление по модулю " << endl;
	cout << "[7] Дифференциал " << endl;
	cout << "[8] Суперпозиция" << endl;
	cout << "[9] Значение в точке " << endl;
	cout << "[10] Очистить экран " << endl;
	cout << "[11] Вернуться на уровень назад " << endl;
	cout << ">> ";
	cin >> choice;
	if (choice[0] - '0' > 1 && choice[0] - '0' < 7 && choice.length() == 1)
	{
		int index = choice[0] - '0' - 2;
		if (index == 1 || index == 3 || index == 4)
		{

			cout << "Выберите нужный полином (1 или 2)" << endl << ">> ";
			char ch;
			cin >> ch;
			if (ch == '1')
			{
				(*masPoliOperations<T>[index])(a, b);
			}
			else if (ch == '2')
			{
				(*masPoliOperations<T>[index])(b, a);
			}
		}
		else
			(*masPoliOperations<T>[index])(a, b);
		cout << endl;
		system("pause");
	}
	else if (choice == "1") //новые значения
	{
		cin >> a;
		cin >> b;
		//cout << endl;
	}
	else if (choice == "7") //diff
	{
		cout << "Выберите нужный полином (1 или 2)" << endl << ">> ";
		char ch;
		cin >> ch;
		if (ch == '1')
		{
			diffenencial(a);
		}
		else if (ch == '2')
		{
			diffenencial(b);
		}
		cout << endl;
		system("pause");
	}
	else if (choice == "8") //суперпозиция
	{
		superpos(a, b);
		cout << endl;
		system("pause");
	}
	else if (choice == "9") //значение в точке
	{
		cout << "Выберите нужный полином (1 или 2)" << endl << ">> ";
		char ch;
		cin >> ch;
		cout << "Укажите точку (натуральное число)" << endl << ">> ";
		int x;
		cin >> x;
		if (ch == '1')
		{
			znach(a, x);
		}
		else if (ch == '2')
		{
			znach(b, x);
		}
		cout << endl;
		system("pause");
	}
	else if (choice == "10") //очистить экран
	{
		system("cls");
	}
	else if (choice == "11")
		return;
	subMenuPoli(a, b);

}

void MenuPoli()
{
	char c;
	cout << "[1] Полином из целых чисел " << endl;
	cout << "[2] Полином из чисел с плавающей точкой " << endl;
	cout << "[3] Полином из целочисленных матриц " << endl;
	cout << "[4] Полином из матриц, состоящих из чисел с плавающей точкой " << endl;
	cout << "[5] Полином из матриц, состоящих из целочисленных дробей " << endl;
	cout << "[6] Полином из матриц, состоящих из дробей, состоящих из чисел с плавающей точкой " << endl;
	cout << "[7] Полином из целочисленных дробей" << endl;
	cout << "[8] Полином из дробей, состоящих из чисел с плавающей точкой" << endl;
	cout << "[9] Вернуться на уровень назад" << endl;
	cout << ">> ";
	cin >> c;
	ClearCin();
	cout << "Вы ввели " << c << endl;
	if (c - '0' > 0 && c - '0' < 9)
	{
		switch (c)
		{
		case '1':
			{
				Polynom<int> a, b;
				cin >> a;
				cin >> b;
				subMenuPoli(a, b);
				break;
			}
		case '2':
		{
			Polynom<double> a, b;
			cin >> a;
			cin >> b;
			subMenuPoli(a, b);
			break;
		}
		case '3':
		{
			Polynom<Matrix<int, 3>> a, b;
			cin >> a;
			cin >> b;
			subMenuPoli(a, b);
			break;
		}
		case '4':
		{
			Polynom<Matrix<double, 3>> a, b;
			cin >> a;
			cin >> b;
			subMenuPoli(a, b);
			break;
		}
		case '5':
		{
			Polynom<Matrix<Frac<int>, 3>> a, b;
			cin >> a;
			cin >> b;
			subMenuPoli(a, b);
			break;
		}
		case '6':
		{
			Polynom<Matrix<Frac<float>, 3>> a, b;
			cin >> a;
			cin >> b;
			subMenuPoli(a, b);
			break;
		}
		case '7':
		{
			Polynom<Frac<int>> a, b;
			cin >> a;
			cin >> b;
			subMenuPoli(a, b);
			break;
		}
		case '8':
		{
			Polynom<Frac<double>> a, b;
			cin >> a;
			cin >> b;
			subMenuPoli(a, b);
			break;
		}
		}
	}
	else
		return;
	MenuPoli();
}
