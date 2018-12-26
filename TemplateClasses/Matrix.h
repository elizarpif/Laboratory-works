#pragma once
#include "Fraction.h"
#define MSIZE 3
//������� ��� ������� ���� � ������������ �������
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

	T getVector() //�������� ������� ������
	{
		return Matr;
	}

	int getSize() //�������� ������� ��������
	{
		return row;
	}

	template<typename T, int n>
	friend T determin(Matrix<T, n> m); //������������

	template<int n>
	friend int determin(Matrix<int, n> m); //������������ ������� ��� ������� ��������

	template<int n>
	friend Matrix<double, n> obr_matrix(Matrix<int, n> m, int det); //�������� �������, ������������

	template<typename T, int n>
	friend Matrix<T, n> obr_matrix(Matrix<T, n> m, T det); //�������� �������
};

template<typename T, int n>
Matrix<T, n> Matrix<T, n>::operator+ (Matrix<T, n> op2)
{
	Matrix<T, n> temp;
	temp = op2;
	//���������� �������
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
	//���������� �������
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
Matrix<T, n> Matrix<T, n>::operator* (Matrix<T, n> op2) //���������� ���������
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
Matrix<T, n> Matrix<T, n>::operator* (int op2) //��������� �� �����
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
	//������� ������ �� ��������������, ��� ��� �������  - ��� ��������� �� ��������, � ��� ������
	//������� ������� �� ����������. ���� �� ����� �������������� ��������,������� ������ �������� �������
	throw 123;
	//return *this;
}


template<typename T, int n>
istream &operator>>(istream &s,  Matrix<T,n> &m)
{
	//���� �������
	T temp;
	try
	{
		cout << "������� ������� (� ��������� � ���������� ������)" << endl;
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
	//����� �������
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
		cout << "�������� � �������� �������" << endl;
	}
	return s;
}



template<typename T, int n>
T determin(Matrix<T, n> m) //������������
{
	int i, j, k, i_1, i_2, minus = 0, size = n;
	T h, max, min, opr, tmp, tmp2;
	opr = 1;
	Matrix<T, n> ish = m; //�������� ����������
	for (i = 0; i < size; i++)
	{
		tmp = m.Matr[i][i];
		if (tmp == 0) //���� ������� ������� 0
		{
			for (j = i + 1; j < size; j++)
			{
				tmp2 = m.Matr[j][i];
				if (tmp2 != 0)
				{
					for (k = 0; k < size; k++) //������ ������� ������
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
		if (tmp != 0) //���� ������� ������� �� ����� 0
		{
			for (k = i + 1; k < size; k++)
			{
				max = m.Matr[k][i]; //max - �������, min -��������
				min = m.Matr[i][i];
				h = max / min; //�����, ����� �������� ��������
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
int determin(Matrix<int, n> m) //������������ ��� int
{
	int i, j, k, i_1, i_2, minus = 0, size = n;
	double h, max, min, opr, tmp, tmp2;
	opr = 1;
	vector<vector<double>> tempMatr(n, vector<double>(n));
	//������� ������
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
		if (tmp == 0) //���� �� �� ��������� 0
		{
			for (j = i + 1; j < size; j++)
			{
				tmp2 = tempMatr[j][i];
				if (tmp2 != 0)
				{
					for (k = 0; k < size; k++)
					{
						//������ �������
						h = tempMatr[j][k];
						tempMatr[j][k] = tempMatr[i][k];
						tempMatr[i][k] = h;
						minus = minus + 1;
					}
				}
				//break;
			}

		}
		if (tmp != 0) //���� �� 0
		{
			for (k = i + 1; k < size; k++)
			{
				max = tempMatr[k][i]; //max - �������, min -��������
				min = tempMatr[i][i]; //����� �� ��� ����� ��� ������
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
Matrix<double, n> obr_matrix(Matrix<int, n> m, int det) //������������ ��� ������������� �������, ��� ��� ��������� ����� ������� ����
{
	int i = 0, j = 0, p=0;
	if (det == 0)
	{
		cout << "�� ���������� ��������" << endl;
		Matrix<double, n> a;
		return a;
	}

	vector<vector<double>> matrix_res(n, vector<double>(n * 2));
	for (i = 0; i < n; i++)
	{
		for(j=0; j<n;j++) 
			matrix_res[i][j] = m.Matr[i][j];
	}
	for ( i = 0; i < n; i++)//������� ���������
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
			//�������� ������� ������
			swap_obr(matrix_res, p, n, n * 2);
		}
		res = matrix_res[p][p] / matrix_res[p][p]; //��� ����� 1, ������� ����� �� �����, ������� �� ���������
		cur = matrix_res[p][p]; //������ ���������� ��� ����� � ����� ��� ������

		for (j = p + 1; j < n*2; j++) //����� 
			matrix_res[p][j] = matrix_res[p][j] / cur;
		for (i = 0; i < n; i++)
		{
			if (i != p)
			{
				for (j = p; j < n*2; j++)
				{
					if (j == p) //���� �������, ������ �������
						karl = matrix_res[i][j];
					roug = matrix_res[i][j] - karl * matrix_res[p][j];
					matrix_res[i][j] = roug;
				}
			}
		}
	}
	//������ �����, ��� ��������� � ����������  ��������������, � ���� �������� �������
	Matrix<double, n> result;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
			result.Matr[i][j] = matrix_res[i][ j + n];
	}
	return result;
}

void swap_obr(vector<vector<double>> a, int p, int n, int m) //������� ������������ ����� ��� ��������������� ������
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
			for (j = p; j < m; j++) //����� �������
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
	if (det == 0) //����������� �������
	{
		cout << "�� ���������� ��������" << endl;
		Matrix<T, n> result;
		return result;
	}
	if (n == 2)
	{ 
		//��� ������� �������� 2
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
			vector<vector<T>> matrix_res(n, vector<T>(n * 2)); //����� - ������������ ������ ������� � ������� ������� ��������
			for (i = 0; i < n; i++)
			{
				for (j = 0; j < n; j++)
					matrix_res[i][j] = m.Matr[i][j];
			}
			for (i = 0; i < n; i++)//������� ���������
			{

				for (j = n; j < n * 2; j++)
				{
					if (j == i + n) //�� ��������� 1
					{
						matrix_res[i][j] = 1;
					}
					else //�� ���� ��������� ������� 0
						matrix_res[i][j] = 0;
				}
			}
			T res, cur, karl, roug;
			for (p = 0; p < n; p++) //����� ������
			{
				if (matrix_res[p][p] == 0) //���� �� ��������� ����� ���� �������, �� ������ �������
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
							for (l = p; l < n * 2; l++) //������ �������
							{
								cur = matrix_res[p][l];
								zer = matrix_res[fl][l];
								matrix_res[p][l] = zer;
								matrix_res[fl][l] = cur;
							}

						}
					}
				}
				res = matrix_res[p][p] / matrix_res[p][p]; //����� ���������� 1
				cur = matrix_res[p][p]; //���������� �������
				for (j = p + 1; j < n * 2; j++) //������ �����
					matrix_res[p][j] = matrix_res[p][j] / cur;
				for (i = 0; i < n; i++)
				{
					if (i != p)
					{
						for (j = p; j < n * 2; j++)
						{
							if (j == p) //������ �������, ���� �������
								karl = matrix_res[i][j];
							roug = matrix_res[i][j] - karl * matrix_res[p][j];
							matrix_res[i][j] = roug;
						}
					}
				}
			}
			//�������� ������ �����, ��� � ���� ���� �������� �������
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
void MatrixPlus(Matrix<T, n> a, Matrix<T, n> b) //����� ������
{
	cout << endl << a << " + " << b << " = " << a + b << endl;
}

template<typename T, int n>
void MatrixMinus(Matrix<T, n> a, Matrix<T, n> b) //�������� ������
{
	cout << endl << a << " - " << b << " = " << a - b << endl;
}

template<typename T, int n>
void MatrixMultiply(Matrix<T, n> a, Matrix<T, n> b) //��������� ������
{
	cout << endl << a << " * " << b << " = " << a * b << endl;
}



template<typename T, int n> //������ ���������� �� ��������� �������, ��� �������� � ���������
void(*masMatrixOperations[MSIZE])(Matrix<T, n> a, Matrix<T, n> b) {
	MatrixPlus,
	MatrixMinus,
	MatrixMultiply,
	//MatrixDivision
};

template<typename T, int n>
void subMatrixMenu(Matrix<T, n> &a, Matrix<T, n> &b) //������ ��� ������ � ��������� �����
{
	ClearCin();
	char choice;
	cout << "������� �������:\n" << a << "\nand\n" << b;
	cout << endl << "[1] ������ ������� ������ " << endl;
	cout << endl << "[2] �������� " << endl;
	cout << endl << "[3] ��������� " << endl;
	cout << endl << "[4] ��������� " << endl;
	cout << endl << "[5] ������������ " << endl;
	cout << endl << "[6] �������� ������� " << endl;
	cout << endl << "[7] �������� ����� " << endl;
	cout << endl << "[8] ��������� �� ������� ����� " << endl;
	cout << ">> ";
	cin >> choice;
	if (choice - '0' > 1 && choice - '0' < 5)
	{
		int index = choice - '0' - 2;

		(*masMatrixOperations<T, n>[index])(a, b);
		system("pause");
	}
	else if (choice == '1') //������ ������
	{
		cin >> a;
		cin >> b;

	}
	else if (choice == '5' || choice == '6')//������������ ��� �������� �������
	{
		cout << "�������� ������ ������� (1 ��� 2)" << endl << ">> ";
		char ch;
		cin >> ch;
		if (ch == '1')
		{
			cout << "det = " << determin(a)<<endl;
			if (choice == '6')
				cout << "�������� �������: " << obr_matrix(a, determin(a));
		}
		if (ch == '2')
		{
			cout << "det = " << determin(b)<<endl;
			if (choice == '6')
				cout << "�������� �������: " << obr_matrix(b, determin(b));
		}
		system("pause");
	}
	else if (choice == '7') //�������
		system("cls");
	else if (choice == '8') //�����
		return;
	subMatrixMenu(a, b);
}

void MatrixMenu()
{
	char typeMatrix;
	cout <<endl<< "[1] ������������� ������� " << endl;
	cout << "[2] ������� �� ����� � ��������� ������" << endl;
	cout << "[3] ������� �� ������������� ������" << endl;
	cout << "[4] ������� �� ������, ��������� �� ����� � ��������� ������" << endl;
	cout << "[5] ��������� �� ������� �����" << endl;

	cout << ">> ";
	cin >> typeMatrix;	
	ClearCin();
	if (typeMatrix=='5') //�����
	{
		return;
	}
	else if (typeMatrix - '0' > 0 && typeMatrix - '0' < 5) //� �������� ���������� �����
	{
		const int sizeMatrix = 3;

		//const int *sizeptr = &sizeMatrix;
		//int * pi = const_cast<int*>(&sizeMatrix);	//������ const � ����������, �� ������� ��������� pi
		//*pi) = sizeM;
		cout << "�� ��������� ������� ������ 3*3! "<<endl;
		switch (typeMatrix)
		{
		case '1': //������� �������������
		{
			
			Matrix<int, sizeMatrix> MInt1, MInt2;
			cin >> MInt1;
			cin >> MInt2;
			subMatrixMenu(MInt1, MInt2);
			break;
		}
		case '2': //������� �� ����� � ��������� ������
		{
			
			Matrix<double, sizeMatrix> MFloat1, MFloat2;
			cin >> MFloat1;
			cin >> MFloat2;
			subMatrixMenu(MFloat1, MFloat2);
			break;
		}
		case '3': //������� �� ������
		{
			
			Matrix<Frac<int>, sizeMatrix> MFracInt1, MFracInt2;
			cin >> MFracInt1;
			cin >> MFracInt2;
			subMatrixMenu(MFracInt1, MFracInt2);
			break;
		}
		case '4': //������� �� ������, ��������� �� ����� � ��������� ������
		{
		
			Matrix<Frac<float>, sizeMatrix> MFracFloat1, MFracFloat2;
			cin >> MFracFloat1;
			cin >> MFracFloat2;
			subMatrixMenu(MFracFloat1, MFracFloat2);
			break;
		}
		}
	}

	MatrixMenu(); //����� �������� �������

}