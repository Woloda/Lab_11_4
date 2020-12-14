#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <Windows.h>

using namespace std;

enum measurement { МГ, Г, ЦН, КГ, ТТ };

string t_measurement[] = { "Мг ",
						   "Гр",
						   "Цн",
						   "Кг",
						   "Тн" };

struct towar
{
	string n_towar;
	int vartіst;
	int kilkist;
	measurement units;
	int masa;
};

void Create(towar& s, const int kilkist, ofstream& file_s, int i);
void Print(towar& s, const int kilkist, ifstream& file_l, int i);

void vulychenya(towar& s, int& kil_towar, int pozution, ifstream& file_l, ofstream& file_s);
void Coppy(towar& s, const int kil_towar, ofstream& file_s, ifstream& file_l);
void dobavut(towar& s, const int kilkist, const char* fname, const char* gname, const char* lname, const int pos);

void SortBIN(towar& str, towar& str_a, towar& str_b, const int kilkist, const char* fname, fstream& f, bool b);
int BinSearch(towar& s, const int kilkist, const string nazva_t, const char* fname, ifstream& file_l);

void BinSearch_vartist(towar& s, const int kil_towar, const int vartisr1, const int vartisr2, int& l1, int& l2, const char* fname, ifstream& file_l);

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int kil_towar;
	cout << "Введіть початкову кількість товарів: "; cin >> kil_towar;
	cout << endl;
	int kil = kil_towar;

	towar s;
	towar str;
	towar str_a;
	towar str_b;

	char fname[101];
	cout << "Введіть назву фізичного файлу: "; cin >> fname; cout << endl;

	char gname[101];
	cout << "Введіть назву фізичного файлу для деяких операцій: "; cin >> gname; cout << endl;

	char lname[101];
	cout << "Введіть назву фізичного файлу для деяких операцій: "; cin >> lname; cout << endl;

	ifstream file_l;
	ofstream file_s;
	fstream f;

	int i, g, pos, zmina, found, index;
	int l1 = 0, l2 = 0;
	int vartisr1, vartisr2;
	string nazwa_towar;
	char filename[100];

	int menutowar;
	do {
		cout << "Виберіть дію:" << endl << endl;

		cout << " [1] - створення списку товарів" << endl;
		cout << " [2] - вивід інформації про товар" << endl;

		cout << " [3] - добавлення товару" << endl;
		cout << " [4] - вулучення товару" << endl;
		cout << " [5] - редагування інформації про товар" << endl;
		cout << " [6] - сортування товару" << endl;
		cout << " [7] - пошук товару за назвою і вивід інформації про товар" << endl;
		cout << " [8] - вивід інформації про товари із заданого діапазону вартості" << endl;
		cout << " [9] - запис даних у файл" << endl;
		cout << " [10] - зчитування даних із файлу" << endl << endl;

		cout << " [0] - вихід та завершення роботи програми" << endl << endl;

		cout << "Введіть пункт меню: "; cin >> menutowar;
		switch (menutowar)
		{
		case 1:
			kil_towar = kil;
			file_s.open(fname, ios::binary);
			Create(s, kil_towar, file_s, 0);
			cout << endl;
			file_s.close();
			break;
		case 2:
			file_l.open(fname, ios::binary);
			Print(s, kil_towar, file_l, 0);
			file_l.close();
			break;
		case 3:
			cout << endl;
			cout << "Введіть певну кількість товарів які ви хочете добавити до списку: "; cin >> g;
			cout << endl;
			kil_towar += g;
			i = kil_towar - g;
			file_s.open(fname, ios::binary | ios::app);
			Create(s, kil_towar, file_s, i);
			file_s.close();
			break;
		case 4:
			cout << endl;
			cout << "Введіть певну позицію товару для вилучення його зі списку: "; cin >> pos;
			cout << endl;

			file_s.open(gname, ios::binary);
			file_l.open(fname, ios::binary);
			Coppy(s, kil_towar, file_s, file_l);
			file_s.close();
			file_l.close();

			file_s.open(fname, ios::binary);
			file_l.open(gname, ios::binary);
			vulychenya(s, kil_towar, pos, file_l, file_s);
			file_s.close();
			file_l.close();

			break;
		case 5:
			cout << endl;
			cout << "Введіть певну позицію товару для редагування його інформації в списку: "; cin >> pos;
			cout << endl;
			dobavut(s, kil_towar, fname, gname, lname, pos);
			break;
		case 6:
			cout << endl;
			cout << "Сортування по назві товару(спосіб 1) або за загальною вартістю(спосіб 0): " << endl;
			cout << "Виберіть певний спосіб(1 або 0): ";cin >> zmina;
			cout << endl;
			SortBIN(str, str_a, str_b, kil_towar, fname, f, zmina);
			break;
		case 7:
			cout << endl;
			cin.get();
			cin.sync();
			cout << "Введіть назву товару: ";getline(cin, nazwa_towar);
			cout << endl;

			if ((found = BinSearch(s, kil_towar, nazwa_towar, fname, file_l)) != -1)
			{
				cout << "Знайдено студента в списку під номером " << found + 1 << endl << endl;

				file_l.open(fname, ios::binary);
				file_l.seekg(found * sizeof(towar), ios::beg);
				Print(s, found + 1, file_l, found);
				file_l.close();
			}
			else
				cout << "Шуканого студента в списку не знайдено" << endl << endl;
			break;
		case 8:
			cout << "Діапазон вартості: " << endl << endl;
			cout << "Введіть мінімальну вартість: ";
			cin >> vartisr1;
			cout << "Введіть максимальну вартість: ";
			cin >> vartisr2;
			l1 = -1;
			l2 = -2;
			BinSearch_vartist(s, kil_towar, vartisr1, vartisr2, l1, l2, fname, file_l);
			file_l.open(fname, ios::binary);
			file_l.seekg(l1 * sizeof(towar), ios::beg);
			Print(s, l2 + 1, file_l, l1);
			file_l.close();
			break;
		case 0:
			cout << endl;
			cout << "завершення роботи програми" << endl << endl;
			break;
		default:
			cout << "Ви ввели помилкове значення! "
				"Слід ввести число - номер вибраного пункту меню" << endl;
			cout << endl;
		}
	} while (menutowar != 0);
	exit(0);
}

void Create(towar& s, const int kilkist, ofstream& file_s, int i)
{
	int towar_l;
	for (; i < kilkist; i++)
	{
		cout << endl;
		cout << "товар № " << i + 1 << endl;

		cin.get();
		cin.sync();

		cout << "  назва: "; getline(cin, s.n_towar);
		cout << "  вартість(в грн.): "; cin >> s.vartіst;
		cout << "  кількість: "; cin >> s.kilkist;
		cout << "  одиниці вимірювання(0 - Міліграм, 1 - Грам, 2 - Центнер, 3 - Кілограм, 4 - Тонна): "; cin >> towar_l;
		s.units = (measurement)towar_l;
		cout << "  упаковка по: "; cin >> s.masa; cout << "  " << t_measurement[towar_l] << endl;

		if (!file_s.write((char*)&s, sizeof(towar)))
		{
			cerr << "Error writing file." << endl;
		}
	}
}

void Print(towar& s, const int kilkist, ifstream& file_l, int i)
{
	cout << "====================================================================="
		<< endl;
	cout << "| №  | Назва        | Вартість(в грн.) | Кількість | упаковка по    |"
		<< endl;
	cout << "---------------------------------------------------------------------" << endl;

	for (; i < kilkist; i++)
	{
		file_l.read((char*)&s, sizeof(towar));
		cout << "| " << setw(2) << right << i + 1 << " "
			<< "| " << setw(13) << left << s.n_towar
			<< "| " << setw(16) << left << s.vartіst << " "
			<< "| " << setw(5) << left << s.kilkist << "     "
			<< "| " << setw(2) << left << s.masa << setw(1) << left << " " << setw(11) << left << t_measurement[s.units] << " |" << endl;
	}
	cout << "=====================================================================" << endl;
}

void vulychenya(towar& s, int& kil_towar, int pozution, ifstream& file_l, ofstream& file_s)
{
	for (int i = 0; i < kil_towar; i++)
	{
		file_l.read((char*)&s, sizeof(towar));
		if (i + 1 != pozution)
			file_s.write((char*)&s, sizeof(towar));
		else
			kil_towar--;
	}
}

void Coppy(towar& s, const int kil_towar, ofstream& file_s, ifstream& file_l)
{
	for (int i = 0; i < kil_towar; i++)
	{
		file_l.read((char*)&s, sizeof(towar));
		file_s.write((char*)&s, sizeof(towar));
	}
}

void dobavut(towar& s, const int kilkist, const char* fname, const char* gname, const char* lname, const int pos)
{
	fstream file_l_s;
	fstream file;
	fstream file_l;

	file.open(fname, ios::binary | ios::in);
	file_l.open(lname, ios::binary | ios::out);
	for (int i = 0; i < kilkist; i++)
	{
		file.read((char*)&s, sizeof(towar));
		file_l.write((char*)&s, sizeof(towar));
	}
	file.close();
	file_l.close();

	int towar_l;
	cout << endl;
	cout << "товар № " << pos << endl;

	cin.get();
	cin.sync();

	cout << "  назва: "; getline(cin, s.n_towar);
	cout << "  вартість(в грн.): "; cin >> s.vartіst;
	cout << "  кількість: "; cin >> s.kilkist;
	cout << "  одиниці вимірювання(0 - Міліграм, 1 - Грам, 2 - Центнер, 3 - Кілограм, 4 - Тонна): "; cin >> towar_l;
	s.units = (measurement)towar_l;
	cout << "  упаковка по: "; cin >> s.masa; cout << "  " << t_measurement[towar_l] << endl;

	file_l_s.open(gname, ios::binary | ios::out);
	if (!file_l_s.write((char*)&s, sizeof(towar)))
	{
		cerr << "Error writing file." << endl;
	}
	file_l_s.close();

	file_l.open(lname, ios::binary | ios::in);
	file.open(fname, ios::binary | ios::out);
	file_l_s.open(gname, ios::binary | ios::out | ios::in);
	for (int i = 0; i < kilkist; i++)
	{
		if (i != pos - 1)
			file_l.read((char*)&s, sizeof(towar));
		else
			file_l_s.read((char*)&s, sizeof(towar));

		file.write((char*)&s, sizeof(towar));
	}
	file.close();
	file_l.close();
	file_l_s.close();

}

void SortBIN(towar& str, towar& str_a, towar& str_b, const int kilkist, const char* fname, fstream& f, bool b)
{
	for (int i0 = 1; i0 < kilkist; i0++)
	{
		for (int i1 = 0; i1 < kilkist - i0; i1++)
		{
			f.open(fname, ios::binary | ios::in | ios::out);
			int l, m;
			l = i1;
			m = i1 + 2;
			while (l < m)
			{
				f.seekg(l * sizeof(towar), ios::beg);
				f.read((char*)&str, sizeof(towar));
				if (l == m - 2)
					str_a = str;
				else
					str_b = str;
				l++;
			}

			if (b)
			{
				if (str_a.n_towar > str_b.n_towar)
				{
					l = i1;
					while (l < m)
					{
						if (l == m - 2)
							str = str_b;
						else
							str = str_a;
						f.seekp(l * sizeof(towar), ios::beg);
						f.write((char*)&str, sizeof(towar));
						l++;
					}
				}
			}
			else
			{
				if (str_a.vartіst > str_b.vartіst)
				{
					l = i1;
					while (l < m)
					{
						if (l == m - 2)
							str = str_b;
						else
							str = str_a;
						f.seekp(l * sizeof(towar), ios::beg);
						f.write((char*)&str, sizeof(towar));
						l++;
					}
				}
			}
			f.close();
		}
	}
}

int BinSearch(towar& s, const int kilkist, const string nazva_t, const char* fname, ifstream& file_l)
{
	int L = 0, R = kilkist - 1, m;
	do {
		m = (L + R) / 2;
		file_l.open(fname, ios::binary);
		file_l.seekg(m * sizeof(towar), ios::beg);
		file_l.read((char*)&s, sizeof(towar));
		file_l.close();
		if (s.n_towar == nazva_t)
			return m;
		if (s.n_towar > nazva_t)
		{
			R = m - 1;
		}
		else
		{
			L = m + 1;
		}
	} while (L <= R);
}

void BinSearch_vartist(towar& s, const int kil_towar, const int vartisr1, const int vartisr2, int& l1, int& l2, const char* fname, ifstream& file_l)
{
	int g = 0;
	file_l.open(fname, ios::binary);
	for (int i = 0; i < kil_towar; i++)
	{
		file_l.read((char*)&s, sizeof(towar));
		if (s.vartіst >= vartisr1 && s.vartіst <= vartisr2)
		{
			l2 = i;
			g++;
		}
		if (g == 1)
			l1 = l2;
	}
	file_l.close();
}