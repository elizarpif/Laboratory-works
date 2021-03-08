#include <iostream>
#include <string>

#define ULL unsigned long long int

using namespace std;


struct phoneBook
{
	string name, last_name, phone, email, company, dolsh;
	friend ostream& operator<< (ostream &os, const phoneBook &rec);
	friend istream& operator>> (istream &is, phoneBook &rec);
	bool operator==(phoneBook b)
	{
		if (this->name == b.name && last_name == b.last_name &&email == b.email&&phone == b.phone&&
			company == b.company && dolsh == b.dolsh)
			return true;
		else
			return false;
	}

};

ostream & operator<<(ostream & os, const phoneBook & rec)
{
	os << " " << rec.name;
	os << " " << rec.last_name;
	os << " " << rec.phone;
	os << " " << rec.email;
	os << " " << rec.company;
	os << " " << rec.dolsh;
	return os;
}

istream& operator>> (istream &is, phoneBook &rec)
{
	cout << "Введите имя, фамилию, телефон, email, компанию, должность: ";
	is >> rec.name >> rec.last_name >> rec.phone >> rec.email>>rec.company>>rec.dolsh;
	return is;
}






ULL Hash(string str) //хеш-функция для телефонной книги
{
	ULL sum = 0;
	for (int i = 0; i < str.length(); i++)
	{
		sum += str[i] * pow(8, str.length() - i - 1);
	}

	return sum;
}



ULL Hash(phoneBook str) //хеш-функция для строк
{
	ULL sum = 0;
	for (int i = 0; i < str.email.length(); i++)
	{
		sum += str.email[i] * pow(8, str.email.length() - i - 1);
	}
	return sum;
}