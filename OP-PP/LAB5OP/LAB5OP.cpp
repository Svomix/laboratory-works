#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>
/*
* Подключение библиотек для:
1) ввода/вывода в поток
2) использование типа данных string
3) использование файлового потока
4) использование функции для подсчета количество знаков " "
*/
using namespace std;

class PressureData
{
private:
	string date;
	double val1, val2, val3;

public:
	explicit PressureData(string date="1970", double val1=0, double val2=0, double val3=0) // конструктор по умолчанию
	{

		this->date = date;
		this->val1 = val1;
		this->val2 = val2;
		this->val3 = val3;
	}
	double GetVal1() const // геттер
	{
		return val1;
	}
	double GetVal2() const // геттер
	{
		return val2;
	}
	double GetVal3() const // геттер
	{
		return val3;
	}
	string GetDate() const // геттер
	{
		return date;
	}
	void SetVal1(double val1) // сеттер
	{
		this->val1 = val1;
	}
	void SetVal2(double val2) // сеттер
	{
		this->val2 = val2;
	}
	void SetVal3(double val3) // сеттер
	{
		this->val3 = val3;
	}
	void SetDate(string date) // сеттер
	{
		this->date = date;
	}

	double AveVal() // функция, выполняющая задачу согласно варианту
	{
		return (val1 + val2 + val3) / 3;
	}

	PressureData(const PressureData& other) // конструктор копирования
	{
		this->date = other.date;
		this->val1 = other.val1;
		this->val2 = other.val2;
		this->val3 = other.val3;
	}

	~PressureData() // деструктор
	{
	}
	// объявление дружественных операторов
	friend ostream& operator<<(ostream& os, const PressureData& data);
	friend ofstream& operator<<(ofstream& ofs, const PressureData& data);
	friend istream& operator>>(istream& is, PressureData& data);
	friend ifstream& operator>>(ifstream& ifs, PressureData& data);
};

bool fail; // объявление глобальной переменной-флага для проверки корректности введенных данных

ostream& operator<<(ostream& os, const PressureData& data) // перегрузка оператора << для вывода на консоль
{
	return os << data.date << " " << data.val1 << " " << data.val2 << " " << data.val3;
}

ofstream& operator<<(ofstream& ofs, const PressureData& data) // перегрузка оператора << для помещения в файл
{
	ofs << data.date << " " << data.val1 << " " << data.val2 << " " << data.val3;
	return ofs;
}

bool is_correct_date(const string& date) // проверка корректности даты
{
	if (date.length() != 5 || date[2] != '.' || !isdigit(date[0]) || !isdigit(date[1]) || !isdigit(date[3]) || !isdigit(date[4]))
		return true;
	int month = (date[3] - '0') * 10 + (date[4] - '0');
	int day = (date[0] - '0') * 10 + (date[1] - '0');
	if (month < 1 || month > 12) return true;
	switch (month)
	{
	case 1: case 3: case 5: case 7: case 8: case 10: case 12:
		if (day < 1 || day > 31) return true;
		break;
	case 4: case 6: case 9: case 11:
		if (day < 1 || day > 30) return true;
		break;
	case 2:
		if (day < 1 || day > 28) return true;
		break;
	}
	return false;
}

istream& operator>>(istream& is, PressureData& data) // перегрузка оператора >> для ввода с консоли
{
	string datat;
	double valt1, valt2, valt3;
	bool check = true; // ввод будет осуществляться пока не будут введены корректные данные и флаг поменяет значение
	while (check)
	{
		is >> datat >> valt1 >> valt2 >> valt3;
		if (!(is) || is.peek() != '\n' || valt1 < 0 || valt2 < 0 || valt3 < 0 || is_correct_date(datat)) // проверка на корректность ввода
		{
			is.clear();
			while (is.get() != '\n');
			cout << "You have not entered a valid values\n";
			cout << "Enter a valid value\n";
		}
		else
		{
			check = false;
		}
	}
	data.date = datat;
	data.val1 = valt1;
	data.val2 = valt2;
	data.val3 = valt3;
	return is;
}

bool is_convertible_to_double(const string& str) // проверка на возможность конвертации в double
{
	size_t pos;
	try
	{
		std::stod(str, &pos);
	}
	catch (invalid_argument&)
	{
		return false;
	}
	return str.size() == pos && stod(str) >= 0; // если функция смогла обработать всю строку и значение больше 0, то возвращается true 
}

ifstream& operator>>(ifstream& ifs, PressureData& data) // перегрузка оператора >> для ввода из файла
{
	string str, temp, datat;
	string p[4];
	fail = false;
	getline(ifs, temp);
	while (temp.empty())
	{
		getline(ifs, temp);
	}
	if (count(temp.begin(), temp.end(), ' ') != 3) // подсчет пробельных символов
	{
		fail = true; // изменение флага на ошибочный
		return ifs;
	}
	int l = 0;
	temp += " ";
	for (int i = 0; i < temp.size(); ++i) // создание массива значений
	{
		if (temp[i] != ' ')
		{
			str += temp[i];
		}
		else
		{
			p[l] = str;
			str = "";
			++l;
		}
	}
	datat = p[0];
	if (!is_correct_date(datat) && is_convertible_to_double(p[1]) && is_convertible_to_double(p[2]) && is_convertible_to_double(p[3])) // проверка на правильность входных данных
	{
		// присваивание значений полям класса
		data.val1 = stod(p[1]);
		data.val2 = stod(p[2]);
		data.val3 = stod(p[3]);
		data.date = datat;
	}
	else
	{
		fail = true; // изменение флага на ошибочный
		return ifs;
	}
	return ifs;
}


void verification_for_retr(string& retr) // проверка слов 'Yes' и 'No' для возможности перезапуска программы
{
	cin >> retr;
	while (retr != "Yes" && retr != "No")
	{
		cout << "You have not entered 'Yes' or 'No'\n";
		cout << "Enter 'Yes' or No'\n";
		cin >> retr;
	}
}

int verification_for_size() // проверка валидности размера массива взятого из консоли
{
	int n;
	while (!(cin >> n) || cin.peek() != '\n' || n < 2)
	{
		cin.clear();
		while (cin.get() != '\n');
		cout << "You have not entered a valid value\n";
		cout << "Enter an integer, positive value greater than 2\n";
	}
	return n;
}

int verification_for_size(const string& s) // проверка валидности размера массива взятого из файла
{
	if (s.empty())
		return 0;
	for (int i = 0; i < s.size(); ++i)
	{
		if (!isdigit(s[i]))
		{
			return 0;
		}
	}
	return stoi(s);
}

string verification_for_put() // проверка на правильность ввода C и F для определения способа ввода/вывода
{
	string c;
	while (!(cin >> c) || c != "C" && c != "F")
	{
		cin.clear();
		while (cin.get() != '\n');
		cout << "You have not enered C or F\n";
		cout << "Print C or F\n";
	}
	return c;
}

void print_results_console(vector< PressureData>& base) // вывод результата на консоль
{
	cout << "Data about mesurements\n";
	for (int i = 0; i < base.size(); ++i)
	{
		cout << base[i] << endl;
	}
	cout << "The arithmetic means of the mesurements\n";
	for (int i = 0; i < base.size(); ++i)
	{
		cout << base[i].GetDate() << ": " << base[i].AveVal() << endl;
	}
}

void print_results_file(vector< PressureData>& base, ofstream& O) // вывод результата в файл
{
	O << "Data about mesurements:" << endl;
	for (int i = 0; i < base.size(); ++i)
	{
		O << base[i] << endl;
	}
	O << "The arithmetic means of the mesurements:" << endl;
	for (int i = 0; i < base.size(); ++i)
	{
		O << base[i].GetDate() << ": " << base[i].AveVal() << endl;
	}
}

int main()
{
	cout << "The program prints averange tire pressure value\n";
	string retr = "Yes";
	while (retr == "Yes")
	{
		cout << "The first string in the file must contain a size of an array\n" << "Size must be an integer, positive value greater than 1\n";
		cout << "The other strings must contain dates about mesurements\n";
		cout << "The first value must be measurement date(dd.mm)\n";
		cout << "The first, second, third and fourth value must be the results of a measurement divided by space\n";
		cout << "Do you want to input into the console or the file?\n";
		cout << "Print F if you want to input into the file and C if you want to input into the console\n";
		string type_of_put;
		int size;
		type_of_put = verification_for_put(); // запрос на ввод способа входных данных
		if (type_of_put == "C")
		{
			cout << "Enter a size of an array\n";
			cout << "Size must be an integer, positive value greater than 1\n";
			vector< PressureData> base{};
			cout << "Enter tire pressure data\n";
			cout << "The first value must be measurement date(dd.mm)\n";
			cout << "The first, second, third and fourth value must be the results of a measurement divided by space\n";
			size = verification_for_size();
			PressureData temp;
			for (int i = 0; i < size; ++i)
			{
				cout << "The " << i + 1 << " element is \n";
				cin >> temp;
				base.push_back(temp);
			}
			cout << "Do you want to output in file or in console\n";
			cout << "Print F if you want to output into the file and C if you want to output into the console\n";
			type_of_put = verification_for_put();
			if (type_of_put == "C")
			{
				print_results_console(base);
			}
			else
			{
				ofstream O("output.txt", ios::app); // открытие файла
				print_results_file(base, O); // вывод данных в файл
				O.close(); // закрытие файла
			};
		}
		else
		{
			cout << "Do you want to output in file or in console\n";
			cout << "Print F if you want to output into the file and C if you want to output into the console\n";
			type_of_put = verification_for_put(); // запрос на выбор способа вывода данных
			ifstream Fin("input.txt");
			{
				PressureData temp;
				vector<PressureData> base{};
				int i = 0;
				while (!Fin.eof())
				{
					Fin >> temp;
					++i;
					if (fail)
					{
						cout << "Element " << i << " has not a valid value.It can't be appended to the other data" << endl;
					}
					else
					{
						base.push_back(temp);
					}
				}
				if (type_of_put == "F")
				{
					ofstream O("output.txt", ios::app); // открыте файла
					print_results_file(base, O); // вывод данных в файл
					O.close(); // закрытие файла
				}
				else
				{
					print_results_console(base); // вывод результат в консоль
				}
			}
		}
		cout << "Do you want to restart the program\n";
		cout << "Print 'Yes' or 'No'\n";
		verification_for_retr(retr); // запрос на перезапуск программы
	}
	cout << "The program is over\n";
}