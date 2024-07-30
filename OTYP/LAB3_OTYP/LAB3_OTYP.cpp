#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <iostream>
#include <vector>
#include <cstring>

enum States { S, V, P, I, L, U, X, H, C, COF, EQF, AF, CF, ZF, IF, E, B }; // перечисление состояний

enum Sym_type { id, vl, less, larg, eq, sc, ao, other, border, co, kw, wl }; // перечисление типов символов

const char* types[] = { "[id]", "[vl]", "[vl]","[vl]", "[eq]", "[sc]", "[ao]", "[ao]", "[ao]","[co]", "[kw]", "[wl]" };

struct Lex
{
    char* text;
    Sym_type type;
};

void create_table(States(*table)[17]) // формирование матрицы состояний
{
    table[id][S] = I;
    table[vl][S] = C;
    table[less][S] = V;
    table[larg][S] = L;
    table[eq][S] = U;
    table[sc][S] = X;
    table[ao][S] = H;
    table[other][S] = E;
    table[border][S] = S;

    table[id][V] = COF;
    table[vl][V] = COF;
    table[less][V] = COF;
    table[larg][V] = P;
    table[eq][V] = COF;
    table[sc][V] = COF;
    table[ao][V] = COF;
    table[other][V] = COF;
    table[border][V] = COF;

    table[id][P] = COF;
    table[vl][P] = COF;
    table[less][P] = COF;
    table[larg][P] = COF;
    table[eq][P] = COF;
    table[sc][P] = COF;
    table[ao][P] = COF;
    table[other][P] = COF;
    table[border][P] = COF;

    table[id][L] = COF;
    table[vl][L] = COF;
    table[less][L] = COF;
    table[larg][L] = COF;
    table[eq][L] = COF;
    table[sc][L] = COF;
    table[ao][L] = COF;
    table[other][L] = COF;
    table[border][L] = COF;

    table[id][H] = AF;
    table[vl][H] = AF;
    table[less][H] = AF;
    table[larg][H] = AF;
    table[eq][H] = AF;
    table[sc][H] = AF;
    table[ao][H] = AF;
    table[other][H] = AF;
    table[border][H] = AF;

    table[id][X] = ZF;
    table[vl][X] = ZF;
    table[less][X] = ZF;
    table[larg][X] = ZF;
    table[eq][X] = ZF;
    table[sc][X] = ZF;
    table[ao][X] = ZF;
    table[other][X] = ZF;
    table[border][X] = ZF;

    table[id][U] = EQF;
    table[vl][U] = EQF;
    table[less][U] = EQF;
    table[larg][U] = EQF;
    table[eq][U] = EQF;
    table[sc][U] = EQF;
    table[ao][U] = EQF;
    table[other][U] = EQF;
    table[border][U] = EQF;

    table[id][I] = I;
    table[vl][I] = I;
    table[less][I] = IF;
    table[larg][I] = IF;
    table[eq][I] = IF;
    table[sc][I] = IF;
    table[ao][I] = IF;
    table[other][I] = E;
    table[border][I] = IF;

    table[id][C] = E;
    table[vl][C] = C;
    table[less][C] = CF;
    table[larg][C] = CF;
    table[eq][C] = CF;
    table[sc][C] = CF;
    table[ao][C] = CF;
    table[other][C] = E;
    table[border][C] = CF;

    table[id][E] = E;
    table[vl][E] = E;
    table[less][E] = B;
    table[larg][E] = B;
    table[eq][E] = B;
    table[sc][E] = B;
    table[ao][E] = B;
    table[other][E] = E;
    table[border][E] = B;

    table[id][COF] = COF;
    table[vl][COF] = COF;
    table[less][COF] = COF;
    table[larg][COF] = COF;
    table[eq][COF] = COF;
    table[sc][COF] = COF;
    table[ao][COF] = COF;
    table[other][COF] = COF;
    table[border][COF] = COF;

    table[id][EQF] = EQF;
    table[vl][EQF] = EQF;
    table[less][EQF] = EQF;
    table[larg][EQF] = EQF;
    table[eq][EQF] = EQF;
    table[sc][EQF] = EQF;
    table[ao][EQF] = EQF;
    table[other][EQF] = EQF;
    table[border][EQF] = EQF;

    table[id][AF] = AF;
    table[vl][AF] = AF;
    table[less][AF] = AF;
    table[larg][AF] = AF;
    table[eq][AF] = AF;
    table[sc][AF] = AF;
    table[ao][AF] = AF;
    table[other][AF] = AF;
    table[border][AF] = AF;

    table[id][CF] = CF;
    table[vl][CF] = CF;
    table[less][CF] = CF;
    table[larg][CF] = CF;
    table[eq][CF] = CF;
    table[sc][CF] = CF;
    table[ao][CF] = CF;
    table[other][CF] = CF;
    table[border][CF] = CF;

    table[id][ZF] = ZF;
    table[vl][ZF] = ZF;
    table[less][ZF] = ZF;
    table[larg][ZF] = ZF;
    table[eq][ZF] = ZF;
    table[sc][ZF] = ZF;
    table[ao][ZF] = ZF;
    table[other][ZF] = ZF;
    table[border][ZF] = ZF;

    table[id][IF] = IF;
    table[vl][IF] = IF;
    table[less][IF] = IF;
    table[larg][IF] = IF;
    table[eq][IF] = IF;
    table[sc][IF] = IF;
    table[ao][IF] = IF;
    table[other][IF] = IF;
    table[border][IF] = IF;

    table[id][B] = B;
    table[vl][B] = B;
    table[less][B] = B;
    table[larg][B] = B;
    table[eq][B] = B;
    table[sc][B] = B;
    table[ao][B] = B;
    table[other][B] = B;
    table[border][B] = B;
}

size_t get_size(std::ifstream& input) // функция для нахождения количества символов в файле
{
    size_t size;
    input.seekg(0, std::ios::end);
    size = input.tellg();
    input.seekg(0, std::ios::beg);
    return size;
}

char* create_word(const char* txt, const size_t start, const size_t end) // функция для создания слова
{
    size_t len = end - start;// вычисление длины слова
    char* word = new char[len + 1];
    strncpy(word, txt + start, len); // копирование получившегося слова из основноего массива txt в массив word
    word[len] = '\0'; // обозначение конца символьного массива 
    return word;
}

bool is_keyword(const char* text) // функция для определения ключевых слов
{
    return !(strcmp(text, "loop") && strcmp(text, "do") && strcmp(text, "until") && strcmp(text, "not") && strcmp(text, "and") && strcmp(text, "or")); // strcmp() возвращает 0, если строки равны
}

Sym_type get_type(const char sym) // функция для определения типа символа
{
    if (isalpha(sym))
        return id;
    if (isdigit(sym))
        return vl;
    if (sym == '<')
        return less;
    if (sym == '>')
        return larg;
    if (sym == '=')
        return eq;
    if (sym == ';')
        return sc;
    if (sym == '/' || sym == '*' || sym == '+' || sym == '-')
        return ao;
    if (isspace(sym) || sym == '\0') // конец файла также является граничным символом
        return border;
    return other;
}

Sym_type state_to_type(const char* word, States cur_st) // функция которая однозначно определяет тип символа по выходному состоянию
{
    if (cur_st == COF)
        return co;
    if (cur_st == EQF)
        return eq;
    if (cur_st == AF)
        return ao;
    if (cur_st == CF && atoi(word) <= 32768) // если число допустимого значения
        return vl;
    if (cur_st == ZF)
        return sc;
    if (cur_st == IF && (strlen(word) < 6)) // максимальная длина идентификатора 5 символов
    {
        if (is_keyword(word)) // идентификатор может являться ключевым словом
            return kw;
        return id;
    }
    return wl;
}

void lex_anlysis(const char* txt, States(*table)[17], std::vector<Lex>& res)
{

    size_t cur_i = 0, start = 0;
    States cur_st = States::S; // начальное состояние
    Lex word;
    size_t text_size = strlen(txt) + 1;
    while (cur_i != text_size) // проход по всему массиву txt 
    {
        const char cur_sym = txt[cur_i]; // текущий символ
        cur_st = table[get_type(cur_sym)][cur_st]; // текущее состояние
        if (cur_st == COF || cur_st == EQF || cur_st == AF || cur_st == CF || cur_st == ZF || cur_st == IF || cur_st == B) // если автомат перешел в одно из конечных состояний, нужно выделить лексему
        {
            word.text = create_word(txt, start, cur_i); // запись лексемы
            word.type = state_to_type(word.text, cur_st); // по выходному состоянию автомата можно определить тип лексемы
            res.push_back(word); // добавление слова в результирующий вектор
            cur_st = table[get_type(cur_sym)][S]; // так как разделительный символ также может оказаться лексемой, необходимо перейти в состояние из S по текущему символу
            start = cur_i; // двигаем границу начала следущего возможного слова
        }
        ++cur_i;
        if (cur_st == S) // для пропуска пробелов
            start = cur_i;
    }
}

void print_res(std::ofstream& outf, std::vector<Lex>& res) // функция для вывода результата в консоль и в файл
{
    for (const Lex& word : res)
    {
        std::cout << word.text << types[word.type] << ' ';
        outf << word.text << types[word.type] << ' ';
    }
    std::cout << std::endl;
    outf << std::endl;
    for (const Lex& word : res)
    {
        if (word.type == id)
        {
            std::cout << word.text << ' ';
            outf << word.text << ' ';
        }
    }
    std::cout << std::endl;
    outf << std::endl;
    for (const Lex& word : res)
    {
        if (word.type == vl)
        {
            std::cout << word.text << ' ';
            outf << word.text << ' ';
        }
    }
}

void delete_res(std::vector<Lex>& res) // удаление выделенной памяти под слова
{
    for (Lex& el : res)
        delete[] el.text;
}

int main()
{
    std::ifstream inpf("input.txt");
    std::ofstream outf("output.txt");
    size_t txt_size = get_size(inpf);//размер текста
    char* txt = new char[txt_size + 1];
    inpf.getline(txt, txt_size + 1, '\0');//читаем из файла в символьный массив txt
    States states_table[9][17];// таблица состояний
    create_table(states_table);// заполение таблицы состояний
    std::vector<Lex> res;
    lex_anlysis(txt, states_table, res);
    print_res(outf, res);// вывод результата в консоль и файл
    delete_res(res);// удаление выделенной памяти для слов
    delete[] txt;// удаление выделенной памяти для хранения текста
    inpf.close();
    outf.close();
}