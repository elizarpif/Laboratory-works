#pragma once
#include "Fraction.h"
#define MSIZE 3
//функция для перемен мест в неквадратной матрицы
void swap_obr(vector<vector<double>> a, int p, int n, int m);


template <typename T, int n>
class Matrix
{
	vector<vector<T>> Matr;
	int row = n;
	T opr;
	double opr2;

public:

	Matrix() {
		try
		{
			vector<vector<T>> t(row, vector<T>(row));
			Matr = t;
		}
		catch (const std::exception&)
		{
			cout << "OOPS!" << endl;
		}
		
	}

	Matrix(vector<vector<T>> inp) : Matr(inp) {}

	~Matrix() { Matr.clear(); }

	Matrix operator- (Matrix op2); 
	Matrix operator+ (Matrix op2);
	Matrix operator* (Matrix op2);
	Matrix operator* (int op2);
	Matrix operator/ (Matrix op2);
	Matrix operator= (int op2)
	{
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < row;j++)
			{
				Matr[i][j] = op2;
			}
		}
		return *this;
	}
	bool operator== (int op2)
	{
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < row; j++)
			{
				if (Matr[i][j] != op2)
					return false;
			}
		}
		return true;
	}
	

	template<typename T, int n>
	friend ostream &operator<<(ostream &s, const Matrix<T, n> &m);

	template<typename T, int n>
	friend istream &operator>>(istream &s, Matrix<T, n> &m);

	T getVector() //получить текущий вектор
	{
		return Matr;
	}

	int getSize() //получить текущее значение
	{
		return row;
	}

	template<typename T, int n>
	friend T determin(Matrix<T, n> m); //определитель

	template<int n>
	friend int determin(Matrix<int, n> m); //спецификация шаблона для интовых значений

	template<int n>
	friend Matrix<double, n> obr_matrix(Matrix<int, n> m, int det); //обратная матрица, спецификация

	template<typename T, int n>
	friend Matrix<T, n> obr_matrix(Matrix<T, n> m, T det); //обратная матрица
};

template<typename T, int n>
Matrix<T, n> Matrix<T, n>::operator+ (Matrix<T, n> op2)
{
	Matrix<T, n> temp;
	temp = op2;
	//одинаковые размеры
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < row; j++)
		{
			temp.Matr[i][j] = op2.Matr[i][j] + Matr[i][j];
		}
	}
	return temp;
}

template<typename T, int n>
Matrix<T, n> Matrix<T, n>::operator- (Matrix<T, n> op2)
{
	Matrix<T, n> temp;
	temp = op2;
	//одинаковые размеры
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < row; j++)
		{
			temp.Matr[i][j] = op2.Matr[i][j] - Matr[i][j];
		}
	}
	return temp;
}
template<typename T, int n>
Matrix<T, n> Matrix<T, n>::operator* (Matrix<T, n> op2) //перегрузка умножения
{
	Matrix temp = op2;
	T sum, rus, tmp;
	sum = 0;
	int i, j, l;
	for (i = 0; i < row; i++) {
		for (j = 0; j < row; j++)
		{
			sum = 0;
			for (int l = 0; l < row; l++)
			{
				rus = sum;
				tmp = Matr[i][l] * op2.Matr[l][j];
				sum = rus + tmp;
				temp.Matr[i][j] = sum;
			}
		}
	}

	return temp;
}
template<typename T, int n>
Matrix<T, n> Matrix<T, n>::operator* (int op2) //умножение на число
{
	T sum, rus, tmp;
	sum = 0;
	int i, j, l;
	for (i = 0; i < row; i++) {
		for (j = 0; j < row; j++)
		{
			(*this).Matr[i][j] = (*this).Matr[i][j] * op2;
		}
	}

	return *this;
}



template<typename T, int n>
Matrix<T, n> Matrix<T, n>::operator/ (Matrix<T, n> op2)
{
	//деление матриц не приветствуется, так как деление - это умножение на обратную, и как такого
	//термина деление не существует. Если же будет исключительная ситуация,деление вернет исходную матрицу
	throw 123;
	//return *this;
}


template<typename T, int n>
istream &operator>>(istream &s,  Matrix<T,n> &m)
{
	//ввод матрицы
	T temp;
	try
	{
		cout << "Введите матрицу (с пробелами и переносами строки)" << endl;
		for (int i = 0; i < m.row; i++)
		{
			for (int j = 0; j < m.row; j++)
			{
				s >> temp;
				
				m.Matr[i][j] = temp;
			}
		}		
	}
	catch (const std::exception&)
	{
		cout << "Problem!" << endl;
	}
	return s;
}


template<typename T, int n>
ostream & operator<<(ostream & s, const Matrix<T, n>& m)
{
	cout << endl<<endl;
	//вывод матрицы
	try
	{
		for (int i = 0; i < m.row; i++)
		{
			for (int j = 0; j < m.row; j++)
			{
				cout << m.Matr[i][j]<<" ";
			}
			cout << endl;
		}
	}
	catch (const exception&)
	{
		cout << "Проблема с размером матрицы" << endl;
	}
	return s;
}



template<typename T, int n>
T determin(Matrix<T, n> m) //определитель
{
	int i, j, k, i_1, i_2, minus = 0, size = n;
	T h, max, min, opr, tmp, tmp2;
	opr = 1;
	Matrix<T, n> ish = m; //исходную запоминаем
	for (i = 0; i < size; i++)
	{
		tmp = m.Matr[i][i];
		if (tmp == 0) //если текущий элемент 0
		{
			for (j = i + 1; j < size; j++)
			{
				tmp2 = m.Matr[j][i];
				if (tmp2 != 0)
				{
					for (k = 0; k < size; k++) //меняем местами строки
					{
						h = m.Matr[j][k];
						m.Matr[j][k] = m.Matr[i][k];
						m.Matr[i][k] = h;
						minus = minus + 1;
					}
				}
				//break;
			}

		}
		if (tmp != 0) //если текущий не 0
		{
			for (k = i + 1; k < size; k++)
			{
				max = m.Matr[k][i]; //max - делимое, min -делитель
				min = m.Matr[i][i];
				h = max / min; //делим, чтобы получить единички
				for (j = i; j < size; j++)
				{
					m.Matr[k][j] = m.Matr[k][j] - h * m.Matr[i][j];
				}
			}
		}
	}
	int edin = 0;
	while (edin < size - 1)
	{
		for (i = 0; i < size; i++)
		{
			tmp = m.Matr[i][i];
			if (tmp == 0) opr = 0;
			if (tmp == 1) edin++;
		}
		edin++;
	}
	if (opr != 0) opr = 1;
	for (i = 0; i < size; i++)
	{
		opr = opr * m.Matr[i][i];
	}
	if (minus % 2 != 0) opr = opr * (-1);
	return opr;
}


template<int n>
int determin(Matrix<int, n> m) //спецификация для int
{
	int i, j, k, i_1, i_2, minus = 0, size = n;
	double h, max, min, opr, tmp, tmp2;
	opr = 1;
	vector<vector<double>> tempMatr(n, vector<double>(n));
	//создаем вектор
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			tempMatr[i][j] = m.Matr[i][j];
		}
	}

	for (i = 0; i < size; i++)
	{
		tmp = tempMatr[i][i];
		if (tmp == 0) //если по гл диагонали 0
		{
			for (j = i + 1; j < size; j++)
			{
				tmp2 = tempMatr[j][i];
				if (tmp2 != 0)
				{
					for (k = 0; k < size; k++)
					{
						//меняем местами
						h = tempMatr[j][k];
						tempMatr[j][k] = tempMatr[i][k];
						tempMatr[i][k] = h;
						minus = minus + 1;
					}
				}
				//break;
			}

		}
		if (tmp != 0) //если не 0
		{
			for (k = i + 1; k < size; k++)
			{
				max = tempMatr[k][i]; 
				min = tempMatr[i][i]; //делим на это число всю строку
				h = max / min;
				for (j = i; j < size; j++)
					tempMatr[k][j] = tempMatr[k][j] - h * tempMatr[i][j];
			}
		}
	}
	int edin = 0;
	while (edin < size - 1)
	{
		
		for (i = 0; i < size; i++)
		{
			tmp = tempMatr[i][i];
			if (tmp == 0) opr = 0;
			if (tmp == 1) edin++;
		}
		edin++;
	}
	if (opr != 0) opr = 1;
	for (i = 0; i < size; i++)
	{
		opr = opr * tempMatr[i][i];
	}
	if (minus % 2 != 0) opr = opr * (-1);
	m.opr = opr;
	return opr;

}

template<int n>
Matrix<double, n> obr_matrix(Matrix<int, n> m, int det) //спецификация для целочисленной матрицы, так как результат будет другого типа
{
	int i = 0, j = 0, p=0;
	if (det == 0)
	{
		cout << "Не существует обратной" << endl;
		Matrix<double, n> a;
		return a;
	}

	vector<vector<double>> matrix_res(n, vector<double>(n * 2));
	for (i = 0; i < n; i++)
	{
		for(j=0; j<n;j++) 
			matrix_res[i][j] = m.Matr[i][j];
	}
	for ( i = 0; i < n; i++)//создаем единичную
	{
		
		for ( j = n; j < n*2; j++)
		{
			if (j == i + n)
			{
				matrix_res[i][j] = 1;
			}
			else
				matrix_res[i][j] = 0;
		}
	}
	double res, cur, karl, roug;
	for (p = 0; p < n; p++)
	{
		if (matrix_res[p][p] == 0)
		{
			//поменять местами строки
			swap_obr(matrix_res, p, n, n * 2);
		}
		res = matrix_res[p][p] / matrix_res[p][p]; //нам нужна 1, поэтому делим на число, стоящее на диагонали
		cur = matrix_res[p][p]; //теперь запоминаем это число и делим всю строку

		for (j = p + 1; j < n*2; j++) //делим
			matrix_res[p][j] = matrix_res[p][j] / cur;
		for (i = 0; i < n; i++)
		{
			if (i != p)
			{
				for (j = p; j < n*2; j++)
				{
					if (j == p) //если совпало, меняем местами
						karl = matrix_res[i][j];
					roug = matrix_res[i][j] - karl * matrix_res[p][j];
					matrix_res[i][j] = roug;
				}
			}
		}
	}
	//правая часть, что получилас в результате преобразований, и есть обратная матрица
	Matrix<double, n> result;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
			result.Matr[i][j] = matrix_res[i][ j + n];
	}
	return result;
}

void swap_obr(vector<vector<double>> a, int p, int n, int m) //функция перестановки строк для целоичесленного случая
{
	double zer = a[p][p], cur;
	int fl = p;
	int j = p + 1;
	while (j < n)
	{
		if (a[j][p] != 0)
		{
			zer = a[j][p];
			fl = j;
		}
		j++;
	}
	if (zer != 0)
	{
		if (fl > p && zer != 0)
		{
			for (j = p; j < m; j++) //менем местами
			{
				cur = a[p][j];
				zer = a[fl][j];
				a[p][j] = zer;
				a[fl][j] = cur;
			}

		}
	}
}




template<typename T, int n>
Matrix<T, n> obr_matrix(Matrix<T, n> m, T det)
{
	int i = 0, j = 0, p =  0;
	if (det == 0) //вырожденная матрица
	{
		cout << "Не существует обратной" << endl;
		Matrix<T, n> result;
		return result;
	}
	if (n == 2)
	{ 
		Matrix<T, n> result = m;
		result.Matr[0][0] = m.Matr[1][1]/det;
		result.Matr[1][1] = m.Matr[0][0]/det;
		result.Matr[0][1] = m.Matr[0][1] * (-1) / det;
		result.Matr[1][0] = m.Matr[1][0] * (-1) /det;
		return result;
	}
	else
	{
		try{
			vector<vector<T>> matrix_res(n, vector<T>(n * 2)); //метод - присоединяем справа матрицу и Гауссом находим обратную		for (i = 0; i < n; i++)
			{
				for (j = 0; j < n; j++)
					matrix_res[i][j] = m.Matr[i][j];
			}
			for (i = 0; i < n; i++)//создали единичную
			{

				for (j = n; j < n * 2; j++)
				{
					if (j == i + n) //по диагонали 1
					{
						matrix_res[i][j] = 1;
					}
					else //во всех остальных случаях 0
						matrix_res[i][j] = 0;
				}
			}
			T res, cur, karl, roug;
			for (p = 0; p < n; p++) //метод Гаусса
			{
				if (matrix_res[p][p] == 0) //если по диагонали слева есть нулевая, то меняем местами
				{
					T zer = matrix_res[p][p], cur;
					int fl = p;
					int l = p + 1;
					while (l < n)
					{
						if (matrix_res[l][p] != 0)
						{
							zer = matrix_res[l][p];
							fl = l;
						}
						l++;
					}
					if (zer != 0)
					{
						if (fl > p && zer != 0)
						{
							for (l = p; l < n * 2; l++) //swap
							{
								cur = matrix_res[p][l];
								zer = matrix_res[fl][l];
								matrix_res[p][l] = zer;
								matrix_res[fl][l] = cur;
							}

						}
					}
				}
				res = matrix_res[p][p] / matrix_res[p][p]; //чтобы получилась 1
				cur = matrix_res[p][p]; //запоминаем текущее
				for (j = p + 1; j < n * 2; j++) //каждый делим
					matrix_res[p][j] = matrix_res[p][j] / cur;
				for (i = 0; i < n; i++)
				{
					if (i != p)
					{
						for (j = p; j < n * 2; j++)
						{
							if (j == p) //меняем местами, если совпало
								karl = matrix_res[i][j];
							roug = matrix_res[i][j] - karl * matrix_res[p][j];
							matrix_res[i][j] = roug;
						}
					}
				}
			}
			//выделяем правую часть, она и есть наша обратная матрица
			Matrix<T, n> result;
			for (i = 0; i < n; i++)
			{
				for (j = 0; j < n; j++)
					result.Matr[i][j] = matrix_res[i][j + n];
			}
			return result;
		}
		catch (const exception&)
		{
			cout << "Error!" << endl;
			return m;
		}

	}

}

template<typename T, int n>
void MatrixPlus(Matrix<T, n> a, Matrix<T, n> b) //сумма матриц
{
	cout << endl << a << " + " << b << " = " << a + b << endl;
}

template<typename T, int n>
void MatrixMinus(Matrix<T, n> a, Matrix<T, n> b) //разность
{
	cout << endl << a << " - " << b << " = " << a - b << endl;
}

template<typename T, int n>
void MatrixMultiply(Matrix<T, n> a, Matrix<T, n> b) //умножение
{
	cout << endl << a << " * " << b << " = " << a * b << endl;
}



template<typename T, int n> //массив указателей на шаблонные функции, для операций с матрицами
void(*masMatrixOperations[MSIZE])(Matrix<T, n> a, Matrix<T, n> b) {
	MatrixPlus,
	MatrixMinus,
	MatrixMultiply,
	//MatrixDivision
};

template<typename T, int n>
void subMatrixMenu(Matrix<T, n> &a, Matrix<T, n> &b) //одменю для работы с выбранным типом
{
	ClearCin();
	char choice;
	cout << "Текущие матрицы:\n" << a << "\nand\n" << b;
	cout << endl << "[1] Ввести матрицы заново " << endl;
	cout << endl << "[2] Сложение " << endl;
	cout << endl << "[3] Вычитание " << endl;
	cout << endl << "[4] Умножение " << endl;
	cout << endl << "[5] Определитель " << endl;
	cout << endl << "[6] Обратная матрица " << endl;
	cout << endl << "[7] Очистить экран " << endl;
	cout << endl << "[8] Вернуться на уровень назад " << endl;
	cout << ">> ";
	cin >> choice;
	if (choice - '0' > 1 && choice - '0' < 5)
	{
		int index = choice - '0' - 2;

		(*masMatrixOperations<T, n>[index])(a, b);
		system("pause");
	}
	else if (choice == '1') //ввести заново
	{
		cin >> a;
		cin >> b;

	}
	else if (choice == '5' || choice == '6')//определитель или обратная матрица
	{
		cout << "Выберите нужную матрицу (1 или 2)" << endl << ">> ";
		char ch;
		cin >> ch;
		if (ch == '1')
		{
			cout << "det = " << determin(a)<<endl;
			if (choice == '6')
				cout << "Обратная матрица: " << obr_matrix(a, determin(a));
		}
		if (ch == '2')
		{
			cout << "det = " << determin(b)<<endl;
			if (choice == '6')
				cout << "Обратная матрица: " << obr_matrix(b, determin(b));
		}
		system("pause");
	}
	else if (choice == '7') 
		system("cls");
	else if (choice == '8') 
		return;
	subMatrixMenu(a, b);
}

void MatrixMenu()
{
	char typeMatrix;
	cout <<endl<< "[1] Целочисленная матрица " << endl;
	cout << "[2] Матрица из чисел с плавающей точкой" << endl;
	cout << "[3] Матрица из целочисленных дробей" << endl;
	cout << "[4] Матрица из дробей, состоящих из чисел с плавающей точкой" << endl;
	cout << "[5] Вернуться на уровень назад" << endl;

	cout << ">> ";
	cin >> typeMatrix;	
	ClearCin();
	if (typeMatrix=='5') //выход
	{
		return;
	}
	else if (typeMatrix - '0' > 0 && typeMatrix - '0' < 5) //в пределах допустимых типов
	{
		const int sizeMatrix = 3;
		cout << "Матрица размера 3*3! "<<endl;
		switch (typeMatrix)
		{
		case '1': //матрица целочисленная
		{
			
			Matrix<int, sizeMatrix> MInt1, MInt2;
			cin >> MInt1;
			cin >> MInt2;
			subMatrixMenu(MInt1, MInt2);
			break;
		}
		case '2': //Матрица из чисел с плавающей точкой
		{
			
			Matrix<double, sizeMatrix> MFloat1, MFloat2;
			cin >> MFloat1;
			cin >> MFloat2;
			subMatrixMenu(MFloat1, MFloat2);
			break;
		}
		case '3': //матрица из дробей
		{
			
			Matrix<Frac<int>, sizeMatrix> MFracInt1, MFracInt2;
			cin >> MFracInt1;
			cin >> MFracInt2;
			subMatrixMenu(MFracInt1, MFracInt2);
			break;
		}
		case '4': //Матрица из дробей, состоящих из чисел с плавающей точкой
		{
		
			Matrix<Frac<float>, sizeMatrix> MFracFloat1, MFracFloat2;
			cin >> MFracFloat1;
			cin >> MFracFloat2;
			subMatrixMenu(MFracFloat1, MFracFloat2);
			break;
		}
		}
	}

	MatrixMenu(); //снова вызываем менюшку

}
