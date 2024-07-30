#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <iostream>
#include <vector>
#include <cstring>

enum States_lex { S, V, Y, P, I, L, U, X, H, C, E, COF, EQF, AF, MINF, CF, ZF, IF, B }; // перечисление состояний лексического анализатора

enum Sym_type { id, vl, less, larg, eq, sc, min, ao, other, border, co, wl, do_kw, unt_kw, not_kw, and_kw, or_kw, loop_kw }; // перечисление типов символов

enum States_synt { K1, K2, K3, K4, Start, DO, UNTIL, UN, Comp_exp1, Comp_exp2, Comp_exp3, Arithm1, Arithm2, Oper1, Oper2, F, Err_st, Err_do, Err_unt, Err_un, Err_comp_exp1, Err_comp_exp2, Err_comp_exp3, Err_Arithm1, Err_Arithm2, Err_Oper1, Err_Oper2, P_Start, Err_K }; // перечисление состояний синтаксического анализатора

const char* types[] = { "[id]", "[vl]","[vl]", "[eq]", "[eq]","[sc]", "[ao]","[ao]", "[ao]", "[ao]","[co]","[wl]", "[do]", "[un]" , "[no]" , "[lo]" , "[lo]", "[lp]" };

struct Lex
{
    char* text;
    Sym_type type;
};

void create_table(States_lex table[10][19]) // формирование матрицы состояний
{
    table[id][S] = I;
    table[vl][S] = C;
    table[less][S] = V;
    table[larg][S] = L;
    table[eq][S] = U;
    table[sc][S] = X;
    table[ao][S] = H;
    table[min][S] = Y;
    table[other][S] = E;
    table[border][S] = S;

    table[id][V] = COF;
    table[vl][V] = COF;
    table[less][V] = COF;
    table[larg][V] = P;
    table[eq][V] = COF;
    table[sc][V] = COF;
    table[ao][V] = COF;
    table[min][V] = COF;
    table[other][V] = COF;
    table[border][V] = COF;

    table[id][P] = COF;
    table[vl][P] = COF;
    table[less][P] = COF;
    table[larg][P] = COF;
    table[eq][P] = COF;
    table[sc][P] = COF;
    table[ao][P] = COF;
    table[min][P] = COF;
    table[other][P] = COF;
    table[border][P] = COF;

    table[id][L] = COF;
    table[vl][L] = COF;
    table[less][L] = COF;
    table[larg][L] = COF;
    table[eq][L] = COF;
    table[sc][L] = COF;
    table[ao][L] = COF;
    table[min][L] = COF;
    table[other][L] = COF;
    table[border][L] = COF;

    table[id][H] = AF;
    table[vl][H] = AF;
    table[less][H] = AF;
    table[larg][H] = AF;
    table[eq][H] = AF;
    table[sc][H] = AF;
    table[ao][H] = AF;
    table[min][H] = AF;
    table[other][H] = AF;
    table[border][H] = AF;

    table[id][X] = ZF;
    table[vl][X] = ZF;
    table[less][X] = ZF;
    table[larg][X] = ZF;
    table[eq][X] = ZF;
    table[sc][X] = ZF;
    table[ao][X] = ZF;
    table[min][X] = ZF;
    table[other][X] = ZF;
    table[border][X] = ZF;

    table[id][U] = EQF;
    table[vl][U] = EQF;
    table[less][U] = EQF;
    table[larg][U] = EQF;
    table[eq][U] = EQF;
    table[sc][U] = EQF;
    table[ao][U] = EQF;
    table[min][U] = EQF;
    table[other][U] = EQF;
    table[border][U] = EQF;

    table[id][I] = I;
    table[vl][I] = I;
    table[less][I] = IF;
    table[larg][I] = IF;
    table[eq][I] = IF;
    table[sc][I] = IF;
    table[ao][I] = IF;
    table[min][I] = IF;
    table[other][I] = E;
    table[border][I] = IF;

    table[id][C] = E;
    table[vl][C] = C;
    table[less][C] = CF;
    table[larg][C] = CF;
    table[eq][C] = CF;
    table[sc][C] = CF;
    table[ao][C] = CF;
    table[min][C] = CF;
    table[other][C] = E;
    table[border][C] = CF;

    table[id][E] = E;
    table[vl][E] = E;
    table[less][E] = B;
    table[larg][E] = B;
    table[eq][E] = B;
    table[sc][E] = B;
    table[ao][E] = B;
    table[min][E] = B;
    table[other][E] = E;
    table[border][E] = B;

    table[id][COF] = COF;
    table[vl][COF] = COF;
    table[less][COF] = COF;
    table[larg][COF] = COF;
    table[eq][COF] = COF;
    table[sc][COF] = COF;
    table[ao][COF] = COF;
    table[min][COF] = COF;
    table[other][COF] = COF;
    table[border][COF] = COF;

    table[id][EQF] = EQF;
    table[vl][EQF] = EQF;
    table[less][EQF] = EQF;
    table[larg][EQF] = EQF;
    table[eq][EQF] = EQF;
    table[sc][EQF] = EQF;
    table[ao][EQF] = EQF;
    table[min][EQF] = EQF;
    table[other][EQF] = EQF;
    table[border][EQF] = EQF;

    table[id][AF] = AF;
    table[vl][AF] = AF;
    table[less][AF] = AF;
    table[larg][AF] = AF;
    table[eq][AF] = AF;
    table[sc][AF] = AF;
    table[ao][AF] = AF;
    table[min][AF] = AF;
    table[other][AF] = AF;
    table[border][AF] = AF;

    table[id][CF] = CF;
    table[vl][CF] = CF;
    table[less][CF] = CF;
    table[larg][CF] = CF;
    table[eq][CF] = CF;
    table[sc][CF] = CF;
    table[ao][CF] = CF;
    table[min][CF] = CF;
    table[other][CF] = CF;
    table[border][CF] = CF;

    table[id][ZF] = ZF;
    table[vl][ZF] = ZF;
    table[less][ZF] = ZF;
    table[larg][ZF] = ZF;
    table[eq][ZF] = ZF;
    table[sc][ZF] = ZF;
    table[ao][ZF] = ZF;
    table[min][ZF] = ZF;
    table[other][ZF] = ZF;
    table[border][ZF] = ZF;

    table[id][IF] = IF;
    table[vl][IF] = IF;
    table[less][IF] = IF;
    table[larg][IF] = IF;
    table[eq][IF] = IF;
    table[sc][IF] = IF;
    table[ao][IF] = IF;
    table[min][IF] = IF;
    table[other][IF] = IF;
    table[border][IF] = IF;

    table[id][Y] = MINF;
    table[vl][Y] = MINF;
    table[less][Y] = MINF;
    table[larg][Y] = MINF;
    table[eq][Y] = MINF;
    table[sc][Y] = MINF;
    table[ao][Y] = MINF;
    table[min][Y] = MINF;
    table[other][Y] = MINF;
    table[border][Y] = MINF;

    table[id][MINF] = MINF;
    table[vl][MINF] = MINF;
    table[less][MINF] = MINF;
    table[larg][MINF] = MINF;
    table[eq][MINF] = MINF;
    table[sc][MINF] = MINF;
    table[ao][MINF] = MINF;
    table[min][MINF] = MINF;
    table[other][MINF] = MINF;
    table[border][MINF] = MINF;

    table[id][B] = B;
    table[vl][B] = B;
    table[less][B] = B;
    table[larg][B] = B;
    table[eq][B] = B;
    table[sc][B] = B;
    table[ao][B] = B;
    table[min][B] = B;
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

Sym_type is_keyword(const char* text) // функция для определения ключевых слов
{
    if (!strcmp(text, "loop"))
        return loop_kw;
    if (!strcmp(text, "do"))
        return do_kw;
    if (!strcmp(text, "until"))
        return unt_kw;
    if (!strcmp(text, "not"))
        return not_kw;
    if (!strcmp(text, "and"))
        return and_kw;
    if (!strcmp(text, "or"))
        return or_kw;
    return id;
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
    if (sym == '/' || sym == '*' || sym == '+')
        return ao;
    if (sym == '-')
        return min;
    if (isspace(sym) || sym == '\0') // конец файла также является граничным символом
        return border;
    return other;
}

Sym_type state_to_type(const char* word, States_lex cur_st) // функция которая однозначно определяет тип символа по выходному состоянию
{
    if (cur_st == COF)
        return co;
    if (cur_st == EQF)
        return eq;
    if (cur_st == AF)
        return ao;
    if (cur_st == MINF)
        return min;
    if (cur_st == CF && atoi(word) <= 32768) // если число допустимого значения
        return vl;
    if (cur_st == ZF)
        return sc;
    if (cur_st == IF && (strlen(word) < 6)) // максимальная длина идентификатора 5 символов
    {
        return is_keyword(word);
    }
    return wl;
}

void lex_anlysis(const char* txt, States_lex table[10][19], std::vector<Lex>& res)
{


    size_t cur_i = 0, start = 0;
    States_lex cur_st = States_lex::S; // начальное состояние
    Lex word;
    size_t text_size = strlen(txt) + 1;
    while (cur_i != text_size) // проход по всему массиву txt 
    {
        const char cur_sym = txt[cur_i]; // текущий символ
        cur_st = table[get_type(cur_sym)][cur_st]; // текущее состояние
        if (cur_st > 10) // если автомат перешел в одно из конечных состояний, нужно выделить лексему
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

void create_table(States_synt table[18][29]) // формирование матрицы состояний
{
    table[do_kw][Start] = DO;
    table[unt_kw][Start] = Err_st;
    table[vl][Start] = Err_st;
    table[id][Start] = Err_st;
    table[co][Start] = Err_st;
    table[and_kw][Start] = Err_st;
    table[or_kw][Start] = Err_st;
    table[not_kw][Start] = Err_st;
    table[ao][Start] = Err_st;
    table[eq][Start] = Err_st;
    table[sc][Start] = Err_st;
    table[wl][Start] = Err_st;
    table[loop_kw][Start] = Err_st;
    table[min][Start] = Err_st;

    table[do_kw][P_Start] = DO;
    table[unt_kw][P_Start] = Err_st;
    table[vl][P_Start] = Err_st;
    table[id][P_Start] = Err_st;
    table[co][P_Start] = Err_st;
    table[and_kw][P_Start] = Err_st;
    table[or_kw][P_Start] = Err_st;
    table[not_kw][P_Start] = Err_st;
    table[ao][P_Start] = Err_st;
    table[eq][P_Start] = Err_st;
    table[sc][P_Start] = Err_st;
    table[wl][P_Start] = Err_st;
    table[loop_kw][P_Start] = Err_st;
    table[min][P_Start] = Err_st;

    table[do_kw][DO] = Err_do;
    table[unt_kw][DO] = UNTIL;
    table[vl][DO] = Err_do;
    table[id][DO] = Err_do;
    table[co][DO] = Err_do;
    table[and_kw][DO] = Err_do;
    table[or_kw][DO] = Err_do;
    table[not_kw][DO] = Err_do;
    table[ao][DO] = Err_do;
    table[eq][DO] = Err_do;
    table[sc][DO] = Err_do;
    table[wl][DO] = Err_do;
    table[loop_kw][DO] = Err_do;
    table[min][DO] = Err_do;

    table[do_kw][UNTIL] = Err_unt;
    table[unt_kw][UNTIL] = Err_unt;
    table[vl][UNTIL] = Comp_exp1;
    table[id][UNTIL] = Comp_exp1;
    table[co][UNTIL] = Err_unt;
    table[and_kw][UNTIL] = Err_unt;
    table[or_kw][UNTIL] = Err_unt;
    table[not_kw][UNTIL] = UN;
    table[ao][UNTIL] = Err_unt;
    table[eq][UNTIL] = Err_unt;
    table[sc][UNTIL] = Err_unt;
    table[wl][UNTIL] = Err_unt;
    table[loop_kw][UNTIL] = Err_unt;
    table[min][UNTIL] = K1;

    table[do_kw][UN] = Err_un;
    table[unt_kw][UN] = Err_un;
    table[vl][UN] = Comp_exp1;
    table[id][UN] = Comp_exp1;
    table[co][UN] = Err_un;
    table[and_kw][UN] = Err_un;
    table[or_kw][UN] = Err_un;
    table[not_kw][UN] = Err_un;
    table[ao][UN] = Err_un;
    table[eq][UN] = Err_un;
    table[sc][UN] = Err_un;
    table[wl][UN] = Err_un;
    table[loop_kw][UN] = Err_un;
    table[min][UN] = K1;

    table[do_kw][Comp_exp1] = Err_comp_exp1;
    table[unt_kw][Comp_exp1] = Err_comp_exp1;
    table[vl][Comp_exp1] = Err_comp_exp1;
    table[id][Comp_exp1] = Oper1;
    table[co][Comp_exp1] = Comp_exp2;
    table[and_kw][Comp_exp1] = UN;
    table[or_kw][Comp_exp1] = UN;
    table[not_kw][Comp_exp1] = Err_comp_exp1;
    table[ao][Comp_exp1] = Err_comp_exp1;
    table[eq][Comp_exp1] = Comp_exp2;
    table[sc][Comp_exp1] = Err_comp_exp1;
    table[wl][Comp_exp1] = Err_comp_exp1;
    table[loop_kw][Comp_exp1] = Err_comp_exp1;
    table[min][Comp_exp1] = Err_comp_exp2;

    table[do_kw][Comp_exp2] = Err_comp_exp2;
    table[unt_kw][Comp_exp2] = Err_comp_exp2;
    table[vl][Comp_exp2] = Comp_exp3;
    table[id][Comp_exp2] = Comp_exp3;
    table[co][Comp_exp2] = Err_comp_exp2;
    table[and_kw][Comp_exp2] = Err_comp_exp2;
    table[or_kw][Comp_exp2] = Err_comp_exp2;
    table[not_kw][Comp_exp2] = Err_comp_exp2;
    table[ao][Comp_exp2] = Err_comp_exp2;
    table[eq][Comp_exp2] = Err_comp_exp2;
    table[sc][Comp_exp2] = Err_comp_exp2;
    table[wl][Comp_exp2] = Err_comp_exp2;
    table[loop_kw][Comp_exp2] = Err_comp_exp2;
    table[min][Comp_exp2] = K2;

    table[do_kw][Comp_exp3] = Err_comp_exp3;
    table[unt_kw][Comp_exp3] = Err_comp_exp3;
    table[vl][Comp_exp3] = Err_comp_exp3;
    table[id][Comp_exp3] = Oper1;
    table[co][Comp_exp3] = Err_comp_exp3;
    table[and_kw][Comp_exp3] = UN;
    table[or_kw][Comp_exp3] = UN;
    table[not_kw][Comp_exp3] = Err_comp_exp3;
    table[ao][Comp_exp3] = Err_comp_exp3;
    table[eq][Comp_exp3] = Err_comp_exp3;
    table[sc][Comp_exp3] = Err_comp_exp3;
    table[wl][Comp_exp3] = Err_comp_exp3;
    table[loop_kw][Comp_exp3] = Err_comp_exp3;
    table[min][Comp_exp3] = Err_comp_exp3;

    table[do_kw][Oper1] = Err_Oper1;
    table[unt_kw][Oper1] = Err_Oper1;
    table[vl][Oper1] = Err_Oper1;
    table[id][Oper1] = Err_Oper1;
    table[co][Oper1] = Err_Oper1;
    table[and_kw][Oper1] = Err_Oper1;
    table[or_kw][Oper1] = Err_Oper1;
    table[not_kw][Oper1] = Err_Oper1;
    table[ao][Oper1] = Err_Oper1;
    table[eq][Oper1] = Arithm1;
    table[sc][Oper1] = Err_Oper1;
    table[wl][Oper1] = Err_Oper1;
    table[loop_kw][Oper1] = Err_Oper1;
    table[min][Oper1] = Err_Oper1;

    table[do_kw][Arithm1] = Err_Arithm1;
    table[unt_kw][Arithm1] = Err_Arithm1;
    table[vl][Arithm1] = Arithm2;
    table[id][Arithm1] = Arithm2;
    table[co][Arithm1] = Err_Arithm1;
    table[and_kw][Arithm1] = Err_Arithm1;
    table[or_kw][Arithm1] = Err_Arithm1;
    table[not_kw][Arithm1] = Err_Arithm1;
    table[ao][Arithm1] = Err_Arithm1;
    table[eq][Arithm1] = Err_Arithm1;
    table[sc][Arithm1] = Err_Arithm1;
    table[wl][Arithm1] = Err_Arithm1;
    table[loop_kw][Arithm1] = Err_Arithm1;
    table[min][Arithm1] = K3;

    table[do_kw][Arithm2] = Err_Arithm2;
    table[unt_kw][Arithm2] = Err_Arithm2;
    table[vl][Arithm2] = Err_Arithm2;
    table[id][Arithm2] = Err_Arithm2;
    table[co][Arithm2] = Err_Arithm2;
    table[and_kw][Arithm2] = Err_Arithm2;
    table[or_kw][Arithm2] = Err_Arithm2;
    table[not_kw][Arithm2] = Err_Arithm2;
    table[ao][Arithm2] = Arithm1;
    table[eq][Arithm2] = Err_Arithm2;
    table[sc][Arithm2] = Oper2;
    table[wl][Arithm2] = Err_Arithm2;
    table[loop_kw][Arithm2] = F;
    table[min][Arithm2] = K4;

    table[do_kw][Oper2] = Err_Oper2;
    table[unt_kw][Oper2] = Err_Oper2;
    table[vl][Oper2] = Err_Oper2;
    table[id][Oper2] = Oper1;
    table[co][Oper2] = Err_Oper2;
    table[and_kw][Oper2] = Err_Oper2;
    table[or_kw][Oper2] = Err_Oper2;
    table[not_kw][Oper2] = Err_Oper2;
    table[ao][Oper2] = Err_Oper2;
    table[eq][Oper2] = Err_Oper2;
    table[sc][Oper2] = Err_Oper2;
    table[wl][Oper2] = Err_Oper2;
    table[loop_kw][Oper2] = Err_Oper2;
    table[min][Oper2] = Err_Oper2;

    table[do_kw][K1] = Err_K;
    table[unt_kw][K1] = Err_K;
    table[vl][K1] = Comp_exp1;
    table[id][K1] = Err_K;
    table[co][K1] = Err_K;
    table[and_kw][K1] = Err_K;
    table[or_kw][K1] = Err_K;
    table[not_kw][K1] = Err_K;
    table[ao][K1] = Err_K;
    table[eq][K1] = Err_K;
    table[sc][K1] = Err_K;
    table[wl][K1] = Err_K;
    table[loop_kw][K1] = Err_K;
    table[min][K1] = Err_K;;

    table[do_kw][K2] = Err_K;
    table[unt_kw][K2] = Err_K;
    table[vl][K2] = Comp_exp3;
    table[id][K2] = Err_K;
    table[co][K2] = Err_K;
    table[and_kw][K2] = Err_K;
    table[or_kw][K2] = Err_K;
    table[not_kw][K2] = Err_K;
    table[ao][K2] = Err_K;
    table[eq][K2] = Err_K;
    table[sc][K2] = Err_K;
    table[wl][K2] = Err_K;
    table[loop_kw][K2] = Err_K;
    table[min][K2] = Err_K;

    table[do_kw][K3] = Err_K;
    table[unt_kw][K3] = Err_K;
    table[vl][K3] = Arithm2;
    table[id][K3] = Err_K;
    table[co][K3] = Err_K;
    table[and_kw][K3] = Err_K;
    table[or_kw][K3] = Err_K;
    table[not_kw][K3] = Err_K;
    table[ao][K3] = Err_K;
    table[eq][K3] = Err_K;
    table[sc][K3] = Err_K;
    table[wl][K3] = Err_K;
    table[loop_kw][K3] = Err_K;
    table[min][K3] = Err_K;

    table[do_kw][K4] = Err_K;
    table[unt_kw][K4] = Err_K;
    table[vl][K4] = Arithm2;
    table[id][K4] = Arithm2;
    table[co][K4] = Err_K;
    table[and_kw][K4] = Err_K;
    table[or_kw][K4] = Err_K;
    table[not_kw][K4] = Err_K;
    table[ao][K4] = Err_K;
    table[eq][K4] = Err_K;
    table[sc][K4] = Err_K;
    table[wl][K4] = Err_K;
    table[loop_kw][K4] = Err_K;
    table[min][K4] = K3;

    table[do_kw][F] = F;
    table[unt_kw][F] = F;
    table[vl][F] = F;
    table[id][F] = F;
    table[co][F] = F;
    table[and_kw][F] = F;
    table[or_kw][F] = F;
    table[not_kw][F] = F;
    table[ao][F] = F;
    table[eq][F] = F;
    table[sc][F] = F;
    table[wl][F] = F;
    table[loop_kw][F] = F;
    table[min][Oper2] = F;
}

const char* error[] = { "vl","vl","vl","vl","do","un","id no vl", "id vl","co eq id lo", "id vl", "id lo", "id vl", "ao lp sc", "eq", "id","do", "do","un","id no vl", "id vl","co eq id lo", "id vl", "id lo", "id vl", "ao lp sc", "eq", "id","do","vl" };

void print_err(std::ofstream& ofs, States_synt cur_st, size_t index) // вывод ошибки 
{
    std::cout << index << ' ' << error[cur_st]; // по состонию ошибки можно однозначно установить возоможные пути ее устранения
    ofs << index << ' ' << error[cur_st];
}

void print_ok(std::ofstream& ofs) // вывод 'OK'
{
    std::cout << "OK";
    ofs << "OK";
}

void synt_anlysis(States_synt table[18][29], std::vector<Lex>& res, std::ofstream& ofs)
{
    States_synt cur_st = P_Start; // начальное состония P_Start нужно, чтобы знать, что мы ни разу не зашли в цикл for
    size_t i;
    for (i = 0; i < res.size(); ++i)
    {
        cur_st = table[res[i].type][cur_st]; // переход по матрице состояний
        if (cur_st > 15) // если текущее состояние одно из ошибочных
        {
            print_err(ofs, cur_st, i); // вывести ошибку
            return;
        }
        else if (cur_st == F) // если конструкция завершена переходим к чтению следующей
            cur_st = Start;
    }
    if (cur_st == Start) // если текущее состоние - начало, это озночает, что все конструкции правильные
    {
        print_ok(ofs); // вывод ОК 
        return;
    }
    print_err(ofs, cur_st, i); // Если текущее состояние не S, а автомат закончил работу, значит работа приостановилась не в коцне конструкции и конструкция неверна
}

void print_res(std::ofstream& outf, std::vector<Lex>& res) // функция для вывода результата обработки лексического анализатора в консоль и в файл
{
    for (const Lex& word : res)
    {
        std::cout << word.text << types[word.type] << ' ';
        outf << word.text << types[word.type] << ' ';
    }
    std::cout << std::endl;
    outf << std::endl;
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
    States_lex states_table_lex[10][19];// таблица состояний для лексического анализатора
    States_synt states_table_synt[18][29];// таблица состояний для синтаксического анализатора
    create_table(states_table_lex);// заполение таблицы состояний для лексического анализатора
    create_table(states_table_synt);// заполение таблицы состояний для синтаксического анализатора
    std::vector<Lex> res;
    lex_anlysis(txt, states_table_lex, res);
    print_res(outf, res);// вывод результата в консоль и файл
    synt_anlysis(states_table_synt, res, outf);
    delete_res(res);// удаление выделенной памяти для слов
    delete[] txt;// удаление выделенной памяти для хранения текста
    inpf.close();
    outf.close();
}