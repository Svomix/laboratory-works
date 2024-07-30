#include <iostream>
#include <fstream>
#include <vector>

// ЭТА ЛАБА НЕПРАВИЛЬНАЯ!!!.В главной функции нужно обрабатывать не файл, а массив символов, который вы получили из файла!

long long skip_space(std::ifstream& in, unsigned long long& res) // функция для пропуска пробельных символов
{
	while (std::isspace(in.peek()))
	{
		in.get();
	}
	res = in.tellg();
	return res;
}

bool is_vowel(const char sym) // функция для проверки гласных букв
{
	return sym == 'а' || sym == 'е' || sym == 'ё' || sym == 'и' || sym == 'ы' || sym == 'о' || sym == 'э' || sym == 'у' || sym == 'я' || sym == 'ю' || sym == 'А' || sym == 'Е' || sym == 'Ё' || sym == 'И' || sym == 'Ы' || sym == 'О' || sym == 'Э' || sym == 'У' || sym == 'Я' || sym == 'Ю';
}

std::vector<char*> text_analys(std::ifstream& inpfile) // главная функция
{
	std::vector<char*> res;
	unsigned long long curr = 0; // текущее положение курсора в файле
	char sym; // извлекаемый символ
	bool vowels; //флаг валидности
	size_t size; // размер слова
	curr = skip_space(inpfile, curr); // положение курсора после пропуска всех пробельных символов
	while (!inpfile.eof())
	{
		size = 0;
		vowels = true;
		while (!std::isspace(inpfile.peek()) && !inpfile.eof()) // собираем непробельные символы для определние размера выделяемой памяти
		{
			inpfile.get(sym); // извлекаем символ
			if (!is_vowel(sym)) // если символ не является гласной буквой русского алфавита, то флаг корректности становится false
				vowels = false;
			++size; // увеличение размера выделяемой памяти
		}
		if (vowels) // если все буквы в слове являются гласными буквами русского алфавита
		{
			inpfile.seekg(curr); // перевод курсора на место, откуда было начато считывание слова
			char* txt = new char[size + 1]; // выделение динамической памяти с учетом нуль-терминатора
			for (size_t i = 0; i < size; ++i) // заполнение массива символов
			{
				txt[i] = inpfile.get();
			}
			txt[size] = '\0'; // обозначение конца символьного массива
			res.push_back(txt); // запись подходящего слова в vector
		}
		curr = skip_space(inpfile, curr); // пропуск всех пробельных символов после нахождение слова
	}
	return res;
}

int main()
{
	setlocale(LC_ALL, "rus");
	std::ifstream inpfile("input.txt");
	std::ofstream outfile("output.txt", std::ios::app); // открытие выходного файла с режимом добавления
	std::vector<char*> res = text_analys(inpfile);
	for (const char* c : res)
	{
		std::cout << c << ' '; // вывод результата в консоль
		outfile << c << ' '; // вывод результата в файл
		delete[] c; // удаление выделенной динамической памяти
	}
	inpfile.close(); // закрытие входного файла
	outfile.close(); // закрытие выходного файла
	return 0;
}