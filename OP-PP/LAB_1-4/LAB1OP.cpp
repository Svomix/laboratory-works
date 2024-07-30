#include <iostream>
#include <stdint.h>
#include <string>
/*
* Подключение библиотек для:
* 1)Ввода, вывода и обработки входных данных
* 2)Получение минимального и максимального значения для типа данных int
* 3)Использование строк
*/

using namespace std;

int main()
{
    // Объявление и инициализация начальных значений для максимума и минимума
    double max = INT32_MIN;
    double min = INT32_MAX;
    // Объявление и инициализация начальных значений для суммы и количества членов ряда
    double sum = 0.0;
    int c = 0;
    //  Объявление переменной 'x', в которую будут записываться входные значения 
    double x;
    // Объявление и инициализация 'флага' для проверки валидности введенных значений
    bool flag = true;
    // Объявление и инициализация 'флага' для проверки необходимости перезапуска программы
    string retr = "Yes";
    cout << "The program calculates maximum, minimum and the arithmetic mean of the sequence\n";
    cout << "Enter some positive and valid numbers\n";
    {
        // Начало главного цикла 'while', в котором проверяется необходимость перезапуска программы
        while (retr == "Yes")
        {
            cin >> x; // Запрос значения 
            // проверка на валидность введенного значения 
            while (flag)
            {
                if (cin.fail() || x < 0)
                {
                    cin.clear();
                    cout << "You have entered a not valid value\n";
                    cout << "Enter a valid value\n";
                    cin.ignore(32767, '\n');
                    cin >> x;
                }
                else
                {
                    flag = false;
                }
            }
            flag = true; // Возвращение флага в начальное положения для проверки следующего значения на валидность
            // После введения нуля последовательность кончается и начинается финальная обработка введенных данных
            if (x == 0)
            {
                // Если первое же число 0, то последовательности закончился и его невозможно обработать, поэтому программа запрашивает хотя одно число, которое не 0
                if (c == 0)
                {
                    cout << "You need enter one number at least\n";
                }
                // Если же 0 не является первым введенным числом, то можно заканчивать ввод и вычислить требуемые значения 
                else
                {
                    // Вывод результата на экран
                    cout << "The maximum is " << max << ", " << "The minimum is " << min << ", " << "The arithmetic mean is " << sum / c;
                    // Возвращения всех переменных в начальное положение
                    c = 0;
                    sum = 0.0;
                    max = INT32_MIN;
                    min = INT32_MAX;
                    // Запрос на перезапуск программы
                    cout << "\nDo you want to restart the program?";
                    // Проверка правильности введеного значения для перезапуска программы
                    while (flag)
                    {
                        cout << "\nPrint 'Yes' or 'No'\n";
                        cin >> retr;
                        if (retr == "Yes" || retr == "No")
                        {
                            flag = false;
                        }
                        else
                        {
                            cout << "You have not entered 'Yes' or 'No' ";
                            
                        }
                    }
                    flag = true;
                }
            }
            // Если введенное число не 0, то идет проверка является ли это число максимальным или минимальным
            else
            {
                if (x > max)
                {
                    max = x;
                }
                if (x < min)
                {
                    min = x;
                }
                // Увеличение счетчика количества чисел и текущей суммы
                c++;
                sum += x;
            }
        }
    }
    cout << "The programm is over";
}