#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <iostream>
#include <vector>
#include <cstring>

enum States { S, E, C, F, B }; // перечисление состояний
enum Sym { rus_vowel, other, border }; // перечисление типов символов

long long int get_size(std::ifstream& input) // функция для нахождения количества символов в файле
{
	long long int size;
	input.seekg(0, std::ios::end);
	size = input.tellg();
	input.seekg(0, std::ios::beg);
	return size;
}

void filling_table(States(*table)[5]) // формирование матрицы состояний
{
	table[rus_vowel][S] = C;
	table[other][S] = E;
	table[border][S] = B;

	table[rus_vowel][E] = E;
	table[other][E] = E;
	table[border][E] = B;

	table[rus_vowel][C] = C;
	table[other][C] = E;
	table[border][C] = F;

	table[rus_vowel][F] = F;
	table[other][F] = F;
	table[border][F] = F;

	table[rus_vowel][B] = B;
	table[other][B] = B;
	table[border][B] = B;
}

bool is_rus_vowel(const char sym) // функция для проверки гласных букв
{
	return sym == 'а' || sym == 'е' || sym == 'ё' || sym == 'и' || sym == 'ы' || sym == 'о' || sym == 'э' || sym == 'у' || sym == 'я' || sym == 'ю' || sym == 'А' || sym == 'Е' || sym == 'Ё' || sym == 'И' || sym == 'Ы' || sym == 'О' || sym == 'Э' || sym == 'У' || sym == 'Я' || sym == 'Ю';
}

Sym get_sym(const char sym) // функция для определения типа символа
{
	if (is_rus_vowel(sym))
		return rus_vowel;
	if (isspace(sym) || sym == '\0')
		return border;
	return other;
}

char* create_word(const char* txt, char* word, const long long int start, const long long int end) // создание слова
{
	int len = end - start; // вычисление длины слова
	strncpy(&word[0], &txt[0] + start, len); // копирование получившегося слова из основноего массива txt в массив word
	word[len] = '\0'; // обозначение конца символьного массива 
	return word;
}

std::vector<char*>& lex_analysis(std::vector<char*>& r, const char* txt, States(*table)[5], const long long int txt_size)
{
	long long int cur_i = 0, start = 0;
	States cur_st = States::S; // начальное состояние
	char* word;
	while (cur_i != txt_size + 1) // проход по всему массиву txt
	{
		char cur_sym = txt[cur_i]; // текущий символ
		cur_st = table[get_sym(cur_sym)][cur_st]; // текущее состояние
		if (cur_st == States::F) // если конечное состояние F, нужно записать слово
		{
			word = new char[cur_i - start + 1]; // выделение памяти
			word = create_word(txt, word, start, cur_i);
			r.push_back(word); // добавление слова в результирующий вектор
		}
		if (cur_st == States::B || cur_st == States::F) // если мы нашли конец слова
		{
			cur_st = States::S; // текущее состояние становится начальным
			start = cur_i + 1; // двигаем границу начала следущего возможного слова
		}
		++cur_i;
	}
	return r;
}

int main()
{
	std::ifstream fin("input.txt");
	std::ofstream fout("output.txt");
	setlocale(LC_ALL, "rus");
	long long int txt_size;
	txt_size = get_size(fin); // размер текста
	char* txt = new char[txt_size + 1];
	fin.getline(txt, txt_size + 1, '\0'); // читаем из файла в символьный массив txt
	std::vector<char*> res;
	States states_table[3][5]; // таблица состояний 
	filling_table(states_table); // заполение таблицы состояний
	lex_analysis(res, txt, states_table, txt_size);
	for (const char* word : res) // вывод результата в консоль и файл
	{
		std::cout << word << " ";
		fout << word << " ";
		delete[] word; // удаление выделенной памяти для слов
	}
	delete[] txt; // удаление выделенной памяти для хранения текста
	fin.close();
	fout.close();
}