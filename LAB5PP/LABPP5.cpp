#include <iostream>
#include <regex>
#include <string>
#include <vector>
#include <fstream>
#include <Windows.h>

using namespace std;


class PressureData
{
private:
	string date;
	double val1, val2, val3, val4;

public:
	explicit PressureData(string date = "1970", double val1 = 0, double val2 = 0, double val3 = 0, double val4 = 0)
	{

		this->date = date;
		this->val1 = val1;
		this->val2 = val2;
		this->val3 = val3;
		this->val4 = val4;
	}
	double GetVal1() const
	{
		return val1;
	}
	double GetVal2() const
	{
		return val2;
	}
	double GetVal3() const
	{
		return val3;
	}
	double GetVal4() const
	{
		return val4;
	}
	string GetDate() const
	{
		return date;
	}
	void SetVal1(double val1)
	{
		this->val1 = val1;
	}
	void SetVal2(double val2)
	{
		this->val2 = val2;
	}
	void SetVal3(double val3)
	{
		this->val3 = val3;
	}
	void SetVal4(double val4)
	{
		this->val4 = val4;
	}
	void SetDate(string date)
	{
		this->date = date;
	}

	double AveVal() // функция, выполняющая задачу согласно варианту
	{
		return (val1 + val2 + val3 + val4) / 4;
	}

	PressureData(const PressureData& other) // конструктор копирования
	{
		this->date = other.date;
		this->val1 = other.val1;
		this->val2 = other.val2;
		this->val3 = other.val3;
		this->val4 = other.val4;
	}

	~PressureData() // деструктор
	{
	}
	friend ostream& operator<<(ostream& os, const PressureData& data);
	friend ofstream& operator<<(ofstream& ofs, const PressureData& data);
	friend istream& operator>>(istream& is, PressureData& data);
	friend ifstream& operator>>(ifstream& ifs, PressureData& data);
};

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

bool is_correct_name(const string& name)
{
	for (const int& c : name)
	{
		if (!isalpha(c))
		{
			return false;
		}
	}
	if (name.empty())
		return false;
	return true;
}

bool fail;
int k = 0;

ostream& operator<<(ostream& os, const PressureData& data)
{
	return os << data.date << " " << data.val1 << " " << data.val2 << " " << data.val3 << " " << data.val4;
}

ofstream& operator<<(ofstream& ofs, const PressureData& data)
{
	ofs << data.date << " " << data.val1 << " " << data.val2 << " " << data.val3 << " " << data.val4;
	return ofs;
}

ifstream& operator>>(ifstream& ifs, PressureData& data)
{
	string pressuredata;
	getline(ifs, pressuredata);
	fail = false;
	regex mask("^(([12][0-9]|3[01]|0[1-9])\\.(0[1-9]|1[012]))\\s(\\d+|\\d+\\.\\d+)\\s(\\d+|\\d+\\.\\d+)\\s(\\d+|\\d+\\.\\d+)\\s(\\d+|\\d+\\.\\d+)");
	smatch match;
	if (regex_match(pressuredata, match, mask) && !is_correct_date(match[1]))
	{
		data.date = match[1];
		data.val1 = stod(match[4]);
		data.val2 = stod(match[5]);
		data.val3 = stod(match[6]);
		data.val4 = stod(match[7]);
	}
	else
	{
		fail = true;
		return ifs;
	}
	return ifs;
}

istream& operator>>(istream& is, PressureData& data) // перегрузка оператора >> для ввода с консоли
{
	string datat;
	double valt1, valt2, valt3, valt4;
	bool check = true;
	while (check)
	{
		is >> datat >> valt1 >> valt2 >> valt3 >> valt4;
		if (!(is) || is.peek() != '\n' || valt1 < 0 || valt2 < 0 || valt3 < 0 || valt4 < 0 || is_correct_date(datat))
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
	data.val4 = valt4;
	return is;
}

class CarData
{
private:
	string name;
	string number;
	PressureData pwheel;
public:
	explicit CarData(string name = "No data", string number = "No data", PressureData pwheel = PressureData())
	{
		this->name = name;
		this->number = number;
		this->pwheel = pwheel; // перегрузить опреатор =
	}
	string GetName() const
	{
		return name;
	}
	string Getnumber() const
	{
		return number;
	}
	PressureData GetPwheel() const
	{
		return pwheel;
	}
	string GetDate() const
	{
		return pwheel.GetDate();
	}
	void SetName(const string& name)
	{
		this->name = name;
	}
	void Setnumber(const string& number)
	{
		this->number = number;
	}
	void SetPwheel(const PressureData& pweel)
	{
		this->pwheel = pweel;
	}
	CarData(const CarData& other)
	{
		this->name = other.name;
		this->number = other.number;
		this->pwheel = other.pwheel;
	}

	double AveVal() // функция, выполняющая задачу согласно варианту
	{
		return pwheel.AveVal();
	}

	~CarData()
	{
	}
	friend ostream& operator<<(ostream& os, const CarData& data);
	friend ofstream& operator<<(ofstream& ofs, const CarData& data);
	friend istream& operator>>(istream& is, CarData& data);
	friend ifstream& operator>>(ifstream& ifs, CarData& data);
};

ostream& operator<<(ostream& os, const CarData& data)
{
	return os << data.name << endl << data.number << endl << data.pwheel;
}

ofstream& operator<<(ofstream& ofs, const CarData& data)
{
	ofs << data.name << endl << data.number << endl << data.pwheel;
	return ofs;
}

istream& operator>>(istream& is, CarData& data)
{
	string name, number, region;
	PressureData pwheel;
	regex mask_number("^([ABEKMHOPCTYX]\\d\\d\\d[ABEKMHOPCTYX][ABEKMHOPCTYX])");
	regex mask_region(("(\\d\\d\\dpyc)$"));
	smatch match;
	is >> name;
	while (!is_correct_name(name))
	{
		while (cin.get() != '\n');
		cout << "You have entred not a valid name\n";
		cout << "Please enter a correct name\n";
		is >> name;
	}
	is >> number >> region;
	while (!regex_match(number, match, mask_number) || !regex_match(region, match, mask_region))
	{
		while (cin.get() != '\n');
		cout << "You have enter not a valid car number\n";
		cout << "Please enter a correct car number\n";
		is >> number >> region;
	}
	is >> pwheel;
	data.name = name;
	data.number = number + " " + region;
	data.pwheel = pwheel;
	return is;
}

int i = 0;

ifstream& operator>>(ifstream& ifs, CarData& data)
{
	fail = false;
	string name, number;
	PressureData pwheel;
	getline(ifs, name);
	++k;
	regex mask_number("^([ABEKMHOPCTYX]\\d\\d\\d[ABEKMHOPCTYX][ABEKMHOPCTYX]\\s\\d\\d\\dpyc)$");
	smatch match;
	if (is_correct_name(name))
	{
		getline(ifs, number);
		++k;
		if (regex_match(number, match, mask_number))
		{
			ifs >> pwheel;
			++k;
		}
		else
		{
			getline(ifs, name);
			++k;
			while (!ifs.eof() && !(is_correct_name(name)))
			{
				i = ifs.tellg();
				if (i == -1)
				{
					fail = true;
					return ifs;
				}
				getline(ifs, name);
				++k;
			}
			ifs.seekg(i, std::ios_base::beg);
			fail = true;
			return ifs;
		}
	}
	else
	{
		while (!ifs.eof() && !(is_correct_name(name)))
		{
			i = ifs.tellg();
			if (i == -1)
			{
				fail = true;
				return ifs;
			}
			getline(ifs, name);
			++k;
		}
		ifs.seekg(i, std::ios_base::beg);
		fail = true;
		return ifs;
	}

	data.name = name;
	data.number = number;
	data.pwheel = pwheel;
	return ifs;
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

void print_results_console(vector<CarData>& base)
{
	cout << "Data about Car\n";
	for (size_t i = 0; i < base.size(); i++)
	{
		cout << base[i] << endl;
	}
	cout << "The arithmetic means of the mesurements\n";
	for (size_t i = 0; i < base.size(); i++)
	{
		cout << base[i].GetDate() << " " << base[i].GetName() << ": " << base[i].AveVal() << endl;
	}
}

void print_results_file(vector<CarData>& base, ofstream& Out)
{
	Out << "Data about mesurements:" << endl;
	for (size_t i = 0; i < base.size(); i++)
	{
		Out << base[i] << endl;
	}
	Out << "The arithmetic means of the mesurements:" << endl;
	for (size_t i = 0; i < base.size(); i++)
	{
		Out << base[i].GetDate() << " " << base[i].GetName() << ": " << base[i].AveVal() << endl;
	}
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

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	string retr = "Yes";
	while (retr == "Yes")
	{
		cout << "The program prints averange tire pressure value\n";
		cout << "The data about car contains 3 strings: name, car number, data about wheel pressure\n";
		cout << "All strings must be separated string\n";
		cout << "The first string is a name of a car and it must contain ONLY letters\n";
		cout << "The second string is a car number and it must contain car number and a region of car separated by space\n";
		cout << "The third string must contain data about wheel pressure: date of a mesurement, 4 mesurements separated by space\n";
		cout << "Do you want to input into the console or the file?\n";
		cout << "Print F if you want to input into the file and C if you want to input into the console\n";
		string type_of_put;
		int size;
		vector<CarData> base{};
		CarData temp;
		type_of_put = verification_for_put();
		if (type_of_put == "C")
		{
			cout << "Enter a size of an array\n";
			cout << "Size must be an integer, positive value greater than 1\n";
			size = verification_for_size();
			cout << "The first string is a name\n";
			cout << "The second string is a car number\n";
			cout << "The third string is a pressure data: first value is a date(dd.mm), 4 values separated by space\n";
			for (int i = 0; i < size; i++)
			{
				cout << "The " << i + 1 << " element is \n";
				cin >> temp;
				base.push_back(temp);
			}
		}
		else
		{
			ifstream Finput("input.txt");
			string p;
			int max = 0;
			while (!Finput.eof() && i != -1)
			{
				Finput >> temp;
				if (fail)
				{
					/*cout << "Element " << k << " has not a valid value.It can't be appended to the other data" << endl;*/
				}
				else
				{
					base.push_back(temp);
				}
			}
			i = 0;
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
			ofstream Out("output.txt", ios::app);
			print_results_file(base, Out);
			Out.close();
		}
		cout << "Do you want to restart the program\n";
		cout << "Print 'Yes' or 'No'\n";
		verification_for_retr(retr);
	}
	cout << "The program is over\n";
}