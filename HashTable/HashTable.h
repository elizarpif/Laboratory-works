#pragma once
#include "PhoneBook.h"
#include <list>
#include <iterator>
#include <algorithm>
#include <fstream>
#include <vector>
#define TEMPL template <typename Tvalue>



TEMPL
class HashTable
{
	int history, maxHistory;
	vector<int> masHist;
	string fileName;

	vector<pair<ULL,Tvalue>> lastStep;
	vector<pair<ULL, list<Tvalue>>> hash_table;
public:
	void initFileName()
	{
		fileName = "hash.data";
	}
	string getFileName()
	{
		return fileName;
	}
	HashTable()
	{
		history = 0;
		maxHistory = 10;
		initFileName();
	}

	void SaveFile()
	{
		ofstream F(fileName);
		for (int i = 0; i < hash_table.size(); i++) {

			for (auto it = hash_table[i].second.begin(); it != hash_table[i].second.end(); it++) {

				F << (*it);
				F << endl;
			}
		}
		F.close();
	}
	
	void Insert(ULL key, Tvalue &value);
	void Change(ULL key);
	TEMPL
		friend void openFile(HashTable<Tvalue> &h);
	TEMPL
	friend void UndoHist(HashTable<Tvalue> &hashT, int h);

	~HashTable()
	{
		hash_table.clear();
		hash_table.shrink_to_fit();
	}

	void setHist(int n)
	{
		maxHistory = n;
		masHist.resize(maxHistory);
	}
	TEMPL
	friend ostream& operator<< (ostream &os, const HashTable<Tvalue> &rec);
	TEMPL
	friend void SearchArg(HashTable<Tvalue> hashT, string str);

	friend void SearchArg(HashTable<phoneBook> hashT, string str, int arg);
};

void OpenFile(HashTable<phoneBook> &h)//открытие файла, спецификация под структур
{
	ifstream F(h.getFileName(), ios::in);

	phoneBook rec;
	int kol_num;
	while (!F.eof()) {
		F >> rec.name >> rec.last_name >> rec.phone >> rec.email >> rec.company >> rec.dolsh;
		if (F.eof())
			break;
		h.Insert(Hash(rec), rec);
	}
	F.close();
}

TEMPL
void OpenFile(HashTable<Tvalue> &h) //открытие файла
{
	ifstream F(h.getFileName(), ios::in);

	Tvalue rec;
	int kol_num;
	while (!F.eof()) {
		F >> rec;
		if (F.eof())
			break;
		h.Insert(Hash(rec), rec);
	}
	F.close();
}



TEMPL
ostream & operator<<(ostream & os, const HashTable<Tvalue>& rec) //вывод таблицы
{
	for (auto it = rec.hash_table.begin(); it != rec.hash_table.end(); ++it)
	{
		pair<ULL, list<Tvalue>> p = (*it);
		list<Tvalue> l = p.second;

		for (auto it1 = l.begin(); it1 != l.end(); ++it1)
		{
			os << (*it1) << endl;
		}
	}
	return os;
}

//для структуры
void SearchArg(HashTable<phoneBook> hashT, string str, int arg)
{
	auto ptr = hashT.hash_table.begin();
	for (ptr; ptr != hashT.hash_table.end(); ptr++)
	{
		list<phoneBook> l = (*ptr).second;
		for (auto it = l.begin(); it != l.end(); it++)
		{
			int found;
			switch (arg)
			{
			case 1:
				found = ((*it).name).find(str);
				break;
			case 2:
				found = ((*it).last_name).find(str);
				break;
			case 3:
				found = ((*it).phone).find(str);
				break;
			case 4:
				found = ((*it).email).find(str);
				break;
			case 5:
				found = ((*it).company).find(str);
				break;
			case 6:
				found = ((*it).dolsh).find(str);
				break;
			}
			if (found != -1)
			{
				cout << "Запись найдена" << endl;
				cout << (*it) << endl;
			}
					
		}
		
	}
}

TEMPL
void SearchArg(HashTable<Tvalue> hashT, string str) //стандартный поиск
{
	auto ptr = hashT.hash_table.begin();
	for (ptr; ptr != hashT.hash_table.end(); ptr++)
	{
		list<Tvalue> l = (*ptr).second;
		for (auto it = l.begin(); it != l.end(); it++)
		{
			int found;
			
			found = (*it).find(str);
			
			if (found != -1)
			{
				cout << "Запись найдена" <<endl;
				cout << (*it) << endl;
			}

		}

	}
}




TEMPL
void HashTable<Tvalue>::Insert( ULL key, Tvalue &value) //вставка записи
{
	//для начала есть ли такой ключ?
	auto ptr = find_if(hash_table.begin(), hash_table.end(), 
		[&key](const pair<ULL, list<Tvalue>>&p)
	{
		return p.first == key;
	});

	if (ptr != hash_table.end())
	{
		pair<ULL, list<Tvalue>> p = (*ptr);
		list<Tvalue> l = p.second;
		for (auto it = l.begin(); it != l.end(); ++it)
		{
			if ((*it) == value)
			{
				return;
			}
		}
		l.push_back(value);
		history++;
		if (history == maxHistory)
		{
			history--;
			lastStep.erase(lastStep.begin());
			masHist.pop_back();
		}
		lastStep.push_back(make_pair(key, value));
		masHist.push_back( 1);
		p.second = l;
		(*ptr) = p;
		//l.sort();		
	}
	else //если ключ был не найден
	{
		list<Tvalue> l;
		l.push_back(value);
		hash_table.push_back(make_pair(key, l));
		history++;
		if (history == maxHistory+1)
		{
			history--;
			lastStep.erase(lastStep.begin());
			masHist.pop_back();
		}
		lastStep.push_back(make_pair(key, value));
		masHist.push_back(1);
		
	}
}

TEMPL
void HashTable<Tvalue>::Change(ULL key) //изменение записи
{
	auto ptr = hash_table.begin();
	for (ptr; ptr != hash_table.end(); ptr++)
	{
		if ((*ptr).first == key)
		{
			int i = 1;
			for (auto it = (*ptr).second.begin(); it != (*ptr).second.end(); ++it, i++)
			{
				cout << i << ") " << (*it)<<endl;
			}
			int num=i;		
			while (abs(num) > i)
			{
				cout <<endl<< "укажите номер записи, которую необходимо заменить: ";
				cin >> num;
				if (num == 0)
				{
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					num = i + 1;
				}
			}
			list<Tvalue> l = (*ptr).second;
			i = 1;
			for (auto ik =l.begin(); ik !=l.end(); ++ik, i++)
				if (num == i)
				{
					
					//history++;
					if (history == maxHistory+1)
					{
						history--;
						lastStep.erase(lastStep.begin());
						masHist.pop_back();
					}
					lastStep.push_back(make_pair(key, (*ik)));
					
					ik = l.erase(ik);
					
					break;
				}
			(*ptr).second = l;
			if ((*ptr).second.size() == 0)
			{
				auto tmp = ptr;
				tmp++;
				ptr = hash_table.erase(ptr);
				ptr = tmp;
			}
			Tvalue val;
			cout << "Введите новое значение: ";
			cin >> val;
			
			this->Insert(Hash(val), val);
			masHist.pop_back();
			masHist.push_back(2);
			break;
		}
	}

}

TEMPL
void UndoHist(HashTable<Tvalue> &hashT, int h)//h - кол-во последних записей
{

	if (h <= hashT.history) //нельзя дальше текущего
	{
		int temp;
		int i = 0;
		while (i < h)
		{
			i++;
			int cur = hashT.history - i;
			temp = hashT.masHist[cur];

			if (temp == 1)//вставка
			{
				for (auto ptr = hashT.hash_table.begin(); ptr != hashT.hash_table.end(); ++ptr)
				{
					if ((*ptr).first == hashT.lastStep[cur].first)//key==key
					{
						list<Tvalue> l = (*ptr).second;
						auto it = l.begin();
						while (it != l.end())
						{
							//нашли элемент!!!
							if ((*it) == hashT.lastStep[cur].second)
							{
								it = l.erase(it);
								(*ptr).second = l;
								if ((*ptr).second.size() == 0)
								{
									auto tmp = ptr;
									tmp++;
									ptr = hashT.hash_table.erase(ptr);
									ptr = tmp;
								}

								break;
							}
							it++;
						}
						break;
					}
				}

			}
			else if (temp == 2)//удаление, значит надо вставить
			{
				auto ptr = hashT.hash_table.begin();
				for (ptr; ptr != hashT.hash_table.end(); ++ptr)
				{
					if ((*ptr).first == hashT.lastStep[cur].first)//key==key
					{
						list<Tvalue> l = (*ptr).second;
						l.push_back(hashT.lastStep[cur].second);
						(*ptr).second = l;
						break;
					}
				}
				if (ptr == hashT.hash_table.end())
				{
					list<Tvalue> l;
					l.push_back(hashT.lastStep[cur].second);
					hashT.hash_table.push_back(make_pair(hashT.lastStep[cur].first, l));
				}
				//cur = cur - 1;
				for (auto ptr = hashT.hash_table.begin(); ptr != hashT.hash_table.end(); ++ptr)
				{
					if ((*ptr).first == hashT.lastStep[cur + 1].first)//key==key
					{
						list<Tvalue> l = (*ptr).second;
						auto it = l.begin();
						while (it != l.end())
						{
							//нашли элемент!!!
							if ((*it) == hashT.lastStep[cur + 1].second)
							{
								it = l.erase(it);
								(*ptr).second = l;
								if ((*ptr).second.size() == 0)
								{
									auto tmp = ptr;
									tmp++;
									ptr = hashT.hash_table.erase(ptr);
									ptr = tmp;
								}

								break;
							}
							it++;
						}
						break;
					}
				}

			}
		}
		hashT.lastStep.resize(hashT.history - h);
		hashT.masHist.resize(hashT.history - h);
		hashT.history -= h;
	}
}
