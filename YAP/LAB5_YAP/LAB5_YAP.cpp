#include <fstream>

class Date
{
private:
	short int day; // дни в дате
	short int month; // месяцы в дате
	long long int year; // года в дате
	short int get_days_feb(long long int) const; // метод для получения количества дней в феврале
	short int get_days_month(short int, long long int) const; // метод для получения количества дней в месяце
	short int get_days_year(long long int) const; // метод для получения количества дней в году
	short int days_passed_to_cur_month(short int, long long int) const; // метод для получения количества дней прошедших с начала года, считая только окончившиеся месяцы
	long long int get_days() const; // сколько дней прошло, считая с 01.01.0000
	void days_to_date(long long int); // перевод числа дней в дату
public:
	explicit Date(short int day = 1, short int month = 1, long long int year = 1970) :day(day), month(month), year(year) {}; // конструктор по умолчанию и конструктор инициализации
	Date(const Date& other) // конструктор копирования
	{
		day = other.day;
		month = other.month;
		year = other.year;
	}
	~Date() {} // деструктор
	short int get_day_number() const; // метод для вычисления номера дня в году
	void to_another_format(std::ofstream&) const; // метод для перевода дату в другой формат
	friend std::ofstream& operator<<(std::ofstream&, const Date&); // операция вывода в поток
	friend std::ifstream& operator>>(std::ifstream&, Date&); // операция ввода из потока
	Date& operator=(const Date&); // операция присваивния
	bool operator<(const Date&); // операция меньше
	bool operator>=(const Date&); // операция больше или равно
	bool operator>(const Date&); // операция больше
	bool operator==(const Date&); // операция проверки на равенство
	bool operator<=(const Date&); // операция меньше или равно
	Date operator+(const long long int); // операция сложения
	Date operator-(const long long int); // операция вычитания
};

std::ofstream& operator<<(std::ofstream& outf, const Date& date)
{
	outf << date.day << '.' << date.month << '.' << date.year; // стандартный формат вывода: день.месяц.год
	return outf;
}

short int Date::get_day_number() const
{
	return day + days_passed_to_cur_month(month, year);
}

void Date::to_another_format(std::ofstream& outf) const
{
	outf << *this << std::endl;
	outf << year << '-' << month << '-' << day << std::endl; // разделителем становится '-' вместо .
	outf << month << '/' << day << '/' << year;// американский формат с разделителем '/'
}

std::ifstream& operator>>(std::ifstream& inpf, Date& date)
{
	inpf >> date.day;
	inpf.get(); // пропускаем разделитель
	inpf >> date.month;
	inpf.get(); // пропускаем разделитель
	inpf >> date.year;
	return inpf;
}

Date& Date::operator=(const Date& other)
{
	if (this != &other) // объект не должен присваиваться себе
	{
		day = other.day;
		month = other.month;
		year = other.year;
	}
	return *this;
}

bool Date::operator<(const Date& other)
{
	if (other.get_days() > this->get_days()) // если количество прошедших дней, считая от 01.01.0000 второй даты больше, чем первой
		return true;
	return false;
}

bool Date::operator>=(const Date& other)
{
	return !(*this < other);
}

bool Date::operator>(const Date& other)
{
	return !(*this < other) && !(*this == other);
}

bool Date::operator==(const Date& other)
{
	return other.get_days() == this->get_days();
}

bool Date::operator<=(const Date& other)
{
	return !(*this > other);
}

short int Date::get_days_feb(long long int year) const
{
	if ((!(year % 4) && (year % 100)) || !(year % 400)) // если год високосный
	{
		return 29;
	}
	return 28;
}

short int Date::get_days_month(short int month, long long int year) const
{
	switch (month)
	{
	case 2:
		return get_days_feb(year);
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		return 31;
	default:
		return 30;
	}
}

short int Date::get_days_year(long long int year) const
{
	const short int without_feb = 337; // число дней в году не считая февраль, который меняется в зависимости от вискосности года
	return without_feb + get_days_feb(year);
}

short int Date::days_passed_to_cur_month(short int month, long long int year) const
{
	short int days = 0;
	for (short int i = 1; i < month; ++i) // начиная с 1 месяца и пока не дойдем до последнего
	{
		days += get_days_month(i, year);
	}
	return days;
}

long long int Date::get_days() const
{
	long long int days = 0;
	for (long long int i = 0; i < year; ++i)
	{
		days += get_days_year(i);
	}
	return days + days_passed_to_cur_month(month, year) + day; // важно прибавить дни в дате т.к функция days_passed_to_cur_month считает только дни в уже закончившихся месяцах
}

void Date::days_to_date(long long int days)
{
	month = 1;
	year = 0;
	while (days > get_days_year(year)) // нахождения года
	{
		days -= get_days_year(year);
		++year;
	}
	while (days > days_passed_to_cur_month(month + 1, year)) // нахождение месяца
	{
		++month;
	}
	day = days - days_passed_to_cur_month(month, year); // нахождения дня
}

Date Date::operator+(const long long int days) // операция + возвращает новый объект
{
	Date new_date = *this;
	new_date.days_to_date(new_date.get_days() + days);
	return new_date;
}

Date Date::operator-(const long long int days) // операция - возвращает новый объект
{
	Date new_date = *this;
	new_date.days_to_date(new_date.get_days() - days);
	return new_date;
}

int main()
{
	std::ifstream inpf("input.txt");
	std::ofstream outf("output.txt");
	Date date;
	short int choice; // переменная для выбора режима работы программы
	inpf >> choice;
	inpf >> date; // чтение даты
	switch (choice)
	{
	case 1: // выполение операции +
	{
		long long days;
		inpf >> days;
		outf << date + days;
		break;
	}
	case 2: // выполение операции -
	{
		long long days;
		inpf >> days;
		outf << date - days;
		break;
	}
	case 3: //выполение метода перевода даты в другой формат
		date.to_another_format(outf);
		break;
	case 4: //Вычисление номера дня в году
		outf << date.get_day_number();
		break;
	case 5: // сравнение дат
		Date other_date;
		inpf >> other_date;
		if (date < other_date)
		{
			outf << "Первая дата наступила раньше второй";
			break;
		}
		if (date == other_date)
		{
			outf << "Одинаковые даты";
			break;
		}
		if (date > other_date)
		{
			outf << "Первая дата наступила позже второй";
			break;
		}
	}
	inpf.close();
	outf.close();
	return 0;
}